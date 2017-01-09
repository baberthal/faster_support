# frozen_string_literal: true

ENV['MAKE'] = 'bear make'

require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

require 'rake/extensiontask'

task build: [:compile, :tooling]

task prespec: [:clobber, :compile, :tooling]

Dir['./lib/tasks/**/*.rake'].each { |f| load f } # load task directory

Rake::ExtensionTask.new('faster_support') do |ext|
  ext.lib_dir = 'lib/faster_support'
  ext.source_pattern = '*.{c,cpp,m,mm}'
  Tooling.exttask = ext
end

task default: [:clobber, :compile, :tooling, :spec]
