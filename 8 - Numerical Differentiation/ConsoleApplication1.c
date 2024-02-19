#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
#define Pi 3.1415926535897932384626

double f14(double x) {
	return (1 + x + x * x)*cos(x);
}

double f18(double x) {
	return (4 / (1 + x * x));
}

double f26derivative(double x) {
	return -(2 / pow((1+x),3));
}

int main(){
	double tmp[33];
	double sum=0,sum1=0;
	for (int i = 0; i <= 32; i++) {
		tmp[i] = f14(Pi / 64 * i);
		if (i != 0) {
			sum +=(tmp[i - 1] + tmp[i])* Pi / 128;
			if (i % 2 == 0) {
				sum1 += (tmp[i - 2] + tmp[i]) * Pi / 64;
			}
		}
	}
	sum1 = sum * 4 / 3 - sum1 / 3;
	printf("14题答案为：%.6lf\n", sum);
	printf("14题龙贝格加速答案为：%.6lf\n", sum1);
	double fx[3] = {0.25, 0.2268, 0.2066};
	tmp[0] = f18(-sqrt((double)3 / 5))* 5 / 9;
	tmp[1] = f18((double)0)* 8 / 9;
	tmp[2] = f18(sqrt((double)3 / 5))* 5 / 9;
	printf("18题答案为：%.6lf\n", (tmp[0] + tmp[1] + tmp[2]) / 2);
	tmp[0] = (fx[0] * (-3) + fx[1] * 4 - fx[2]) / (2 * 0.1);
	tmp[1] = (fx[2] - fx[0]) / (2 * 0.1);
	tmp[2] = (fx[0] - fx[1] * 4 + fx[2] * 3) / (2 * 0.1);
	printf("26题答案为：%.6lf %.6lf %.6lf\n", tmp[0], tmp[1], tmp[2]);
	printf("26题绝对误差为：%.6lf %.6lf %.6lf\n", -(f26derivative(1.0)-tmp[0]), -(f26derivative(1.1) - tmp[1]), -(f26derivative(1.2) - tmp[2]));
	printf("26题相对误差为：%.6lf %.6lf %.6lf\n", -(f26derivative(1.0) - tmp[0])/ f26derivative(1.0), -(f26derivative(1.1) - tmp[1])/ f26derivative(1.1), -(f26derivative(1.2) - tmp[2])/ f26derivative(1.2));
}
