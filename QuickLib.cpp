long long pow(long long x,long long n,long long m){
	long long res = 1;
	while(n > 0){
		if(n & 1)	res = res * x % m;
		x = x * x % m;
		n >>= 1;
	}
	return res;
}

int gcd(int a,int b) {
	if (b > a) SWAP(a, b);
	do{
		if (a %= b) {
			SWAP(a, b); 
		}
		else {
			return b;
		}
	} while (true);
}
