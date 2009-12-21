/************************************************************************/
/*                                                                      */
/*   kernel.h                                                           */
/*                                                                      */
/*   User defined kernel function. Feel free to plug in your own.       */
/*                                                                      */
/*   Copyright: Thorsten Joachims                                       */
/*   Date: 16.12.97                                                     */
/*                                                                      */
/************************************************************************/

/* KERNEL_PARM is defined in svm_common.h The field 'custom' is reserved for */
/* parameters of the user defined kernel. You can also access and use */
/* the parameters of the other kernels. Just replace the line 
             return((double)(1.0)); 
   with your own kernel. */

  /* Example: The following computes the polynomial kernel. sprod_ss
              computes the inner product between two sparse vectors. 

      return((CFLOAT)pow(kernel_parm->coef_lin*sprod_ss(a->words,b->words)
             +kernel_parm->coef_const,(double)kernel_parm->poly_degree)); 
  */

/* If you are implementing a kernel that is not based on a
   feature/value representation, you might want to make use of the
   field "userdefined" in SVECTOR. By default, this field will contain
   whatever string you put behind a # sign in the example file. So, if
   a line in your training file looks like

   -1 1:3 5:6 #abcdefg

   then the SVECTOR field "words" will contain the vector 1:3 5:6, and
   "userdefined" will contain the string "abcdefg". */

double k_value(char* a, char* b, int len, int N);
char pair(char* a);
void swap(char* s,int a, int alen, int b, int blen);

double custom_kernel(KERNEL_PARM *kernel_parm, SVECTOR *a, SVECTOR *b) 
     /* plug in you favorite kernel */                          
{
	double kernel_value = 0;
	int N = atoi(kernel_parm->custom);
	int N_c = N/2;
	int n_c, m_c;
	int i, j, n, m;
	char* x;
	char* y;
	int len_a = strlen(a->userdefined);
	int len_b = strlen(b->userdefined);
	int aa=11,alen=6,bb=18,blen=7; //a:始点 alen:前半の長さ b:後半の始点 blen:後半の長さ
	if(len_a == 0 || len_b ==0){
		return((double)0);
	}
	// printf("%d\n",len_a);


	if(len_a >= len_b){
		n = len_b;
		m = len_a;
		x = b->userdefined;
		y = a->userdefined;
	}
	else{
		n = len_a;
		m = len_b;
		x = a->userdefined;
		y = b->userdefined;
	}
	char xx[n],yy[m];
	strcpy(xx,x);strcpy(yy,y);
	swap(xx,aa,alen,bb,blen);swap(yy,aa,alen,bb,blen);
	char *xzenhan,*xkouhan,*yzenhan,*ykouhan;
	xzenhan = xx;	yzenhan = yy;
	xzenhan[aa+blen] = '\0';	yzenhan[aa+blen] = '\0';
	xkouhan = &xx[bb-alen+blen];
	ykouhan = &yy[bb-alen+blen];
	
	n_c = n/2;
	m_c = m/2;
	//printf("%s\n",xkouhan);
  if(N>n){
    if(N>m){
      kernel_value = k_value(xzenhan, yzenhan+(m_c)-(n_c), n, n);
    }
    else{
      for(i=(N_c)-(n_c); i<=m-N+(N_c)-(n_c); i++){
	kernel_value += k_value(xzenhan, yzenhan+i, n, n);
      }
    }
  }
  else{
    for(i=(N-n); i<=(m-N);i++){
      if(i<0){
	kernel_value += k_value(xzenhan-i, yzenhan, n+i, N);
      }
      if(i>=0 && i<=(m-n)){
	kernel_value += k_value(xzenhan, yzenhan+i, n, N);
      }
      if(i>(m-n)){
	kernel_value += k_value(xzenhan, yzenhan+i, m-i, N);
      }
    }
  }

  if(N>n){
    if(N>m){
      kernel_value = k_value(xkouhan, ykouhan+(m_c)-(n_c), n, n);
    }
    else{
      for(i=(N_c)-(n_c); i<=m-N+(N_c)-(n_c); i++){
	kernel_value += k_value(xkouhan, ykouhan+i, n, n);
      }
    }
  }
  else{
    for(i=(N-n); i<=(m-N);i++){
      if(i<0){
	kernel_value += k_value(xkouhan-i, ykouhan, n+i, N);
      }
      if(i>=0 && i<=(m-n)){
	kernel_value += k_value(xkouhan, ykouhan+i, n, N);
      }
      if(i>(m-n)){
	kernel_value += k_value(xkouhan, ykouhan+i, m-i, N);
      }
    }
  }
  //printf("%f\n",kernel_value);
  return(kernel_value); 
}

double k_value(char* a, char* b, int len, int N)
{
  int i,j;
  double value = 0;

  char* pa = a;
  char* pb = b;

  double k[len][len];
  double l[len];

  for(i=0;i<len;i++){
    for(j=0;j<len;j++){
      k[i][j] = 1;
    }
    l[i] = 0;
  }

  for(j=(len-2);j>=(len-N);j--){
    for(i=0;i<=j;i++){
      if((*(pa+i) == pair(pa+len-1-j+i)) && (*(pb+i) == pair(pb+len-1-j+i)))
	l[j-i] += k[i+1][j+1-i];
      k[i][j-i] = k[i][j+1-i] + l[j-i];
      //printf("%f ",k[i][j]);
    }
  }

  for(i=0; i<=(len-N); i++){
      value += k[i][len-N-i];
  }

  return value;
}

char pair(char* a)
{
	switch (*a) {
		case 'A':return('U');
		case 'U':return('A');
		case 'C':return('G');
		case 'G':return('C');
		default: return(*a);
	}
}

void swap(char* s,int a, int alen, int b, int blen){
	int i;
	int n=strlen(s);
	char tmp[n];
	for(i=0;i<a;i++)		tmp[i]				= s[i];
	for(i=0;i<blen;i++)		tmp[a+i]			= s[b+i];
	for(i=0;i<b-a-alen;i++)	tmp[a+blen+i] 		= s[a+alen+i];
	for(i=0;i<blen;i++)		tmp[b-alen+blen+i]	= s[a+i];
	for(i=0;i<n-b-blen;i++)	tmp[b+blen+i]		= s[b+blen+i];
	for(i=0;i<n;i++)		s[i]				= tmp[i];
	return;
}
