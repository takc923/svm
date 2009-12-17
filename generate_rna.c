#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* aucg(int c){
	switch(c){
		case '0':return"A";
		case '1':return"U";
		case '2':return"C";
		case '3':return"G";
	}
}

int main(int argc, char *argv[]){
	int i,j;
	int c;
	int r;
	char *tmp;
	FILE *fp;
	srand(time(NULL));	
	fp = fopen("rna.txt","w");
	if(argc != 3){
		printf("please input number and length.\n");
		exit(1);
	}
	for(j=0;j<atoi(argv[1]);j++){
		for(i=0;i<atoi(argv[2]);i++){
			r = rand()%4;
			printf("aaa\n");
			tmp = aucg(r);
			printf("%s\n",tmp);
			fputs(tmp,fp);
			printf("bbb\n");
		}
		fputs("\n",fp);
	}
	fclose(fp);
}


