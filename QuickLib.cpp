long long pow(long long x,long long n,long long m){
	long long res = 1;
	while(n > 0){
		if(n & 1)	res = res * x % m;
		x = x * x % m;
		n >>= 1;
	}
	return res;
}

bool isPrime(unsigned long long n) {
	unsigned long long a, x;
	unsigned long long d = n - 1;
	int s = 0;
	if (n <= 3)
	{
		return true;
	}
	if (0 != (n + 1) % 6 && 0 != (n - 1) % 6) {
		return false;
	}

	while (!(d & 1)) {
		d = d >> 1;
		s++;
	}

	for (int i = 0; i < 12; i++) {
		a = 1 + (rand() % (n - 2));

		x = pow(a, d, n);
		if (1 == x || n - 1 == x) {
			continue;
		}

		for (int r = 0; r < s - 1; r++) {
			x = x * x % n;
			if (x == n - 1) {
				break;
			}
		}
		if (x == n - 1) {
			continue;
		}
		return false;
	}

	for (unsigned long long i = 2; i * i < n; i++) {
		if (0 == n % i) {
			return false;
		}
	}
	return true;
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
