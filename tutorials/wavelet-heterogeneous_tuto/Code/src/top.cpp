#include "top.h"

// http://wavelets.pybytes.com/wavelet/db2/

void Source_Highpass_filter(int FILTER_SIZE, float* filter)
{
	if(FILTER_SIZE != 5)
	{
		printf("Didn't implement filter coef calculation. Use FILTER_SIZE = 5. Sorry\n");
		exit(-1);
	}

	filter[0] = 0;
	filter[1] = -0.12941f;
	filter[2] = -0.22414f;
	filter[3] = 0.83652f;
	filter[4] = -0.48296f;
}

void Source_Lowpass_filter(int FILTER_SIZE, float* filter)
{
	if(FILTER_SIZE != 5)
	{
		printf("Didn't implement filter coef calculation. Use FILTER_SIZE = 5. Sorry\n");
		exit(-1);
	}

	filter[0] = 0;
	filter[1] = 0.48296f;
	filter[2] = 0.83652f;
	filter[3] = 0.22414f;
	filter[4] = -0.12941f;
}

void reverse_filter(int FILTER_SIZE, IN float* input, OUT float* output)
{
	for (int i = 0; i < FILTER_SIZE; i++)
		output[i] = input[FILTER_SIZE-1-i];
}

void reshape_image(int WIDTH, int HEIGHT, unsigned char* in_High_High, unsigned char* in_High_Low, unsigned char* in_Low_High, unsigned char* in_Low_Low, unsigned char* y)
{
	/*
	data retrieved as HH, HL, LH, LL

	need to output them as 

	LL,HL
	LH,HH
	*/

	// Copying lines of LL and HL into y
	for (int i = 0; i < HEIGHT/2; i++)
	{

		// Copying a line of LL into y
		for (int j = 0; j < WIDTH/2; j++)
		{
			y[i*WIDTH + j] = in_Low_Low[i * WIDTH/2 + j];
		}

		int col_index = 0;

		// Copying a line of HL into y
		for (int j = WIDTH/2; j < WIDTH; j++)
		{
			y[i*WIDTH + j] = in_High_Low[i * WIDTH/2 + col_index];
			col_index++;
		}
	}


	int line_index = 0;
	// Copying lines of LH and HH into y
	for (int i = HEIGHT/2; i < HEIGHT; i++)
	{


		// Copying a line of LL into y
		for (int j = 0; j < WIDTH/2; j++)
		{
			y[i*WIDTH + j] = in_Low_High[line_index * WIDTH/2 + j];
		}

		int col_index = 0;

		// Copying a line of HL into y
		for (int j = WIDTH/2; j < WIDTH; j++)
		{
			y[i*WIDTH + j] = in_High_High[line_index * WIDTH/2 + col_index];
			col_index++;
		}

		line_index++;
	}
}

void reshape_image_float(int WIDTH, int HEIGHT, float* in_High_High, float* in_High_Low, float* in_Low_High, float* in_Low_Low, float* y)
{
    /*
    data retrieved as HH, HL, LH, LL
    need to output them as

    LL,HL
    LH,HH
    */

    // Copying lines of LL and HL into y
    for (int i = 0; i < HEIGHT/2; i++)
    {

        // Copying a line of LL into y
        for (int j = 0; j < WIDTH/2; j++)
        {
            y[i*WIDTH + j] = in_Low_Low[i * WIDTH/2 + j];
        }

        int col_index = 0;

        // Copying a line of HL into y
        for (int j = WIDTH/2; j < WIDTH; j++)
        {
            y[i*WIDTH + j] = in_High_Low[i * WIDTH/2 + col_index];
            col_index++;
        }
    }

    int line_index = 0;
    // Copying lines of LH and HH into y
    for (int i = HEIGHT/2; i < HEIGHT; i++)
    {
        // Copying a line of LL into y
        for (int j = 0; j < WIDTH/2; j++)
        {
            y[i*WIDTH + j] = in_Low_High[line_index * WIDTH/2 + j];
        }

        int col_index = 0;
        // Copying a line of HL into y
        for (int j = WIDTH/2; j < WIDTH; j++)
        {
            y[i*WIDTH + j] = in_High_High[line_index * WIDTH/2 + col_index];
            col_index++;
        }

        line_index++;
    }
}

void reshape_uv(int WIDTH, int HEIGHT, unsigned char* input, unsigned char* output)
{
	/*
	reshape u or v component as 
	
	u,0
	0,0

	sizeof(input) = WIDTH*HEIGHT
	sizeof(output) = WIDTH*2*HEIGHT*2
	*/

	// memset(output, 0, WIDTH*2*HEIGHT*2);

	// for (int i = 0; i < HEIGHT; i++)
	// {

	// 	// Copying a line of LL into y
	// 	for (int j = 0; j < WIDTH; j++)
	// 	{
	// 		output[i*WIDTH*2 + j] = input[i * WIDTH + j];
	// 	}
	// }

	#if 0

	memset(output, 127, WIDTH*2*HEIGHT*2);

	#else
	for (int i = 0; i < HEIGHT; i++)
	{

		// Copying a line of LL into y
		for (int j = 0; j < WIDTH; j++)
		{
			output[i*WIDTH + j] = input[i * WIDTH/2 + j];
		}

		int col_index = 0;
		for (int j = WIDTH; j < WIDTH*2; j++)
		{
			output[i*WIDTH + j] = input[i * WIDTH/2 + col_index];
			col_index++;
		}
	}


	int line_index = 0;
	// Copying lines of LH and HH into y
	for (int i = HEIGHT; i < HEIGHT*2; i++)
	{


		// Copying a line of LL into y
		for (int j = 0; j < WIDTH; j++)
		{
			output[i*WIDTH + j] = input[line_index * WIDTH/2 + j];
		}

		int col_index = 0;
		for (int j = WIDTH; j < WIDTH*2; j++)
		{
			output[i*WIDTH + j] = input[line_index * WIDTH/2 + col_index];
			col_index++;
		}

		line_index++;
	}

	#endif
}

void writePGM_ASCII(int WIDTH, int HEIGHT, unsigned char* data)
{

	FILE * pgm_img = NULL;
	pgm_img = fopen("test.pgm", "wb");

	// Writing Magic Number to the File
	fprintf(pgm_img, "P2\n");

	// Writing Width and Height
	fprintf(pgm_img, "%d %d\n", WIDTH, HEIGHT);

	// Writing the maximum gray value
	fprintf(pgm_img, "255\n");

//	int count = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			// Writing the gray values in the 2D array to the file
			fprintf(pgm_img, "%d ", data[i*WIDTH + j]);
		}
		fprintf(pgm_img, "\n");
	}
	fclose(pgm_img);

	asm("nop");
}

void uchar_to_float(int WIDTH, int HEIGHT, unsigned char* input, float* output)
{
	for (int i = 0; i < WIDTH*HEIGHT; i++)
		output[i] = (float) input[i];
}

void float_to_uchar(int WIDTH, int HEIGHT, float* input, unsigned char* output)
{
	for (int i = 0; i < WIDTH*HEIGHT; i++) {
        unsigned char temp;

        if (input[i] < 0) {
            temp = 0;
        } else if (input[i] > 255) {
            temp = 255;
        } else {
            temp = (unsigned char) input[i];
        }

        output[i] = temp;
    }
}

void passthrough(int WIDTH, int HEIGHT, unsigned char* input, unsigned char* output)
{

}
