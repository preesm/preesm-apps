/**
 * @file image_ppm.c
 * @brief
 * @date 4 juin 2015
 * @author Judicael Menant
 */

#include "image_ppm.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

/**
 * This function reads the pxm magic number.
 * @param file The pxm file, with the cursor at start of file.
 * @return -1 if it is not a pxm magic number, the pxm mode (1 to 6).
 */
static int getppm_MagicNumber(FILE* file)
{
	char head[2];

	if(fread(&head, sizeof(char), 2, file) != 2)
	{
		return -1;
	}

	if(head[0] != 'P')
	{
		return -1;
	}

	if(head[1] >= '1' && head[1] <= '6')
	{
		return head[1] - '0';
	}

	return -1;
}

/**
 * Test if a character is a space character (ie it is ' ', '\n', '\t' or '\r').
 * @param v The char to test
 * @return 1 if v is a space char, 0 otherwise.
 */
static int isWhite(char v)
{
	switch(v)
	{
	case ' ' :
	case '\0':
	case '\n':
	case '\r':
	case '\t':
		return 1;
		break;
	default :
		return 0;
		break;
	}
}

/**
 * Reads an assci string in a file. Escape space char and comments.
 * @param file pxm file opened, with cursor to the first char to read.
 * @param str the output string
 * @param nbMax the size of output string (including ending char). Must be at least 2.
 * @return 0 if everything ok, error code otherwise.
 */
static int pxm_readNextAscii(FILE* file, char* str, unsigned int nbMax)
{
	char data;
	/*0 : waiting, 1: comment, 2:reading, 3:finished*/
	int state = 0;
	/*remove all white space and comments*/

	nbMax--; /*reserve one space for '\0'*/
	do
	{
		if(fread(&data, sizeof(char), 1, file) != 1)
		{
			if(state != 2)
			{
				return -1;
			}
			else
			{
				/*if end of file, finish parsing*/
				data = '\0';
			}

		}
		switch(state)
		{
		case 0:
			/*waiting for content, remove whitespaces*/
			if(data == '#')
			{
				state = 1;
			}
			else if(isWhite(data) == 0)
			{
				*str++ = data;
				nbMax--;
				state = 2;
			}
			break;

		case 1:
			/*waiting for end of comment (\n)*/
			if(data == '\n')
			{
				state = 0;
			}
			break;

		case 2:
			/*reading data until next whitespace*/
			if(isWhite(data))
			{
				state = 3;
			}else if(nbMax)
			{
				*str++ = data;
				nbMax--;
			}
			else
			{
				/*not long enough*/
				return -1;
			}
			break;

		case 3:
			break;
		default :
			state = 0;
			break;
		}

	}while(state != 3); /*reading finished*/

	*str++ = '\0'; /*end of string*/

	return 0;
}

/**
 * Reads the next number (in ascci format) in the file.
 * @param file pxm file opened, with cursor to the first char to read.
 * @param num Pointer to store the result.
 * @return 0 if everything ok, error code otherwise.
 */
static int pxm_getNextNumber(FILE* file, int* num)
{
	char str_tmp[16];

	if(num != NULL)
	{
		if(pxm_readNextAscii(file, str_tmp, 15) != 0)
		{
			return -1;
		}

		*num = strtol(str_tmp, NULL, 10);

		if((num == 0) && (str_tmp[0] != '0'))
		{
			return -1;
		}
	}

	return 0;
}

/**
 * Reads the header of a pxm file and extract informations.
 * @param file The pxm file, with cursor on the first header char.
 * @param height Pointer to store the height of image.
 * @param width Pointer to store the width of image.
 * @param maxN Pointer to store the maximum value of a pixel.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_getHeader(FILE* file, int* height, int* width, int* maxN)
{
	if(pxm_getNextNumber(file, width))
	{
		return -1;
	}

	if(pxm_getNextNumber(file, height))
	{
		return -1;
	}

	if(pxm_getNextNumber(file, maxN))
	{
		return -1;
	}

	return 0;
}

/**
 * @brief Read the binary part of a pxm file.
 *
 * It manage 8 and 16 bits case (convert to 8 bit), and scale the dynamic
 * according to maxn. Dynamic in the file is from 0 to maxn, and it is store
 * to be 0 to 255 on out buffer.
 *
 * @param file pxm file, with cursor pointing to first byte of data.
 * @param maxn The file dynamic (read in the header).
 * @param nb number of element to read.
 * @param out The output buffer (must be nb size).
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_readBin(FILE* file, int maxn, int nb, uint8_t* out)
{
	int i, tmp;
	if(maxn > 255)
	{
		uint16_t* buff_tmp = malloc(sizeof(uint16_t)*nb);

		if(buff_tmp == NULL)
		{
			return -1;
		}

		if(fread(out, sizeof(uint16_t), nb, file) != nb)
		{
			free(buff_tmp);
			return -1;
		}

		for(i=0; i<nb; i++)
		{
			tmp = buff_tmp[i];
			tmp *= 255;
			tmp /= maxn;
			out[i] = tmp;
		}

		free(buff_tmp);
	}
	else
	{
		if(fread(out, sizeof(uint8_t), nb, file) != nb)
		{
			return -1;
		}

		/*plain scale*/
		for(i=0; i<nb; i++)
		{
			tmp = out[i];
			tmp *= 255;
			tmp /= maxn;
			out[i] = tmp;
		}
	}

	return 0;
}

/**
 * @brief Read the ASCII content of a pxm file.
 *
 * It scales the dynamic according to maxn. Dynamic in the file is from 0 to
 * maxn, and it is store to be 0 to 255 on out buffer.
 *
 * @param file pxm file, with cursor pointing to first char of content.
 * @param maxn The file dynamic (read in the header).
 * @param nb number of element to read.
 * @param out The output buffer (must be nb size).
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_readASCII(FILE* file, int maxn, int nb, uint8_t* out)
{
	int i, tmp;

	for(i=0; i<nb; i++)
	{
		if(pxm_getNextNumber(file, &tmp))
		{
			return -1;
		}

		tmp *= 255;
		tmp /= maxn;
		out[i] = tmp;
	}

	return 0;
}

/**
 * Read the content part of a pbm file (mode P1, ascci black and white).
 * @param file The pxm file, with cursor after the header.
 * @param str Image to store results, must be initialized.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_p1_readContent(FILE* file, struct str_image_rgb* str)
{
	unsigned int i;
	if(pxm_readASCII(file, 1, str->w*str->h, str->g))
	{
		return -1;
	}

	for(i=0; i<str->w*str->h; i++)
	{
		str->g[i] = 255 - str->g[i];
	}

	memcpy(str->r, str->g, sizeof(uint8_t)*str->w*str->h);
	memcpy(str->b, str->g, sizeof(uint8_t)*str->w*str->h);

	return 0;
}

/**
 * Read the content part of a pgm file (mode P2, ascci gray scale).
 * @param file The pxm file, with cursor after the header.
 * @param maxn The scale of image (read in header).
 * @param str Image to store results, must be initialized.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_p2_readContent(FILE* file, int maxn, struct str_image_rgb* str)
{
	if(pxm_readASCII(file, maxn, str->w*str->h, str->g))
	{
		return -1;
	}

	memcpy(str->r, str->g, sizeof(uint8_t)*str->w*str->h);
	memcpy(str->b, str->g, sizeof(uint8_t)*str->w*str->h);

	return 0;
}

/**
 * Read the content part of a ppm file (mode P3, ascci rgb).
 * @param file The pxm file, with cursor after the header.
 * @param maxn The scale of image (read in header).
 * @param str Image to store results, must be initialized.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_p3_readContent(FILE* file, int maxn, struct str_image_rgb* str)
{
	int i, j;
	uint8_t* buffer = malloc(sizeof(uint8_t)*3*str->w*str->h);

	if(buffer == NULL)
	{
		return -1;
	}


	if(pxm_readASCII(file, maxn, str->w*str->h*3, buffer))
	{
		free(buffer);
		return -1;
	}

	for(i=0, j=0; i<str->w*str->h; i++)
	{
		str->r[i] = buffer[j++];
		str->g[i] = buffer[j++];
		str->b[i] = buffer[j++];
	}

	free(buffer);

	return 0;
}

/**
 * Read the content part of a pbm file (mode P4, binary black and white).
 * @param file The pxm file, with cursor after the header.
 * @param str Image to store results, must be initialized.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_p4_readContent(FILE* file, struct str_image_rgb* str)
{
	int rowSize = (str->w+7)/8 - 1;
	int rest = str->w - 8*rowSize;
	int y, x, i, pos_bytes, pos_out;
	uint8_t curdata, v;

	/*str->g is used as a buffer*/
	if(pxm_readBin(file, 255, (rowSize+1)*str->h, str->g))
	{
		return -1;
	}

	for(y=0, pos_bytes = 0, pos_out = 0; y<str->h; y++)
	{
		for(x=0; x<rowSize; x++)
		{
			curdata = str->g[pos_bytes++];
			for(i=0; i<8; i++)
			{
				v = (curdata&0x80)?0:255;
				str->r[pos_out++] = v;
				curdata<<=1;
			}
		}

		curdata = str->g[pos_bytes++];
		for(i=0; i<rest; i++)
		{
			v = (curdata&0x80)?0:255;
			str->r[pos_out++] = v;
			curdata<<=1;
		}
	}

	memcpy(str->g, str->r, sizeof(uint8_t)*str->w*str->h);
	memcpy(str->b, str->r, sizeof(uint8_t)*str->w*str->h);

	return 0;
}

/**
 * Read the content part of a pgm file (mode P5, binary, gray scale).
 * @param file The pxm file, with cursor after the header.
 * @param maxn The scale of image (read in header).
 * @param str Image to store results, must be initialized.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_p5_readContent(FILE* file, int maxn, struct str_image_rgb* str)
{
	if(pxm_readBin(file, maxn, str->w*str->h, str->g))
	{
		return -1;
	}

	memcpy(str->r, str->g, sizeof(uint8_t)*str->w*str->h);
	memcpy(str->b, str->g, sizeof(uint8_t)*str->w*str->h);

	return 0;
}

/**
 * Read the content part of a ppm file (mode P6, binary, rgb).
 * @param file The pxm file, with cursor after the header.
 * @param maxn The scale of image (read in header).
 * @param str Image to store results, must be initialized.
 * @return 0 if everything success, error code otherwise.
 */
static int pxm_p6_readContent(FILE* file, int maxn, struct str_image_rgb* str)
{
	int i, j;
	size_t size_malloc = 3*str->w*str->h;

	uint8_t* buffer = malloc(sizeof(uint8_t)*size_malloc);

	if(buffer == NULL)
	{
		return -1;
	}

	if(pxm_readBin(file, maxn, str->w*str->h*3, buffer))
	{
		free(buffer);
		return -1;
	}

	for(i=0, j=0; i<str->w*str->h; i++)
	{
		str->r[i] = buffer[j++];
		str->g[i] = buffer[j++];
		str->b[i] = buffer[j++];
	}

	free(buffer);

	return 0;
}


int image_rgb_loadPxm(const char* filename, struct str_image_rgb* str)
{
	FILE* file = NULL;
	int errcode = -1;
	int magic = 0;
	int width = 0, height = 0, maxn = 0;

	file = fopen(filename, "rb");

	if(file == NULL)
	{
		printf("Error : Unable to open '%s'\n", filename);
		goto error;
	}

	magic = getppm_MagicNumber(file);
	if(magic < 0)
	{
		printf("Error : '%s' is not a ppm file\n", filename);
		goto close_file;
	}

	if(magic == 1 || magic == 4)
	{
		errcode = pxm_getHeader(file, &height, &width, NULL);
	}
	else
	{
		errcode = pxm_getHeader(file, &height, &width, &maxn);
	}

	if(errcode)
	{
		printf("Error : While parsing '%s' header\n", filename);
		goto close_file;
	}

	if(image_rgb_init(str, width, height))
	{
		printf("Error : Enomem\n");
		goto close_file;
	}

	switch(magic)
	{
	case 1:
		errcode = pxm_p1_readContent(file, str);
		break;
	case 2:
		errcode = pxm_p2_readContent(file, maxn, str);
		break;
	case 3:
		errcode = pxm_p3_readContent(file, maxn, str);
		break;
	case 4:
		errcode = pxm_p4_readContent(file, str);
		break;
	case 5:
		errcode = pxm_p5_readContent(file, maxn, str);
		break;
	case 6:
		errcode = pxm_p6_readContent(file, maxn, str);
		break;

	default :
		printf("Error : Unrecognized file format for '%s'\n", filename);
		goto free_image;
		break;
	}

	if(errcode)
	{
		printf("Error : While parsing '%s'\n", filename);
		goto free_image;
	}

	errcode = 0;
	goto close_file;

free_image :
	image_rgb_destroy(str);

close_file :
	fclose(file);
error :
	return errcode;

}

int image_gray_loadPxm(const char* filename, struct str_image_gray* str)
{
	int errcode = 0;
	struct str_image_rgb str_rgb;


	errcode = image_rgb_loadPxm(filename, &str_rgb);
	if(errcode)
	{
		goto finish;
	}

	errcode = image_gray_init(str, str_rgb.w, str_rgb.h);
	if(errcode)
	{
		goto free_rgb;
	}

	image_rgb2gray(str, &str_rgb);

free_rgb :
	image_rgb_destroy(&str_rgb);

finish :
	return errcode;

}

/**
 * Writes a pxm header which contains magic number, image size and scale (optionnal).
 * @param file Output pxm file, must be empty.
 * @param mode Image format (from 1 to 6).
 * @param width Width of image.
 * @param height Height of image.
 * @param nbMax Scale of image, ignored in pbm (1 and 4).
 */
static void pxm_writeHeader(FILE* file, int mode, int width, int height, int nbMax)
{
	fprintf(file, "P%d\n%d %d\n", mode, width, height);
	if(mode != 1 && mode != 4)
	{
		fprintf(file, "%d\n", nbMax);
	}
}

/**
 * Writes the content part of a pbm image in mode 1 (ASCII, black and white).
 * @param file output file, with cursor after the header.
 * @param str Image to write.
 * @return 0 if everything success, error code otherwise.
 */
static int image_savePxm_p1(FILE* file, const struct str_image_gray* str)
{
	int x, y, i;
	char endc, bit;

	i=0;
	for(y = 0; y < str->h; y++)
	{
		for(x = 0; x < str->w; x++)
		{
			endc = (x == (str->w - 1)) ? '\n' : ' ';
			bit = (str->g[i] < 128) ? '1' : '0';
			fprintf(file, "%c%c", bit, endc);
			i++;
		}
	}

	return 0;
}

/**
 * Writes the content part of a pgm image in mode 1 (ASCII, grayscale).
 * @param file output file, with cursor after the header.
 * @param str Image to write.
 * @return 0 if everything success, error code otherwise.
 */
static int image_savePxm_p2(FILE* file, const struct str_image_gray* str)
{
	int x, y, i;
	char endc;

	i=0;
	for(y = 0; y < str->h; y++)
	{
		for(x = 0; x < str->w; x++)
		{
			endc = (x == (str->w - 1)) ? '\n' : ' ';
			fprintf(file, "%3d%c", str->g[i], endc);
			i++;
		}
	}

	return 0;
}

/**
 * Writes the content part of a ppm image in mode 3 (ASCII, rgb).
 * @param file output file, with cursor after the header.
 * @param str Image to write.
 * @return 0 if everything success, error code otherwise.
 */
static int image_savePxm_p3(FILE* file, const struct str_image_rgb* str)
{
	int x, y, i;
	char endc;

	i=0;
	for(y = 0; y < str->h; y++)
	{
		for(x = 0; x < str->w; x++)
		{
			endc = (x == (str->w - 1)) ? '\n' : ' ';
			fprintf(file, "%3d %3d %3d  %c", str->r[i], str->g[i], str->b[i], endc);
			i++;
		}
	}

	return 0;
}

/**
 * Writes the content part of a pbm image in mode 4 (binary, black and white).
 * @param file output file, with cursor after the header.
 * @param str Image to write.
 * @return 0 if everything success, error code otherwise.
 */
static int image_savePxm_p4(FILE* file, const struct str_image_gray* str)
{
	uint8_t* buffer;
	int linesize, buffsize;
	int x, y, i, pgray, pbyte, lastbits;
	uint8_t tmp;

	int errcode = 0;

	linesize = (str->w+7)/8;

	// allocate buffer
	buffsize = linesize*str->h;
	buffer = malloc(sizeof(uint8_t)*buffsize);

	if(buffer == NULL)
	{
		printf("Error : ENOMEM\n");
		return -1;
	}

	//fill buffer
	pgray=0;
	pbyte=0;
	lastbits = (str->w - 1)%8 + 1; /*value 1 to 8*/
	for(y=0; y<str->h; y++)
	{
		for(x = 0; x < (linesize - 1); x++)
		{
			tmp = 0;
			for(i=0; i<8; i++)
			{
				tmp <<= 1;
				tmp |= (str->g[pgray] < 128)?0x01:0;
				pgray++;
			}
			buffer[pbyte++]=tmp;
		}

		/*last byte*/
		tmp = 0;
		for(i = 0; i < lastbits; i++)
		{
			tmp |= ((str->g[pgray] < 128)?0x01:0) << (7-i);
			pgray++;
		}
		buffer[pbyte++]=tmp;
	}

	//write buffer
	if(fwrite(buffer, sizeof(uint8_t), buffsize, file) != buffsize)
	{
		printf("Error : Unable to write\n");
		errcode = -1;
	}

	free(buffer);

	return errcode;
}

/**
 * Writes the content part of a pgm image in mode 5 (binary, grayscale).
 * @param file output file, with cursor after the header.
 * @param str Image to write.
 * @return 0 if everything success, error code otherwise.
 */
static int image_savePxm_p5(FILE* file, const struct str_image_gray* str)
{
	int buffsize = str->w * str->h;
	int errcode = 0;

	//write buffer
	if(fwrite(str->g, sizeof(uint8_t), buffsize, file) != buffsize)
	{
		printf("Error : Unable to write\n");
		errcode = -1;
	}

	return errcode;
}

/**
 * Writes the content part of a ppm image in mode 6 (binary, rgb).
 * @param file output file, with cursor after the header.
 * @param str Image to write.
 * @return 0 if everything success, error code otherwise.
 */
static int image_savePxm_p6(FILE* file, const struct str_image_rgb* str)
{
	int i;
	uint8_t* buffer;
	int buffsize;

	int errcode = 0;

	// allocate buffer
	buffsize = str->w*str->h*3;
	buffer = malloc(sizeof(uint8_t)*buffsize);

	if(buffer == NULL)
	{
		printf("Error : ENOMEM\n");
		return -1;
	}

	//fill buffer
	for(i=0; i<str->w*str->h; i++)
	{
		buffer[3*i + 0] = str->r[i];
		buffer[3*i + 1] = str->g[i];
		buffer[3*i + 2] = str->b[i];
	}

	//write buffer
	if(fwrite(buffer, sizeof(uint8_t), buffsize, file) != buffsize)
	{
		printf("Error : Unable to write\n");
		errcode = -1;
	}

	free(buffer);

	return errcode;
}

int image_rgb_savePxm(const char* filename, const struct str_image_rgb* str, int mode)
{
	int errcode = -1;
	FILE* file = NULL;

	if(mode <= 0 || mode > 6)
	{
		printf("Error : Invalid mode\n");
		return -1;
	}

	if(mode != 3 && mode != 6)
	{
		//convert to gray image
		struct str_image_gray imgray;

		if(image_gray_init(&imgray, str->w, str->h))
		{
			return -1;
		}

		image_rgb2gray(&imgray, str);
		//call gray save function
		errcode = image_gray_savePxm(filename, &imgray, mode);
		image_gray_destroy(&imgray);

		return errcode;
	}

	file = fopen(filename, "wb");

	if(file == NULL)
	{
		printf("Error : Unable to open '%s'\n", filename);
		return -1;
	}

	pxm_writeHeader(file, mode, str->w, str->h, 255);

	if(mode == 3)
	{
		//ascii
		errcode = image_savePxm_p3(file, str);
	}
	else
	{
		//binary
		errcode = image_savePxm_p6(file, str);
	}

	fclose(file);
	return errcode;
}

int image_gray_savePxm(const char* filename, const struct str_image_gray* str, int mode)
{
	int errcode = -1;
	FILE* file = NULL;

	if(mode <= 0 || mode > 6)
	{
		printf("Error : Invalid mode\n");
		return -1;
	}

	if(mode == 3 || mode == 6)
	{
		//convert to rgb image
		struct str_image_rgb imrgb;

		if(image_rgb_init(&imrgb, str->w, str->h))
		{
			return -1;
		}

		image_gray2rgb(&imrgb, str);
		//call rgb save function
		errcode = image_rgb_savePxm(filename, &imrgb, mode);
		image_rgb_destroy(&imrgb);

		return errcode;
	}

	file = fopen(filename, "wb");

	if(file == NULL)
	{
		printf("Error : Unable to open '%s'\n", filename);
		return -1;
	}

	pxm_writeHeader(file, mode, str->w, str->h, 255);

	switch(mode)
	{
	case 1:
		errcode = image_savePxm_p1(file, str);
		break;
	case 2:
		errcode = image_savePxm_p2(file, str);
		break;
	case 4:
		errcode = image_savePxm_p4(file, str);
		break;
	case 5:
		errcode = image_savePxm_p5(file, str);
		break;
	default :
		break;
	}

	fclose(file);
	return errcode;
}
