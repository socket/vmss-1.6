#include <stdio.h>

typedef struct BITFIELD_T BITFIELD;

struct BITFIELD_T {
	unsigned v : 1;
};

int get_hibit(int value) {
	int i = 0;
	while (!(value & (1 << (31 - i))) && i < 31 ) i++;
	return 31-i;
}

int get_bits(int value, int hi, int lo) {
	return (value >> lo) ;//&  ~((~0) << (hi - lo));
}

int get_hibits(int value, int count) {
	int hb = get_hibit(value);
	return get_bits(value, hb, hb-count);
}

int set_bit(int value, int bit) {
	return value & (1 << bit);
}

int clear_bit(int value, int bit) {
	return value & ~(1 << bit);
}

const char* bin(int value) {
	static char bin[64];
	int k = 0;
	int h = get_hibit(value);
	for (int i=h; i>=0; i--) {
		bin[k++] = value & (1 << i) ? '1' : '0';
	}
	bin[k] = 0;
	return bin;
}

int main (int argc, const char * argv[]) {
  //int src = 0x1234;
	//int del = 0x56;
	/*
	int hb_del = get_hibit(del);
	int hb_src = get_hibit(src);
	int bitpos = hb_src;
	int val = 0;
	
	if ( hb_src > hb_del ) {
		val = get_hibits(src, hb_del);
		bitpos -= hb_del;
		if ( hval > hb_del ) {
			// put 1 to result and add next bit
			val = hval - hb_del;
			val <<= 1;
			if ( bitpos >= 0 ) {
				val |= get_bits(src, bitpos--, 1);
			}
		}
		else {
			// put 0 to result and add next bit
			val <<= 1;
			if ( bitpos >= 0 ) {
				val |= get_bits(src, bitpos--, 1);
			}
		}

	}
	else {
		
	}
	*/
	/*
	int src = 550;
	int del = 24;
	
	int hb_del = get_hibit(del);	// количество бит в делителе
	int hb_src = get_hibit(src);	// кол-во бит в исх числе
	int bitpos = 0;								// текущая позиция в исх числе
	int val = 0;									// стартовое снесенное число
	
	bitpos = get_hibit(src);

	printf("SRC: %s\n", bin(src));
	printf("DEL: %s\n", bin(del));
	
	//do {
		if ( hb_del > bitpos ) {
			src <<= hb_del - hb_src;
			// FIXME: учесть где там запятая
		}
		
		bitpos = get_hibit(src);
		printf("POS: %d DELPOS: %d\n", bitpos, hb_del);
		val = get_bits(src, bitpos, bitpos-hb_del);							// сносим старшие биты
		printf("%s\n", bin(val));
	
		if ( val > del ) {
			// выписываем 1 в результат
			printf("1");
		}
		else {
			// выписываем 0 в результат
			printf("0");
		}

	//} while (bitpos > 0 && val > 0);
	
	get_bits(0xFFFFFFFF, 5, 0);
	*/

	char res[128];
	int i = 0;
	
	int src = 800;
	int del = 2;
	int rem = src;
	int n = 0;
	
	while (get_hibit(del) < get_hibit(src)) {
		del <<= 1;
		n++;
	}
	n++;
	
	while ( n-- ) {
		src -= del;
		if ( src >= 0 ) {
			del >>= 1;
			res[i++] = '1';
		}
		else {
			src += del;
			res[i++] = '0';
		}
	}
	
	
	res[i] = 0;
	
	printf("%s", res);
	return 0;
}
