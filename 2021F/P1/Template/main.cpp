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
		long long sum=0;
		long len;
		long long lastTrashCan = -1;
		string trash;
		cin>>len;
		cin>>trash;
		for(long long i=0;i<len;i++){
			if(trash[i] == '1'){
				if(lastTrashCan == -1){
					sum+=(i+1)*i/2;
				}
				else{
					long long k = (i-lastTrashCan - 1)/2;
					sum+=(k+1)*(k);
					if((i-lastTrashCan)%2 == 0){
						sum += k+1;
					}
				}
				lastTrashCan = i;
			}
		}	
		long long k = len -1 - lastTrashCan;
		sum+=(k+1)*k/2;
		cout << "Case #" << case_count << ": " <<sum<< endl;
	}
}