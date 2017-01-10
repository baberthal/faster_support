# frozen_string_literal: true
require 'forwardable'
require 'pathname'
require 'json'

require 'rake'
require 'rake/tasklib'

module Tooling
  class << self
    include ::Rake::DSL

    def cc_jsons
      @cc_jsons ||= []
    end

    def add_cc_json(text)
      cc_jsons << JSON.parse(text)
    end

    def cc_json(as: :hash)
      result = []
      cc_jsons.each { |json| result += json }
      return result if :hash == as

      JSON.pretty_generate(result)
    end

    def color_coded_commands
      @color_coded_commands ||= [Tooling::PRE_COMPILE_FLAGS,
                                 inner_cc_commands,
                                 Tooling::POST_COMPILE_FLAGS].uniq
    end

    def add_task(*args, ext:, **opts)
      Tooling::Task.new(ext, *args, **opts)
    end

    def tasks
      @tasks ||= []
    end

    def define(name = :tooling)
      desc 'Prerequisites for compile_commands.json'
      task "#{name}:pre_compile_commands" => pre_compile_commands

      define_ccjson(name)
      # define_color_coded

      # CLEAN.include('.color_coded')
      CLEAN.include('compile_commands.json')

      desc 'Default vim tooling task'
      task "#{name}:default" => ['compile_commands.json']

      desc 'Generate vim tooling'
      task name => [:compile, "#{name}:default"]
    end

    private

    def define_ccjson(name)
      file 'compile_commands.json' => "#{name}:pre_compile_commands" do
        puts "Generating compile_commands.json at #{Rake.original_dir}"
        Dir.chdir(Rake.original_dir) do
          File.open('compile_commands.json', 'w') do |io|
            io.write cc_json(as: :json)
          end
        end
        puts 'Done'
      end
    end

    def define_color_coded
      file '.color_coded' => 'compile_commands.json' do
        puts 'Generating .color_coded...'
        File.open('.color_coded', 'w') { |io| io.puts color_coded_commands }
        puts 'Done'
      end
    end

    def pre_compile_commands
      @pre_compile_commands ||= tasks.map(&:cc_json_task_name)
    end

    def inner_cc_commands # rubocop:disable Metrics/AbcSize,MethodLength
      @inner_cc_commands ||=
        begin
          commands = []
          raw = File.read(File.join(Rake.original_dir, 'compile_commands.json'))
          JSON.parse(raw).each do |cmd_def|
            commands << cmd_def['command'].split(' ')[2..-4].map do |string|
              string.strip
                    .sub('../../../..', Rake.original_dir.to_s)
                    .sub('/../', '/')
                    .sub(/-I\.\z/, "-I#{Rake.original_dir}/ext/.")
            end
          end
          commands.uniq
        rescue Errno::ENOENT
          puts "File not found: #{raw}"
          exit 2
        end
    end
  end

  class Task < ::Rake::TaskLib
    include ::Rake::DSL
    extend Forwardable

    attr_accessor :ext_task

    def initialize(ext_task, *args, **opts)
      @ext_task = ext_task
      @_name = args.shift || ext_task.name
      @namespace = opts.fetch(:namespace, :tooling)
      @namespaced = opts.fetch(:namespaced, !@namespace.nil?)
      yield self if block_given?

      Tooling.tasks << self

      define(args)
    end

    def name
      @_name ||= extname.dup
    end

    def_delegators :ext_task, :tmp_dir, :platform
    def_delegator :ext_task, :name, :extname

    def platform_tmp_dir
      Pathname.new(File.join(ext_task.tmp_dir, ext_task.platform, ext_task.name))
    end

    def build_dir
      platform_tmp_dir.join(RUBY_VERSION.to_s)
    end

    def cc_json_task_name
      task_name :pre_compile_commands
    end

    protected

    def namespaced?
      @namespaced
    end

    def define(args)
      desc "Required setup for compile_commands.json for #{name}"
      task cc_json_task_name, *args do
        add_cc_json
      end

      task 'tooling:pre_compile_commands' => cc_json_task_name
    end

    private

    def run_file_tasks(_args)
      add_cc_json
    end

    def cc_json
      @cc_json ||=
        begin
          file = File.join(build_dir, 'compile_commands.json')
          JSON.parse(File.read(file))
        rescue Errno::ENOENT => e
          puts nil, '=' * 70
          puts "File not found: #{File.expand_path(file)} (#{e})"
          puts '=' * 70
          exit 1
        end
    end

    def add_cc_json
      # puts "Adding compile_commands.json for #{name}"
      Tooling.cc_jsons << cc_json
    end

    def task_name(task)
      "#{name}:#{task}" unless namespaced?
      "#{@namespace}:#{name}:#{task}"
    end
  end

  XCODE_TOOLCHAIN_PATH = '/Applications/Xcode.app/Contents/Developer' \
                         '/Toolchains/XcodeDefault.xctoolchain'
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
    #{XCODE_TOOLCHAIN_PATH}/usr/lib/clang/8.0.0/include
    -fspell-checking
  ).freeze
end
