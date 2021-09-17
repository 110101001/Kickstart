#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <queue>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {int tempVar = (x); (x) = (y) ; (y) = tempVar;}

using namespace std;

typedef struct s{
	int v;
	int seq; 
}s;

bool cmp(const s &a, const s &b){
	return a->v > b->v;
}

