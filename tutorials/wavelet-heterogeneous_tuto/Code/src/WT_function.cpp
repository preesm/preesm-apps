#include "WT_function.h"

// Should be parallelizable along HEIGHT
void convolution_1D_row(int WIDTH, int HEIGHT, int FILTER_SIZE, float* input, float* filter, float* output)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			float sum = 0.0f;

			for (int kIndex = -FILTER_SIZE/2; kIndex <= FILTER_SIZE/2; kIndex++)
			{
				sum += input[i*WIDTH + ((j + kIndex + WIDTH) % WIDTH)] * filter[kIndex + FILTER_SIZE/2];
			}

			output[i*WIDTH + j] = sum;
		}
	}
}

void convolution_1D_row_decimation_col(int WIDTH, int HEIGHT, int FILTER_SIZE, float* input, float* filter, float* output)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j+=2)
        {
            float sum = 0.0f;

            for (int kIndex = -FILTER_SIZE/2; kIndex <= FILTER_SIZE/2; kIndex++)
            {
                sum += input[i*WIDTH + ((j + kIndex + WIDTH) % WIDTH)] * filter[kIndex + FILTER_SIZE/2];
            }

            output[i*WIDTH/2 + j/2] = sum;
        }
    }
}

// Should be parallelizable along WIDTH but need to properlly handle the fork
void convolution_1D_col(int WIDTH, int HEIGHT, int FILTER_SIZE, float* input, float* filter, float* output)
{
	for (int j = 0; j < WIDTH; j++)
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			float sum = 0.0f;

			for (int kIndex = -FILTER_SIZE/2; kIndex <= FILTER_SIZE/2; kIndex++)
			{
				sum += input[((i+kIndex+HEIGHT)%HEIGHT)*WIDTH + j] * filter[kIndex + FILTER_SIZE/2];
			}

			output[i*WIDTH + j] = sum;
		}
	}
}

void downsample_row(int WIDTH, int HEIGHT, float* input, float* output)
{
//	writePGM_ASCII(WIDTH, HEIGHT*2, input);
	//WIDTH and HEIGHT correspond to output data size
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			output[i*WIDTH + j] = input[(2*i)*WIDTH + j];
		}
	}
//	writePGM_ASCII(WIDTH, HEIGHT, output);
}

// Not tested for odd WIDTH*2 values (from upper level)
void downsample_col(int WIDTH, int HEIGHT, float* input, float* output)
{
	//WIDTH and HEIGHT correspond to output data size
#if 0
	for (int i = 0; i < WIDTH*HEIGHT; i++)
		output[i] = input[2*i];
#else

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			output[i*WIDTH + j] = input[(i*WIDTH + j)*2];
		}
	}
#endif
}

// Should be parallelizable along HEIGHT
void upsample_row(int WIDTH, int HEIGHT, float* input, float* output)
{
	//WIDTH and HEIGHT correspond to input data size

#if 0
	memset(output, 0, WIDTH*HEIGHT * 2 * sizeof(*output));

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			output[(2*i)*WIDTH + j] = input[i*WIDTH + j];
		}
	}
#else

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			output[2*i*WIDTH + j] = input[i*WIDTH + j];
			output[(2*i+1)*WIDTH + j] = 0;
		}
	}

#endif
}

// Should be parallelizable along HEIGHT
void upsample_col(int WIDTH, int HEIGHT, float* input, float* output)
{
	//WIDTH and HEIGHT correspond to input data size

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			output[i*WIDTH*2 + j*2] = input[i*WIDTH + j];
			output[i*WIDTH*2 + j*2+1] = 0;
		}
	}
}

// Should be parallelizable along whatever
void image_add(int WIDTH, int HEIGHT, float* input1, float* input2, float* output)
{
	for (int i = 0; i < WIDTH*HEIGHT; i++)
		output[i] = input1[i] + input2[i];

}

void soft_threshold(int WIDTH, int HEIGHT, float* input, float* output)
{
	float threshold_value = 1;

	for (int i = 0; i < WIDTH*HEIGHT; i++)
	{
		float temp = input[i];

		//using an int* pointer to do bit operation on the float
		int* temp_bit = (int*) &temp;

		//extracting sign
		unsigned int sign_bit = *temp_bit & 0x80000000;

		//get absolute value
		*temp_bit = *temp_bit & ~sign_bit;

		//apply max()
		temp = fmaxf(temp - threshold_value, (float) 0.0f);

		*temp_bit = *temp_bit | sign_bit;

		output[i] = temp;
	}
}

void median_histogram_threshold_filter(int WIDTH, int HEIGHT, float* input, float* output) {
	unsigned int histogram[512] = {0};

	// 1 : make histogram
	for(int i=0 ; i<WIDTH*HEIGHT; i++) {
		// convert to byte value in [0, 255]
		unsigned int approximate = (unsigned int) fmin(fabs(input[i]), 511);

		histogram[approximate]++;
	}

	// 2 : find median
	unsigned int nbvalues = 0;
	int median = 0;
	while(nbvalues < 3 * WIDTH * HEIGHT / 4) { // 32.079401
		nbvalues += histogram[median];
		median++;
	}

	// 3 : cap to median
	for(int i=0 ; i<WIDTH*HEIGHT; i++) {
		if(input[i] < 0) {
			output[i] = fmax(input[i], -median);
		}
		else {
			output[i] = fmin(input[i], median);
		}
	}
	
}
