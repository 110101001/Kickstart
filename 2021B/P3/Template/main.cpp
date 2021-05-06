#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

using namespace std;

#define MAX_GAP 282

long long quick_pow(long long x, long long n, long long m) {
	long long res = 1;
	while (n > 0) {
		if (n & 1)	res = res * x % m;
		x = x * x % m;
		n >>= 1;
	}
	return res;
}

bool isPrime(unsigned long long n) {
	unsigned long long a, x;
	unsigned long long d = n - 1;
	int s = 0;
	if (n <= 3)
	{
		return true;
	}
	if (0 != (n + 1) % 6 && 0 != (n - 1) % 6) {
		return false;
	}

	while (!(d & 1)) {
		d = d >> 1;
		s++;
	}

	for (int i = 0; i < 12; i++) {
		a = 1 + (rand() % (n - 2));

		x = quick_pow(a, d, n);
		if (1 == x || n - 1 == x) {
			continue;
		}

		for (int r = 0; r < s - 1; r++) {
			x = x * x % n;
			if (x == n - 1) {
				break;
			}
		}
		if (x == n - 1) {
			continue;
		}
		return false;
	}

	for (unsigned long long i = 2; i * i < n; i++) {
		if (0 == n % i) {
			return false;
		}
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;
	for (int case_count = 1; case_count <= case_number; case_count++) {
		unsigned long long Z, res;
		unsigned long long Zsqrt, s1, s2, l1;

		cin >> Z;
		
		Zsqrt = sqrt(Z);

		for (int i = 1; i <= MAX_GAP; i++) {
			if (isPrime(Zsqrt + i)) {
				l1 = Zsqrt + i;
				break;
			}
		}

		for (int i = 0; i <= MAX_GAP - (l1 - Zsqrt); i++) {
			if (isPrime(Zsqrt - i)) {
				s1 = Zsqrt - i;
				break;
			}
		}

		res = (unsigned long long)l1 * s1;

		if (res > Z) {
			for (int i = 2; i <= MAX_GAP; i++) {
				if (isPrime(s1 - i)) {
					s2 = s1 - i;
					break;
				}
			}

			res = (unsigned long long) s1 * s2;
		}

		cout << "Case #" << case_count << ": " << res << endl;
	}
}
