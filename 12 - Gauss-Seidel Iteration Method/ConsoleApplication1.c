#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>

int main() {
	printf("求解方程组根\n");
	double currentx1=0, currentx2=0, currentx3=0, currentx4=0, currentx5=0, currentx6=0;
	for (int i = 1; i <= 10; i++) {
		currentx1 = (currentx2 + currentx4) / 4;
		currentx2 = (currentx1 + currentx3+currentx5+5) / 4;
		currentx3 = (currentx2 + currentx6) / 4;
		currentx4 = (currentx1 + currentx5+6) / 4;
		currentx5 = (currentx2 + currentx4 + currentx6-2) / 4;
		currentx6 = (currentx3 + currentx5+6) / 4;
	}
	printf("高斯-德赛尔迭代法（迭代10次）\n");
	printf("x1=%.10lf\n", currentx1);
	printf("x2=%.10lf\n", currentx2);
	printf("x3=%.10lf\n", currentx3);
	printf("x4=%.10lf\n", currentx4);
	printf("x5=%.10lf\n", currentx5);
	printf("x6=%.10lf\n", currentx6);
}