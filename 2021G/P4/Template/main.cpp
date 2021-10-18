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
		int n,a;
		cin>>n>>a;
		vector<int[2]> pts(n);
		if(a < n-2){
			cout << "Case #" << case_count << ": " <<"IMPOSSIBLE"<< endl;
			continue;
		}
		pts[0][0]=0;
		pts[0][1]=0;
		for(int i=1;i<n/2;i++){
			pts[i][0]=1-pts[i-1][0];
			pts[i][1]=1+pts[i-1][1];
		}
		pts[n-1][0]=1;
		pts[n-1][1]=0;

		for(int i=n-2;i>=n/2;i--){
			pts[i][0]=3-pts[i+1][0];
			pts[i][1]=1+pts[i+1][1];
		}
		pts[n-1][0]+=a-n+2;
		cout << "Case #" << case_count << ": "<<"POSSIBLE" << endl;
		for(int i=0;i<n;i++){
			cout<<pts[i][0]<<" "<<pts[i][1]<<endl;
		}
	}
}