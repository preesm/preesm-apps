#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include "hls_math.h"
#include "hls_stream.h"

template<typename T>
void difference(hls::stream<T> &src1, hls::stream<T> &src2,
		hls::stream<T> &snk) {
#pragma HLS PIPELINE II=1 style=flp
	snk.write(src1.read() - src2.read());
}

template<typename T>
void sum(hls::stream<T> &input1, hls::stream<T> &input2, hls::stream<T> &output) {
#pragma HLS PIPELINE II=1 style=flp
	output.write(input1.read() + input2.read());
}

template<typename input1_t, typename input2_t, typename output_t>
void sum(hls::stream<input1_t> &input1, hls::stream<input2_t> &input2, hls::stream<output_t> &output) {
#pragma HLS PIPELINE II=1 style=flp // passé de 1 à 2 pour éviter une erreur de timing
	output.write(input1.read() + input2.read());
}

#endif //ARITHMETIC_HPP
