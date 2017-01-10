# frozen_string_literal: true

require 'spec_helper'

RSpec.describe FasterSupport do
  it 'has a version number' do
    expect(FasterSupport::VERSION).not_to be nil
  end

  describe '.blank_implementation' do
    it 'returns :active_support by default' do
      expect(described_class.blank_implementation).to be :active_support
    end

    it 'returns the set value if it was set' do
      described_class.blank_implementation = :mri
      expect(described_class.blank_implementation).to be :mri
      described_class.blank_implementation = :active_support
    end
  end

  describe '.blank_implementation=' do
    it 'works with :mri' do
      expect { described_class.blank_implementation = :mri }.not_to raise_error
    end

    it 'works with :active_support' do
      expect { described_class.blank_impl = :active_support }.not_to raise_error
    end

    it 'raises if something else is passed' do
      expect { described_class.blank_impl = :unknown }
        .to raise_error ArgumentError, /Please use :active_support or :mri/
    end
  end
end
