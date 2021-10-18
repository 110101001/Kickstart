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
		int n,k,inf,ans;
		cin>>n>>k;
		ans=inf=n+1;
		vector<int> tree(n);
		vector<int> best(k+1,inf);
		best[0]=0;
		for(int i=0;i<n;i++){
			cin >> tree[i];
		}
		for(int i=n-1;i>=0;i--){
			int preSum=0;
			for(int j=i;j>=0;j--){
				preSum+=tree[j];
				if(preSum > k){
					break;
				}
				ans=MIN(ans,i-j+1+best[k-preSum]);	
			}
			preSum=0;
			for(int j=i+1;j<n;j++){
				preSum+=tree[j];
				if(preSum > k){
					break;
				}
				best[preSum]=MIN(best[preSum],j-i);
			}
		}
		if(ans ==inf) ans = -1;
		cout << "Case #" << case_count << ": " << ans<<endl;
	}
}
