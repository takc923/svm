#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char s[1000];
	int c;
	char *family;
	char *name;
	FILE *rfam,*output;
	if(argc != 4){
		printf("please input 3 argument!\nFirst is RNA family name.\n");
		printf("Second is Rfam.fasta.\nThird is output file\n");
		exit(1);
	}
	family = argv[1];
	if((rfam = fopen(argv[2],"r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output = fopen(argv[3],"w")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(s,1000,rfam) != NULL){
		if(strstr(s,family)==NULL)continue;
		fputs("+1 #",output);
		while((c=getc(output)) != '>'){
			if(c != '\n'){
				putc(c,output);
			}
		}
		putc('\n',output);
	}
	fclose(rfam);
	fclose(output);
	return 0;
}
