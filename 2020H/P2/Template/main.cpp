#include <iostream>

using namespace std;

long long pow5[19];


void splitDigit(long long b, int *d, int *k) {
	int i = 0;
	while (b != 0) {
		d[i] = b % 10;
		b /= 10;
		i++;
	}
	*k = i;
	return;
}

long long borings(int *d, int k, int e) {
	long long sum = 0;
	if (1 == e) {
		sum += ((d[k - 1] + 1) / 2) * pow5[k - 1];
	} else {
		sum += (d[k - 1] / 2) * pow5[k - 1];
	}
	if (k != 1 && d[k - 1] % 2 != e) {
		sum += borings(d, k - 1, 1 - e);
	}
	return sum;
}

int main() {
	int n;
	cin >> n;
	pow5[0] = 1;
	for (int i = 1; i < 19; i++) {
		pow5[i] = 5 * pow5[i - 1];
	}
	for (int c = 1; c <= n; c++) {
		long long L, R, Lres, Rres;
		int k;
		int d[20];
		cin >> L >> R;
		splitDigit(R + 1, d, &k);
		Rres = borings(d, k, 0);
		Rres += 5 * (pow5[k - 1] - 1) / 4;
		splitDigit(L, d, &k);
		Lres = borings(d, k, 0);
		Lres += 5 * (pow5[k - 1] - 1) / 4;
		cout << "Case #" << c << ": " << Rres - Lres << endl;
	}

	return 0;
}