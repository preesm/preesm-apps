//
// Created by hmiomand on 25/02/2020.
//

#include "SSIM.h"

void compute_SSIM(int WIDTH, int HEIGHT, unsigned char* reference, unsigned char* modified)
{
	static int iter = 0;

	double SSIM_value = 0;
	int dynamic_range = 255;
	double c1 = (0.01*dynamic_range)*(0.01*dynamic_range);
	double c2 = (0.03*dynamic_range)*(0.03*dynamic_range);

	double mean_ref = mean(WIDTH*HEIGHT, reference);
	double mean_mod = mean(WIDTH*HEIGHT, modified);

	double var_ref = variance(WIDTH*HEIGHT, reference);
	double var_mod = variance(WIDTH*HEIGHT, modified);

	double cov = covariance(WIDTH * HEIGHT, reference, modified);

	SSIM_value = (2*mean_ref*mean_mod + c1) * (2*cov + c2) / ((mean_ref*mean_ref + mean_mod*mean_mod + c1) * (var_ref + var_mod + c2));

//	printf("c1\t\t\t%lf\n", c1);
//	printf("c2\t\t\t%lf\n", c2);
//
//	printf("mean_ref\t%lf\n", mean_ref);
//	printf("mean_mod\t%lf\n", mean_mod);
//
//	printf("var_ref\t\t%lf\n", var_ref);
//	printf("var_mod\t\t%lf\n", var_mod);
//
//	printf("cov\t\t\t%lf\n\n", cov);
    if (iter % 10 == 0)
	    printf("%d : SSIM = %lf\n", iter, SSIM_value);
//	printf("%d : PSNR = %lf\n", iter++, PSNR_value);

    iter++;
}

double mean(int nb_value, unsigned char* values)
{
	double result = 0;

	for (int i = 0; i < nb_value; i++)
		result += (double) values[i];

	return result/nb_value;
}

double variance(int nb_value, unsigned char* values)
{
	double mean_value = mean(nb_value, values);

	double result = 0;

	for (int i = 0; i < nb_value; i++)
	{
		double temp = ((double) values[i] - mean_value);

		result += temp * temp;
	}

	return result/nb_value;
}

double covariance(int nb_value, unsigned char* values_1, unsigned char* values_2)
{
	double mean_values_1 = mean(nb_value, values_1);
	double mean_values_2 = mean(nb_value, values_2);

	double result = 0;
	for (int i = 0; i < nb_value; i++)
	{
		result += ((double) values_1[i] - mean_values_1) * ((double) values_2[i] - mean_values_2);
	}

	return result/(nb_value-1);
}