#include "bitvec.h"
#include <vector>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;

bitvec::bitvec(int n) {
	maxdisp = -1;
	size = n;
	bits = (uint64_t*)malloc(8*n);
	memset(bits, 0, size*8);
}

bitvec::~bitvec() {
	free(bits);
}
bitvec bitvec::operator<<(int k) {
	bitvec b(size);
	b = *this;
	int q = k/64, r = k%64;
	copy(b.bits, b.bits+size-q, b.bits+q);
	uint64_t carry = 0, temp;
	int s = 64-r;
	for (int i=q; i<size; ++i) {
		temp = b.bits[i] >> s;
		b.bits[i] <<= r;
		b.bits[i] |= carry;
		carry = temp;
	}
	return b;
}
void bitvec::operator<<=(int k) {
	int q = k/64, r = k%64;
	copy(bits, bits+size-q, bits+q);
	uint64_t carry = 0, temp;
	int s = 64-r;
	for (int i=q; i<size; ++i) {
		temp = bits[i] >> s;
		bits[i] <<= r;
		bits[i] |= carry;
		carry = temp;
	}
}
bitvec bitvec::operator>>(int k) {
	bitvec b(size);
	int q = k/64, r = k%64;
	copy(b.bits+q, b.bits+size, b.bits);
	uint64_t carry = 0, temp;
	int s = 64-r;
	uint64_t mask = (1ULL<<r);
	for (int i=size-q; i>-1; --i) {
		temp = (b.bits[i] & mask) << s;
		b.bits[i] >>= r;
		b.bits[q] |= carry;
		carry = temp;
	}
	return b;
}
void bitvec::operator>>=(int k) {
	int q = k/64, r = k%64;
	copy(bits+q, bits+size, bits);
	uint64_t carry = 0, temp;
	int s = 64-r;
	uint64_t mask = (1ULL<<r);
	for (int i=size-q; i>-1; --i) {
		temp = (bits[i] & mask) << s;
		bits[i] >>= r;
		bits[q] |= carry;
		carry = temp;
	}
}
void bitvec::operator=(const bitvec &v) {
	memset(bits, 0, size*8);
	int bound = v.size < size ? v.size : size;
	for (int i=0; i<bound; ++i)
		bits[i] = v.bits[i];
}
void bitvec::operator=(uint64_t n) {
	memset(bits, 0, size*8);
	bits[0] = n;
}
void bitvec::operator^=(const bitvec &v) {
	int n = min(v.size,size);
	for (int i=0; i<n; ++i) {
		bits[i] ^= v.bits[i];
	}
}
bitvec bitvec::operator^(const bitvec &v) {
	bitvec b(max(v.size,size));
	copy(bits, bits+size, b.bits);
	for (int i=0; i<v.size; ++i) {
		b.bits[i] ^= v.bits[i];
	}
	return b;
}
bool bitvec::match(int n) {
	int q=n/64, r=n%64;
	uint64_t on = (1ULL<<64)-1, off=0;
	if (bits[0]) {
		for (int i=0; i<q; ++i)
			if (bits[i] != on)
				return 0;
		return (bits[q] & ((1ULL<<r)-1)) == ((1ULL<<r)-1);
	} else {
		for (int i=0; i<q; ++i)
			if (bits[i] != 0)
				return 0;
		return (bits[q] & ((1ULL<<r)-1)) == 0;
	}
}
void bitvec::xorwith(const bitvec &other, int start) {
	int q = start/64, r = start%64, bound = min(q+size+1,other.size), j;
	uint64_t mask = (1ULL<<r)-1, c=other.bits[q]>>r;
	j = 0;
	for (int i=q+1; i<bound; ++i) {
		c |= other.bits[i]&mask;
		bits[j] ^= c;
		++j;
		c = other.bits[i]>>r;
	}	
	if (other.size < q+size+1)
		bits[j] ^= c;	
}

bool bitvec::operator[](int n) {
	return (bits[n/64] & (1ULL<<(n%64))) > 0;
}

ostream& operator<<(ostream &out, bitvec &v) {
	int start = v.size*64-1;
	while (v[start] == 0) start--;
	for (int i=start; i>-1; --i) {
		out << v[i];
	}
	return out;
/*
	for (int i=v.size-1; i>-1; --i) {
		for (int j=63; j>-1; --j)
			out << ((v.bits[i]&(1ULL<<j))?'1':'0');
	}
	return out;*/
}

