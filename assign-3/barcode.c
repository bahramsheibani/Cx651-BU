#include "barcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QUIET_AREA_WIDTH 9
#define START_PATTERN_WIDTH 3
#define LEFT_SECTION_WIDTH 6
#define MIDDLE_PATTERN_WIDTH 5
#define RIGHT_SECTION_WIDTH 6
#define END_PATTERN_WIDTH 3

struct image *barcode(char *data, int width, int height)
{
    struct image *img = (struct image *)malloc(sizeof(struct image));
    img->height = height;
    img->width = width;
    img->pixels = (struct pixel *)malloc(sizeof(struct pixel) * width * height);

    fill_quite_area(0, QUIET_AREA_WIDTH, img);
    fill_start(img);
    fill_left(data, img);
    fill_middle(img);
    fill_right(data, img);
    fill_end(img);
    fill_quite_area(width - QUIET_AREA_WIDTH, QUIET_AREA_WIDTH, img);

    return img;
}

void fill_digit(int start_x, int digit, struct image *img)
{
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < 7 && start_x + j < img->width; j++)
        {
            int bit = GET_BIT(digit, 6 - j);
            int color = bit ? 255 : 0;
            img->pixels[i * img->width + start_x + j].r = color;
            img->pixels[i * img->width + start_x + j].g = color;
            img->pixels[i * img->width + start_x + j].b = color;
        }
    }
}


void fill_quite_area(int start_x, int width, struct image *img)
{
    for (int i = 0; i < img->height; i++)
    {
        for (int j = start_x; j < start_x + width && j < img->width; j++)
        {
            img->pixels[i * img->width + j].r = 255;
            img->pixels[i * img->width + j].g = 255;
            img->pixels[i * img->width + j].b = 255;
        }
    }
}

void fill_start(struct image *img)
{
    int start_pattern[START_PATTERN_WIDTH] = {0, 1, 0};
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < START_PATTERN_WIDTH; j++)
        {
            int color = start_pattern[j] == 0 ? 0 : 255;
            int x = QUIET_AREA_WIDTH + j;
            img->pixels[i * img->width + x].r = color;
            img->pixels[i * img->width + x].g = color;
            img->pixels[i * img->width + x].b = color;
        }
    }
}

void fill_end(struct image *img)
{
    int end_pattern[END_PATTERN_WIDTH] = {0, 1, 0};
    int start_x = img->width - QUIET_AREA_WIDTH - END_PATTERN_WIDTH;
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < END_PATTERN_WIDTH; j++)
        {
            int color = end_pattern[j] == 0 ? 0 : 255;
            int x = start_x + j;
            img->pixels[i * img->width + x].r = color;
            img->pixels[i * img->width + x].g = color;
            img->pixels[i * img->width + x].b = color;
        }
    }
}

void fill_left(char *data, struct image *img)
{
    int left_codes[10] = {0b1110010, 0b1100110, 0b1101100, 0b1010000,
                         0b1011100, 0b1001110, 0b1000010, 0b1000100,
                         0b1001000, 0b1110100};
    int x = QUIET_AREA_WIDTH + START_PATTERN_WIDTH;
    for (int i = 0; i < 6; i++)
    {
        int digit = data[i] - '0';
        fill_digit(x + i * 7, left_codes[digit], img);
    }
}

void fill_middle(struct image *img)
{
    int middle_pattern[MIDDLE_PATTERN_WIDTH] = {1, 0, 1, 0, 1};
    int start_x = QUIET_AREA_WIDTH + START_PATTERN_WIDTH + LEFT_SECTION_WIDTH * 7;
    int end_x = start_x + MIDDLE_PATTERN_WIDTH;
    for (int i = 0; i < img->height; i++)
    {
        for (int j = start_x; j < end_x; j++)
        {
            int color = middle_pattern[j - start_x] == 0 ? 0 : 255;
            img->pixels[i * img->width + j].r = color;
            img->pixels[i * img->width + j].g = color;
            img->pixels[i * img->width + j].b = color;
        }
    }
}

void fill_right(char *data, struct image *img)
{
    int left_codes[10] = {0b1110010, 0b1100110, 0b1101100, 0b1010000,
                         0b1011100, 0b1001110, 0b1000010, 0b1000100,
                         0b1001000, 0b1110100};
    int x = QUIET_AREA_WIDTH + START_PATTERN_WIDTH + LEFT_SECTION_WIDTH * 7 + MIDDLE_PATTERN_WIDTH;

    for (int i = 0; i < 6; i++)
    {
        int digit = data[6 + i] - '0';
        int right_digit = left_codes[digit] ^ 0b1111111;
        fill_digit(x + i * 7, right_digit, img);
    }
}

int GET_BIT(int value, int position)
{
    return (value >> position) & 1;
}
