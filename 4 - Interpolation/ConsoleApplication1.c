#pragma warning(disable:4996)
#include <stdio.h>

int main(){
	int n, k, j,s;
	float r, m, i;
	float x[100], y[100], yp[100], z[100], a[100], b[100];
	printf("请输入值个数\n");
	scanf("%d", &n);
	for (k = 0; k < n; k++) {
		printf("请输入第%d个x值\n", k + 1);
		scanf("%f", &x[k]);
		printf("请输入第%d个y值\n", k + 1);
		scanf("%f", &y[k]);
		printf("请输入第%d个y'值\n", k + 1);
		scanf("%f", &yp[k]);
	}
	while (1) {
		printf("请输入需插值的x\n");
		scanf_s("%f", &r);
		i = 0;
		m = 1;
		for (j = 0; j < n; j++) {
			z[j] = 1;
			for (k = 0; k < n; k++) {
				if(k!=j)
					z[j] = z[j] * (r - x[k]) / (x[j] - x[k]);
			}
		}
		for (j = 0; j < n; j++) {
			a[j] = 1;
			for (k = 0; k < n; k++) {
				if (k != j)
					a[j] = a[j] + 2 * (x[j]-r)/ (x[j]-x[k]);
			}
			a[j] = a[j] * z[j] * z[j];
		}
		for (j = 0; j < n; j++) {
			b[j] = (r - x[j])*z[j]*z[j];
		}
		for (k = 0; k < n; k++) {
			i += a[k] * y[k] + b[k] * yp[k];
		}
		printf("%f\n", i);
	}
}
