#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		string str;
		int N, K;
		cin >> N >> K;
		cin >> str;
		for (int i = 0; i < N / 2; i++) {
			if (str[i] != str[N - i - 1]) {
				K--;
			}
		}

		cout << "Case #" << case_count << ": " << ABS(K);
		cout << endl;
	}
}