# frozen_string_literal: true

RSpec.describe String do
  describe '#ascii_8bit' do
    let(:ascii) { Encoding::ASCII_8BIT }

    context 'with a string that is already 8-bit ascii' do
      let(:string) { 'hello'.encode(ascii) }

      it 'returns self' do
        expect(string.ascii_8bit).to be string
      end
    end

    context 'with a frozen string' do
      let(:string) { 'i am frozen' }
      let(:newstr) { string.ascii_8bit }

      it 'returns self with 8-bit encoding' do
        expect(newstr.encoding).to eq ascii
      end

      it 'does not raise an error' do
        expect { newstr }.not_to raise_error
      end

      it 'is basically the same as #force_encoding(BINARY)' do
        bin = string.dup.force_encoding('BINARY')
        expect(newstr.encoding).to eq bin.encoding
      end
    end

    context 'with a non-frozen string' do
      let(:string) { String.new('hello') }
      let(:newstr) { string.ascii_8bit }

      it 'returns self with 8-bit encoding' do
        expect(newstr.encoding).to eq ascii
      end

      it 'does not raise an error' do
        expect { newstr }.not_to raise_error
      end

      it 'is basically the same as #force_encoding(BINARY)' do
        bin = string.dup.force_encoding('BINARY')
        expect(newstr.encoding).to eq bin.encoding
      end
    end
  end
end
