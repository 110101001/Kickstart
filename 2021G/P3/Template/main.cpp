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
		int n,k;
		cin>>n>>k;
		int minTree=n+1;
		vector<int> tree(n);
		vector<int> prefix(n+1);
		prefix[0]=0;
		for(int i=0;i<n;i++){
			cin >> tree[i];
			prefix[i+1]=prefix[i]+tree[i];
		}
		for(int s1=0;s1<k;s1++){

		}
		for(int s1=0;s1<n;s1++){
			for(int e1=s1+1;e1<n+1;e1++){
				int diff = k-prefix[e1]+prefix[s1];
				if(diff == 0){
					minTree=MIN(minTree,e1-s1);
				}
				else if(diff < 0){
					break;
				}
				else{
					int s2=e1+1,e2=s2;
					while(e2<n+1){
						if(prefix[e2]-prefix[s2] > diff){
							s2++;
						}
						else if(prefix[e2]-prefix[s2] < diff){
							e2++;
						}
						else{
							minTree=MIN(minTree,e1-s1+e2-s2);
							s2++;
						}
					}
				}
			}
		}
		if(minTree == n+1){
			minTree=-1;
		}
		cout << "Case #" << case_count << ": " << minTree<<endl;
	}
}