# frozen_string_literal: true

require 'faster_support/version'
require 'faster_support/faster_support'
require 'faster_support/core_ext'

module FasterSupport
  class << self
    def blank_implementation
      @blank_implementation ||= :active_support
    end

    def blank_implementation=(impl)
      @blank_implementation =
        case impl.to_sym
        when :mri, :ruby then :mri
        when :as, :active_support, :rails then :active_support
        else
          raise ArgumentError, "Unknown implementation: #{impl}. " \
            'Please use :active_support or :mri.'
        end
    end

    alias blank_impl blank_implementation
    alias blank_impl= blank_implementation=
  end

  @blank_implementation = :active_support
end
