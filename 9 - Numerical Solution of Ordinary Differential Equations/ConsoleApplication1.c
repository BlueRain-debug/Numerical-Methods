#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define comp 0.0001
#define firsth 0.5
#define finalx 2
#define euler 2.718281828459045235360287471352

double f(double xi, double yi) {
	return - yi + xi + 1;
}

double process_K1(double xi, double yi) {
	return f(xi, yi);
}

double process_K2(double xi, double yi, double h) {
	return f(xi + h / 2, yi + h / 2 * process_K1(xi, yi));
}

double process_K3(double xi, double yi, double h) {
	return f(xi + h / 2, yi + h / 2 * process_K2(xi, yi, h));
}

double process_K4(double xi, double yi, double h) {
	return f(xi + h, yi + h * process_K3(xi, yi, h));
}

double y(double xi, double yi, double h) {
	return yi + h / 6 * (process_K1(xi, yi)+ 2 * process_K2(xi, yi, h)+ 2 * process_K3(xi, yi, h)+ process_K4(xi, yi, h));
}

int main()
{
	double y_1, y_2;
	double currenth = firsth;
	double currentx=0, currenty=1;
	int flag_1=0,flag_2=0;
	while(1) {
		printf("%.12lf %.12lf\n", currentx, currenty);
		if (currentx + currenth >= finalx) {
			currenth = finalx - currentx;
			currenty = y(currentx, currenty, currenth);
			break;
		}
		while (1) {
			y_1 = y(currentx, currenty, currenth);
			y_2 = y(currentx, currenty, currenth/2);
			if ((y_1 - y_2 > comp)||(y_1 - y_2 < -comp)) {
				if (flag_2 == 1) {
					currenty=y_2;
					currentx += currenth/2;
					flag_2 = 0;
					break;
				}
				currenth = currenth / 2;
				flag_1 = 1;
			}
			else {
				if (flag_1 == 1) {
					currenty = y_1;
					currentx += currenth;
					flag_1 = 0;
					break;
				}
				currenth = currenth * 2;
				flag_2 = 1;
			}
		}
	}
	printf("近似解：%.16lf\n", currenty);
	printf("精确解：%.16lf\n", finalx + pow(euler, -finalx));
	printf("绝对误差：%.16lf\n", currenty - (finalx + pow(euler, -finalx)));

}
