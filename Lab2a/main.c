#include <stdio.h>

#include "vmss_common.h"
#include "vmss_convert.h"
#include "vmss_bitfields.h"

int main (int argc, const char * argv[]) {
	char buffer[256];
	char *pb = buffer;
	FILE* hsrc = fopen("INPUT.txt", "r");
	
	if ( !hsrc ) {
		printf("Cannot open input file\n");
		return -1;
	}
	
	int bitcount = BIT_COUNT - 1;
	
	while (pb = fgets(buffer, 256, hsrc) ) {
		char *left, *right;
		vmss_strchop(pb);

		left = right = pb;
		while(*right && *right != ':') right++;
		*right++ = '\0';
		
		// convert dec to bin
		printf("%s / %s =>", left, right);
		
		char left2[128], right2[128];
		int countl = vmss_removedot(left, left2);
		int countr = vmss_removedot(right, right2);
		int result = 0;
		
		if ( countl > countr ) {
			vmss_addzeroes( right2, countl-countr );
		}
		else {
			vmss_addzeroes( left2, countr-countl );
		}

		double ld, rd;
		result |= vmss_str2double(left2, 10, &ld);
		result |= vmss_str2double(right2, 10, &rd);		
		
		if ( rd == 0 ) {
			result = -1;
		}
		
		// convert back
		
		char binleft[128];
		char binright[128];
		int power = 0;		
		
		//printf("%s / %s =>", left2, right2);
		if ( SUCCESS ( result ) ) { 
			while (fabs(ld) > fabs(rd) ) {
				rd *= 10.0f;
				power++;
			}
			
			
			result |= vmss_double2str(ld, 2, binleft, bitcount);
			result |= vmss_double2str(rd, 2, binright, bitcount);
			
			printf("%f / %f => %s / %s =>", ld, rd, binleft, binright);
		}
		
		if ( SUCCESS( result ) ) {
			char binres[128], binresdec[128], binreshex[128];
			INTFIELD src, del;

			string2bits(binleft, &src);
			string2bits(binright, &del);
			//shift_right(&src);
			//shift_right(&del);
			//printf("DIV: %s / ", bits2string(&src));
			//printf("%s\n", bits2string(&del));
			divide_dc(&src, &del, binres);
			
			printf("BIN: %s\n", binres);
			
			double outval;
			if ( ! SUCCESS( vmss_str2double(binres, 2, &outval) ) ) {
				printf("INVALID 1");
				continue;
			}
			
			while( power-- ) outval *= 10.0f;
			
			vmss_double2str(outval, 10, binresdec, BIT_COUNT);
			vmss_double2str(outval, 16, binreshex, BIT_COUNT);
			
/*
			vmss_str2number(binres, 2, 10, binresdec, BIT_COUNT);
			
			divide_dc(&src, &del, binres);
			vmss_str2number(binres, 2, 16, binreshex, BIT_COUNT);
*/			
			printf("============================\n Result: %s [%s]\n", binresdec, binreshex);

		}
		else {
			printf("INVALID");
		}
		printf("\n");
	}
	
	fclose(hsrc);
	
	return 0;
}

