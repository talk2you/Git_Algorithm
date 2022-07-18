#include <stdio.h>
#include <string.h>

long long h[100000] = { 0, };

long long max(long long a, long long b) {
	return a > b ? a : b;
}
long long min(long long a, long long b) {
	return a < b ? a : b;
}

long long cal(int l, int r) {
	if (l == r) return h[l];

	int mid = (l + r) / 2;
	long long ans = max(cal(l, mid), cal(mid + 1, r));
	int a = mid, b = mid;
	long long height = h[mid];


	while (l < a || b < r) {
		if (l < a && (b == r || h[a - 1] > h[b + 1])) {
			a--;
			height = min(height, h[a]);
		}
		else {
			b++;
			height = min(height, h[b]);
		}
		ans = max(ans, height * (b - a + 1));
	}
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	while (n != 0) {
		for (int i = 0; i < n; i++) {
			scanf("%lld", &h[i]);
		}
		printf("%lld\n", cal(0, n - 1));
		scanf("%d", &n);
	}
}