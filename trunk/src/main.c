/* Tryout FLAC decoder for STM32F103RET setup.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <stm32f10x.h>
#include <stdio.h>
#include <stdlib.h>
#include "FLAC/stream_decoder.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

static FLAC__StreamDecoderReadStatus read_callback(const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client_data);
static FLAC__StreamDecoderSeekStatus seek_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 absolute_byte_offset, void *client_data);
static FLAC__StreamDecoderTellStatus tell_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data);
static FLAC__StreamDecoderLengthStatus length_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 *stream_length, void *client_data);
static FLAC__bool eof_callback(const FLAC__StreamDecoder *decoder, void *client_data);
static FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data);
static void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data);
static void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data);

/**
 * RCC configuration.
 */
void RCC_configure(void)
{
    //TODO
}

/**
 * GPIO configuration.
 */
void GPIO_configure(void)
{
    // TODO
}

/**
 * Send character
 *
 * @param data	Data to send
 */
static inline
void sendByte(uint8_t data)
{

}

/**
  * Retarget the C library printf function to the USART.
  */
PUTCHAR_PROTOTYPE
{
	USART3->DR = ch;	// clears TXE bit

	// wait for transmission to complete
	// TXE=1 -> data transfered to shift register
	// TC=1 -> transmission complete
	while ((USART3->SR & USART_FLAG_TXE) == RESET);

    return ch;
}

#ifdef TO_PORT
static FLAC__uint64 total_samples = 0;
static unsigned sample_rate = 0;
static unsigned channels = 0;
static unsigned bps = 0;

/**
 *
 */
static FLAC__bool write_little_endian_uint16(FILE *f, FLAC__uint16 x)
{
	return
		fputc(x, f) != EOF &&
		fputc(x >> 8, f) != EOF
	;
}

/**
 *
 */
static FLAC__bool write_little_endian_int16(FILE *f, FLAC__int16 x)
{
	return write_little_endian_uint16(f, (FLAC__uint16)x);
}

/**
 *
 */
static FLAC__bool write_little_endian_uint32(FILE *f, FLAC__uint32 x)
{
	return
		fputc(x, f) != EOF &&
		fputc(x >> 8, f) != EOF &&
		fputc(x >> 16, f) != EOF &&
		fputc(x >> 24, f) != EOF
	;
}
#endif

/**
 * Main.
 */
int main(int argc, char *argv[])
{
    FLAC__bool ok = true;
	FLAC__StreamDecoder* decoder = 0;
	FLAC__StreamDecoderInitStatus init_status;

	// init system
	SystemInit();
	RCC_configure();
	GPIO_configure();

    //TODO
    // setup UART, LEDs, SDIO, I2S, etc

    // setup decoder
	if((decoder = FLAC__stream_decoder_new()) == NULL) {
		fprintf(stderr, "ERROR: allocating decoder\n");
		return 1;
	}

    // is this needed?
	FLAC__stream_decoder_set_md5_checking(decoder, true);

    // init decoder
    void* client_data = 0;  //TODO
	init_status = FLAC__stream_decoder_init_stream(decoder, 
        read_callback,
        seek_callback,
        tell_callback,
        length_callback,
        eof_callback,
        write_callback, 
        metadata_callback,
        error_callback,
        client_data);
	if (init_status != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
		fprintf(stderr, "ERROR: initializing decoder: %s\n", FLAC__StreamDecoderInitStatusString[init_status]);
		ok = false;
	}

	if (ok) {
		ok = FLAC__stream_decoder_process_until_end_of_stream(decoder);
		fprintf(stderr, "decoding: %s\n", ok? "succeeded" : "FAILED");
		fprintf(stderr, "   state: %s\n", FLAC__StreamDecoderStateString[FLAC__stream_decoder_get_state(decoder)]);
	}

    // loop forever, just handle IRQs
	while(1);
     
    // never called but usefull to know
    //FLAC__stream_decoder_delete(decoder);
    
	return 0;
}

/**
 *
 */
FLAC__StreamDecoderReadStatus read_callback(const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client_data)
{
    //TODO
}

/**
 *
 */
FLAC__StreamDecoderSeekStatus seek_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 absolute_byte_offset, void *client_data)
{
    //TODO
}

/**
 *
 */
FLAC__StreamDecoderTellStatus tell_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data)
{
    //TODO
}

/**
 *
 */
FLAC__StreamDecoderLengthStatus length_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 *stream_length, void *client_data)
{
    //TODO
}

/**
 *
 */
FLAC__bool eof_callback(const FLAC__StreamDecoder *decoder, void *client_data)
{
    //TODO
}

/**
 *
 */
FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
{
#ifdef TO_PORT
	FILE *f = (FILE*)client_data;
	const FLAC__uint32 total_size = (FLAC__uint32)(total_samples * channels * (bps/8));
	size_t i;

	(void)decoder;

	if(total_samples == 0) {
		fprintf(stderr, "ERROR: this example only works for FLAC files that have a total_samples count in STREAMINFO\n");
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}
	if(channels != 2 || bps != 16) {
		fprintf(stderr, "ERROR: this example only supports 16bit stereo streams\n");
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}

	/* write WAVE header before we write the first frame */
	if(frame->header.number.sample_number == 0) {
		if(
			fwrite("RIFF", 1, 4, f) < 4 ||
			!write_little_endian_uint32(f, total_size + 36) ||
			fwrite("WAVEfmt ", 1, 8, f) < 8 ||
			!write_little_endian_uint32(f, 16) ||
			!write_little_endian_uint16(f, 1) ||
			!write_little_endian_uint16(f, (FLAC__uint16)channels) ||
			!write_little_endian_uint32(f, sample_rate) ||
			!write_little_endian_uint32(f, sample_rate * channels * (bps/8)) ||
			!write_little_endian_uint16(f, (FLAC__uint16)(channels * (bps/8))) || /* block align */
			!write_little_endian_uint16(f, (FLAC__uint16)bps) ||
			fwrite("data", 1, 4, f) < 4 ||
			!write_little_endian_uint32(f, total_size)
		) {
			fprintf(stderr, "ERROR: write error\n");
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
		}
	}

	/* write decoded PCM samples */
	for(i = 0; i < frame->header.blocksize; i++) {
		if(
			!write_little_endian_int16(f, (FLAC__int16)buffer[0][i]) ||  /* left channel */
			!write_little_endian_int16(f, (FLAC__int16)buffer[1][i])     /* right channel */
		) {
			fprintf(stderr, "ERROR: write error\n");
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
		}
	}
#endif
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

/**
 *
 */
void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
{
#ifdef TO_PORT
	(void)decoder, (void)client_data;

	/* print some stats */
	if(metadata->type == FLAC__METADATA_TYPE_STREAMINFO) {
		/* save for later */
		total_samples = metadata->data.stream_info.total_samples;
		sample_rate = metadata->data.stream_info.sample_rate;
		channels = metadata->data.stream_info.channels;
		bps = metadata->data.stream_info.bits_per_sample;

		fprintf(stderr, "sample rate    : %u Hz\n", sample_rate);
		fprintf(stderr, "channels       : %u\n", channels);
		fprintf(stderr, "bits per sample: %u\n", bps);
		fprintf(stderr, "total samples  : %llu\n", total_samples);
	}
#endif
}

/**
 * 
 */
void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
{
#ifdef TO_PORT
	(void)decoder, (void)client_data;

	fprintf(stderr, "Got error callback: %s\n", FLAC__StreamDecoderErrorStatusString[status]);
#endif
}
