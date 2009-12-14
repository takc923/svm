#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[])
{
  FILE *ifp, *ofp;
  int c;

  if(argc != 3){
    fprintf(stderr, "Enter 2 files.\n");
    exit(1);
  }
  else{
    if((ifp = fopen(*++argv, "r")) == NULL){
      fprintf(stderr, "can't open %s.\n", *argv);
      return 1;
    }
    else{
      if((ofp = fopen(*++argv, "w")) == NULL){
	fprintf(stderr, "can't open %s.\n", *argv);
	return 1;
      }
      else{
	while((c=getc(ifp)) != EOF){
	  if(c == '6'){
	    if((c=getc(ifp)) == 'S'){
	      if((c=getc(ifp)) == ';'){
		fputs("-1 #", ofp);
		while((c=getc(ifp)) != '>'){
		  if(c != '\n'){
		    putc(c, ofp);
		  }
		}
		putc('\n', ofp);
	      }
	    }
	  }
	}
      }
    }
    fclose(ifp);
    fclose(ofp);
  }
}
