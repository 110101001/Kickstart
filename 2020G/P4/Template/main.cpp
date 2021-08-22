#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iomanip>

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#define MAX(x, y) ((x > y) ? (x) : (y))
#define MIN(x, y) ((x < y) ? (x) : (y))
#define SWAP(x, y)                 \
	{                          \
		int tempVar = (x); \
		(x) = (y);         \
		(y) = tempVar;     \
	}

#define MAX_SIZE 5002

using namespace std;

long double cnt[MAX_SIZE][MAX_SIZE];

long double get_count(int n, int i)
{
	if (cnt[n][i] < 1)
	{
		cnt[n][i] = 0;
		if (i > 0)
		{
			cnt[n][i] += i * get_count(n - 1, i - 1) + 1;
		}
		if (i < n - 1)
		{
			cnt[n][i] += (n - i - 1) * get_count(n - 1, i) + 1;
		}
		cnt[n][i] /= n - 1;
	}
	return cnt[n][i];
}

long double solve()
{
	int n;
	long double sum = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int v;
		cin >> v;
		sum += v * get_count(n, i);
	}
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number; //total number of case
	cin >> case_number;
	cnt[2][0] = 1;
	cnt[2][1] = 1;
	for (int case_count = 1; case_count <= case_number; case_count++)
	{
		cout << "Case #" << case_count << ": " <<setprecision(9)<< solve() << endl;
	}
}