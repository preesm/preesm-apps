#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include "hls_stream.h"

template<int WIDTH, int HEIGHT, int FILTER_SIZE, typename input_t,
		typename filter_t, typename output_t>
void convolution_1D_row(hls::stream<input_t> &input,
		hls::stream<filter_t> &filter, hls::stream<output_t> &output) {
	// Read filter coefficients
	filter_t filter_tab[FILTER_SIZE];
	crow_init_filter: for (int i = 0; i < FILTER_SIZE; i++) {
        #pragma HLS pipeline style=flp
		filter_tab[i] = filter.read();
	}

	input_t buffer_line[2][WIDTH];
	input_t buffer_conv[FILTER_SIZE];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=buffer_conv
	crow_height: for (int i = 0; i < HEIGHT + 1; i++) {
		crow_width: for (int j = 0; j < WIDTH + FILTER_SIZE - 1; j++) {
            #pragma HLS pipeline style=flp
			// Populate double buffer
			if (i < HEIGHT && j < WIDTH) {
				buffer_line[i % 2][j] = input.read();
			}
			// Compute result with 1 line latency to access wrap around values
			crow_shift: for (int k = 0; k < FILTER_SIZE - 1; k++) {
				buffer_conv[k] = buffer_conv[k + 1];
			}
			buffer_conv[FILTER_SIZE - 1] = buffer_line[(i + 1) % 2][(j - (FILTER_SIZE / 2) + WIDTH) % WIDTH];
			if (i > 0 && j >= FILTER_SIZE - 1) {
				float sum = 0;
				crow_filter: for (int k = 0; k < FILTER_SIZE; k++) {
					sum += (float) (buffer_conv[k] * filter_tab[k]);
				}

				output.write((output_t)sum);
			}
		}
	}
}


template<int WIDTH, int HEIGHT, int FILTER_SIZE, typename input_t,
		typename filter_t, typename output_t>
void convolution_1D_col_ref(hls::stream<input_t> &input,
		hls::stream<filter_t> &filter, hls::stream<output_t> &output) {
	// Read filter coefficients
	filter_t filter_tab[FILTER_SIZE];
	ccol_init_filter: for (int i = 0; i < FILTER_SIZE; i++) {
        #pragma HLS pipeline style=flp
		filter_tab[i] = filter.read();
	}

	input_t buffer[HEIGHT][WIDTH];
	ccol_copy_height: for (int i = 0; i < HEIGHT; i++) {
		ccol_copy_width: for (int j = 0; j < WIDTH; j++) {
            #pragma HLS pipeline style=flp
			buffer[i][j] = input.read();
		}
	}

	ccol_height: for (int i = 0; i < HEIGHT; i++) {
		ccol_width: for (int j = 0; j < WIDTH; j++) {
            #pragma HLS pipeline style=flp
			float sum = 0.0f;

			ccol_filter: for (int k = 0; k < FILTER_SIZE; k++) {
				sum += (float) (buffer[(i + k - FILTER_SIZE / 2 + HEIGHT) % HEIGHT][j] * filter_tab[k]);
			}

			output.write((output_t)sum);
		}
	}
}

// Compute convolution in column, shifting values by FILTER_SIZE / 2 - 1 columns to avoid storing the entire image
template<int WIDTH, int HEIGHT, int FILTER_SIZE, typename input_t,
		typename filter_t, typename output_t>
void convolution_1D_col(hls::stream<input_t> &input,
		hls::stream<filter_t> &filter, hls::stream<output_t> &output) {
	// Read filter coefficients
	filter_t filter_tab[FILTER_SIZE];
	ccol_init_filter: for (int i = 0; i < FILTER_SIZE; i++) {
        #pragma HLS pipeline style=flp
		filter_tab[i] = filter.read();
	}

	input_t init_buffer[FILTER_SIZE][WIDTH];
	input_t buffer[FILTER_SIZE][WIDTH];
#pragma HLS ARRAY_RESHAPE dim=1 type=complete variable=buffer

	ccol_height: for (int i = 0; i < HEIGHT + FILTER_SIZE - 1; i++) {
		ccol_width: for (int j = 0; j < WIDTH; j++) {
            #pragma HLS pipeline style=flp
			// read input value from fifo or initial buffer for wrap around
			input_t val;
			if (i < HEIGHT) {
				val = input.read();
				if (i < FILTER_SIZE) {
					init_buffer[i][j] = val;
				}
			} else {
				// for last lines go back to initial buffer values
				val = init_buffer[i - HEIGHT][j];
			}

			ccol_shift_buffer: for(int k = 0; k < FILTER_SIZE - 1; k++) {
				buffer[k][j] = buffer[k + 1][j];
			}
			buffer[FILTER_SIZE - 1][j] = val;

			if (i >= FILTER_SIZE - 1) {
				float sum = 0.0f;

				ccol_filter: for (int k = 0; k < FILTER_SIZE; k++) {
					sum += (float) (buffer[k][j] * filter_tab[k]);
				}

				output.write((output_t)sum);
			}
		}
	}
}

#endif //CONVOLUTION_HPP
