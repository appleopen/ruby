module REXML
	module Parsers
		class SAX2Parser
			def initialize source
				@parser = BaseParser.new(source)
				@listeners = []
				@procs = []
				@namespace_stack = []
				@has_listeners = false
				@tag_stack = []
			end
			
			# Listen arguments:
			#
			# Symbol, Array, Block
			# 	Listen to Symbol events on Array elements
			# Symbol, Block
			#   Listen to Symbol events
			# Array, Listener
			# 	Listen to all events on Array elements
			# Array, Block
			# 	Listen to :start_element events on Array elements
			# Listener
			# 	Listen to All events
			#
			# Symbol can be one of: :start_element, :end_element,
			# :start_prefix_mapping, :end_prefix_mapping, :characters,
			# :processing_instruction, :doctype, :attlistdecl, :elementdecl,
			# :entitydecl, :notationdecl, :cdata, :xmldecl, :comment
			#
			# Array contains regular expressions or strings which will be matched
			# against fully qualified element names.
			#
			# Listener must implement the methods in SAX2Listener
			#
			# Block will be passed the same arguments as a SAX2Listener method would
			# be, where the method name is the same as the matched Symbol.
			# See the SAX2Listener for more information.
			def listen( *args, &blok )
				if args[0].kind_of? Symbol
					if args.size == 2
						args[1].each { |match| @procs << [args[0], match, blok] }
					else
						add( [args[0], /.*/, blok] )
					end
				elsif args[0].kind_of? Array
					if args.size == 2
						args[0].each { |match| add( [nil, match, args[1]] ) }
					else
						args[0].each { |match| add( [ :start_element, match, blok ] ) }
					end
				else
					add([nil, /.*/, args[0]])
				end
			end
			
			def deafen( listener=nil, &blok )
				if listener
					@listeners.delete_if {|item| item[-1] == listener }
					@has_listeners = false if @listeners.size == 0
				else
					@procs.delete_if {|item| item[-1] == blok }
				end
			end
			
			def parse
				@procs.each { |sym,match,block| block.call if sym == :start_document }
				@listeners.each { |sym,match,block| 
					block.start_document if sym == :start_document or sym.nil?
				}
				root = context = []
				while true
					event = @parser.pull
					case event[0]
					when :end_document
						handle( :end_document )
						break
					when :end_doctype
						context = context[1]
					when :start_element
						@tag_stack.push(event[1])
						# find the observers for namespaces
						procs = get_procs( :start_prefix_mapping, event[1] )
						listeners = get_listeners( :start_prefix_mapping, event[1] )
						if procs or listeners
							# break out the namespace declarations
							# The attributes live in event[2]
							nsdecl = event[2].find_all { |n, value| n =~ /^xmlns:/ }
							nsdecl.collect! { |n, value| [ n[6..-1], value ] }
							@namespace_stack.push({})
							nsdecl.each do |n,v|
								@namespace_stack[-1][n] = v
								# notify observers of namespaces
								procs.each { |ob| ob.call( n, v ) } if procs
								listeners.each { |ob| ob.start_prefix_mapping(n, v) } if listeners
							end
						end
						event[1] =~ Namespace::NAMESPLIT
						prefix = $1
						local = $2
						uri = get_namespace(prefix)
						# find the observers for start_element
						procs = get_procs( :start_element, event[1] )
						listeners = get_listeners( :start_element, event[1] )
						# notify observers
						procs.each { |ob| ob.call( uri, local, event[1], event[2] ) } if procs
						listeners.each { |ob| 
							ob.start_element( uri, local, event[1], event[2] ) 
						} if listeners
					when :end_element
						@tag_stack.pop
						event[1] =~ Namespace::NAMESPLIT
						prefix = $1
						local = $2
						uri = get_namespace(prefix)
						# find the observers for start_element
						procs = get_procs( :end_element, event[1] )
						listeners = get_listeners( :end_element, event[1] )
						# notify observers
						procs.each { |ob| ob.call( uri, local, event[1] ) } if procs
						listeners.each { |ob| 
							ob.end_element( uri, local, event[1] ) 
						} if listeners

						namespace_mapping = @namespace_stack.pop
						# find the observers for namespaces
						procs = get_procs( :end_prefix_mapping, event[1] )
						listeners = get_listeners( :end_prefix_mapping, event[1] )
						if procs or listeners
							namespace_mapping.each do |prefix, uri|
								# notify observers of namespaces
								procs.each { |ob| ob.call( prefix ) } if procs
								listeners.each { |ob| ob.end_prefix_mapping(prefix) } if listeners
							end
						end
					when :text
						normalized = @parser.normalize( event[1] )
						handle( :characters, normalized )
					when :processing_instruction, :comment, :doctype, :attlistdecl, 
						:elementdecl, :entitydecl, :cdata, :notationdecl, :xmldecl
						handle( *event )
					end
				end
			end

			private
			def handle( symbol, *arguments )
				tag = @tag_stack[-1]
				procs = get_procs( symbol, tag )
				listeners = get_listeners( symbol, tag )
				# notify observers
				procs.each { |ob| ob.call( *arguments ) } if procs
				listeners.each { |l| 
					l.send( symbol.to_s, *arguments ) 
				} if listeners
			end

			# The following methods are duplicates, but it is faster than using
			# a helper
			def get_procs( symbol, name )
				return nil if @procs.size == 0
				@procs.find_all do |sym, match, block|
					(
						(sym.nil? or symbol == sym) and 
						(name.nil? or (
							(name == match) or
							(match.kind_of? Regexp and name =~ match)
							)
						)
					)
				end.collect{|x| x[-1]}
			end
			def get_listeners( symbol, name )
				return nil if @listeners.size == 0
				@listeners.find_all do |sym, match, block|
					(
						(sym.nil? or symbol == sym) and 
						(name.nil? or (
							(name == match) or
							(match.kind_of? Regexp and name =~ match)
							)
						)
					)
				end.collect{|x| x[-1]}
			end

			def add( pair )
				if pair[-1].respond_to? :call
					@procs << pair unless @procs.include? pair
				else
					@listeners << pair unless @listeners.include? pair
					@has_listeners = true
				end
			end

			def get_namespace( prefix ) 
				uri = @namespace_stack.find do |ns|
					not ns[prefix].nil?
				end
				uri[prefix] unless uri.nil?
			end
		end
	end
end