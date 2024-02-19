#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define comp 0.00001
#define firsth 0.125
#define finalx 6
double firstz = (double)0;

double f(double xi, double yi, double zi) {
	return yi*yi*yi*2;
}

double process_L1(double xi, double yi, double zi) {
	return f(xi, yi, zi);
}

double process_L2(double xi, double yi, double zi, double h) {
	return f(xi+h/2, yi+h/2*zi, zi+h/2* process_L1(xi, yi, zi));
}

double process_L3(double xi, double yi, double zi, double h) {
	return f(xi+h/2, yi + h / 2 * zi+h*h/4* process_L1(xi, yi, zi), zi + h / 2 * process_L2(xi, yi, zi, h));
}

double process_L4(double xi, double yi, double zi, double h) {
	return f(xi+h, yi + h * zi + h * h / 2 * process_L2(xi, yi, zi, h), zi+h* process_L3(xi, yi, zi, h));
}

double y(double xi, double yi, double zi, double h) {
	return yi + h * zi+h*h/6*(process_L1(xi, yi, zi) + process_L2(xi, yi, zi, h) + process_L3(xi, yi, zi, h));
}

double z(double xi, double yi, double zi, double h) {
	return zi + h / 6 * (process_L1(xi, yi,zi) + 2 * process_L2(xi, yi, zi, h) + 2 * process_L3(xi, yi, zi, h) + process_L4(xi, yi, zi, h));
}

int main()
{
	double y_1, y_2;
	double currenth = firsth;
	double currentx=3, currenty=1,currentz=0;
	double latesterror=10000;
	double targety[4];
	int flag_1=0,flag_2=0;
	double latestz=currentz;
	while (1) {
		latestz -= 0.05;
		currentx = 3, currenty = 1, currentz = latestz;
		while (1) {
			//printf("%.12lf %.12lf %.12lf %.12lf %.12lf\n", currentx, currenty, currentz, (double)1 / (currentx - 2), (double)(-1) / (currentx - 2) / (currentx - 2));
			if (currentx + currenth >= finalx) {
				currenth = finalx - currentx;
				y_1 = y(currentx, currenty, currentz, currenth);
				currentz = z(currentx, currenty, currentz, currenth);
				currenty = y_1;
				break;
			}
			if (currentz >= 100)break;
			while (1) {
				y_1 = y(currentx, currenty, currentz, currenth);
				y_2 = y(currentx, currenty, currentz, currenth / 2);
				if ((y_1 - y_2 > comp) || (y_1 - y_2 < -comp)) {
					if (flag_2 == 1) {
						currentz = z(currentx, currenty, currentz, currenth / 2);
						currenty = y_2;
						currentx += currenth / 2;
						flag_2 = 0;
						break;
					}
					currenth = currenth / 2;
					flag_1 = 1;
				}
				else {
					if (flag_1 == 1) {
						currentz = z(currentx, currenty, currentz, currenth);
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
		if (latesterror <= comp) {
			latestz += 0.05;
			break;
		}
		latesterror = currenty - 0.25;
	}
	currentz = latestz;
	targety[0] = 1;
	for (int i = 1; i < 4; i++) {
		currentx = 2+i, currenty = targety[i-1];
		while (1) {
			//printf("%.12lf %.12lf %.12lf %.12lf %.12lf\n", currentx, currenty, currentz, (double)1 / (currentx - 2), (double)(-1) / (currentx - 2) / (currentx - 2));
			if (currentx + currenth >= 3+i) {
				currenth = 3+i - currentx;
				y_1 = y(currentx, currenty, currentz, currenth);
				currentz = z(currentx, currenty, currentz, currenth);
				currenty = y_1;
				break;
			}
			if (currentz >= 100)break;
			while (1) {
				y_1 = y(currentx, currenty, currentz, currenth);
				y_2 = y(currentx, currenty, currentz, currenth / 2);
				if ((y_1 - y_2 > comp) || (y_1 - y_2 < -comp)) {
					if (flag_2 == 1) {
						currentz = z(currentx, currenty, currentz, currenth / 2);
						currenty = y_2;
						currentx += currenth / 2;
						flag_2 = 0;
						break;
					}
					currenth = currenth / 2;
					flag_1 = 1;
				}
				else {
					if (flag_1 == 1) {
						currentz = z(currentx, currenty, currentz, currenth);
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
		targety[i] = currenty;
	}
	printf("z(3)近似解：%.16lf\n\n", latestz);
	for (int i = 3; i <= 6; i++) {
		printf("y(%d)近似解：%.16lf\ny(%d)精确解：%.16lf\n", i,targety[i-3], i, (double)1 / (i - 2));
		printf("y(%d)绝对误差：%.16lf\n\n",i, targety[i - 3] - (double)1 / (i - 2));
	}
}
