#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdint>
using namespace std;
void getPrimesTo(int n, vector<int64_t> &v) {
	if (v.size() == 0) {
		v.push_back(2);
	}
	int start = v[v.size()-1];
	for (int i=start+1; i<n; ++i) {
		for (vector<int64_t>::iterator it=v.begin(); (*it)*(*it) <= i; ++it)
			if (!(i%(*it))) goto skip;
		v.push_back(i);
		skip:;
	}
}

vector<int> getPrimeVec(int64_t n, vector<int64_t> &primes) {
	vector<int> v;
	int p,k;
	for (auto it=primes.begin(); it!=primes.end() && n > 1; ++it) {
		p = *it;
		k = 0;
		while (!(n%p)) {
			n /= p;
			++k;
		}
		v.push_back(k);
	}
	return v;
}

void getPrimeVecs(int64_t n, vector<int64_t> &primes, vector<int> &counts, vector<int64_t> &relprimes) {
	int64_t p;
	int k;
	for (auto it=primes.begin(); it!=primes.end() && n > 1; ++it) {
		p = *it;
		k = 0;
		while (!(n%p)) {
			n /= p;
			++k;
		}
		if (k > 0) {
			counts.push_back(k);
			relprimes.push_back(p);
		}
	}
	if (n > 1) {
		counts.push_back(1);
		relprimes.push_back(n);
	}
}

void getNextPrime(vector<int64_t> &primes) {
	int64_t start = primes[primes.size()-1];
	for (int64_t p=start+1; ; ++p) {
		for (int j=0; j<primes.size(); ++j) {
			if (!(p%primes[j])) {
				goto gnp_skip;
			}
		}
		primes.push_back(p);
		return;
		gnp_skip:;
	}
}
void primeFact(int64_t n, vector<int64_t> &primes, vector<int> &counts, vector<int64_t> &relprimes) {
	int64_t p;
	int k;
	if (primes.size() == 0)
		primes.push_back(2);
	for (int i=0; primes[i]*primes[i] < n && n > 1; ++i) {
		p = primes[i];
		k = 0;
		while (!(n%p)) {
			n /= p;
			++k;
		}
		if (k > 0) {
			counts.push_back(k);
			relprimes.push_back(p);
		}
		if (i == primes.size()-1 && n > 1) {
			getNextPrime(primes);
		}
	}
	if (n > 1) {
		counts.push_back(1);
		relprimes.push_back(n);
	}
}
