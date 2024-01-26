/* 
 *  Name: Bethany Kim
 *  UID: 005 995 244
 */

#include <stdlib.h>
#include <omp.h>

#include "utils.h"
#include "parallel.h"



/*
 *  PHASE 1: compute the mean pixel value
 *  This code is buggy! Find the bug and speed it up.
 */
void mean_pixel_parallel(const uint8_t img[][NUM_CHANNELS], int num_rows, int num_cols, double mean[NUM_CHANNELS]) {
    long count = 0;

    #pragma omp parallel for reduction(+:count) reduction(+:mean[:NUM_CHANNELS])
    for (int row = 0; row < num_rows; row++){
        int temp = row * num_cols;
        for (int col = 0; col < num_cols; col++) {
            int temp2 = temp + col;
            mean[0] += img[temp2][0];
            mean[1] += img[temp2][1];
            mean[2] += img[temp2][2];
            count += 3;
        }
    }

    count /= NUM_CHANNELS;

    mean[0] /= count;
    mean[1] /= count;
    mean[2] /= count;
}



/*
 *  PHASE 2: convert image to grayscale and record the max grayscale value along with the number of times it appears
 *  This code is NOT buggy, just sequential. Speed it up.
 */
void grayscale_parallel(const uint8_t img[][NUM_CHANNELS], int num_rows, int num_cols, uint32_t grayscale_img[][NUM_CHANNELS], uint8_t *max_gray, uint32_t *max_count) {
    *max_gray = 0;
    uint8_t temp_max_gray = 0;
    *max_count = 0;
    int temp_max_count[255] = {0};
    
    #pragma omp parallel for reduction(max:temp_max_gray) reduction(+:temp_max_count[:255])
    for (int row = 0; row < num_rows; row++)
    {
        int temp = row * num_cols;
        for (int col = 0; col < num_cols; col++)
        {
            int temp2 = temp + col;
            for (int gray_ch = 0; gray_ch < NUM_CHANNELS; gray_ch++) {
                uint32_t sum = 0;
                for (int ch = 0; ch < NUM_CHANNELS; ch++) {
                    sum += img[temp2][ch];
                }
                grayscale_img[temp2][gray_ch] = sum/NUM_CHANNELS;

                if (grayscale_img[temp2][gray_ch] == temp_max_gray) {
                    temp_max_count[temp_max_gray]++;
                }
                else if (grayscale_img[temp2][gray_ch] > temp_max_gray) {
                    temp_max_gray = grayscale_img[temp2][gray_ch];
                    temp_max_count[temp_max_gray] = 1;
                }
            }
        }
    }

    *max_gray = temp_max_gray;
    *max_count = temp_max_count[temp_max_gray];
}



/*
 *  PHASE 3: perform convolution on image
 *  This code is NOT buggy, just sequential. Speed it up.
 */
void convolution_parallel(const uint8_t padded_img[][NUM_CHANNELS], int num_rows, int num_cols, const uint32_t kernel[], int kernel_size, uint32_t convolved_img[][NUM_CHANNELS]) {
    // compute kernel normalization factor
    int kernel_norm = 0;
    //#pragma omp parallel for reduction(+:kernel_norm)
    for(int i = 0; i < kernel_size*kernel_size; i++) {
        kernel_norm += kernel[i];
    }

    // compute dimensions of convolved image
    int conv_rows = num_rows - kernel_size + 1;
    int conv_cols = num_cols - kernel_size + 1;

    // perform convolution
    #pragma omp parallel for
    for (int row = 0; row < conv_rows; row++) {
        int temp0 = row * conv_cols;
        int temp1 = row * num_cols;
        for (int col = 0; col < conv_cols; col++) {
            int temp2 = temp0 + col;
                
            convolved_img[temp2][0] = 0;
            convolved_img[temp2][1] = 0;
            convolved_img[temp2][2] = 0;
            for (int kernel_row = 0; kernel_row < kernel_size; kernel_row++) {
                int temp3 = temp1 + (kernel_row * num_cols) + col;
                int temp4 = kernel_row * kernel_size;
                for (int kernel_col = 0; kernel_col < kernel_size; kernel_col++) {
                    convolved_img[temp2][0] += padded_img[temp3 + kernel_col][0] * kernel[temp4 + kernel_col];
                    convolved_img[temp2][1] += padded_img[temp3 + kernel_col][1] * kernel[temp4 + kernel_col];
                    convolved_img[temp2][2] += padded_img[temp3 + kernel_col][2] * kernel[temp4 + kernel_col];
                }
            }

            convolved_img[temp2][0] /= kernel_norm;
            convolved_img[temp2][1] /= kernel_norm;
            convolved_img[temp2][2] /= kernel_norm;
        } 
    }
}