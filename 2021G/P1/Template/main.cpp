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
		string line;
		long long N,D,C,M,i;
		bool flag=true;
		cin>>N>>D>>C>>M;
		cin>>line;
		for(i=0;i<line.size();i++){
			if(line[i] == 'C' && C>0){
				C--;
			}
			else if(line[i] == 'D' &&D>0)
			{
				D--;
				C+=M;
			}
			else{
				break;
			}
		}

		for(;i<line.size();i++){
			if(line[i] == 'D'){
				flag = false;
				break;
			}
		}
		if(flag){
		cout << "Case #" << case_count << ": " <<"YES"<< endl;
		}
		else{
		cout << "Case #" << case_count << ": " <<"NO"<< endl;
		}
	}
}