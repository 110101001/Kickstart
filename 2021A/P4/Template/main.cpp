#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))

using namespace std;

typedef struct edge{
	int w = 0, to = -1;
}edge;

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int K,n;
		int total_weight=0;
		int max_weight=0;
		cin >> n;
		K = 2 * n;
		vector<vector<int>> graph(K);
		vector<bool> selected(K,false);
		vector<edge> candidate(K);
		candidate[0].w = 0;

		for (int i = 0; i < K; i++) {
			graph[i] = vector<int>(K);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int garbage;
				cin >> garbage;
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> graph[i][j+n];
				graph[j+n][i] = graph[i][j+n];
				total_weight += graph[i][j+n];
			}
		}
		for (int i = 0; i < K; i++) {
				int garbage;
				cin >> garbage;
		}
		for (int i = 0; i < K;i++) {
			if (false == selected[i]) {
				bool first_flag = true;
				for (int j = 0; j < K; j++) {
					int select = -1;
					for (int l = 0; l < K; l++) {
						if ((!selected[l]) && (-1 == select || candidate[l].w > candidate[select].w)) {
							select = l;
						}
					}
					
					if((-1 == select || 0 == candidate[select].w)&&!first_flag) {
						break;
					}

					first_flag = false;

					selected[select] = true;
					max_weight += candidate[select].w;

					for (int l = 0; l < K;l++) {
						if (graph[select][l] > candidate[l].w) {
							candidate[l] = { graph[select][l],select };
						}
					}
				}
			}
		}

		cout << "Case #" << case_count << ": "<<total_weight - max_weight << endl;
	}
}