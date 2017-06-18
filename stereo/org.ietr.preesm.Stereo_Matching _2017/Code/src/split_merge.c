#include "split_merge.h"
#include <stdio.h>


int split(int n_slice, int width, int height, struct str_image_gray * im_r, struct str_image_gray * im_l, struct str_image_gray * slice_r, struct str_image_gray * slice_l)
{
    int i ;

    for(i=0 ; i<n_slice ; ++i)
    {
		// Structure init
        image_gray_init(&slice_r[i],width,height/n_slice);
        image_gray_init(&slice_l[i],width,height/n_slice);
		
		// Data copy
        memcpy(&slice_r[i].g[0],&im_r->g[i*width*height/n_slice],width*height/n_slice);
        memcpy(&slice_l[i].g[0],&im_l->g[i*width*height/n_slice],width*height/n_slice);
        
		
        #ifdef VERBOSE
			char f[50]= "";
			char b[50]= "";
			sprintf(f,"../images/test_split/slice_r_%d.ppm",i+1);
			sprintf(b,"../images/test_split/slice_l_%d.ppm",i+1);
			image_gray_save(f,&slice_r[i]);
			image_gray_save(b,&slice_l[i]);	
			printf("Copy of slice %d --> OK\n",i+1);
        #endif // VERBOSE

    }
    return 0;
}

int merge(int n_slice, int width, int height, int n_disp, uint8_t * slice_disp_map, uint8_t * disp_map)
{
     int i ;

    for(i=0 ; i<n_slice ; ++i)
    {
        memcpy( &disp_map[i*width*height/n_slice],&slice_disp_map[i*width*height/n_slice],width*height/n_slice);

    }
    return 0;
}



void remove_lines_sup(int n_slice, int width, int height, int n_disp, int nb_lines_sup, uint8_t * in, uint8_t * out)
{
    int block_size;
	// size to copy
    block_size = width* height*n_disp /n_slice; 
	// data copy
	memcpy( &out[0],&in[(nb_lines_sup*width*n_disp)],block_size); 
}

int split_complex(int n_slice, int width, int height, int window_size, struct str_image_gray * image, struct str_image_gray * slices)
{
    if((n_slice<=0) || (n_slice>height))
        {
            fprintf(stderr,"Uncorrect value of n_slice in %s. Should be in [1,%d]\n",__FUNCTION__,height);
            return -1;
        }
        /* VARIABLES DECLARATIONS*/
    int i;
    int data_height_full; // height of an original block of data to copy. Full slice
    int data_height_completed; // height of an original block of data to copy. Completed slice
    int slice_height ; // Size of the output slices
    int number_of_complete_slices ; // Number of slices to fill with only input data the others slices are completed with zero
    int nb_lines_sup; // Number of extra lines on top and bottom of each slice
    int top_bottom_block_size, top_bottom_block_size_completed, middle_block_size, middle_block_size_completed; // Sizes of blocks to copy from the original image to the output slices. Completed for slices non fully filled with input data

        /*INITIALISATION OF THE VARIABLES*/
    data_height_full = (int) floor(height/n_slice)+1;
    data_height_completed = (int) floor(height/n_slice);
    nb_lines_sup = (int)window_size /2 ;
    slice_height = ((int) floor(height/n_slice)+1)+ 2* nb_lines_sup;
    number_of_complete_slices = height % n_slice ;
    top_bottom_block_size_completed = (slice_height-1-nb_lines_sup)*width;
    middle_block_size_completed = (slice_height-1)*width;
    top_bottom_block_size = (slice_height -nb_lines_sup)*width;
    middle_block_size = (slice_height )*width;


        /*INITIALISATION OF THE OUTPUT SLICES*/
    for( i=0; i<n_slice; ++i)
    {
        image_gray_init(&slices[i],width,slice_height);
    }

        /*DATA COPY INTO OUTPUT SLICES*/
    for( i=0; i<n_slice; ++i)
    {
        if(i<number_of_complete_slices) // FULL SLICES
        {
            if((i!=0)&&(i!=n_slice-1))
            {
                memcpy(&slices[i].g[0],&image->g[(i*width*data_height_full)-(nb_lines_sup*width)],middle_block_size);
            }
            else
            {
                if(i!=0) // LAST SLICE
                {
                    memcpy(&slices[i].g[0],&image->g[(i*width*data_height_full)-(nb_lines_sup*width)],top_bottom_block_size);
                    memset(&slices[i].g[(slice_height -nb_lines_sup)*width],0,nb_lines_sup*width); // Fill the nb_lines_sup last lines with zeros
                }
                else // FIRST SLICE
                {
                    memset(&slices[0].g[0],0,nb_lines_sup*width); // Fill the nb_lines_sup first lines with zeros
                    memcpy(&slices[0].g[nb_lines_sup*width],&image->g[0],top_bottom_block_size);
                }
            }
        }
        else // ADJUSTED SLICES
        {
            if((i!=0)&&(i!=n_slice-1))
            {
                memcpy(&slices[i].g[0],&image->g[(number_of_complete_slices*width*data_height_full)+((i-number_of_complete_slices)*data_height_completed*width) -(nb_lines_sup*width)],middle_block_size_completed);
            }
            else
            {
                if(i!=0) // LAST SLICE
                {
                    memcpy(&slices[i].g[0],&image->g[(number_of_complete_slices*width*data_height_full)+((i-number_of_complete_slices)*data_height_completed*width) -(nb_lines_sup*width)],top_bottom_block_size_completed);
                    memset(&slices[i].g[(slice_height -(nb_lines_sup+1))*width],0,(nb_lines_sup+1)*width); // Fill the nb_lines_sup last lines with zeros
                }
                else // FIRST SLICE
                {
                    memset(&slices[0].g[0],0,(nb_lines_sup)*width); // Fill the nb_lines_sup first lines with zeros
                    memcpy(&slices[0].g[(nb_lines_sup)*width],&image->g[0],top_bottom_block_size_completed);
                    memset(&slices[0].g[top_bottom_block_size_completed + (nb_lines_sup)*width],0,width); // Fill a line with zeros
                }
            }
        }
		
    #ifdef VERBOSE
		char tab[50];
		sprintf(tab,"../images/test_split/slice%d.ppm",i+1);
		image_gray_save(tab,&slices[i]);
	#endif // VERBOSE
	
    }
    return 0;
}

void merge_complex(int n_slice, int width, int height, int window_size, uint8_t * slices, uint8_t * disp_map)
{
        /* VARIABLES DECLARATIONS*/
    int i;
    int data_height_full; // height of a block of data to copy. Full slice
    int data_height_completed; // height of ablock of data to copy. Completed slice
    int number_of_complete_slices ; // Number of full slices (not filled with zeros)
    int nb_lines_sup; // Number of extra lines to remove on top and bottom of each slice
    int data_block_size_completed, data_block_size_full; // Sizes of blocks to copy from the original slices to the output image.
	
        /*INITIALISATION OF THE VARIABLES*/
    data_height_full = (int) floor(height/n_slice)+1;
    data_height_completed = (int) floor(height/n_slice);
    nb_lines_sup = (int)window_size /2 ;
    number_of_complete_slices = height % n_slice ;
    data_block_size_completed = data_height_completed*width;
    data_block_size_full = data_height_full*width;


    for(i=0 ; i<n_slice ; ++i)
    {
        if(i<number_of_complete_slices) // Case slice fully filled with data
        {
            memcpy(&disp_map[i*data_block_size_full],&slices[((2*i+1)*nb_lines_sup*width)+(i*data_block_size_full)],data_block_size_full);
        }
        else // Case Slice with one line of zeros to delete
        {
            memcpy(&disp_map[(number_of_complete_slices*data_block_size_full)+((i-number_of_complete_slices)*data_block_size_completed)],&slices[((2*i+1)*nb_lines_sup*width)+(i*data_block_size_full)],data_block_size_completed);
        }
    }
}

void merge_complex_without_extra_lines(int n_slice, int width, int height, uint8_t * slices, uint8_t * disp_map)
{
    /* VARIABLES DECLARATIONS*/
    int i;
    int data_height_full; // height of a block of data to copy. Full slice
    int data_height_completed; // height of ablock of data to copy. Completed slice
    int number_of_complete_slices ; // Number of full slices (not filled with zeros)
    int data_block_size_completed, data_block_size_full; // Sizes of blocks to copy from the original slices to the output image.
        /*INITIALISATION OF THE VARIABLES*/
    data_height_full = (int) floor(height/n_slice)+1;
    data_height_completed = (int) floor(height/n_slice);
    number_of_complete_slices = height % n_slice ;
    data_block_size_completed = data_height_completed*width;
    data_block_size_full = data_height_full*width;


    for(i=0 ; i<n_slice ; ++i)
    {
        if(i<number_of_complete_slices) // Case slice fully filled with data
        {
            memcpy(&disp_map[i*data_block_size_full],&slices[(i*data_block_size_full)],data_block_size_full);
        }
        else // Case Slice with one line of zeros to delete
        {
            memcpy(&disp_map[(number_of_complete_slices*data_block_size_full)+((i-number_of_complete_slices)*data_block_size_completed)],&slices[i*data_block_size_full],data_block_size_completed);
        }
    }
}

