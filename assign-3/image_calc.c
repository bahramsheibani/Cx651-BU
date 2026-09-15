#include "barcode.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char** argv){

    char* barcode_value = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    char* filename = argv[4];
    if(argc !=5) {
        printf("Incorrect number of arguments. Expected: ./build/image_calc <barcode_value> <width> <height> <output_image_path>\n");
        printf("Received %d arguments.\n", argc - 1);
        return -1;
    }

    struct image* img = barcode(barcode_value, width, height);
    saveimage(filename, img);
    free(img->pixels);
    free(img);
}
