# frozen_string_literal: true

require 'spec_helper'

RSpec.describe Object, :blank do
  describe '#blank?' do
    context 'when the object is blank' do
      Spec::BlankHelper::BLANK.each do |value|
        it "returns true when called on #{value.inspect}" do
          expect(value).to be_blank
        end
      end
    end

    context 'when the object is not blank' do
      Spec::BlankHelper::NOT.each do |value|
        it "returns false when called on #{value.inspect}" do
          expect(value).not_to be_blank
        end
      end
    end
  end

  describe '#present?' do
    context 'when the object is blank' do
      Spec::BlankHelper::BLANK.each do |value|
        it "returns false when called on #{value.inspect}" do
          expect(value).not_to be_present
        end
      end
    end

    context 'when the object is not blank' do
      Spec::BlankHelper::NOT.each do |value|
        it "returns true when called on #{value.inspect}" do
          expect(value).to be_present
        end
      end
    end
  end
end
