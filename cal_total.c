#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 値を返すswap
 */

int main(){
	int i,j,k;
	int total;
	char s[1000],t[1000];
	char *new;
	char *space;
	FILE *model1,*model2,*output1,*output2,*output3;
	float told;//thresh old

	//最初に全てファイルオープン
	if((model1 = fopen("model1.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((model2 = fopen("model2.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output1 = fopen("output1.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output2 = fopen("output2.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output3 = fopen("output3.txt","w")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	//配列の数を取得
	for(i=0;i!=9;i++){
		fgets(s,256,model1);
		fgets(t,256,model2);
	}
	space = strchr(s,' ');	
	*space = '\0';
	space = strchr(t,' ');	
	*space = '\0';
	total = atoi(s);

	//閾値を取得
	for(i=0;i!=2;i++){
		fgets(s,256,model1);
		fgets(t,256,model2);
	}
	space = strchr(s,' ');	
	*space = '\0';
	space = strchr(t,' ');	
	*space = '\0';
	told = atof(s)+atof(t);

	fclose(model1);
	fclose(model2);

	for(i=0;i<total;i++){
		fgets(s,256,output1);
		fgets(t,256,output2);
		fprintf(output3,"%f\n",atof(s)+atof(t));
	}

	
	fclose(output1);
	fclose(output2);
	fclose(output3);
	return 0;
}
