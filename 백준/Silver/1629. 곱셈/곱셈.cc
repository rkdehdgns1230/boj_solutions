#include <stdio.h>

int pow(int, int, int);

int main() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	printf("%d\n", pow(a, b, c));
	return 0;
}

int pow(int a, int b, int c) {
	if (b == 0)
		return 1;
	long long n = pow(a, b / 2, c);	//a**b
	long long tmp = (n * n) % c;

	if (b % 2 == 0)
		return tmp;
	else
		return (tmp * a) % c;
}