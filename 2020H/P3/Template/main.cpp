#include <iostream>
#include <vector>
#include <algorithm>

#define ABS(x,y) (x>y)?(x-y):(y-x)

using namespace std;

vector<int> arrayx;
vector<int> arrayy;

int main() {
	int n;
	cin >> n;
	for (int c = 1; c <= n; c++) {
		int count, xstart;
		long long step = 0;

		cin >> count;

		for (int i = 0; i < count; i++) {
			int x, y;
			cin >> x >> y;
			arrayx.push_back(x);
			arrayy.push_back(y);
		}

		nth_element(arrayy.begin(), arrayy.begin() + count / 2, arrayy.end());

		for (int i = 0; i < count; i++) {
			step += ABS(arrayy[i], arrayy[count / 2]);
		}

		sort(arrayx.begin(), arrayx.end());

		if (count % 2 == 0) {
			xstart = arrayx[(count / 2) - 1];
		} else {
			xstart = arrayx[count / 2] - count / 2;
		}


		for (int i = 0; i < count; i++) {
			step += ABS(arrayx[i], xstart);
			xstart++;
		}

		cout << "Case #" << c << ": " << step << endl;
		arrayx.clear();
		arrayy.clear();
	}


	return 0;
}