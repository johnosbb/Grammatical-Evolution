
#ifndef _RANDOM_H
#define _RANDOM_H

/*************************************************************************/

class Random
{
public:
  Random();
  ~Random();
  
  void randomize(void);
  int mult(int p, int q);
  int random();
  int randomint(int r); // generates a random int in the range 0 to r-1
  int randomintrange(int r1, int r2);
  float chisquare(int N, int r, int &s);
  int probably(const double pos);
  double normal_distr_rand_var_1_0(void);
  double normal_distr_rand_var(double mean,double stdev);
  int flip (double prob);
  double Gauss(double sigma);
  double Uniform(void);
  
  
};

/*************************************************************************/
#endif




































