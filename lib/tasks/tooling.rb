# frozen_string_literal: true
require 'forwardable'
require 'pathname'
require 'json'

module Tooling
  class << self
    extend Forwardable
    attr_writer :exttask

    def exttask
      @exttask || raise('No extension task present!')
    end

    def_delegators :exttask, :tmp_dir, :platform
    def_delegator :exttask, :name, :extname

    def platform_tmp_dir
      Pathname.new(File.join(exttask.tmp_dir, exttask.platform, exttask.name))
    end

    def build_dir
      platform_tmp_dir.join(RUBY_VERSION.to_s)
    end
  end

  XCODE_TOOLCHAIN_PATH = '/Applications/Xcode.app/Contents/Developer' \
                         '/Toolchains/XcodeDefault.xctoolchain'.freeze
  PRE_COMPILE_FLAGS = %w(-x c -std=c99).freeze

  POST_COMPILE_FLAGS = %W(
    -isystem
    /usr/local/include
    -isystem
    /usr/include
    -isystem
    /Library/Developer/CommandLineTools/usr/include
    -isystem
    #{XCODE_TOOLCHAIN_PATH}/usr/include
    -isystem
    /System/Library/Frameworks
    -isystem
    /Library/Frameworks
    -isystem
    #{XCODE_TOOLCHAIN_PATH}/usr/lib/clang/7.3.0/include
    -fspell-checking
  ).freeze
end
