#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

using namespace std;

typedef struct node {
	int u;
	int d;
	int l;
	int r;
} node;

int find_L(int x, int y) {
	if (x <= 1 || y <= 1) {
		return 0;
	}

	return MIN(x / 2, y) + MIN(x, y / 2) - 2;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int R, C;
		long long sum = 0;
		cin >> R >> C;
		vector<vector<int>> grid(R,vector<int>(C));
		vector<vector<node>> nodes(R,vector<node>(C));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> grid[i][j];
			}
		}

		for (int i = 0; i < R; i++) {
			int len = 0;
			for (int j = 0; j < C; j++) {
				if (grid[i][j] == 1) {
					len++;
					nodes[i][j].l = len;
				}
				else if(len != 0){
					for (; len != 0; len--) {
						nodes[i][j - len].r = len;
					}
				}
				if (grid[i][j] == 1 && j == C - 1) {
					j++;
					for (; len != 0; len--) {
						nodes[i][j - len].r = len;
					}
				}
			}
		}

		for (int i = 0; i < C; i++) {
			int len = 0;
			for (int j = 0; j < R; j++) {
				if (grid[j][i] == 1) {
					len++;
					nodes[j][i].u = len;
				}
				else if (len != 0) {
					for (; len != 0; len--) {
						nodes[j - len][i].d = len;
					}
				}
				if (grid[j][i] == 1 && j == R - 1) {
					j++;
					for (; len != 0; len--) {
						nodes[j - len][i].d = len;
					}
				}
			}
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				sum += find_L(nodes[i][j].u, nodes[i][j].l);
				sum += find_L(nodes[i][j].u, nodes[i][j].r);
				sum += find_L(nodes[i][j].d, nodes[i][j].l);
				sum += find_L(nodes[i][j].d, nodes[i][j].r);
			}
		}

		cout << "Case #" << case_count << ": " <<sum<< endl;
	}
}