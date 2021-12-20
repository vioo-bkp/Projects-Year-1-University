/* Mateescu F. Viorel - Cristian
   Grupa: 312 CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"
#pragma pack(1)

typedef struct {
bmp_infoheader x;
bmp_fileheader y;
unsigned char ***bitmap;
int pad;
char testNo;
} imagine;

#pragma pack()

imagine* citeste_img(char *fisier) {
FILE *file = fopen(fisier, "rb");

imagine *img = (imagine*)calloc(1, sizeof(imagine));
fread(&img->y, sizeof(img->y), 1, file);
fread(&img->x, sizeof(img->x), 1, file);
img->testNo = fisier[4];
img->bitmap = (unsigned char***)calloc(img->x.height, sizeof(unsigned char**));
int i, j;
for (i = 0; i < img->x.height; i++) {
    img->bitmap[i] = (unsigned char**)calloc(img->x.width, sizeof(unsigned char*));
for (j = 0; j < img->x.width; j++) {
    img->bitmap[i][j] = (unsigned char*)calloc(3, sizeof(unsigned char));
}
	}
	img->pad = img->x.width % 4;
	fseek(file, img->y.imageDataOffset, SEEK_SET);
	for (i = 0; i < img->x.height; i++) {
		for (j = 0; j < img->x.width; j++) {
			fread(img->bitmap[i][j], sizeof(unsigned char), 3, file);
		}
		fseek(file, img->pad, SEEK_CUR);
	}

	fclose(file);

	return img;
}

void scrie_img(imagine *img) {
	FILE *file = fopen("img.bmp", "wb");
	fwrite(&img->y, sizeof(img->y), 1, file);
	fwrite(&img->x, sizeof(img->x), 1, file);
	fseek(file, img->y.imageDataOffset, SEEK_SET);

	unsigned char pad = 0;
	int i, j;

	for (i = 0; i < img->x.height; i++) {
        for (j = 0; j < img->x.width; j++) {
			fwrite(img->bitmap[i][j], sizeof(unsigned char), 3, file);
		}

	fwrite(&pad, sizeof(unsigned char), img->pad, file);
	}

	fclose(file);
}

void black_white(imagine *img) {
	int sum;
	int i, j, k;
	for (i = 0; i < img->x.height; i++) {
		for (j = 0; j < img->x.width; j++) {
			sum = 0;

			for (k = 0; k < 3; k++) {
				sum += img->bitmap[i][j][k];
			}
			sum /= 3;

			for (k = 0; k < 3; k++) {
				img->bitmap[i][j][k] = sum;
			}
		}
	}
	char *fileT = (char*)calloc(25, sizeof(char));
	strcpy(fileT, "test");
	fileT[4] = img->testNo;
	strcat(fileT, "_black_white.bmp");

	FILE *file = fopen(fileT, "wb");
	fwrite(&img->y, sizeof(img->y), 1, file);
	fwrite(&img->x, sizeof(img->x), 1, file);
	fseek(file, img->y.imageDataOffset, SEEK_SET);
	unsigned char pad = 0;
	for (i = 0; i < img->x.height; i++) {
		for (j = 0; j < img->x.width; j++) {
			fwrite(img->bitmap[i][j], sizeof(unsigned char), 3, file);
		}
		for (j = 0; j < img->pad; j++) {
			fwrite(&pad, sizeof(unsigned char), 1, file);
		}
	}
	fclose(file);
}

void free_img(imagine *img) {
	int i;
	for (i = 0; i < img->x.height; i++) {
		free(img->bitmap[i]);
	}

	free(img);
}

void no_crop(imagine *img) {
	char *fileT = (char*)calloc(25, sizeof(char));
	strcpy(fileT, "test");
	fileT[4] = img->testNo;
	strcat(fileT, "_nocrop.bmp");
	FILE *file = fopen(fileT, "wb");

	int input_height = img->x.height;
	int input_width = img->x.width;

	int diferenta = input_width - input_height;
		if (diferenta % 2 == 1) {
			diferenta = diferenta / 2 + 1;
		} else {
			diferenta /= 2;
		}
		img->x.height = img->x.width;
		fwrite(&img->y, sizeof(img->y), 1, file);
		fwrite(&img->x, sizeof(img->x), 1, file);
		fseek(file, img->y.imageDataOffset, SEEK_SET);
		unsigned char white = 255;
		unsigned char pad = 0;
		int i, j, k;
		for (i = 0; i < img->x.height; i++) {
			if (i < diferenta) {
				for (j = 0; j < img->x.width; j++) {
					for(k = 0; k < 3; k++) {
						fwrite(&white, sizeof(unsigned char), 1, file);
					}
					printf("1 %d %d\n", i, j);
				}
				for (j = 0; j < img->pad; j++) {
					fwrite(&pad, sizeof(unsigned char), 1, file);
				}
			} else if (i >= diferenta && i < diferenta + input_height) {
				for (j = 0; j < img->x.width; j++) {
					fwrite(img->bitmap[i - diferenta][j], sizeof(unsigned char), 3, file);
					printf("2 %d %d\n", i - diferenta, j);
				}
				for (j = 0; j < img->pad; j++) {
					fwrite(&pad, sizeof(unsigned char), 1, file);
				}
			} else {
				for (j = 0; j < img->x.width; j++) {
					for(k = 0; k < 3; k++) {
						fwrite(&white, sizeof(unsigned char), 1, file);
					}
					printf("3 %d %d\n", i, j);
				}
				for (j = 0; j < img->pad; j++) {
					fwrite(&pad, sizeof(unsigned char), 1, file);
				}
			}
		}
	img->x.height = input_height;
	img->x.width = input_width;
fclose(file);
}

int main() {
    FILE *input = fopen("input.txt", "rt");
	char *fileIn = (char*)calloc(25, sizeof(char));
	fscanf(input, "%s", fileIn);
	imagine *img = citeste_img(fileIn);
	black_white(img);
	free_img(img);

	img = citeste_img(fileIn);
	no_crop(img);
	free_img(img);

	return 0;
}
