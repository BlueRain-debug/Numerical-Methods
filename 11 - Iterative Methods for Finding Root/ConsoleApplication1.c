#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
#define pai 3.14159265358979
#define x0 pai/4
#define x1 pai/2
#define min 0.00001
#define e 2.718281828459045
#define f(x) cos(x)*4-pow(e,x)
#define fp(x) -sin(x)*4-pow(e,x)

int main() {
	printf("求解方程4cosx=e^x的正根\n");
	double currentx=x0;
	currentx = 1;
	for (; fabs(f(currentx)) >= min * min;) {
		currentx = currentx - (f(currentx)) * (currentx - x0) / (f(currentx) - f(x0));
	}
	double high = currentx;
	printf("牛顿法（高精度）：%.10lf\n", high);
	currentx = x0;
	for (; fabs(f(currentx)) >= min;) {
			currentx = currentx-(f(currentx)) / (fp(currentx));
	}
	printf("牛顿法：%.10lf\n", currentx);
	printf("ε=%.10lf\n", fabs(currentx-high));
	currentx = 1;
	for (; fabs(f(currentx)) >= min;) {
		currentx = currentx - (f(currentx)) * (currentx - x0) / (f(currentx) - f(x0));
	}
	printf("弦截法：%.10lf\n", currentx);
	printf("ε=%.10lf\n", fabs(currentx - high));
	double prevx = x0;
	currentx = x1;
	for (; fabs(f(currentx)) >= min;) {
		currentx = currentx - (f(currentx))*(currentx-prevx) / (f(currentx)-f(prevx));
	}
	printf("快速弦截法：%.10lf\n", currentx);
	printf("ε=%.10lf\n", fabs(currentx - high));
}