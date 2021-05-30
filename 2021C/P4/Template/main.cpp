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
	NUM = 0, ADD = 1, MULT = 2, SPEC = 3, SERIALIZED = 4
}op_type;

class item{
public:
	op_type t;
	union {
		int v;
		struct {
			vector<item*>* s;
			vector<int> *coef;
		};
	};
	item* l;
	item* r;
	item* p;

	item(int _num) :
		t(NUM), v(_num) {
		l = r = p = NULL;
	}

	item(enum op_type _t): 
	t(_t),v(0){
		l = r = p = NULL;
	}

	item(const item& rhs):
	t(rhs.t),v(rhs.v){
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
	
	~item() {
		if (SERIALIZED == t) {
			delete s;
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

//reduce tree to ensure when iterating from root or #'s subtrees, adds are always visited before mults, until meet #
item* reduce(item *e) {
	switch (e->t) {
	case NUM:
		return e;
		break;
	case SPEC:
		e->l = reduce(e->l);
		e->r = reduce(e->r);
		//e->v = match_spec(*e);
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
			delete e->l;
			delete e->r;
			e->l = NULL;
			e->r = NULL;
			return e;
		}
		else if (e->l->t == NUM) {
			if (e->l->v == 1) {
				item* r = e->r;
				r->p = e->p;
				delete e->l;
				delete e;
				return r;
			}
			else if (e->l->v == 0) {
				item* r = new item(0);
				r->p = e->p;
				delete e->r;
				delete e->l;
				delete e;
				return r;
			}
		}
		else if (e->r->t == NUM) {
			if (e->r->v == 1) {
				item* l = e->l;
				l->p = e->p;
				delete e->r;
				delete e;
				return l;
			}
			else if (e->r->v == 0) {
				item* l = new item(0);
				l->p = e->p;
				delete e->r;
				delete e->l;
				delete e;
				return l;
			}
		}
		if (e->l->t == ADD) {
			item* p = new item(ADD);
			p->p = e->p;
			p->l = new item(MULT);
			p->r = new item(MULT);
			p->l->p = p;
			p->r->p = p;
			p->l->l = e->l->l;
			p->l->r = e->r;
			p->r->l = e->l->r;
			p->r->r = new item(*e->r);

			p->l->l->p = p->l;
			p->l->r->p = p->l;
			p->r->l->p = p->r;
			p->r->r->p = p->r;
			delete e->l;
			delete e;
			reduce(p);
			return p;
		}
		if (e->r->t == ADD) {
			item* p = new item(ADD);
			p->p = e->p;
			p->l = new item(MULT);
			p->r = new item(MULT);
			p->l->p = p;
			p->r->p = p;
			p->l->r = e->r->l;
			p->l->l = e->l;
			p->r->r = e->r->r;
			p->r->l = new item(*e->l);

			p->l->l->p = p->l;
			p->l->r->p = p->l;
			p->r->l->p = p->r;
			p->r->r->p = p->r;
			delete e->r;
			delete e;
			reduce(p);
			return p;
		}
		break;
	}
	if ((*e->l) > (*e->r)) {
		item* temp = e->l;
		e->l = e->r;
		e->r = temp;
	}
	return e;
}

//combine terms
item *serialize(item *p) {
	switch (p->t) {
		case NUM:
			p->t = SERIALIZED;
			item* tmp = new item(1);
			p->s = new vector<item*>(1);
			(*p->s)[0] = tmp;
			(*p->coef)[0] = p->v;
			break;
		case ADD:
			p->t = SERIALIZED;
			p->s = new vector<item*>;
			if (p->l->t == SERIALIZED && p->r->t == SERIALIZED) {
				int i = 0;
				int j = 0;
				int k = 0;
				vector<int>* coefa = p->l->coef, *coefb = p->r->coef;
				vector<item*>* sa = p->l->s, * sb = p->r->s;
				p->s->resize(sa->size() + sb->size());
				p->coef->resize(coefa->size() + coefb->size());
				while (i < sa->size() &&
					j < sb->size()) {
					if (*(*sa)[i] > *(*sb)[j]) {
						(*p->s)[k] = (*sb)[j];
						(*p->coef)[k] = (*coefb)[j];
						j++;
					}
					else if (*(*sa)[i] == *(*sb)[j]) {
						(*p->s)[k] = (*sa)[i];
						(*p->coef)[k] = (*coefa)[i] + (*coefb)[j];
						i++;
						j++;
					}
					else {
						(*p->s)[k] = (*sa)[i];
						(*p->coef)[k] = (*coefa)[i];
						i++;
					}
					k++;
				}
				
			}
	}
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