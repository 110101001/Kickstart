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
const string one("PRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRSPRS");
const string zero("PPPPPPPPPPPPPPPPPPPPRRRRRRRRRRRRRRRRRRRRRSSSSSSSSSSSSSSSSSSS");

void calcBest(double W,double E) {
	int bestI=0, maxRes=0;
	for (int i = 0; i < 60; i++) {
		int k = i + 1;
		int p = i + 1, s = 0, r = 0;
		double res=0;
		for (; k < 60; k++) {
			if (W * p / (k) + E * s / (k) < W * r / (k) + E * p / (k) &&
				W * s / (k) + E * r / (k) < W * r / (k) + E * p / (k)) {
				res += W * r / (k) + E * p / (k);
				s++;
			}
			else if (W * s / (k) + E * r / (k) < W * p / (k) + E * s / (k)) {
				res += W * p / (k) + E * s / (k);
				r++;
			}
			else {
				res += W * s / (k) + E * r / (k);
				p++;
			}
		}
		
		if (res > maxRes) {
			bestI = i;
			maxRes = res;
		}
	}
	maxRes += W / 3 + E / 3;
	cout << maxRes << endl;
	int p = 0, s = 0, r = 0;
	for (int i = 0; i < bestI;i++) {
		cout << "P";
		p++;
	}
	for (int i = bestI+1; i <= 60; i++) {
		if (W * p / (i - 1) + E * s / (i - 1) < W * r / (i - 1) + E * p / (i - 1)&&
			W * s / (i - 1) + E * r / (i - 1) < W * r / (i - 1) + E * p / (i - 1)) {
			s++;
			cout << "S";
		}
		else if (W * s / (i - 1) + E * r / (i - 1) < W * p / (i - 1) + E * s / (i - 1)) {
			r++;
			cout << "R";
		}
		else {
			p++;
			cout << "P";
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	int goal;
	cin >> case_number;
	cin >> goal;
	for (int case_count = 1; case_count <= case_number; case_count++) {
		int W, E;
		cin >> W >> E;
		
		cout << "Case #" << case_count << ": ";
		if (E > 0.01) {
			cout << one;
		}
		else {
			cout << zero;
		}
		cout << endl;
	}
}