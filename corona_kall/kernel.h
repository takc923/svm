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
  // printf("%d\n",N);

  if(len_a == 0 || len_b ==0){
    return((double)0);
  }


  if(len_a >= len_b){
    m = len_a;
    n = len_b;
    x = b->userdefined;
    y = a->userdefined;
  }
  else{
    m = len_b;
    n = len_a;
    x = a->userdefined;
    y = b->userdefined;
  }

  n_c = n/2;
  m_c = m/2;

  if(N>n){
    if(N>m){
      kernel_value = k_value(x, y+(m_c)-(n_c), n, n);
    }
    else{
      for(i=(N_c)-(n_c); i<=m-N+(N_c)-(n_c); i++){
	kernel_value += k_value(x, y+i, n, n);
      }
    }
  }
  else{
    for(i=(N-n); i<=(m-N);i++){
      if(i<0){
	kernel_value += k_value(x-i, y, n+i, N);
      }
      if(i>=0 && i<=(m-n)){
	kernel_value += k_value(x, y+i, n, N);
      }
      if(i>(m-n)){
	kernel_value += k_value(x, y+i, m-i, N);
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
