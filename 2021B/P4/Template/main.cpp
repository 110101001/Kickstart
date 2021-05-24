#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <assert.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {long long tempVar = (x); (x) = (y) ; (y) = tempVar;}

#define LCHILD(x) 2*(x) + 1
#define RCHILD(x) 2*(x) + 2
#define PARENT(x) ((x)-1)/2

#define MAXN 200010

using namespace std;

typedef struct segtree {
	int r, l;
	long long v;
}segTree;

segTree tree[4*MAXN];

typedef struct road {
	int to, L;
	long long A;
	road(int _to, int _L,long long _A) {
		this->to = _to;
		this->L = _L;
		this->A = _A;
	}
}road;

typedef struct query {
	int W;
	long long ans;
}query;

typedef	struct city{
	vector<road> r;
	vector<int> q;
}city;

long long gcd(long long a,long long b) {
	if (b > a) SWAP(a, b);
	if (0 == b) {
		return a;
	}
	do{
		if (a %= b) {
			SWAP(a, b); 
		}
		else {
			return b;
		}
	} while (true);
}

void buildTree(int idx,int l,int r) {
	tree[idx].l = l;
	tree[idx].r = r;
	tree[idx].v = 0;
	if (l != r) {
		buildTree(LCHILD(idx),l,(l+r)/2);
		buildTree(RCHILD(idx),(l+r)/2+1,r);
	}
}

long long updateTree(int idx,int id, long long val) {
	if (id == tree[idx].l && id == tree[idx].r) {
		tree[idx].v = val;
	}
	else {
		if (id <= ((tree[idx].r + tree[idx].l) / 2)) {
			long long u = updateTree(LCHILD(idx), id, val);
			tree[idx].v = gcd(u, tree[RCHILD(idx)].v);
		}
		else {
			long long u = updateTree(RCHILD(idx), id, val);
			tree[idx].v = gcd(u, tree[LCHILD(idx)].v);
		}
	}
	return tree[idx].v;
}

long long queryTree(int idx,long long end) {
	if (tree[idx].r <= end) {
		return tree[idx].v;
	}
	else if (end > (tree[idx].r+tree[idx].l)/2) {
		return gcd(tree[LCHILD(idx)].v,
			queryTree(RCHILD(idx),end));
	}
	else {
		return queryTree(LCHILD(idx),end);
	}
}

void dfs(vector<bool> &visited,vector<city> &g,vector<query> &qry, int idx) {
	for (auto r : g[idx].r) {
		if (!visited[r.to - 1]) {
			visited[r.to - 1] = true;
			updateTree(0,r.L,r.A);
			for (auto q : g[r.to - 1].q) {
				qry[q].ans = queryTree(0,qry[q].W);
			}
			dfs(visited,g,qry,r.to-1);
			updateTree(0,r.L,0);
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int Q, N, maxL = 0;
		cin >> N >> Q;
		
		vector<city> g(N);
		vector<bool> visited(N);
		vector<query> a(Q);


		for (size_t i = 0; i < N - 1; i++)
		{
			int x, y, L;
			long long A;
			cin >> x >> y >> L >> A;
			g[x-1].r.push_back(road(y, L, A));
			g[y-1].r.push_back(road(x, L, A));
		}

		buildTree(0,0,MAXN);

		for (size_t i = 0; i < Q; i++)
		{
			int W, C;
			cin >> C >> W;
			a[i].W = W;
			g[C - 1].q.push_back(i);
		}
		
		visited[0] = true;

		dfs(visited,g,a,0);

		cout << "Case #" << case_count << ": ";

		for (size_t i = 0; i < Q; i++)
		{
			cout<<a[i].ans<<" ";
		}

		cout<< endl;
	}
}
