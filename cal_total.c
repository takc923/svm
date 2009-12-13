#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 値を返すswap
 */

int main(){
	int i,j,k;
	char s[1000],t[1000];
	char *new;
	char *space;
	FILE *model1,*model2,*output1,*output2;
	
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
	for(i=0;i!=11;i++){
		fgets(s,256,model1);
		fgets(t,256,model2);
	}
	space = strchr(s,' ');	
	*space = '\0';
	space = strchr(t,' ');	
	*space = '\0';
	printf("%s\n%s\n",s,t);
	fclose(model1);
	fclose(model2);

	
	fclose(output1);
	fclose(output2);
	return 0;
}
