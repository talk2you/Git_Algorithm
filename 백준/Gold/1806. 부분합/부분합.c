#include <stdio.h>

#define MAX_ARR 100000
#define min(x,y) x < y ? x : y

int main() {
	int n, s;
	int arr[MAX_ARR];
	scanf("%d %d", &n, &s);
	for (int i = 0; i < n; ++i) {
		scanf("%d ", &arr[i]);
	}

	int low = 0;
	int high = 0;
	int sum = arr[0];
	int len = n + 1;

	while (low <= high && high < n) {
		if (sum < s) {
			sum += arr[++high];
		}
		else {
			len = min(len, high - low + 1);
			sum -= arr[low++];
		}
	}

	if (len == n + 1) len = 0;
	printf("%d\n", len);

	return 0;
}