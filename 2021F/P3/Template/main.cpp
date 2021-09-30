#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <iomanip>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {int tempVar = (x); (x) = (y) ; (y) = tempVar;}

using namespace std;

typedef struct vec{
	double angel;
	int x,y;
}vec;

bool cmp(const vec &a,const vec&b){
	return a.angel < b.angel;	
}

double len(int x,int y){
	return sqrt(x*x+y*y);
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int N;
		double min = 10E9+1;
		cin>>N;
		N++;
		vector<int> x(N);
		vector<int> y(N);
		vector<vec> v(N-1);
		for(int i = 0;i<N;i++){
			cin>>x[i]>>y[i];
		}
		for(int i =0;i<N-1;i++){
			v[i].x=x[i]-x[N-1];
			v[i].y=y[i]-y[N-1];
			if(v[i].x == 0){
				v[i].angel = v[i].y>0?M_PI/2:-M_PI/2;
			}
			else{
				v[i].angel =atan(((double)v[i].y)/((double)v[i].x));
			}
			if(v[i].x < 0){
				v[i].angel = M_PI + v[i].angel;
			}
		}			
		sort(v.begin(),v.end(),cmp);

		for(int i=0;i<N-1 && v[i].angel < M_PI/2;i++){
			for(int j=i+1;j<N-1 && v[j].angel <= v[i].angel + M_PI;j++){
				if(v[i].x*v[j].y - v[j].x*v[i].y == 0){
					continue;
				}
				vec tmp = {v[i].angel + M_PI, 0, 0};
				auto k = lower_bound(v.begin(), v.end(), tmp, cmp);
				for (; k != v.end() && k->angel <= v[j].angel + M_PI; k++)
				{
					if (k->x * v[j].y - v[j].x * k->y == 0)
					{
						continue;
					}
					for (auto u = k + 1; u != v.end() && u->angel <= v[j].angel + M_PI; u++)
					{
						if (v[i].x * u->y - u->x * v[i].y == 0)
						{
							continue;
						}
						if (u->x * k->y - k->x * u->y == 0)
						{
							continue;
						}
						double total = len(k->x - u->x, k->y - u->y);
						total += len(u->x - v[i].x, u->y - v[i].y);
						total += len(k->x - v[j].x, k->y - v[j].y);
						total += len(v[j].x - v[i].x, v[j].y - v[i].y);
						min = MIN(total, min);
					}
					if (v[i].x * k->y - k->x * v[i].y == 0)
					{
						continue;
					}
					double total = len(k->x - v[i].x, k->y - v[i].y);
					total += len(k->x - v[j].x, k->y - v[j].y);
					total += len(v[j].x - v[i].x, v[j].y - v[i].y);
					min = MIN(total,min);
				}
			}
		}
		if(min>10E9){
			cout << "Case #" << case_count << ": IMPOSSIBLE" <<endl;
		}
		else{
			cout << "Case #" << case_count << ": "<<setprecision(8) << min <<endl;
		}
	}
}