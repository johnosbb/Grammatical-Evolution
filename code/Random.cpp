
#include "Random.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int seed;

static int isinit = 0;


Random::Random()
{
}

Random::~Random()
{
}

/*************************************************************************/
void Random::randomize(void)
{

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
int Random::mult(int p, int q)
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
int Random::random()
{
  const long m = 100000000;
  const long bd = 31415821;

  seed = (mult(seed,bd)+1) % m;
  return seed;
}
/*************************************************************************/
int Random::randomint(int r)
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


int Random::randomintrange(int r1,int r2)
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
float Random::chisquare(int N, int r, int &s)
{
  /**************************************************************/
  /* N is the number of randoms generated, in the range 0-r,    */
  /* and upon return s will contain the value of the seed used. */
  /* the result from chisquare should be in the range 2*sqrt(r) */
  /* for 90% of the tests.                                      */
  /**************************************************************/
 int i,t,f[r];
 randomize();
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


int Random::probably(const double pos)
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


double Random::normal_distr_rand_var_1_0(void)
{
  return normal_distr_rand_var(0,1);
}


//returns a normal random variable using given mean and stdev
double Random::normal_distr_rand_var(double mean,double stdev)
{
    return mean + Gauss(stdev);
}


double Random::Uniform(void)
{
    double result;

    if (!isinit) {
	srand(seed);
	isinit = 1;
    }
    result = ((double) rand());
    result /= RAND_MAX;

    return (result);
}


double Random::Gauss(double sigma)
{
    /* System generated locals */
    double ret_val;

    /* Local variables */
    static double d, u, x, y, u0, u1, u2;


/* 	SIGMA	--> standard deviation */

/* L1: */
    u = Uniform();
    u0 = Uniform();
    if (u >= .919544406) {
	goto L2;
    }
    x = (u0 + u * .825339283) * 2.40375766 - 2.11402808;
    goto L10;
  L2:
    if (u < .965487131) {
	goto L4;
    }
  L3:
    u1 = Uniform();
    y = sqrt(4.46911474 - log(u1) * 2.);
    u2 = Uniform();
    if (y * u2 > 2.11402808) {
	goto L3;
    }
    goto L9;
  L4:
    if (u < .949990709) {
	goto L6;
    }
  L5:
    u1 = Uniform();
    y = u1 * .273629336 + 1.84039875;
    u2 = Uniform();
    if (exp(y * -.5 * y) * .39894228 - .443299126 + y * .209694057 < u2 *
	.0427025816) {
	goto L5;
    }
    goto L9;
  L6:
    if (u < .925852334) {
	goto L8;
    }
  L7:
    u1 = Uniform();
    y = u1 * 1.55066917 + .289729574;
    u2 = Uniform();
    if (exp(y * -.5 * y) * .39894228 - .443299126 + y * .209694057 < u2 *
	.0159745227) {
	goto L7;
    }
    goto L9;
  L8:
    u1 = Uniform();
    y = u1 * .289729574;
    u2 = Uniform();
    if (exp(y * -.5 * y) * .39894228 - .382544556 < u2 * .0163977244) {
	goto L8;
    }
  L9:
    x = y;
    if (u0 >= .5) {
	x = -y;
    }
  L10:
    ret_val = sigma * x;
    return ret_val;
}












