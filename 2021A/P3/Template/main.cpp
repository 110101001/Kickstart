#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int R, C;
		long long sum = 0;
		cin >> R >> C;
		vector<vector<int>> grid(R, vector<int>(C));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> grid[i][j];
				sum -= grid[i][j];
			}
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				for (int k = 0; k < j; k++) {
					grid[i][j] = MAX(grid[i][j], grid[i][k] - j + k);
				}
				for (int k = j + 1; k < C; k++) {
					grid[i][j] = MAX(grid[i][j], grid[i][k] - k + j);
				}
			}
		}

		for (int i = 0; i < C; i++) {
			for (int j = 0; j < R; j++) {
				for (int k = 0; k < j; k++) {
					grid[j][i] = MAX(grid[j][i], grid[k][i] - j + k);
				}
				for (int k = j + 1; k < R; k++) {
					grid[j][i] = MAX(grid[j][i], grid[k][i] - k + j);
				}
			}
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				sum += grid[i][j];
			}
		}

		cout << "Case #" << case_count << ": " <<sum << endl;
	}
}