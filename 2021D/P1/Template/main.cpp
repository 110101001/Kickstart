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
		int arr[3][3];
		cin>>arr[0][0]>>arr[0][1]>>arr[0][2];
		cin >> arr[1][0] >> arr[1][2];
		cin >> arr[2][0] >> arr[2][1] >> arr[2][2];
		int res[4], tmp[4][2];
		bool valid[4]={true,true,true,true};
		res[0] = (arr[1][0] + arr[1][2]) / 2;
		if(2*res[0] != arr[1][0]+arr[1][2]){
			valid[0]=false;
		}
		res[1] = (arr[0][0] + arr[2][2]) / 2;
		if(2*res[1] != arr[0][0]+arr[2][2]){
			valid[1]=false;
		}
		res[2] = (arr[0][1] + arr[2][1]) / 2;
		if(2*res[2] != arr[0][1]+arr[2][1]){
			valid[2]=false;
		}
		res[3] = (arr[0][2] + arr[2][0]) / 2;
		if(2*res[3] != arr[0][2]+arr[2][0]){
			valid[3]=false;
		}
		for (int i = 0; i < 4; i++)
		{
			tmp[i][0] = 0;
			tmp[i][1] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			if(valid[i] == false){
				continue;
			}
			tmp[i][0]=res[i];
			tmp[i][1]=1;
			for(int j=0;j<i;j++){
				if(res[i] == tmp[j][0]){
					tmp[j][1]++;
					break;	
				}
			}
		}
		int max=0;
		for(int i=0;i<4;i++){
			max = MAX(max,tmp[i][1]);
		}
		if(arr[0][0]+arr[0][2]==2*arr[0][1]){
			max++;
		}
		if(arr[0][0]+arr[2][0]==2*arr[1][0]){
			max++;
		}
		if(arr[0][2]+arr[2][2]==2*arr[1][2]){
			max++;
		}
		if(arr[2][0]+arr[2][2]==2*arr[2][1]){
			max++;
		}
		cout << "Case #" << case_count << ": " <<max<< endl;
	}
}