# frozen_string_literal: true

require 'mkmf'
# rubocop:disable all
$CPPFLAGS += "-I#{File.expand_path('../../../../', __FILE__)}"
create_makefile('faster_support/core_ext/object/blank')
