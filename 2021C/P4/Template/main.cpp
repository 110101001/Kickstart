#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <algorithm>
#include <math.h>

#define ABS(x) (((x)>0)?(x):(-(x)))
#define MAX(x,y) ((x>y)?(x):(y))
#define MIN(x,y) ((x<y)?(x):(y))
#define SWAP(x,y)  {int tempVar = (x); (x) = (y) ; (y) = tempVar;}

using namespace std;

typedef enum op_type {
	NUM=0,ADD,MULT,SPEC
}op_type;

class item{
public:
	op_type t;
	int v;
	item* l;
	item* r;
	item* p;

	item(int _num) {
		t = NUM;
		v = _num;
		l = r = p = NULL;
	}

	item(enum op_type _t) {
		t = _t;
		v = 0;
		l = r = p = NULL;
	}

	item(const item& rhs) {
		t = rhs.t;
		v = rhs.v;
		if (rhs.l != NULL) {
			l = new item(*rhs.l);
		}
		else {
			l = NULL;
		}
		if (rhs.r != NULL) {
			r = new item(*rhs.r);
		}
		else {
			r = NULL;
		}
	}

	bool operator ==(const item &rhs) {
		if (t != rhs.t) {
			return false;

		}

		if(t == NUM && v != rhs.v) {
			return false;
		}

		if (l != rhs.l) {
			return false;
		}
		else if (l != NULL) {
			if (!((*l) == (*rhs.l))) {
				return false;
			}
		}

		if (r != rhs.r) {
			return false;
		}
		else if (r != NULL) {
			if (!((*r) == (*rhs.r))) {
				return false;
			}
		}
		return true;
	}


	bool operator >(const item &rhs) {
		if (t > rhs.t) {
			return true;
		}

		if (v > rhs.v) {
			return true;
		}

		if (l != NULL) {
			if (rhs.l != NULL) {
				if ((*l) > (*rhs.l)) {
					return true;
				}
				else if((*rhs.l) > (*l)){
					return false;
				}
			}
			else {
				return true;
			}
		}
		else if (rhs.l != NULL) {
			return false;
		}

		if (r != NULL) {
			if (rhs.r != NULL) {
				if ((*r) > (*rhs.r)) {
					return true;
				}
				else if((*rhs.r) > (*r)){
					return false;
				}
			}
			else {
				return true;
			}
		}
		else if (rhs.r != NULL) {
			return false;
		}
	}
};

map<item,int> terms;
int current_count = 0;

int match_spec(item &i) {
	auto iter = terms.find(i);
	if (iter == terms.end()) {
		auto ins = make_pair(i,--current_count);
		terms.insert(ins);
		return current_count;
	}
	else {
		return iter->second;
	}
}

item* parse_exp() {
	item* p = NULL, * l = NULL, * r = NULL;
	char c = cin.peek();
	if (c == ' ' || c == '\n') {
		cin >> c;
		c = cin.peek();
	}
	if (c == '(') {
		cin >> c;
		l = parse_exp();
	}
	else {
		int lval;
		cin >> lval;
		l = new item(lval);
	}

	cin >> c;
	switch (c) {
	case '+':
		p = new item(ADD);
		break;
	case '*':
		p = new item(MULT);
		break;
	case '#':
		p = new item(SPEC);
		break;
	}

	c = cin.peek();
	if (c == '(') {
		cin >> c;
		r = parse_exp();
	}
	else {
		int rval;
		cin >> rval;
		r = new item(rval);
	}
	if (p != NULL) {
		p->l = l;
		p->r = r;
		l->p = p;
		r->p = p;
	}
	return p;
}

item* reduce(item *e) {
	switch (e->t) {
	case NUM:
		return e;
		break;
	case SPEC:
		e->l = reduce(e->l);
		e->r = reduce(e->r);
		e->v = match_spec(*e);
		return e;
		break;
	case ADD: 
		e->l = reduce(e->l);
		e->r = reduce(e->r);
		if (e->l->t == NUM && e->r->t == NUM) {
			e->v = e->l->v + e->r->v;
			delete e->l;
			delete e->r;
			e->t = NUM;
			e->l = NULL;
			e->r = NULL;
		}
		else if (e->l->t == NUM && e->l->v == 0) {
			item* r = e->r;
			r->p = e->p;
			delete e->l;
			delete e;
			return r;
		}
		else if (e->r->t == NUM && e->r->v == 0) {
			item* l = e->l;
			l->p = e->p;
			delete e->r;
			delete e;
			return l;
		}
		break;
	case MULT:
		e->l = reduce(e->l);
		e->r = reduce(e->r);
		if (e->l->t == NUM && e->r->t == NUM) {
			e->v = e->l->v * e->r->v;
		}
		else if (e->l->t == NUM) {
			if (e->l->v == 1) {
				item* r = e->r;
				r->p = e->p;
				delete e->l;
				delete e;
				return r;
			}

		}
		break;
	}
	return e;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int case_number;//total number of case
	cin >> case_number;

	for (int case_count = 1; case_count <= case_number; case_count++) {
		int n;
		cin >> n;
		vector<vector<item>> exp(n);
		for (int i = 0; i < n; i++) {
			item *e = parse_exp();
			e = reduce(e);
		}
		cout << "Case #" << case_count << ": " << endl;
	}
}