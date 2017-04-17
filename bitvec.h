#ifndef BITVEC_H
#define BITVEC_H
#include <cstdint>
#include <iostream>
struct bitvec {	
	int size;
	int maxdisp;
	uint64_t* bits;
	bitvec(int n);
	~bitvec();
	bitvec operator<<(int k);
	void operator<<=(int k);
	bitvec operator>>(int k);
	void operator>>=(int k);
	void operator=(const bitvec &v);
	void operator=(uint64_t n);
	void operator^=(const bitvec &v);
	bitvec operator^(const bitvec &v);
	bool match(int n);
	void xorwith(const bitvec &other, int start);
	bool operator[](int n);
};
std::ostream& operator<<(std::ostream &out, const bitvec &v);
#endif
