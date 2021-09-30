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

typedef struct attr{
	int hap;
	int days;
	int daye;
}attr;

bool cmp(const attr &a,const attr &b){
	return a.hap>b.hap;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int D,N,K;
		long long max = 0;
		cin>>D>>N>>K;
		vector<long long> haps(D);
		vector<int> rides(D,0);
		vector<attr> attrs(N);
		for(int i =0;i<N;i++){
			cin>>attrs[i].hap>>attrs[i].days>>attrs[i].daye;
		}
		sort(attrs.begin(),attrs.end(),cmp);

		for(int i=0;i<N;i++){
			auto cur_attr=attrs[i];
			for(int j=cur_attr.days-1;j<=cur_attr.daye-1;j++){
				if(rides[j]<K){
					rides[j]++;
					haps[j] += cur_attr.hap;
				}
			}
		}

		for(int i=0;i<D;i++){
			max = MAX(max,haps[i]);
		}
		cout << "Case #" << case_count << ": " <<max<< endl;
	}
}