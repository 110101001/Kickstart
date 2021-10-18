#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {int tempVar = (x); (x) = (y) ; (y) = tempVar;}

#define LC(a) ((a+1)*2-1)
#define RC(a) ((a+1)*2)

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int n;
		int x,y;
		int left,right;
		cin>>n;
		vector<vector<int>> fur(2,vector<int>(2*n));
		for(int i=0;i<n;i++){
			cin>>fur[0][2*i]>>fur[1][2*i]>>fur[0][2*i+1]>>fur[1][2*i+1];
		}
		nth_element(fur[0].begin(),fur[0].begin()+n-1,fur[0].end());
		nth_element(fur[1].begin(),fur[1].begin()+n-1,fur[1].end());
		x=fur[0][n-1];
		y=fur[1][n-1];
		cout << "Case #" << case_count << ": " << x<<" "<< y<<endl;
	}
}