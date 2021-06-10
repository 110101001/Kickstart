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
		int N;
		long long max=0;
		cin>>N;

		vector<long long> c(2*N -1);
		for(int i=0;i<N;i++){
			for(int j=0;j< N;j++){
				int coin;
				cin >> coin;
				c[N-1 + i - j]+=coin;
			}
		}

		for(long long value : c){
			if(value > max){
				max = value;
			}
		}
		cout << "Case #" << case_count << ": "<<max << endl;
	}
}