#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {int tempVar = (x); (x) = (y) ; (y) = tempVar;}

const long long MODL = (1e9 + 7);

using namespace std;

long long pow(long long x, long long n, long long m) {
	long long res = 1;
	while (n > 0) {
		if (n & 1)	res = res * x % m;
		x = x * x % m;
		n >>= 1;
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int N, K;
		long long res = 0;
		int flag = 0;
		string S;
		cin >> N >> K;
		cin >> S;

		for (int i = ((N + 1) / 2) - 1; i >= 0; i--) {
			if (flag != -1 && flag != 2) {
				if (S[i] == S[N - i - 1]) {
					flag = 1;
				}
				else if (S[i] < S[N - i - 1]) {
					flag = 2;
				}
				else {
					flag = -1;
				}
			}
		}
		
		for (int i = 0; i < (N+1) / 2; i++) {
			res = (res + (pow(K, (N + 1) / 2 - i - 1, MODL) * (S[i]-'a'))) % MODL;
		}
		if (flag == 2) {
			res = (res + 1 ) % MODL;
		}

		cout << "Case #" << case_count << ": "<<res << endl;
	}
}