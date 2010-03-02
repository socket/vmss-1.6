#include <iostream>

static const char* alph = "0123456789ABCDEF";

int str2int(char* str) {
	register int multiplier = 1;
	register int value = 0;
	char* s_end = str;
	while(*(++s_end)) multiplier *= 10;
	
	while(char c = *str++) {
		value += multiplier * (c - '0');
		multiplier /= 10;
	}
	return value;
}

void splitvalue(char* str, char* &left, char* &right) {
	left = str;
	while(*str++ != '.');
	if ( !*str) right = 0;
	right = --str;
	*right++ = 0;
}

void int2hex(int input, char* buffer) {
	register char* s_buff = buffer;
	register int rem = 0;
	do {
		rem = input % 0x10;
		input = input / 0x10;
		*buffer++ = alph[rem];
	} while ( input != 0 );
	*buffer = 0;
	
	char tmp[256];
	register char* ptmp = tmp + (buffer - s_buff);
	strcpy(tmp, s_buff);
	while(*s_buff) {
		*s_buff++ = *(--ptmp);
	}
}

int v_rank(int val) {
	register int rank = 0;
	while(val=val/10) rank ++;
	return rank+1;
}

int pow10(int q) {
	register int num = 1;
	while(q--) num*=10;
	return num;
}

void fract2hex(int input, char* buffer) {
	char b2[256];
	int2hex(input, b2);
	for (int i=0; i<strlen(b2); ++i ) {
		int src_rank = v_rank(input);
		input *= 0x10;
		int digit = input / pow10(src_rank);
		input %= pow10(src_rank);
		*buffer++ = alph[digit];
	}
	*buffer = 0;
}

void number2hex(char* number, char* output, int size) {
	if ( *number == '-' ) {
		*output++ = *number++;
	}
	char* buff = output;
	memset(buff, size, 0x00);
	
	char *l, *r;
	splitvalue(number, l, r);

	int2hex(str2int(l), buff);
	char* pb = buff;
	while (*pb++);
	*(--pb)++ = '.';
	
	fract2hex(str2int(r), pb);
	
	_asm nop;
}

int main (int argc, char * const argv[]) {
	// insert code here...
	std::cout << "Result: " << str2int("1234567") << "\n";
	char buf1[128];
	strcpy(buf1, "12345.6789");
	char buf[128];
	number2hex(buf1, buf, 128);
	
	std::cout << "\nV3: " << buf;
	
	return 0;
}
