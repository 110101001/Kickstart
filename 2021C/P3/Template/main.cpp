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

enum {
	S,P,R
};

typedef struct sol {
	double val;
	unsigned char c;
}sol;

sol v[61][61][61];
double W, E;

double dp(int r,int s,int p) {
	if (v[r][s][p].val < 0) {
		int t = r + s + p - 1;
		double valr=0, vals=0, valp=0;
		if (r != 0) {
			valr = dp(r - 1, s, p) + (W * p) / t + (E * s) / t;
		}
		if (s != 0) {
			vals = dp(r, s-1, p) + (W * r) / t + (E * p) / t;
		}
		if (p != 0) {
			valp = dp(r , s, p-1) + (W * s) / t + (E * r) / t;
		}
		if (valr > vals && valr > valp) {
			v[r][s][p].val = valr;
			v[r][s][p].c = R;
		}
		else if (vals > valp) {
			v[r][s][p].val = vals;
			v[r][s][p].c = S;
		}
		else {
			v[r][s][p].val = valp;
			v[r][s][p].c = P;
		}
	}
	return v[r][s][p].val;
}

void dp_init() {
	for (int r = 0; r < 61; r++) {
		for (int s = 0; s < 61; s++) {
			for (int p = 0; p < 61; p++) {
				v[r][s][p].val = -1;
			}
		}
	}
	v[1][0][0].val = W / 3 + E / 3;
	v[1][0][0].c = R;
	v[0][1][0].val = W / 3 + E / 3;
	v[0][1][0].c = S;
	v[0][0][1].val = W / 3 + E / 3;
	v[0][0][1].c = P;
}

void search(int* r, int* s, int* p) {
	double best=0;
	for (int i = 0; i <= 60; i++) {
		for (int j = 0; j < 60 - i; j++) {
			int k = 60 - i - j;
			double res = dp(i, j, k);
			if (best < res) {
				*r = i;
				*s = j;
				*p = k;
				best = res;
			}
		}
	}
}

void rev(int r,int s,int p,char *seq) {
	for (int i = 59; i >= 0; i--) {
		switch (v[r][s][p].c) {
		case R:
			seq[i] = 'R';
			r--;
			break;
		case S:
			seq[i] = 'S';
			s--;
			break;
		case P:
			seq[i] = 'P';
			p--;
			break;
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
		int r, s, p;
		char ans[61];
		ans[60] = 0;
		cin >> W >> E;
		dp_init();
		search(&r,&s,&p);
		rev(r, s, p, ans);

		cout << "Case #" << case_count << ": " << ans << endl;

		cout << endl;
	}
}