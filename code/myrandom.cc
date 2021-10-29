/*************************************************************************/
/*                                                                       */
/*             FILE   :  MYRANDOM.CC                                     */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG - SEPT 1996                                 */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements functionality declared in header file "myrandom.h".       */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#include "myrandom.h"
#include <stdio.h>
#include <stdlib.h>
static int seed;

/*************************************************************************/
void myrandomize()
{
  //printf("\n enetring myrandom()");
  // The current value of the seed is stored in file "state.dat". 
  #define MAX_SEED 32767

  FILE *fp;
  
  if ((fp=fopen("state.dat","r"))==NULL) {
    fprintf(stderr,"Linear Congruential Method:");
    fprintf(stderr,"\n  Error: could not open file state.dat");
    fprintf(stderr,"\n  Setting seed = 1 and creating file 'state.dat'\n");
    seed = 1;
  }
  else {
     fscanf(fp,"%d",&seed);
     fclose(fp);
     seed++;
     if(seed > MAX_SEED) seed = 1;
  }
  //printf("\n seed = %d",seed);
  fp=fopen("state.dat","w");
  fprintf(fp,"%d",seed);
  fclose(fp);
}
/*************************************************************************/
int mult(int p, int q)
{
  const long m = 100000000;
  const long m1 = 10000;

  int p1,p0,q1,q0;
  p1 = p/m1;
  p0 = p % m1;
  q1 = q/m1;
  q0 = q % m1;
  return (((p0*q1+p1*q0) % m1)*m1+p0*q0) % m;
}
/*************************************************************************/
int myrandom()
{
  const long m = 100000000;
  const long bd = 31415821;

  seed = (mult(seed,bd)+1) % m;
  return seed;
}
/*************************************************************************/
int randomint(int r)
{
  /**************************************************************/
  /* Generates a random number in the range 0 to r-1            */
  /**************************************************************/

  const long m = 100000000;
  const long m1 = 10000;
  const long bd = 31415821;

  seed = (mult(seed,bd)+1) % m;
  //printf(" <<%d>> ",seed);
  return ((seed/m1)*r)/m1;
}
/*************************************************************************/

int randomintrange(int r1,int r2)
{
  /**************************************************************/
  /* Generates a random number in the range r1  to r2 -1         */
  /**************************************************************/

  const long m = 100000000;
  const long m1 = 10000;
  const long bd = 31415821;
  r2 = r2 - r1;
  seed = (mult(seed,bd)+1) % m;
  //printf(" <<%d>> ",seed);
  return (((seed/m1)*r2)/m1) + r1;
}

/*************************************************************************/
float chisquare(int N, int r, int &s)
{
  /**************************************************************/
  /* N is the number of randoms generated, in the range 0-r,    */
  /* and upon return s will contain the value of the seed used. */
  /* the result from chisquare should be in the range 2*sqrt(r) */
  /* for 90% of the tests.                                      */
  /**************************************************************/
 int i,t,f[r];
 myrandomize();
 seed--;
 s=seed;
 FILE *fp = fopen("state.dat","w");
 fprintf(fp,"%d",seed);
 fclose(fp);
 for(i=0; i<r; i++)
   f[i] = 0;
 for(i=0; i<N; i++)
   f[randomint(r)]++;
 for(i=0, t=0; i<r; i++)
   t+= f[i]*f[i];
 return (float)((r*t/N)-N);
}
/*************************************************************************/
int probably(const double pos)
{
  /**************************************************************/
  /* Based on weighted coin toss. Returns boolean value true or */
  /* false depending on the value 'pos' which is the probability*/
  /* factor. Probability factor must be in range 0 - 1 and can  */
  /* be up to four decimal places.                              */
  /**************************************************************/

  // printf("\n    entering PROBABLY.");

  const int MAX_RANGE = 10000;
  if((pos < 0)||(pos > 1)) {
    fprintf(stderr,"\n ERROR: probability factor (of %f) 0 < p > 1",pos);
    fprintf(stderr,"\n EXITING! \n\n");
    exit(1);
  } 
  if(pos <= 0.000000) return 0;
  if(pos == 1.000000) return 1;
  double new_pos = (int)(pos * (double)(MAX_RANGE));
  if((int)(new_pos) > randomint(MAX_RANGE)) return 1;
  else return 0;

  // printf("\n    leaving PROBABLY."); 

}
/*************************************************************************/


