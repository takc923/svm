#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char aucg(int c){
	switch{
		case '0'return'A';
		case '1'return'U';
		case '2'return'C';
		case '3'return'G';
	}
}

int main(){
	int i;
	int c;
	int r;
	char line1[3],line2[5],line3[6],line4[1],line5[5],line6[6],line7[3];
	FILE *fp;
	srand(time(NULL));	
	fp = fopen("rna.txt",'w');
	for(i=1;i<20;i++){
		r = rand()%4;
		putc(aucg(r),fp);
	}
	free(fp);
}


