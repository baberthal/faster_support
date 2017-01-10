# frozen_string_literal: true

ENV['MAKE'] = 'bear make'

require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

require 'rake/extensiontask'

task build: [:compile, :tooling]

task prespec: [:clobber, :compile, :tooling]

require 'tasks/tooling'

Rake::ExtensionTask.new('faster_support') do |ext|
  ext.lib_dir = 'lib/faster_support'
  ext.source_pattern = '*.{c,cpp,m,mm}'
  Tooling.add_task(ext: ext)
end

Rake::ExtensionTask.new('faster_support/core_ext/object/blank') do |ext|
  ext.lib_dir = 'lib'
  ext.source_pattern = '*.{c,cpp,m,mm}'
  Tooling.add_task(ext: ext)
end

Rake::ExtensionTask.new('faster_support/core_ext/string') do |ext|
  ext.lib_dir = 'lib'
  ext.source_pattern = '*.{c,cpp,m,mm}'
  Tooling.add_task(ext: ext)
end

Tooling.define(:tooling)

task default: [:clobber, :compile, :tooling, :spec]
