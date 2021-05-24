#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {int tempVar = (x); (x) = (y) ; (y) = tempVar;}

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		long long G;
		long long res=0;
		cin >> G;
		for (long long i = 1; i * i - i < 2 * G; i++) {
			if ((G - (i * (i - 1) / 2)) % i == 0) {
				res += 1;
			}
		}
		cout << "Case #" << case_count << ": " << res << endl;
	}
}