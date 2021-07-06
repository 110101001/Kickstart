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

int FindLarger(vector<long long>& nums, long long n)
{
	int left = 0;
	int right = nums.size() - 1;
	while(left < right)
	{
		int middle = (left + right) / 2;
		if(nums[middle] > n)
			right = middle;
		else if(nums[middle] <= n)
			left = middle + 1;
	}
	if(nums[left] > n)
		return left;
	else
		return -1;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int I,N;
		long long min_sum=-1;
		cin>>I>>N;
		vector<long long> k(I);
		vector<long long> sum(I); 
		for(int i= 0;i< I;i++){
			cin>>k[i];
		}
		
		sort(k.begin(),k.end());

		sum[0]=k[0];
		for(int i=1;i<I;i++){
			sum[i]=sum[i-1] + k[i];
		}

		for(int i=0;i<I;i++){
			long long cur_sum=0;
			long long val = (k[i] + N/2 -1)%N +1;
			long long ind = FindLarger(k,val);
			if(ind == -1) ind = I;
			if(ind > i){
				cur_sum += (sum[ind -1] - sum[i]) - k[i] * (ind -1 -i);
				cur_sum += -(sum[I-1]-sum[ind-1]) + (k[i] + N) *(I - ind);
				if(0 != i){
					cur_sum += -sum[i-1] + k[i] * (i);
				}
			}
			else{
				cur_sum += (sum[I -1] - sum[i]) - k[i] * (I -1 -i);
				if(0 != ind){
					cur_sum += sum[ind - 1] + (N - k[i]) * ind;
					cur_sum += -(sum[i - 1] - sum[ind - 1]) + k[i] * (i - ind);
				}
				else if(0 != i){
					cur_sum += -(sum[i - 1]) + k[i] * (i - ind);
				}
			}
			if(min_sum == -1 || cur_sum < min_sum){
				min_sum = cur_sum;
			}
		}

		cout << "Case #" << case_count << ": " <<min_sum<< endl;
	}
}
