#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

using namespace std;

unsigned int find(vector<unsigned int>& list, int l, int r, unsigned int x) {
	if (r - l == 0 || r - l == 1) {
		if (list[r] == x) {
			return r;
		}
		return l;
	}

	if (x > list[(l + r) >> 1]) {
		return find(list, (l + r) >> 1, r, x);
	}
	else {
		return find(list, l, (l + r) >> 1, x);
	}
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;
	vector<bool> np(1E5 + 1, false);
	vector<unsigned int> primes;
	for (unsigned int i = 2; i <= 1E5; i++) {
		if (!np[i]) {
			primes.push_back(i);
		}
		for (unsigned int k : primes) {
			if (k * i > 1E5) {
				break;
			}
			np[k * i] = true;
			if (0 == i % k) {
				break;
			}
		}
	}

	for (int case_count = 1; case_count <= case_number; case_count++) {
		unsigned long long Z;
		unsigned long long res;
		unsigned int Zsqrt;
		int index;

		cin >> Z;
		Zsqrt = sqrt(Z);
		index = find(primes, 0, primes.size() - 1, Zsqrt);

		res = primes[index] * primes[index + 1];
		if (res > Z) {

			res = primes[index - 1] * primes[index];
		}

		cout << "Case #" << case_count << ": " << res << endl;
	}
}