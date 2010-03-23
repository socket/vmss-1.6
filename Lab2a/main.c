#include <stdio.h>

#define BIT_COUNT		6
#define POINT_POS		2

struct BITFIELD_T {
	unsigned v : 1;
};

typedef struct BITFIELD_T BITFIELD;

struct INTFIELD_T {
	BITFIELD bits[BIT_COUNT];
};

typedef struct INTFIELD_T INTFIELD;

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
	while (*bitstring) {
		if ( *bitstring == ' ' ) {
			bitstring++;
			continue;
		}
		fld->bits[i++].v = (*bitstring++ == '1') ? 1 : 0;
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

void reverse_bits(INTFIELD* b, INTFIELD* res) {
	for (int i=0; i<BIT_COUNT; i++ ) {
		res->bits[i].v = !b->bits[i].v;
	}
}

int main (int argc, const char * argv[]) {
	/*INTFIELD b1, b2, b3;
	string2bits("00 1110", &b1);
	string2bits("00 1101", &b2);
	subtract_bits(&b1, &b2, &b3);
	printf("%s", bits2string(&b3));
	
	
	return 0;*/
	/// 00,1001 / 00,1101
	char result[100];
	int pos = 0;
	
	INTFIELD src, del, rdel;
	string2bits("00 1001", &src);
	string2bits("00 1101", &del);
	
	for (int i=0; i<BIT_COUNT; i++ ) {
		shift_left(&src);
		reverse_bits(&del, &rdel);
		
		printf("%s\n", bits2string(&src));
		printf("%s\n", bits2string(&del));
		
		subtract_bits(&src, &del, &src);
		printf("%s\n", bits2string(&src));
		printf("-----\n");

		if ( src.bits[0].v == 1 ) { 
			result[pos++] = '0';
			sum_bits(&src, &del, &src);
		}
		else {
			result[pos++] = '1';
		}
	}

	result[pos] = 0;
	
	printf("%s", result);
	
	return 0;
}
