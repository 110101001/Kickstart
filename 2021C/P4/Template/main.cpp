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

struct Wint :vector<int>
{
	Wint(int n = 0)
	{
		push_back(n);
		check();
	}
	Wint& check()
	{
		while (!empty() && !back())pop_back();
		if (empty())return *this;
		for (int i = 1; i < size(); ++i)
		{
			(*this)[i] += (*this)[i - 1] / 10;
			(*this)[i - 1] %= 10;
		}
		while (back() >= 10)
		{
			push_back(back() / 10);
			(*this)[size() - 2] %= 10;
		}
		return *this;
	}
};

istream& operator>>(istream& is, Wint& n)
{
	string s;
	is >> s;
	n.clear();
	for (int i = s.size() - 1; i >= 0; --i)n.push_back(s[i] - '0');
	return is;
}
ostream& operator<<(ostream& os, const Wint& n)
{
	if (n.empty())os << 0;
	for (int i = n.size() - 1; i >= 0; --i)os << n[i];
	return os;
}


bool operator!=(const Wint& a, const Wint& b)
{
	if (a.size() != b.size())return 1;
	for (int i = a.size() - 1; i >= 0; --i)
		if (a[i] != b[i])return 1;
	return 0;
}
bool operator==(const Wint& a, const Wint& b)
{
	return !(a != b);
}
bool operator<(const Wint& a, const Wint& b)
{
	if (a.size() != b.size())return a.size() < b.size();
	for (int i = a.size() - 1; i >= 0; --i)
		if (a[i] != b[i])return a[i] < b[i];
	return 0;
}
bool operator>(const Wint& a, const Wint& b)
{
	return b < a;
}
bool operator<=(const Wint& a, const Wint& b)
{
	return !(a > b);
}
bool operator>=(const Wint& a, const Wint& b)
{
	return !(a < b);
}

Wint& operator+=(Wint& a, const Wint& b)
{
	if (a.size() < b.size())a.resize(b.size());
	for (int i = 0; i != b.size(); ++i)a[i] += b[i];
	return a.check();
}
Wint operator+(Wint a, const Wint& b)
{
	return a += b;
}

Wint& operator-=(Wint& a, Wint b)
{
	if (a < b)swap(a, b);
	for (int i = 0; i != b.size(); a[i] -= b[i], ++i)
		if (a[i] < b[i])
		{
			int j = i + 1;
			while (!a[j])++j;
			while (j > i)
			{
				--a[j];
				a[--j] += 10;
			}
		}
	return a.check();
}
Wint operator-(Wint a, const Wint& b)
{
	return a -= b;
}

Wint operator*(const Wint& a, const Wint& b)
{
	Wint n;
	n.assign(a.size() + b.size() - 1, 0);
	for (int i = 0; i != a.size(); ++i)
		for (int j = 0; j != b.size(); ++j)
			n[i + j] += a[i] * b[j];
	return n.check();
}
Wint& operator*=(Wint& a, const Wint& b)
{
	return a = a * b;
}

Wint divmod(Wint& a, const Wint& b)
{
	Wint ans;
	for (int t = a.size() - b.size(); a >= b; --t)
	{
		Wint d;
		d.assign(t + 1, 0);
		d.back() = 1;
		Wint c = b * d;
		while (a >= c)
		{
			a -= c;
			ans += d;
		}
	}
	return ans;
}
Wint operator/(Wint a, const Wint& b)
{
	return divmod(a, b);
}
Wint& operator/=(Wint& a, const Wint& b)
{
	return a = a / b;
}
Wint& operator%=(Wint& a, const Wint& b)
{
	divmod(a, b);
	return a;
}
Wint operator%(Wint a, const Wint& b)
{
	return a %= b;
}

Wint pow(const Wint& n, const Wint& k)
{
	if (k.empty())return 1;
	if (k == 2)return n * n;
	if (k.back() % 2)return n * pow(n, k - 1);
	return pow(pow(n, k / 2), 2);
}


typedef enum op_type {
	NUM = 0, ADD = 1, MULT = 2, SPEC = 3
}op_type;

class sp{
public:
	Wint a;
	Wint b;

	sp(Wint _a, Wint _b) :a(_a), b(_b) {

	}

	bool operator>(const sp& rhs) const{
		if (a > rhs.a) {
			return true;
		}
		else if (a == rhs.a) {
			if (b > rhs.b) {
				return true;
			}
		}
		return false;
	}

	bool operator<(const sp& rhs) const{
		if (a < rhs.a) {
			return true;
		}
		else if (a == rhs.a) {
			if (b < rhs.b) {
				return true;
			}
		}
		return false;
	}

	bool operator==(const sp& rhs) const{
		if (a == rhs.a && b == rhs.b) {
			return true;
		}
		return false;
	}
};

map<sp, Wint> term;

Wint getValue(Wint a,Wint b) {
	Wint res;
	auto i = term.find(sp(a,b));
	if (term.end() == i) {
		res = rand();
		auto p = make_pair(sp(a,b),res);
		term.insert(p);
	}
	else {
		res = i->second;
	}
	return res;
}

class item{
public:
	op_type t;
	Wint v;
	item* l;
	item* r;

	item(Wint _num) :
		t(NUM), v(_num) {
		l = r  = NULL;
	}

	item(enum op_type _t): 
	t(_t),v(0){
		l = r  = NULL;
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
		if (l != NULL) {
			delete l;
		}
		if (r != NULL) {
			delete r;
		}
	}
};

item* parse_exp() {
	item* p = NULL, * l = NULL, * r = NULL;
	bool bra = false;
	char c = cin.peek();
	if (c == ' ' || c == '\n') {
		cin.ignore(1);
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
	c = cin.peek();
	if (c != '+' && c != '*' && c != '#') {
		return l;
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
		Wint rval;
		cin >> rval;
		r = new item(rval);
	}
	cin >> c;
	if (p != NULL) {
		p->l = l;
		p->r = r;
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
		e->v = getValue(e->l->v, e->r->v);
		return e;
		break;
	case ADD: 
		e->l = reduce(e->l);
		e->r = reduce(e->r);
		e->v = e->l->v + e->r->v;
		break;
	case MULT:
		e->l = reduce(e->l);
		e->r = reduce(e->r);
		e->v = e->l->v * e->r->v;
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
		vector<Wint> exp(n);
		for (int i = 0; i < n; i++) {
			item *e = parse_exp();
			e = reduce(e);
			exp[i] = e->v;
		}
		cout << "Case #" << case_count << ": ";
		for (int i = 0; i < n; i++) {
			cout << exp[i] << " " ;
		}
		cout << endl;
	}
}