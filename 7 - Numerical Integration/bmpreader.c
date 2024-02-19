// bmpreader.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable:4996)
#include"bmpdef.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

INFOHEADER* infoHeader;

FILE* openBmpImage(char* fileName) {
	FILE* fp;
	if ((fp = fopen(fileName, "rb")) == NULL) {
		return NULL;
	}
	return fp;
}

void closeBmpImage(FILE* fp) {
	fclose(fp);
	free(fp);
}

FILEHEADER* readBmpFileHeader(FILE* fp) {
	FILEHEADER* fileHeader = (FILEHEADER*)malloc(sizeof(FILEHEADER));
	if (fileHeader == NULL) {
		fprintf(stderr, "内存分配失败");
	}
	fread(fileHeader, sizeof(FILEHEADER), 1, fp);
	return fileHeader;
}

INFOHEADER* readBmpInfoHeader(FILE* fp) {
	//printf("%d\n", sizeof(INFOHEADER));
	infoHeader = (INFOHEADER*)malloc(sizeof(INFOHEADER));
	if (infoHeader == NULL) {
		fprintf(stderr, "内存分配失败");
	}
	fread(infoHeader, sizeof(INFOHEADER), 1, fp);
	printf("图片宽度：%d像素\n", infoHeader->bImageWidth);
	printf("图片高度：%d像素\n", infoHeader->bImageHeight);
	return infoHeader;
}

RGBDATA** createMatrix(int width, int height) {
	RGBDATA** Matrix;
	int i;

	Matrix = (RGBDATA**)malloc(sizeof(RGBDATA*) * height);
	if (Matrix == NULL) {
		fprintf(stderr, "内存分配失败");
		return NULL;
	}

	for (i = 0; i < height; i++) {
		Matrix[i] = (RGBDATA*)malloc(sizeof(RGBDATA) * width);
		if (Matrix[i] == NULL) {
			fprintf(stderr, "内存分配失败");
			return NULL;
		}
	}
	return(Matrix);
}

RGBDATA** readBmpDataToArray(FILE* fp) {
	int i = 0, j = 0;
	int width = 0, height = 0;
	FILEHEADER* fileHeader = readBmpFileHeader(fp);
	INFOHEADER* infoHeader = readBmpInfoHeader(fp);
	width = infoHeader->bImageWidth;
	height = infoHeader->bImageHeight;
	RGBDATA** data = createMatrix(width, height);
	if (infoHeader->bBitsPerPixel < 8) {
		RGBQUAD* rgbQuad = (RGBQUAD*)malloc(sizeof(RGBQUAD));
		if (rgbQuad == NULL) {
			printf("内存分配失败");
			exit(0);
		}
		fread(rgbQuad, sizeof(rgbQuad), 1, fp);
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			fread(&data[i][j], sizeof(RGBDATA), 1, fp);
			if (j == width - 1) {
				fseek(fp, 1, SEEK_CUR);
			}
		}
	}
	return data;
}

void Area(int count,double amount) {
	double area=(15 * 7 * count / amount);
	printf("面积（平方厘米）为：%lf\n", area);
	return;
}

int main() {
	int count=0;
	double amount;
	double area=0;
	int firstX=-1;
	int lastX=-1;
	int flag=0;
	int X[800];
	int Y[800];
	int tmp;
	FILE* fp = openBmpImage("C:\\Users\\BlueRain\\source\\repos\\bmpreader\\x64\\Debug\\read.bmp");//记得修改路径
	RGBDATA** data = readBmpDataToArray(fp);
	closeBmpImage(fp);
	amount = infoHeader->bImageHeight * infoHeader->bImageWidth;
	printf("\n像素法直接计算：\n");
	for (int i = 0; i < infoHeader->bImageHeight; i++) {
		for (int j = 0; j < infoHeader->bImageWidth; j++) {
			if (data[i][j].blue!=255||data[i][j].green!=255||data[i][j].red!=255) {
				count++;
			}
		}
	}
	printf("指定颜色像素块总数为：%d\n", count);
	Area(count, amount);
	printf("\n复化梯形公式取样计算：\n");
	for (int j = 0; j < infoHeader->bImageWidth; j++) {
		for (int i = 0; i < infoHeader->bImageHeight; i++) {
			if (data[i][j].blue != 255 || data[i][j].green != 255 || data[i][j].red != 255) {
				flag = 1;
			}
		}
		if (flag == 1) {
			firstX = j + 1;
			flag = 0;
			break;
		}
	}
	for (int j = firstX; j < infoHeader->bImageWidth; j++) {
		flag = 0;
		for (int i = 0; i < infoHeader->bImageHeight; i++) {
			if (data[i][j].blue != 255 || data[i][j].green != 255 || data[i][j].red != 255) {
				flag = 1;
			}
		}
		if (flag != 1) {
			lastX = j;
			flag = 0;
			break;
		}
	}
	printf("指定颜色像素首个出现列为：%d\n", firstX);
	printf("指定颜色像素末个出现列为：%d\n", lastX);
	printf("请指定中间需要采样的数量：\n");
	int n;
	scanf("%d", &n);
	tmp = (lastX - firstX) / (n + 1);
	if (tmp == 0) {
		printf("采样过多，数量已被重置为最大值！\n");
		n = lastX - firstX;
		tmp = 1;
	}
	X[n + 1] = lastX+1;
	for (int i = 0; i <= n; i++) {
		X[i] = firstX + i * tmp;
	}
	for (int k = 0; k <= n; k++) {
		Y[k] = 0;
		int j = X[k];
		for (int i = 0; i < infoHeader->bImageHeight; i++) {
			if (data[i][j].blue != 255 || data[i][j].green != 255 || data[i][j].red != 255) {
					Y[k]++;
			}
		}
	}
	{
		int j = lastX - 1;
		Y[n+1] = 0;
		for (int i = 0; i < infoHeader->bImageHeight; i++) {
			if (data[i][j].blue != 255 || data[i][j].green != 255 || data[i][j].red != 255) {
				Y[n+1]++;
			}
		}
	}
	count = 0;
	for (int i = 0; i <= n; i++) {
		count+=(Y[i]+Y[i+1])/2*(X[i+1]-X[i]);
	}
	Area(count, amount);
	return 0;
}