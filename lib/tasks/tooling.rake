# frozen_string_literal: true

require 'json'
require_relative 'tooling'
require 'rake/clean'

namespace :tooling do
  file 'compile_commands.json' do
    Dir.chdir(Tooling.build_dir) do
      cp 'compile_commands.json', Rake.original_dir
    end
  end

  file '.color_coded' do
    commands = []
    JSON.parse(File.read('compile_commands.json')).each do |commanddef|
      commands << commanddef['command'].split(' ')[2..-4]
    end
    commands = [Tooling::PRE_COMPILE_FLAGS,
                commands.uniq,
                Tooling::POST_COMPILE_FLAGS]
    puts 'Generating .color_coded...'
    File.open('.color_coded', 'w') { |io| io.puts commands }
    puts 'Done'
  end

  CLEAN.include('.color_coded')
  CLEAN.include('compile_commands.json')

  desc 'Generate vim tooling'
  task default: ['compile_commands.json', '.color_coded']
end

desc 'Generate vim tooling (color_coded and youcompleteme)'
task tooling: [:compile, 'tooling:default']
