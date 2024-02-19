#pragma warning(disable:4996)
#include <stdio.h>

int main()
{
	int n,k,j;
	float r,m,i;
	float x[100], y[100];
	printf("请输入值个数\n");
	scanf("%d", &n);
	for (k=0;k<n;k++) {
		printf("请输入第%d个x值\n", k + 1);
		scanf("%f", &x[k]);
		printf("请输入第%d个y值\n", k + 1);
		scanf("%f", &y[k]);
	}
	while (1) {
		printf("请输入需插值的x\n");
		scanf_s("%f", &r);
		i = 0;
		for (k = 0; k < n; k++) {
			m = 1;
			for (j = 0; j < n; j++) {
				if (j != k) {
					m = m * (r - x[j]) / (x[k] - x[j]); 
				}
			}
			i+= m * y[k];
		}
		printf("%f\n", i);
	}
}
