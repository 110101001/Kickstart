#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;
	for (int c = 1; c <= N; c++) {
		long long n, k, s;
		long long res;
		cin >> n >> k >> s;
		if (k - s < s) {
			res = n + (k - s) + (k - s);
		} else {
			res = n + k;
		}
		cout << "Case #" << c << ": " << res << endl;
	}
	return 0;
}