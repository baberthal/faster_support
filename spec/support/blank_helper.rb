# frozen_string_literal: true

module Spec
  module BlankHelper
    class EmptyTrue
      def empty?
        0
      end
    end

    class EmptyFalse
      def empty?
        nil
      end
    end

    BLANK = [EmptyTrue.new, nil, false, '', '   ', "  \n\t  \r ", '　',
             "\u00a0", [], {}].freeze

    NOT   = [EmptyFalse.new, Object.new, true, 0, 1, 'a', [nil],
             { nil => 0 }].freeze
  end
end
