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

const string ps = "KICK";
const string pe = "START";

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		string s;
		int i=0,j=0;
		int ps_num = 0;
		long long frags=0;
		cin >> s;
		for (char c : s)
		{
			if (c == ps[i])
			{
				i++;
				if (i == ps.size())
				{
					ps_num++;
					i=1;
				}
			}
			else if(c == ps[0])
			{
				i = 1;
			}
			else{
				i = 0;
			}	
			if (c == pe[j])
			{
				j++;
				if (j == pe.size())
				{
					frags += ps_num;
					j=0;
				}
			}
			else if(c == pe[0])
			{
				j = 1;
			}
			else{
				j = 0;
			}

		}
		cout << "Case #" << case_count << ": " <<frags<< endl;
	}
}