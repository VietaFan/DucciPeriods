#include <vector>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "bitvec.cpp"
#define MAX_N 10000
using namespace std;

bitvec binCoeffs(int n) {
	bitvec v(n/64+2), v2(n/64+2);
	v = 1;
	for (int i=0; i<n; ++i) {
		v2 = v;
		v <<= 1;
		v ^= v2;
	}
	return v;
}

bool works(int n, int k, bitvec &v) {
	bool* counts = new bool[n];
	for (int i=0; i<n ;i++)
		counts[i] = 0;
	for (int i=0; i<k; i++)
		counts[i%n] ^= v[i];
	for (int i=1; i<n; i++)
		if (counts[i] != counts[0])
			return false;
	return true;
}
#define VEC_SIZE 500

int getk(int n) {
	bitvec v(VEC_SIZE), v2(VEC_SIZE);
	v = 1;
	for (int t=1; t*n < 64*VEC_SIZE; t++) {
		for (int i=0; i<n; ++i) {
			v2 = v;
			v2 <<= 1;
			v ^= v2;
		}
		if (works(n, t*n, v)) {
			return t*n;
		}
	}
	return -1;
}

string getPattern(int n, int r, int kmax) {
	string s;
	bool b;
	for (int i=1; i<=kmax; i++) {
		bitvec x = binCoeffs(i);
		cout << x << endl;
		b = 0;
		for (int j=0; j<i; j+=n)
			b ^= x[j];
		if (b) s += '1'; else s += '0';
	}
	return s;
}


ostream& operator<<(ostream &out, const bitvec &v) {
	for (int i=v.size-1; i>-1; --i) {
		for (int j=63; j>-1; --j)
			out << ((v.bits[i]&(1ULL<<j))?'1':'0');
	}
	return out;
}
/*
int main() {
	int n, r;
	while (true) {
		cout << "n? >";
		cin >> n;
		cout << "r? >";
		cin >> r;
		cout << getPattern(n,r,20) << '\n';;
	}
		
	/*cout << binCoeffs(63) << endl;
	cout << binCoeffs(64) << endl;
	/*bitvec v(2);
	v = (1ULL<<64)-1;
	bitvec v2(2);
	v2 = v;
	cout << v << endl;
	v <<= 1;
	cout << v << endl;
	v ^= v2;
	cout << v << endl;*/
	/*freopen("pascal.txt", "w", stdout);
	for (int i=0; i<100; i++) {
		bitvec v = binCoeffs(i);
		for (int j=0; j<=i; ++j)
			cout << v[j];
		cout << endl;
	}
	fclose(stdout);
	/*cout << getk(3) << '\n';
	cout << binCoeffs(getk(3)) << '\n';*/
	/*int n=16;
	int k = getk(n);
	cout << k << '\n';
	cout << binCoeffs(k) << '\n';
	bitvec v = binCoeffs(k);
	for (int i=0; i<n; ++i) {
		for (int j=0; j<k; ++j) {
			if (j%n == i && v[j])
				cout << j << ' ';
		}
		cout << endl;
	}
	/*
	for (int i=0; i<20; ++i) {
		cout << binCoeffs(i) << endl;
	}
	
	clock_t t0 = clock();
	bitvec v = binCoeffs(200000);
	clock_t t1 = clock();
	cout << "time to get to stage 200000: " << t1-t0 << " ms." << endl;
	//freopen("minkvals.txt", "w", stdout);
	for (int n=3; n<=1000; n+=2) {
		cerr << n << endl;
		int k = getk(n);		
		cout << "n = " << n;
		if (k < 0) {
			cout << ", k > 32000\n";
		} else {
			cout << ", k = " << k << ", k/n = " << k/n << endl;
		}
	}
	fclose(stdout);
	return 0;
}
*/
