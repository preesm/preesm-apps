//////////////////////////////NEW SOBEL FUNCTION/////////////////////////////

#include <string.h>
#include <stdlib.h>

#include "sobel.h"
#include <stdio.h>
//#include "platform/frame_size.h"
#include "ap_video.hpp"

//#include "manr.h"



#define SOBEL_SIZE 3
#define ABSDIFF(x,y)    ((x>y)? x - y : y - x)
#define ABS(x)          ((x>0)? x : -x)

typedef ap_window<unsigned char,SOBEL_SIZE,SOBEL_SIZE> WINDOW;
typedef ap_linebuffer<unsigned char, SOBEL_SIZE, NUMCOLS> Y_BUFFER;

/* SOBEL 0 */

//Sobel Computation using a 3x3 neighborhood
unsigned char sobel_operator0(WINDOW *window)
{
  short x_weight = 0;
  short y_weight = 0;

  short edge_weight;
  unsigned char edge_val;

  int i;
  int j;

  const short x_op[SOBEL_SIZE][SOBEL_SIZE] = { {-1,0,1},
                             {-2,0,2},
                             {-1,0,1}};

  const short y_op[SOBEL_SIZE][SOBEL_SIZE] = { {1,2,1},
                             {0,0,0},
                             {-1,-2,-1}};

  //Compute approximation of the gradients in the X-Y direction
  for(i=0; i < SOBEL_SIZE; i++){
    for(j = 0; j < SOBEL_SIZE; j++){

      // X direction gradient
      x_weight = x_weight + (window->getval(i,j) * x_op[i][j]);

      // Y direction gradient
      y_weight = y_weight + (window->getval(i,j) * y_op[i][j]);
    }
  }

  edge_weight = ABS(x_weight) + ABS(y_weight);

  //Edge thresholding
//  if(edge_weight > 200)
//    edge_weight = 255;
//  else if(edge_weight < 100)
//    edge_weight = 0;
  edge_val = (unsigned char)edge_weight;

  return edge_val;
}

//Main function for Sobel Filtering
//This function includes a line buffer for a streaming implementation
#pragma SDS data copy(yc_in[0:NUMCOLS*height], yc_out[0:NUMCOLS*height])
#pragma SDS data access_pattern(yc_in:SEQUENTIAL, yc_out:SEQUENTIAL)
void sobel_filter0( unsigned char *yc_in,unsigned char *yc_out, int height)
{
  int row;
  int col;

  Y_BUFFER buff_A;
  WINDOW buff_C;

  for(row = 0; row < height+1; row++){
    for(col = 0; col < NUMCOLS+1; col++){
#pragma AP PIPELINE II = 1

      // Temp values are used to reduce the number of memory reads
      unsigned char input_data = 0;
      unsigned char temp = 0;
      unsigned char tempx = 0;

      //Line Buffer fill
      if(col < NUMCOLS) {
        buff_A.shift_up(col);
        temp = buff_A.getval(0,col);
      }

      //There is an offset to accomodate the active pixel region
      //There are only NUMCOLS and NUMROWS valid pixels in the image
      if((col < NUMCOLS) & (row < height)) {
        unsigned char y;
        input_data = yc_in[row*NUMCOLS+col];
        y = input_data ;
        tempx = y;
        buff_A.insert_bottom(tempx,col);
      }

      //Shift the processing window to make room for the new column
      buff_C.shift_right();

      //The Sobel processing window only needs to store luminance values
      //rgb2y function computes the luminance from the color pixel
      if(col < NUMCOLS) {
        buff_C.insert(buff_A.getval(2,col),0,2);
        buff_C.insert(temp,1,2);
        buff_C.insert(tempx,2,2);
      }

      unsigned char edge;
      //The sobel operator only works on the inner part of the image
      //This design assumes there are no edges on the boundary of the image
      if( row <= 1 || col <= 1 || row > (height-1) || col > (NUMCOLS-1)) {
        edge=0;
      }
      else {
        //Sobel operation on the inner portion of the image
        edge = sobel_operator0(&buff_C);
      }

      if(row > 0 && col > 0) {
        	yc_out[(row-1)*NUMCOLS+(col-1)] = (edge);
      }
    }
  }
}

/* SOBEL 1 */

//Sobel Computation using a 3x3 neighborhood
unsigned char sobel_operator1(WINDOW *window)
{
  short x_weight = 0;
  short y_weight = 0;

  short edge_weight;
  unsigned char edge_val;

  int i;
  int j;

  const short x_op[SOBEL_SIZE][SOBEL_SIZE] = { {-1,0,1},
                             {-2,0,2},
                             {-1,0,1}};

  const short y_op[SOBEL_SIZE][SOBEL_SIZE] = { {1,2,1},
                             {0,0,0},
                             {-1,-2,-1}};

  //Compute approximation of the gradients in the X-Y direction
  for(i=0; i < SOBEL_SIZE; i++){
    for(j = 0; j < SOBEL_SIZE; j++){

      // X direction gradient
      x_weight = x_weight + (window->getval(i,j) * x_op[i][j]);

      // Y direction gradient
      y_weight = y_weight + (window->getval(i,j) * y_op[i][j]);
    }
  }

  edge_weight = ABS(x_weight) + ABS(y_weight);

  //Edge thresholding
//  if(edge_weight > 200)
//    edge_weight = 255;
//  else if(edge_weight < 100)
//    edge_weight = 0;
  edge_val = (unsigned char)edge_weight;

  return edge_val;
}

//Main function for Sobel Filtering
//This function includes a line buffer for a streaming implementation
#pragma SDS data copy(yc_in[0:NUMCOLS*height], yc_out[0:NUMCOLS*height])
#pragma SDS data access_pattern(yc_in:SEQUENTIAL, yc_out:SEQUENTIAL)
void sobel_filter1( unsigned char *yc_in,unsigned char *yc_out, int height)
{
  int row;
  int col;

  Y_BUFFER buff_A;
  WINDOW buff_C;

  for(row = 0; row < height+1; row++){
    for(col = 0; col < NUMCOLS+1; col++){
#pragma AP PIPELINE II = 1

      // Temp values are used to reduce the number of memory reads
      unsigned char input_data = 0;
      unsigned char temp = 0;
      unsigned char tempx = 0;

      //Line Buffer fill
      if(col < NUMCOLS) {
        buff_A.shift_up(col);
        temp = buff_A.getval(0,col);
      }

      //There is an offset to accomodate the active pixel region
      //There are only NUMCOLS and NUMROWS valid pixels in the image
      if((col < NUMCOLS) & (row < height)) {
        unsigned char y;
        input_data = yc_in[row*NUMCOLS+col];
        y = input_data ;
        tempx = y;
        buff_A.insert_bottom(tempx,col);
      }

      //Shift the processing window to make room for the new column
      buff_C.shift_right();

      //The Sobel processing window only needs to store luminance values
      //rgb2y function computes the luminance from the color pixel
      if(col < NUMCOLS) {
        buff_C.insert(buff_A.getval(2,col),0,2);
        buff_C.insert(temp,1,2);
        buff_C.insert(tempx,2,2);
      }

      unsigned char edge;
      //The sobel operator only works on the inner part of the image
      //This design assumes there are no edges on the boundary of the image
      if( row <= 1 || col <= 1 || row > (height-1) || col > (NUMCOLS-1)) {
        edge=0;
      }
      else {
        //Sobel operation on the inner portion of the image
        edge = sobel_operator0(&buff_C);
      }

      if(row > 0 && col > 0) {
        	yc_out[(row-1)*NUMCOLS+(col-1)] = (edge);
      }
    }
  }
}



/* SOBEL 2 */

//Sobel Computation using a 3x3 neighborhood
unsigned char sobel_operator2(WINDOW *window)
{
  short x_weight = 0;
  short y_weight = 0;

  short edge_weight;
  unsigned char edge_val;

  int i;
  int j;

  const short x_op[SOBEL_SIZE][SOBEL_SIZE] = { {-1,0,1},
                             {-2,0,2},
                             {-1,0,1}};

  const short y_op[SOBEL_SIZE][SOBEL_SIZE] = { {1,2,1},
                             {0,0,0},
                             {-1,-2,-1}};

  //Compute approximation of the gradients in the X-Y direction
  for(i=0; i < SOBEL_SIZE; i++){
    for(j = 0; j < SOBEL_SIZE; j++){

      // X direction gradient
      x_weight = x_weight + (window->getval(i,j) * x_op[i][j]);

      // Y direction gradient
      y_weight = y_weight + (window->getval(i,j) * y_op[i][j]);
    }
  }

  edge_weight = ABS(x_weight) + ABS(y_weight);

  //Edge thresholding
//  if(edge_weight > 200)
//    edge_weight = 255;
//  else if(edge_weight < 100)
//    edge_weight = 0;
  edge_val = (unsigned char)edge_weight;

  return edge_val;
}

//Main function for Sobel Filtering
//This function includes a line buffer for a streaming implementation
#pragma SDS data copy(yc_in[0:NUMCOLS*height], yc_out[0:NUMCOLS*height])
#pragma SDS data access_pattern(yc_in:SEQUENTIAL, yc_out:SEQUENTIAL)
void sobel_filter2( unsigned char *yc_in,unsigned char *yc_out, int height)
{
  int row;
  int col;

  Y_BUFFER buff_A;
  WINDOW buff_C;

  for(row = 0; row < height+1; row++){
    for(col = 0; col < NUMCOLS+1; col++){
#pragma AP PIPELINE II = 1

      // Temp values are used to reduce the number of memory reads
      unsigned char input_data = 0;
      unsigned char temp = 0;
      unsigned char tempx = 0;

      //Line Buffer fill
      if(col < NUMCOLS) {
        buff_A.shift_up(col);
        temp = buff_A.getval(0,col);
      }

      //There is an offset to accomodate the active pixel region
      //There are only NUMCOLS and NUMROWS valid pixels in the image
      if((col < NUMCOLS) & (row < height)) {
        unsigned char y;
        input_data = yc_in[row*NUMCOLS+col];
        y = input_data ;
        tempx = y;
        buff_A.insert_bottom(tempx,col);
      }

      //Shift the processing window to make room for the new column
      buff_C.shift_right();

      //The Sobel processing window only needs to store luminance values
      //rgb2y function computes the luminance from the color pixel
      if(col < NUMCOLS) {
        buff_C.insert(buff_A.getval(2,col),0,2);
        buff_C.insert(temp,1,2);
        buff_C.insert(tempx,2,2);
      }

      unsigned char edge;
      //The sobel operator only works on the inner part of the image
      //This design assumes there are no edges on the boundary of the image
      if( row <= 1 || col <= 1 || row > (height-1) || col > (NUMCOLS-1)) {
        edge=0;
      }
      else {
        //Sobel operation on the inner portion of the image
        edge = sobel_operator2(&buff_C);
      }

      if(row > 0 && col > 0) {
        	yc_out[(row-1)*NUMCOLS+(col-1)] = (edge);
      }
    }
  }
}

/* SOBEL 3 */

//Sobel Computation using a 3x3 neighborhood
unsigned char sobel_operator3(WINDOW *window)
{
  short x_weight = 0;
  short y_weight = 0;

  short edge_weight;
  unsigned char edge_val;

  int i;
  int j;

  const short x_op[SOBEL_SIZE][SOBEL_SIZE] = { {-1,0,1},
                             {-2,0,2},
                             {-1,0,1}};

  const short y_op[SOBEL_SIZE][SOBEL_SIZE] = { {1,2,1},
                             {0,0,0},
                             {-1,-2,-1}};

  //Compute approximation of the gradients in the X-Y direction
  for(i=0; i < SOBEL_SIZE; i++){
    for(j = 0; j < SOBEL_SIZE; j++){

      // X direction gradient
      x_weight = x_weight + (window->getval(i,j) * x_op[i][j]);

      // Y direction gradient
      y_weight = y_weight + (window->getval(i,j) * y_op[i][j]);
    }
  }

  edge_weight = ABS(x_weight) + ABS(y_weight);

  //Edge thresholding
//  if(edge_weight > 200)
//    edge_weight = 255;
//  else if(edge_weight < 100)
//    edge_weight = 0;
  edge_val = (unsigned char)edge_weight;

  return edge_val;
}

//Main function for Sobel Filtering
//This function includes a line buffer for a streaming implementation
#pragma SDS data copy(yc_in[0:NUMCOLS*height], yc_out[0:NUMCOLS*height])
#pragma SDS data access_pattern(yc_in:SEQUENTIAL, yc_out:SEQUENTIAL)
void sobel_filter3( unsigned char *yc_in,unsigned char *yc_out, int height)
{
  int row;
  int col;

  Y_BUFFER buff_A;
  WINDOW buff_C;

  for(row = 0; row < height+1; row++){
    for(col = 0; col < NUMCOLS+1; col++){
#pragma AP PIPELINE II = 1

      // Temp values are used to reduce the number of memory reads
      unsigned char input_data = 0;
      unsigned char temp = 0;
      unsigned char tempx = 0;

      //Line Buffer fill
      if(col < NUMCOLS) {
        buff_A.shift_up(col);
        temp = buff_A.getval(0,col);
      }

      //There is an offset to accomodate the active pixel region
      //There are only NUMCOLS and NUMROWS valid pixels in the image
      if((col < NUMCOLS) & (row < height)) {
        unsigned char y;
        input_data = yc_in[row*NUMCOLS+col];
        y = input_data ;
        tempx = y;
        buff_A.insert_bottom(tempx,col);
      }

      //Shift the processing window to make room for the new column
      buff_C.shift_right();

      //The Sobel processing window only needs to store luminance values
      //rgb2y function computes the luminance from the color pixel
      if(col < NUMCOLS) {
        buff_C.insert(buff_A.getval(2,col),0,2);
        buff_C.insert(temp,1,2);
        buff_C.insert(tempx,2,2);
      }

      unsigned char edge;
      //The sobel operator only works on the inner part of the image
      //This design assumes there are no edges on the boundary of the image
      if( row <= 1 || col <= 1 || row > (height-1) || col > (NUMCOLS-1)) {
        edge=0;
      }
      else {
        //Sobel operation on the inner portion of the image
        edge = sobel_operator3(&buff_C);
      }

      if(row > 0 && col > 0) {
        	yc_out[(row-1)*NUMCOLS+(col-1)] = (edge);
      }
    }
  }
}

