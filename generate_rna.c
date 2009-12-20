#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define A 11
#define ALEN 6
#define B 18
#define BLEN 7
#define L 35
void generate_positive(FILE *fp,int n);
void generate_negative(FILE *fp,int n);
char aucg();
char pair(char a);

int main(int argc, char *argv[]){
	int i,j;
	int c;
	int r;
	char *tmp;
	FILE *fp;
	srand(time(NULL));	
	if(argc != 3){
		printf("please input number and output file.\n");
		exit(1);
	}
	fp = fopen(argv[2],"w");
	int n = atoi(argv[1]);//作る数。
	int half = (int)(n/2);
	generate_positive(fp,half);
	generate_negative(fp,half);
	fclose(fp);
}

//fp:入力するファイルポインタ,n:作る数
void generate_positive(FILE *fp,int n){
	int i,j;
	char l1[A+1],l2[ALEN+1],l3[B-A-ALEN+1],l4[BLEN+1],l5[ALEN+1],l6[L-B-BLEN-ALEN+1];
	for(j=0;j<n;j++){
		for(i=0;i<A;i++){
			l1[i] = aucg();
		}
		l1[i] = '\0';
		for(i=0;i<ALEN;i++){
			l2[i] = aucg();
		}
		l2[i] = '\0';
		for(i=0;i<B-A-ALEN;i++){
			l3[i] = aucg();
		}
		l3[i] = '\0';
		for(i=0;i<BLEN;i++){
			l4[i] = pair(l1[A-1-i]);
		}
		l4[i] = '\0';
		for(i=0;i<ALEN;i++){
			l5[i] = pair(l2[ALEN-1-i]);
		}
		l5[i] = '\0';
		for(i=0;i<L-B-BLEN-ALEN;i++){
			l6[i] = aucg();
		}
		l6[i] = '\0';
		fprintf(fp,"+1 #%s%s%s%s%s%s\n",l1,l2,l3,l4,l5,l6);
	}
}

//fp:入力するファイルポインタ,n:作る数
void generate_negative(FILE *fp,int n){
	int i,j;
	char l1[A+1],l2[ALEN+1],l3[B-A-ALEN+1],l4[BLEN+1],l5[ALEN+1],l6[L-B-BLEN-ALEN+1];
	for(j=0;j<n;j++){
		for(i=0;i<A;i++){
			l1[i] = aucg();
		}
		l1[i] = '\0';
		for(i=0;i<ALEN;i++){
			l2[i] = aucg();
		}
		l2[i] = '\0';
		for(i=0;i<B-A-ALEN;i++){
			l3[i] = aucg();
		}
		l3[i] = '\0';
		for(i=0;i<BLEN;i++){
			l4[i] = aucg();
		}
		l4[i] = '\0';
		for(i=0;i<ALEN;i++){
			l5[i] = aucg();
		}
		l5[i] = '\0';
		for(i=0;i<L-B-BLEN-ALEN;i++){
			l6[i] = aucg();
		}
		l6[i] = '\0';
		fprintf(fp,"-1 #%s%s%s%s%s%s\n",l1,l2,l3,l4,l5,l6);
	}
}
//AUCGのいずれかをランダムで出力する。
char aucg(){
	int r = rand()%4;
	switch(r){
		case 0: return 'A';
		case 1: return 'U';
		case 2: return 'C';
		case 3: return 'G';
		default:return 'A';
	}
}

char pair(char a)
{
	switch (a) {
		case 'A':return('U');
		case 'U':return('A');
		case 'C':return('G');
		case 'G':return('C');
		default: return(a);
	}
}
