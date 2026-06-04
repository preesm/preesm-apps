#ifndef FILTER_HPP
#define FILTER_HPP

#include "hls_math.h"
#include "hls_stream.h"

template<typename T>
void soft_threshold(hls::stream<T> &src, hls::stream<T> &snk) {
#pragma HLS PIPELINE II=1 style=flp
	T threshold_value = 1;

	T data = src.read();
	T filtered = fmaxf(data - threshold_value, 0);

	filtered = std::copysign(filtered, data);
	snk.write(filtered);
}

template<typename T, int WIDTH, int HEIGHT>
void median_histogram_threshold_filter(hls::stream<T> &src, hls::stream<T> &snk) {
	// #pragma HLS PIPELINE style=flp
	unsigned int histogram[512] = {0};
	T sauvegarde[WIDTH*HEIGHT];

	// 1 : make histogram
	build_histogram: for(int i=0 ; i<WIDTH*HEIGHT; i++) {
		#pragma HLS PIPELINE style=flp
		// convert to value in [0, 511]
		T value = src.read();
		unsigned int approximate = (unsigned int) fmin(fabs(value), 511);
		sauvegarde[i] = value;

		histogram[approximate]++;
	}

	// 2 : find median
	unsigned int nbvalues = 0;
	int median = 0;
	find_median: while(nbvalues < 3 * WIDTH * HEIGHT / 4) { // 32.079401
		#pragma hls latency max=512
		nbvalues += histogram[median];
		median++;
	}

	// 3 : cap to median
	cap: for(int i=0 ; i<WIDTH*HEIGHT ; i++) {
		#pragma HLS PIPELINE style=flp
		if(sauvegarde[i] < 0) {
			snk.write(fmax(sauvegarde[i], -median));
		}
		else {
			snk.write(fmin(sauvegarde[i], median));
		}
	}
	
}



#endif //FILTER_HPP
