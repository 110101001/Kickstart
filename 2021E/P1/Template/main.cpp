#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <queue>

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#define MAX(x, y) ((x > y) ? (x) : (y))
#define MIN(x, y) ((x < y) ? (x) : (y))
#define SWAP(x, y)                  \
	{                           \
		char tempVar = (x); \
		(x) = (y);          \
		(y) = tempVar;      \
	}

using namespace std;

typedef struct s
{
	char v;
	int index;
} s;

bool cmp(const s &a, const s &b)
{
	return a.v < b.v;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number; //total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++)
	{
		vector<int> cnt(26, 0);
		string str;
		bool flag = false;
		cin >> str;
		vector<s> arr(str.size());

		for (int i = 0; i < str.size(); i++)
		{
			arr[i].v = str[i];
			arr[i].index = i;
		}

		sort(arr.begin(), arr.end(), cmp);

		for (auto c : str)
		{
			cnt[c - 'a']++;
		}
		for (int i = 0; i < 26; i++)
		{
			if (cnt[i] > arr.size() / 2)
			{
				flag = true;
			}
		}
		if (flag)
		{
			cout << "Case #" << case_count << ": IMPOSSIBLE" << endl;
		}
		else
		{
			for (int i = 0; i < arr.size() / 2; i++)
			{
				str[arr[i + (arr.size() + 1) / 2].index] = arr[i].v;
			}
			for (int i = arr.size() / 2; i < arr.size(); i++)
			{
				str[arr[i - arr.size() / 2].index] = arr[i].v;
			}
			cout << "Case #" << case_count << ": " << str << endl;
		}
	}
}
