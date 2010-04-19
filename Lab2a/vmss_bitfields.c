/*
 *  vmss_bitfields.c
 *  Lab2a
 *
 *  Created by Alexey Streltsow on 3/30/10.
 *  Copyright 2010 Zila Networks LLC. All rights reserved.
 *
 */

#include "vmss_bitfields.h"
#include <stdio.h>

const char* bits2string(INTFIELD* fld) {
	static char sbits[128];
	sbits[0] = fld->bits[0].v ? '1' : '0';
	sbits[1] = ':';
	
	for (int i=1; i<BIT_COUNT; ++i) {
		sbits[i+1] = fld->bits[i].v?'1':'0';
	}
	sbits[BIT_COUNT+2] = 0;
	
	return sbits;
}

void string2bits(const char* bitstring, INTFIELD* fld) {
	int i=0;
	const char* istr = bitstring;
	
	while (*bitstring) {
		if ( *bitstring == ' ' || *bitstring == '.' ) {
			bitstring++;
			continue;
		}
		fld->bits[++i].v = (*bitstring++ == '1') ? 1 : 0;
	}
	int count = BIT_COUNT - i;
	while (--count > 0) {
		shift_right(fld);
	}
	
	if (*istr == '-' ) {
		fld->bits[0].v = 1;
	}
}

void shift_left(INTFIELD* fld) {
	for (int i=0; i<BIT_COUNT-1; ++i) {
		fld->bits[i].v = fld->bits[i+1].v;
	}
	fld->bits[BIT_COUNT-1].v=0;
}

void shift_right(INTFIELD* fld) {
	for (int i=BIT_COUNT-1; i>=0; --i) {
		fld->bits[i].v = fld->bits[i-1].v;
	}
	fld->bits[0].v = 0;
}

void sum_bits(INTFIELD* b1, INTFIELD* b2, INTFIELD* res) {
	int add = 0;
	for (int i=BIT_COUNT-1; i>=0; --i) {
		if ( b1->bits[i].v == 0 && b2->bits[i].v == 0 ) {
			res->bits[i].v = add;
			add = 0;
		}
		else if ((b1->bits[i].v == 1 && b2->bits[i].v == 0) || 
						 (b1->bits[i].v == 0 && b2->bits[i].v == 1)) {
			res->bits[i].v = !add;
		}
		else if ( b1->bits[i].v == 1 && b2->bits[i].v == 1 ) {
			res->bits[i].v = add;
			add = 1;
		}
	}
}

void subtract_bits(INTFIELD* b1, INTFIELD* b2, INTFIELD* res) {
	int sub = 0;
	for (int i=BIT_COUNT-1; i>=0; --i) {
		if ( b1->bits[i].v == 0 && b2->bits[i].v == 0 ) {
			res->bits[i].v = sub;
		}
		else if ( b1->bits[i].v == 1 && b2->bits[i].v == 0 ) {
			res->bits[i].v = !sub;
			sub = 0;
		}
		else if ( b1->bits[i].v == 0 && b2->bits[i].v == 1 ) {
			res->bits[i].v = !sub;
			sub = 1;
		}
		else if ( b1->bits[i].v == 1 && b2->bits[i].v == 1 ) {
			res->bits[i].v = sub;
			//sub = 1;
		}
	}
}

void 
reverse_bits(INTFIELD* b, INTFIELD* res) {
	for (int i=0; i<BIT_COUNT; i++ ) {
		res->bits[i].v = !b->bits[i].v;
	}
}

void 
divide_dc(INTFIELD* fsrc, INTFIELD* fdel, char* result) {
	INTFIELD src, del;
	src = *fsrc;
	del = *fdel;
	
	//char *pres = result;
	
	int sign = fsrc->bits[0].v ^ fdel->bits[0].v;
	//fsrc->bits[0].v = fdel->bits[0].v = 0;
	src.bits[0].v = del.bits[0].v = 0;
	
	if ( sign ) *result++ = '-';

	*result++ = '0';
	*result++ = '.';

	for (int i=0; i<BIT_COUNT; i++ ) {
//		printf("--- %d ---\nSHIFT: %s =>", i, bits2string(&src));
		shift_left(&src);
//		printf(" %s\n", bits2string(&src));
//		printf("SUB: %s - ", bits2string(&src));
//		printf("%s = ", bits2string(&del));
		subtract_bits(&src, &del, &src);
//		printf("%s\n", bits2string(&src));
		
		if ( src.bits[0].v == 1 ) { 
			*result++ = '0';
			sum_bits(&src, &del, &src);
		}
		else {
			*result++ = '1';
		}
		
		*result = 0;
		//printf("RES: %s\n", pres);
	}
	*result = 0;
}

int 
bits2int(INTFIELD* b) {
	int value = 0;
	for (int i=1; i<BIT_COUNT; i++) {
		value |= (b->bits[i].v << (BIT_COUNT - i) );
	}
	//double fv = value / pow(10, b->p);
	return value;
}
