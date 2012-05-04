#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shuffle(char music[], int size);

int main(int argc, char *argv[]){
	char s[1000];
	int c;
	int i=0;
	char line[1000];
	char *family;
	char *name;
	FILE *rfam,*output;

	srand((unsigned) time(NULL));
	if(argc != 3){
		printf("please input 2 argument!\n");
		printf("First is family name.\nSecond is output file\n");
		exit(1);
	}
	family = argv[1];
	if((rfam = fopen("Rfam.fasta","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output = fopen(argv[2],"w")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(s,1000,rfam) != NULL){
		if(strstr(s,family)==NULL)continue;
		fputs("+1 #",output);
		while((c=getc(rfam)) != '>'){
			if(c != '\n'){
				putc(c,output);
		    	line[i++]=c;
			}
		}
		putc('\n',output);
		line[i++] = '\0';
		shuffle(line, i-1);
		fputs("-1 #", output);
		fputs(line, output);
		putc('\n', output);
		i=0;
	}
	fclose(rfam);
	fclose(output);
	return 0;
}

void shuffle(char music[], int size)
{
    int j;
    for (j = 0; j < size; j++) {
      int r = (int)(rand()%size);
      char m = music[j];
      music[j] = music[r];
      music[r] = m;
    }
}
