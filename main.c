#include <stdio.h>
#include <esi.h>
#include "qdbmp.h"
#include <string.h>

int main(int argc, char *argv[])
{
    BMP *bmp;
    struct esi_image *image = malloc(sizeof(struct esi_image));
    char *out_fn;
    if(argc > 1) {
        bmp = BMP_ReadFile(argv[argc - 1]);
        if(!bmp) {
            printf("Not a BMP\n");
            return -1;;
        }
        if(BMP_GetDepth(bmp) != 24) {
            printf("Sorry, bmp2esi can only convert 24bit bmps.\n");
            printf("Honestly, it's not even hard to convert 32 bit bmps.\n");
            printf("I'm just incredibly frustrated over this garbage format, and some weird fread behavior.\n");
            exit(-1);
        }
        image->width = BMP_GetWidth(bmp);
        image->height = BMP_GetHeight(bmp);
        image->bdepth = BMP_GetDepth(bmp) / 3;
        image->grayscale = false;
        image->data = malloc(image->width * image->height * 3);
        for(uint64_t x = 0; x < image->width; x++) {
            for(uint64_t y = 0; y < image->height; y++) {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                BMP_GetPixelRGB(bmp, x, y, &r, &g, &b);
                image->data[((y * image->width)*3) + (x * 3)] = r;
                image->data[((y * image->width)*3) + (x * 3) + 1] = g;
                image->data[((y * image->width)*3) + (x * 3) + 2] = b;
            }
        }
        out_fn = malloc(strlen(argv[argc - 1]) + 5);
        strcpy(out_fn, argv[argc - 1]);
        strcat(out_fn, ".esi");
        printf("Saving to %s\n", out_fn);
        FILE *file = fopen(out_fn, "wb");
        save_esi_image(file, image);
        fclose(file);
    }
    return 0;
}
