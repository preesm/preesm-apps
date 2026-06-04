#ifndef SAMPLING_CHANGE_HPP
#define SAMPLING_CHANGE_HPP

#include "hls_stream.h"

template<int WIDTH, int HEIGHT, typename T>
void downsample_row(hls::stream<T> &input, hls::stream<T> &output) {
	for (int i = 0; i < HEIGHT * 2; i++) {
		for (int j = 0; j < WIDTH; j++) {
			auto val = input.read();
			if (i % 2 == 0) {
				output.write(val);
			}
		}
	}
}

template<int WIDTH, typename T>
void downsample_row_linewise(hls::stream<T> &input, hls::stream<T> &output) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < WIDTH; j++) {
			auto val = input.read();
			if (i % 2 == 0) {
				output.write(val);
			}
		}
	}
}

template<int WIDTH, int HEIGHT, typename T>
void downsample_col(hls::stream<T> &input, hls::stream<T> &output) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH * 2; j++) {
			auto val = input.read();
			if (j % 2 == 0) {
				output.write(val);
			}
		}
	}
}

template<typename T>
void downsample_col_pixelwise(hls::stream<T> &input, hls::stream<T> &output) {
	auto val = input.read();
	val = input.read();
	output.write(val);
}

template<int WIDTH, int HEIGHT, typename T>
void upsample_row(hls::stream<T> &input, hls::stream<T> &output) {
	for (int i = 0; i < HEIGHT * 2; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i % 2 == 0) {
				auto val = input.read();
				output.write(val);
			} else {
				output.write(0);
			}
		}
	}
}

template<int WIDTH, typename T>
void upsample_row_linewise(hls::stream<T> &input, hls::stream<T> &output) {
    #pragma HLS PIPELINE style=flp // voir si on peut remplacer par un simple rewind, sans pipeline
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i % 2 == 0) {
				auto val = input.read();
				output.write(val);
			} else {
				output.write(0);
			}
		}
	}
}

template<int WIDTH, int HEIGHT, typename T>
void upsample_col(hls::stream<T> &input, hls::stream<T> &output) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH * 2; j++) {
			if (j % 2 == 0) {
				auto val = input.read();
				output.write(val);
			} else {
				output.write(0);
			}
		}
	}
}

template<typename T>
void upsample_col_pixelwise(hls::stream<T> &input, hls::stream<T> &output) {
#pragma HLS PIPELINE II=2 style=flp
	auto val = input.read();
	output.write(val);
	output.write(0);
}

#endif //SAMPLING_CHANGE_HPP
