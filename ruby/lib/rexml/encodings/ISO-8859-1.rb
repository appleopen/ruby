module REXML
	module Encoding
		# Convert from UTF-8
		def to_iso_8859_1 content
			array_utf8 = content.unpack('U*')
			array_enc = []
			array_utf8.each do |num|
				if num <= 0xFF
					array_enc << num
				else
					# Numeric entity (&#nnnn;); shard by  Stefan Scholl
					array_enc.concat "&\##{num};".unpack('C*')
				end
			end
			array_enc.pack('C*')
		end

		# Convert to UTF-8
		def from_iso_8859_1(str)
			str.unpack('C*').pack('U*')
		end
	end
end