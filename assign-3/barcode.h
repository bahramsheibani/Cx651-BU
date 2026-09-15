#include "common.h"
#include <math.h>
#include <stdlib.h>

struct image* barcode(char* data, int width, int height);
void fill_digit(int start_x, int digit, struct image* img);
int GET_BIT(int value, int position);
void fill_quite_area(int start_x, int width, struct image* img);
void fill_start(struct image* img);
void fill_end(struct image* img);
void fill_left(char* data, struct image* img);
void fill_middle(struct image* img);
void fill_right(char* data, struct image* img); 
    
