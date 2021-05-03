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
		int len = 0;
		int maxArithLen = 0;
		cin >> len;
		if (0 != len) {
			int chunkStart[4] = { 0,0,0,0 }, currDiff = 0, length = 0;
			vector<int> array(len);
			vector<int> diff(len - 1);
			for (int i = 0; i < len; i++) {
				cin >> array[i];
			}
			for (int i = 0; i < len - 1; i++) {
				diff[i] = array[i + 1] - array[i];
			}
			for (int i = 0; i < len; i++) {
				if (i != len - 1 && diff[i] == currDiff) {
					length++;
				}
				else {
					if (chunkStart[0] >= 2 && diff[chunkStart[0]] + diff[chunkStart[0] - 1] == 2 * diff[chunkStart[2]]) {
						maxArithLen = MAX(maxArithLen, chunkStart[0] - chunkStart[2] + 2);
					}

					if (chunkStart[0] >= 2 && diff[chunkStart[0] - 1] + diff[chunkStart[0] - 2] == 2 * currDiff) {
						if (currDiff == diff[chunkStart[3]]) {
							maxArithLen = MAX(maxArithLen, chunkStart[0] - chunkStart[3] + length + 1);
						}
						else {
							maxArithLen = MAX(maxArithLen,length + 3);
						}						
					}
					else if (chunkStart[0] != 0 || length != len - 1) {
						maxArithLen = MAX(maxArithLen, length+2);
					}
					else {
						maxArithLen = MAX(maxArithLen, length+1);
					}
					if (i != len - 1) {
						chunkStart[3] = chunkStart[2];
						chunkStart[2] = chunkStart[1];
						chunkStart[1] = chunkStart[0];
						chunkStart[0] = i;
						currDiff = diff[i];
						length = 1;
					}
				}
			}
		}
		cout << "Case #" << case_count << ": " << maxArithLen << endl;
	}
}