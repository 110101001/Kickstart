#include <iostream>
#include <vector>

#define MAX_NODES 100

using namespace std;

int shortest[MAX_NODES][MAX_NODES];

int main() {
	int n;
	cin >> n;
	for (int c = 1; c <= n; c++) {
		int N, Q;
		char name[21];
		vector<vector<int>> graph(26);
		cin >> N >> Q;
		for (int i = 0; i < N; i++) {
			int k = 0;
			cin >> name;
			while (name[k] != 0) {
				if (graph[name[k] - 'A'].empty() || graph[name[k] - 'A'].back() != i) {
					graph[name[k] - 'A']
					.push_back(i);
				}
				k++;
			}
		}
		for (int k = 0; k < N; k++) {
			for (int m = 0; m < N; m++) {
				shortest[k][m] = 99999;
			}
		}

		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				for (int x = j + 1; x < graph[i].size(); x++) {
					shortest[graph[i][x]][graph[i][j]] = 1;
					shortest[graph[i][j]][graph[i][x]] = 1;
					//	cout << (char)(i + 'A') << " " << graph[i][x] << " " << graph[i][j] << endl;
				}
			}
		}

		for (int k = 0; k < N; k++) {
			for (int u = 0; u < N; u++) {
				for (int v = u + 1; v < N; v++) {
					if (k != u && k != v &&
					        shortest[u][v] > shortest[u][k] + shortest[k][v]) {
						shortest[u][v] = shortest[u][k] + shortest[k][v];
						shortest[v][u] = shortest[u][k] + shortest[k][v];

						//	cout << u << "-" << k << "-" << v << endl;
						//	cout << shortest[u][v] << endl;
					}
				}
			}
		}

		cout << "Case #" << c << ": ";
		for (int i = 0; i < Q; i++) {
			int p1, p2;
			cin >> p1 >> p2;
			p1++;
			p2++;
			if (shortest[p1][p2] == 99999) {
				cout << "-1 ";
			} else {
				cout << shortest[p1][p2] + 1 << " ";
			}
		}
		cout << endl;

		for (int i = 0; i < 26; i++) {
			graph[i].clear();
		}
	}


	return 0;
}