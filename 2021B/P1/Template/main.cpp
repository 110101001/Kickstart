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
		int len;
		int currentInc = 1;
		string str;
		cin >> len >> str;
		cout << "Case #" << case_count << ": " << 1 <<" ";
		for (int i = 1; i < len;i++) {
			if (str[i] > str[i - 1]) {
				currentInc++;
			}
			else {
				currentInc = 1;
			}
			cout<< currentInc << " ";
		}
		cout << endl;
	}
}