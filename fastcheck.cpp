#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include "bincoeffs.cpp"
#include "primefact.cpp"
using namespace std;

bool quickcheck(int n, int64_t k) {
	bool* current = (bool*) malloc(n);
	bool* temp = (bool*) malloc(n);
	memset(current, 0, n);
	current[0] = 1;
	int64_t s,t;
	for (int64_t p=1; p>0; p<<=1) {
		if (!(k&p)) continue;
		t = (-p)%n;
		for (int r=0; r<n; ++r) {
			s = r+t;
			if (s < 0) s += n;
			temp[r] = current[r]^current[s];
		}
		memcpy(current, temp, n);
	}	
	current[0] ^= 1;
	bool ans = 1;
	for (int i=1; i<n; ++i) {
		if (current[i] != current[0]) {
			ans = 0;
			break;
		}
	}
	free(current);
	free(temp);
	return ans;
}

int gamma2(int n) {
	int m = 2, i;
	for (i=1; m != 1; ++i) {
		m *= 2;
		m %= n;
	}
	return i;
}

int64_t q(int n) {
	int gam2 = gamma2(n);
	if ((gam2%2 && gam2 > 62) || (gam2%2 == 0&& gam2/2 > 62-log2(n))) {
		return (1LL<<62);
	}
	if (gam2%2) {
		return (1LL << gam2)-1;
	}
	else {
		return ((1LL << (gam2/2))-1)*n;
	}
}

vector<int64_t> primes;


// returns the smallest divisor of the number with the given prime factorization that works
// if none is found (e.g. it's > 2^63-1 and overflows an int64_t), it returns 0;
int64_t mindiv(int n, vector<int> &minexp, vector<int> &maxexp, vector<int> &current, vector<int64_t> &relprimes, int depth) {
/*	if (depth%1000 == 0) {
		cout << "depth = " << depth << endl;
	} */
	if (depth == maxexp.size()) {
		int64_t k = 1;
		for (int i=0; i<current.size(); ++i) {
			for (int j=0; j<current[i]; ++j) {
				k *= relprimes[i];
			}
		}
		//cout << "checking divisor: " << k << "... ";
		if (quickcheck(n, k)) {
			//cout << "yes!\n";
			return k;
		}
		//cout << "no\n";
		return 0;
	}
	int64_t ans = 0, x;
	for (int i=minexp[depth]; i<=maxexp[depth]; ++i) {
		current[depth] = i;
		x = mindiv(n, minexp, maxexp, current, relprimes, depth+1);
		if (x > 0 && (ans == 0 || x < ans))
			ans = x;
	}
	return ans;
}
// for odd prime n, finds the largest d such that q(n)/d that is a multiple
// of the cycle length
int64_t maxqdiv(int n) {
	int64_t qn = q(n);
	cout << "n = " << n << '\n';
	cout << "q(" << n << ") = " << qn << '\n';
	//cout << (int)(sqrt(qn)+1) << '\n';
	if ((int)(sqrt(qn)+1) > primes[primes.size()-1]) {
		cout << "generating primes from " << primes[primes.size()-1] << " to " << (int)(sqrt(qn)+1) << "...";
		getPrimesTo((int)(sqrt(qn)+1), primes);
		cout << "done! new largest stored = " << primes[primes.size()-1] << '\n';
	}
	vector<int> pvec;
	vector<int64_t> relprimes;
	getPrimeVecs(qn, primes, pvec, relprimes);
	vector<int> minexp;
	int64_t n2 = n;
	for (int i=0; i<pvec.size(); ++i) {
		minexp.push_back(0);
		while (!(n2%relprimes[i])) {
			n2 /= relprimes[i];
			minexp[i]++;
		}
	}
	/*int64_t prod = 1;
	for (int i=0; i<pvec.size(); ++i) {
		for (int j=0; j<pvec[i]; ++j) {
			prod *= primes[i];
		}
	}
	bool hugePrime = false;
	cout << "(max computed prime = " << primes[primes.size()-1] << ")\n";
	if (prod < qn) {
		hugePrime = true;
		cout << "(huge prime divisor of q(n): " << qn/prod << ")\n";
		primes.push_back(qn/prod);
		pvec.push_back(1);
	}*/
	//cout << pvec.size()<< '\n';
	vector<int> v; 
	for (int i=0; i<pvec.size(); ++i)
		v.push_back(0);
	//cout << "pvec = ";
	//for (int i=0; i<pvec.size(); ++i)
	//	cout  << pvec[i] << ' ';
	//cout << '\n';
//	cout << pvec.size() << '\n';
	int64_t sol = mindiv(n, minexp, pvec, v, relprimes, 0);
	cout << "minimum divisor solution: " << sol << '\n';
	int64_t ans = qn/sol;
	//if (hugePrime)
	//	primes.pop_back();
	cout << "ratio = " << ans << '\n';
	return ans;
}

int quickfind(unsigned n) {
	for (int k=n; k < 100000000; k+=n) {
		if (quickcheck(n, k)) {
			return k;
		}
	}
	return 100000000;
}

int64_t divfind(unsigned n) {
	int ord = gamma2(n);
	int64_t maxval = (1LL<<ord)-1;
	vector<int> pvec;
	vector<int64_t> relprimes;
	primeFact(maxval, primes, pvec, relprimes);
	vector<int> minexp;
	int n2 = n;
	vector<int> v;
	for (int i=0; i<pvec.size(); ++i) {
		v.push_back(0);
		minexp.push_back(0);
		while (!(n2%relprimes[i])) {
			n2 /= relprimes[i];
			minexp[i]++;
		}
	}
	/*cout << maxval << endl;
	for (int i=0; i<relprimes.size(); ++i) {
		cout << relprimes[i] << ' ' << minexp[i] << ' ' << pvec[i] << '\n';
	}*/
	return mindiv(n, minexp, pvec, v, relprimes, 0);
}
int main() {
	int n,k;
	int64_t x;
	freopen("svals.txt", "w", stdout);
	for (int n=3; n<500; n += 2) {
		x = divfind(n);
		cout << "s(" << n << ") ";
		if (x == 0) {
			cout << ">= 2^63\n";
		} else {
			cout << "= " << x << '\n';
		}
	}
	fclose(stdout);
/*	getPrimesTo(100, primes);
	for (int i=1; primes[i] < 50000; ++i) {
		if (q(primes[i]) > 1e15)
			continue;
		maxqdiv(primes[i]);
	}*/
	/*
	while (1) {
		cout << "Enter n:>";
		cin >> n;
	//	cout << "Enter k:>";
	//	cin >> k;
		//quickcheck(n,k);
		//cout << binCoeffs(k) << endl;
		cout << divfind(n) << '\n';
		//cout << quickfind(n) << '\n';
		//cout << maxqdiv(n) << '\n';
		//cout << getk(n) << '\n';
	}*/
}
