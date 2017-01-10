# frozen_string_literal: true
# coding: utf-8

lib = File.expand_path('../lib', __FILE__)
$:.unshift(lib) unless $:.include?(lib)
require 'faster_support/version'

Gem::Specification.new do |spec|
  spec.name          = 'faster_support'
  spec.version       = FasterSupport::VERSION
  spec.authors       = ['J. Morgan Lieberthal']
  spec.email         = ['j.morgan.lieberthal@gmail.com']

  spec.summary       = 'Faster Implementations of ActiveSupport Methods'
  spec.homepage      = 'https://github.com/baberthal/faster_support'
  spec.license       = 'MIT'

  spec.files = %x(git ls-files -z).split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/faster_support/extconf.rb',
                        'ext/faster_support/object/blank/extconf.rb']

  spec.add_development_dependency 'bundler', '~> 1.13'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rake-compiler'
  spec.add_development_dependency 'rspec', '~> 3.0'
end
