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

int main(int argc, char *argv[]){
	int i,j;
	int c;
	int r;
	char *tmp;
	FILE *fp;
	srand(time(NULL));	
	fp = fopen("rna.txt","w");
	if(argc != 2){
		printf("please input number.\n");
		exit(1);
	}
	int n = atoi(argv[1]);//作る数。
	int half = (int)(n/2);
	printf("half=%d\n",half);
	printf("a\n");
	generate_positive(fp,half);
	generate_negative(fp,half);
	printf("a\n");
	fclose(fp);
}

//fp:入力するファイルポインタ,n:作る数
void generate_positive(FILE *fp,int n){
	int i,j;
	char l1[A],l2[ALEN],l3[B-A-ALEN],l4[BLEN],l5[L-B-BLEN],l6[L-B-BLEN-ALEN];
	for(j=0;j<n;j++){
		for(i=0;i<A;i++){
			l1[i] = aucg();
		}
		for(i=0;i<ALEN;i++){
			l2[i] = aucg();
		}
		for(i=0;i<B-A-ALEN;i++){
			l3[i] = aucg();
		}
		for(i=0;i<BLEN;i++){
			l4[i] = l1[A-1-i];
		}
		for(i=0;i<ALEN;i++){
			l5[i] = l2[ALEN-1-i];
		}
		for(i=0;i<L-B-BLEN-ALEN;i++){
			l6[i] = aucg();
		}
		fprintf(fp,"+1 #%s%s%s%s%s\n",l1,l2,l3,l4,l5);
	}
}

//fp:入力するファイルポインタ,n:作る数
void generate_negative(FILE *fp,int n){
	int i,j;
	char l1[A],l2[ALEN],l3[B-A-ALEN],l4[BLEN],l5[L-B-BLEN],l6[L-B-BLEN-ALEN];
	for(j=0;j<n;j++){
		for(i=0;i<A;i++){
			l1[i] = aucg();
		}
		for(i=0;i<ALEN;i++){
			l2[i] = aucg();
		}
		for(i=0;i<B-A-ALEN;i++){
			l3[i] = aucg();
		}
		for(i=0;i<BLEN;i++){
			l4[i] = aucg();
		}
		for(i=0;i<ALEN;i++){
			l5[i] = aucg();
		}
		for(i=0;i<L-B-BLEN-ALEN;i++){
			l6[i] = aucg();
		}
		fprintf(fp,"+1 #%s%s%s%s%s\n",l1,l2,l3,l4,l5);
	}
}
//AUCGのいずれかをランダムで出力する。
char aucg(){
	int r = rand()%4;
	char c[1];
	switch(r){
		case '0': return 'A';
		case '1': return 'U';
		case '2': return 'C';
		case '3': return 'G';
	}
}
