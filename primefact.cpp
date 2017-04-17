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
