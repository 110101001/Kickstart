#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#define MAX(x, y) ((x > y) ? (x) : (y))
#define MIN(x, y) ((x < y) ? (x) : (y))
#define SWAP(x, y)                 \
	{                          \
		int tempVar = (x); \
		(x) = (y);         \
		(y) = tempVar;     \
	}

using namespace std;

struct status
{
	char v;
	bool isRep;
	unsigned int x : 10;
	unsigned int y : 10;
};

void merge_status(vector<vector<status>> &s, int y1, int x1, int y2, int x2)
{
	while (s[x1][y1].isRep == false)
	{
		int tmpx, tmpy;
		tmpx = s[x1][y1].x;
		tmpy = s[x1][y1].y;
		x1 = tmpx;
		y1 = tmpy;
	}
	while (s[x2][y2].isRep == false)
	{
		int tmpx, tmpy;
		tmpx = s[x2][y2].x;
		tmpy = s[x2][y2].y;
		x2 = tmpx;
		y2 = tmpy;
	}
	if((x1 == x2 )&&( y1 == y2)){
		return;
	}
	s[x2][y2].x = x1;
	s[x2][y2].y = y1;
	s[x2][y2].isRep = false;
	if (s[x2][y2].v != 0 && s[x2][y2].v != '.')
	{
		s[x1][y1].v = s[x2][y2].v;
	}
	return;
}

char lookup_status(vector<vector<status>> &s, int x, int y)
{
	int count = 0;
	int xb = x, yb = y;
	while (s[x][y].isRep == false)
	{
		int tmpx, tmpy;
		tmpx = s[x][y].x;
		tmpy = s[x][y].y;
		x = tmpx;
		y = tmpy;
		count++;
	}
	return s[x][y].v;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number; //total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++)
	{
		int n, m, sum = 0;
		cin >> n >> m;
		vector<vector<struct status>> sts(n, vector<struct status>(m));

		vector<int> starty(m, -1);
		for (int i = 0; i < n; i++)
		{
			int startx = -1;
			int ind = 0;
			for (int j = 0; j < m; j++)
			{
				char in;
				cin >> in;
				sts[i][j].isRep = true;
				sts[i][j].v = in;
				switch (in)
				{
				case '#':
					if (startx != -1)
					{ // a segment
						for (int k = startx; k < (startx + j) / 2; k++)
						{
							merge_status(sts, k, i, (j - 1) - (k - startx), i);
						}
					}
					startx = -1;
					if (starty[j] != -1)
					{
						for (int k = starty[j]; k < (starty[j] + i) / 2; k++)
						{
							merge_status(sts, j, k, j, (i - 1) - (k - starty[j]));
						}
					}
					starty[j] = -1;
					break;
				case '.':
					if (startx == -1)
					{
						startx = j;
					}
					if (starty[j] == -1)
					{
						starty[j] = i;
					}
					break;
				default:
					if (startx == -1)
					{
						startx = j;
					}
					if (starty[j] == -1)
					{
						starty[j] = i;
					}

					sum--;
					break;
				}
				ind++;
			}
			if (startx != -1)
			{ // a segment that ends at edge
				for (int k = startx; k < (startx + m) / 2; k++)
				{
					merge_status(sts, k, i, (m - 1) - (k - startx), i);
				}
			}
		}
		for (int j = 0; j < m; j++)
		{

			if (starty[j] != -1)
			{
				for (int k = starty[j]; k < (starty[j] + n) / 2; k++)
				{
					merge_status(sts, j, k, j, (n - 1) - (k - starty[j]));
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				sts[i][j].v = lookup_status(sts, i, j);
				if (sts[i][j].v != '#' && sts[i][j].v != '.')
				{
					sum++;
				}
			}
		}

		cout << "Case #" << case_count << ": " << sum << endl;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << sts[i][j].v;
			}
			cout<<endl;
		}


	}
}