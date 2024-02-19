#pragma warning(disable:4996)
#include <stdio.h>

int main(){
	int n, k, j,s;
	float r, m, i;
	float x[100], y[100],z[100];
	printf("请输入值个数\n");
	scanf("%d", &n);
	for (k = 0; k < n; k++) {
		printf("请输入第%d个x值\n", k + 1);
		scanf("%f", &x[k]);
		printf("请输入第%d个y值\n", k + 1);
		scanf("%f", &y[k]);
	}
	while (1) {
		printf("请输入需插值的x\n");
		scanf_s("%f", &r);
		i = y[0];
		m = 1;
		for (j = 0; j < n; j++) {
			z[j] = (y[j + 1] - y[j]) / (x[j + 1] - x[j]);
		}
		for (j = 1; j < n; j++) {
				for (s = n-2; s >=j; s--) {
					z[s] = (z[s - 1] - z[s]) / (x[s - j] - x[s+1]);
				}
		}
		for (k = 1; k < n; k++) {
			m = 1;
			for (j = 0; j < k; j++) {
				if (j != k) {
					m = m*(r - x[j]);
				}
			}
			i += m * z[k-1];
		}
		printf("%f\n", i);
	}
}
