#!/usr/bin/env ruby
# frozen_string_literal: false
require 'tk'
require 'tkextlib/iwidgets'

Tk::Iwidgets::Spindate.new.pack(:padx=>10, :pady=>10)

Tk.mainloop
