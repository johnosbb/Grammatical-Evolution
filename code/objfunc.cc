/*************************************************************************/
/*                                                                       */
/*             FILE   :  OBJFUNC.CC                                      */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG 1996/1997                                   */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "objfunc.hpp".             */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#include <math.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "objfunc.hpp"
#include "myrandom.h"
#include "ge.hpp"
/*************************************************************************/
objective_function::objective_function()
{
  if(ELITISM != F) {
    powerF1  = 24;
    powerF2 =  48;
    powerF3  = 15;
    powerF4  = 48;
    powerF6  = 48;
    powerF7  = 16;
    powerF8  = 96;
    powerF9  = 24;
    powerF10 = 24;
  }
  else
    powerF1  = 12;
    powerF2  = 24;
    powerF3  = 7;
    powerF4  = 24;
    powerF6  = 24;
    powerF7  = 8;
    powerF8  = 48;
    powerF9  = 12;
    powerF10 = 12;
}    
/*************************************************************************/
double objective_function::my_abs(double x)
{
  if( x < 0) return x * (-1);
  else return x;
}
/*************************************************************************/
int objective_function::near(double x, double y, double x1, double y1,double dist)
{
  if (((x-dist)  <= x1) && ((x+dist)  >= x1) && 
     ((y-dist)  <= y1) && ((y+dist)  >= y1)) 
    return 1;
  else return 0;   
}
/*************************************************************************/
double objective_function::objfuncF1(double genes[])
{
  /**************************************************/
  /* TEST FUNCTION : INVERTED DEJONG F1             */
  /* 3 genes in the range -5.12 < g < 5.12          */
  /* Maximum of infinity is at (x,y,z) = (0,0,0)    */ 
  /* Result of 0.9 (coef = 11000)                   */
  /* for ie. (0.01,0,0,                             */
  /* 0.0).                                          */
  /**************************************************/

 double temp;
 const double coef = 10000;
 temp = pow(genes[0],2) + pow(genes[1],2) + pow(genes[2],2);

 return pow(1-temp/coef,powerF1);   // normalise data using coefficient to be 
                                    // in the range {0,1}, and magnify error.

}
/*************************************************************************/
double objective_function::objfuncF2(double genes[])
{
  /**************************************************/
  /* TEST FUNCTION : INVERTED DEJONG F2             */
  /* 2 genes in the range -2.048 < g < 2.048        */
  /* maximum result is +3905.926226841600           */
  /*   located at x1=-2.048e+00, x2=-2.048e+00      */
  /* minium result is +0.000000000000               */
  /*   located at x1=+1.000e+00, x2=+1.000e+00      */
  /*                                                */
  /**************************************************/

  double res;
  // double max = 3905.926226841600;
  double temp = pow(genes[0],2);

  res = 100 * pow(temp -genes[1],2) + pow(1-genes[0],2);

  if((res > -10e-20)&&(res < 10e-20)) res = 0;
  if(res==0) return 1;
  else return 1/(pow(res+1.009,powerF2));



}
/*************************************************************************/
double objective_function::objfuncF3(double genes[])
{
  /**************************************************/
  /* TEST FUNCTION : DEJONG F3                      */
  /* 5 genes in the range -5.12 < g < 5.12          */
  /* chosen as a test for handling discontinuities  */
  /*                                                */
  /* Maximum of 25 at (5.11,5.11,5.11,5.11,5.11).   */
  /**************************************************/

  double coef = -25;
  int res = 0;
  for(int i=0; i<5; i++) 
    res += (int)(genes[i]);
  return pow((double)(res)/coef,powerF3);
}
/*************************************************************************/
double objective_function::objfuncF4(double genes[])
{
  /**************************************************/
  /* TEST FUNCTION : DEJONG F4                      */
  /* 30 genes in the range -1.28 < g < 1.28         */
  /* Maximum is 1.268417e+03 for all x = plus/minus */
  /* 1.28 and Gauss(1). Minimum is 1.224745 for all */
  /* x = plus/minus 0.0 and Gauss(0).               */
  /**************************************************/

  double res,num,gauss;
  double min = 1.224745;
  double max = 1.268417e+03;

  res=0;
  for(int i=0; i<30; i++) {
    num = (double)(randomint(101))/100;
    gauss = exp(pow(num,2) * 0.50)/sqrt(2*pi);
    res += (i+1) * pow(genes[i],4) + gauss;
  }
  double res1 = (res-min)/(max-min);
  return pow(1 - res1,powerF4);

}
/*************************************************************************/
double objective_function::objfuncF5(double genes[])
{ 
  /*******************************************************/
  /* TEST FUNCTION : DEJONG F5   (Multimodal)            */
  /* 9 points distributed through landscape at (-10,-10) */
  /* (-10,0) (-10,10) (0,-10) (0,0) (0,10) (10,-10)      */
  /* (10,0) (10,10). ga required to find 2 points.       */
  /* 4 genes in the range -16.384 < g < 16.384. Maximum  */
  /* 2.002of 1.002 at (x,y) = (0,0) (x1,y1) = (0,-10)    */
  /*******************************************************/

  double s    = 10.00000e+00;
  double coef = +2.0020e+00;
  
  double result;
  double a,a1,b,b1,c,c1;

  a = pow(genes[0]+s,6); a1 = pow(genes[1]+s,6);
  b = pow(genes[0],6);   b1 = pow(genes[1],6);
  c = pow(genes[0]-s,6); c1 = pow(genes[1]-s,6);

  result = 0.002 + (1/(1+ a + a1)) + (1/( 1+ a + b1)) +
              (1/( 1+ a + c1)) + (1/( 1+ b + a1)) +
              (1/( 1+ b + b1)) + (1/( 1+ b + c1)) +
              (1/( 1+ c + a1)) + (1/( 1+ c + b1)) +
              (1/( 1+ c + c1));
  
  a = pow(genes[2]+s,6); a1 = pow(genes[3]+s,6);
  b = pow(genes[2],6);   b1 = pow(genes[3],6);
  c = pow(genes[2]-s,6); c1 = pow(genes[3]-s,6);

  result = result +   (1/(1+ a + a1)) + (1/( 1+ a + b1)) +
              (1/( 1+ a + c1)) + (1/( 1+ b + a1)) +
              (1/( 1+ b + b1)) + (1/( 1+ b + c1)) +
              (1/( 1+ c + a1)) + (1/( 1+ c + b1)) +
              (1/( 1+ c + c1));
  if (((genes[0]-2)  <= genes[2]) && ((genes[0]+2)  >= genes[2]) && 
      ((genes[1]-2)  <= genes[3]) && ((genes[1]+2)  >= genes[3]))
    result = result/2;
  return result/coef;
}
/*************************************************************************/
double objective_function::objfuncF6(double genes[])
{
  /************************************************************/
  /* F6: Rastrigin's function                                 */
  /* According to Hinterding, Gielewski and Peachy (1995)     */
  /*  Proc. 6th ICGA pp 65--72                                */
  /* minimum at x_i = {0}, i = 1,...,n : f(x) = 0             */
  /* maximum at x_i = plus/minus 4.523 f(x) = 201.767         */
  /************************************************************/
  //double min = 0;
  double max = 201.768;
  double res;

  
  res = 50 + (pow(genes[0],2) - (10 * cos(2*pi*genes[0]))) +
             (pow(genes[1],2) - (10 * cos(2*pi*genes[1]))) +
             (pow(genes[2],2) - (10 * cos(2*pi*genes[2]))) +
             (pow(genes[3],2) - (10 * cos(2*pi*genes[3]))) +
             (pow(genes[4],2) - (10 * cos(2*pi*genes[4])));


  return pow(1-(res/max),powerF6);  // normalise data using coefficient to be 
                                    // in the range {0,1}, and magnify error.
}
/*************************************************************************/
double objective_function::objfuncF7(double genes[])
{ 
  /************************************************************/
  /* F6: Schwefel's function                                  */
  /* According to Hinterding, Gielewski and Peachy (1995)     */
  /*  Proc. 6th ICGA pp 65--72                                */
  /* minimum at x_i = {421}, i = 1,...,n :                    */
  /*         f(x) = -2.09491382e+03;                          */
  /*                                                          */  
  /************************************************************/
  double min,max,res,r;
  max = +2094.91382008072150711088; // at (-421,-421,...,-421)
  min = -2094.91382008072150711088; // at (+421,+421,...,+421)
  
  res = (-genes[0] * sin(sqrt(my_abs(genes[0])))) +
        (-genes[1] * sin(sqrt(my_abs(genes[1])))) +
        (-genes[2] * sin(sqrt(my_abs(genes[2])))) +
        (-genes[3] * sin(sqrt(my_abs(genes[3])))) +
        (-genes[4] * sin(sqrt(my_abs(genes[4]))));
  
  r = max - min;
  return pow(1 - ((r/2 + res)/r),powerF7);  // normalise data using coefficient to be
                                            // in the range {0,1} and magnify error
}
/*************************************************************************/
double objective_function::objfuncF8(double genes[])
{
  /************************************************************/
  /* F6: Rastrigin's function                                 */
  /* According to Hinterding, Gielewski and Peachy (1995)     */
  /*  Proc. 6th ICGA pp 65--72                                */
  /* maximum at extremes of range.                            */
  /* minimum at x_i = {0}, i = 1,...,n : f(x) = 0             */
  /************************************************************/
  //char c[10];
  double res;
  //double min = 0;
  double max = 329.6;

  res = 1 + (pow(genes[0],2)/4000 + pow(genes[1],2)/4000 +
             pow(genes[2],2)/4000 + pow(genes[3],2)/4000 +
             pow(genes[4],2)/4000) -
            (cos(genes[0]/sqrt(1)) * cos(genes[1]/sqrt(2)) *
             cos(genes[2]/sqrt(3)) * cos(genes[3]/sqrt(4)) *
             cos(genes[4]/sqrt(5)));
  

  return pow(1 - (res/max),powerF8);  // normalise data using coefficient to be
                                      // in the range {0,1} and magnify error.
}
/*************************************************************************/
double objective_function::objfuncF9(double genes[])
{
  /************************************************************/
  /* SCHAFFER'S FUNCTION:                                     */
  /* 2 genes in the range -104.8576 < 0 < 104.8576            */
  /* multiple max result of 9.975283e-01; one minimum at      */
  /* min result is 0.000000e+00 located at x= 0.00, y=0.00    */
  /* AFTER SETTING COEFFICIENT = MAX_RESULT AND NORMALISATION */
  /* max result is 1.0 (one located at x=-1.4, y=-0.7)        */
  /* min result is 0.0 located at x=0.0, y=0.0                */
  /* max fitness is 0.997528336509 at x=1.400, y=0.700        */
  /* min fitness is 0.000000000000 at x=0.000, y=0.000        */
  /************************************************************/
  double res = 0.0;
  double coefficient = 0.99752833651;
  res =  0.5 + (pow(sin(sqrt(pow(genes[0],2)+pow(genes[1],2))),2) - 0.5 ) 
	   / pow(1.0 + (0.001)*(pow(genes[0],2)+pow(genes[1],2)),2);
  res = pow(1 - (res/coefficient),powerF9); // normalise data using coefficient to be
  return res;                               // in the range {0,1} and magnify error
}
/*************************************************************************/ 
double objective_function::objfuncF10(double genes[])
{
  /************************************************************/
  /* SCHAFFER'S FUNCTION:                                     */
  /* 2 genes in the range -104.8576 < 0 < 104.8576            */
  /* multiple max result of  2.330924e+01, one minimum at     */     
  /* min result is 0.000000e+00 located at x=0.0,  y=0.0      */
  /* AFTER SETTING COEFFICIENT = MAX_RESULT AND NORMALISATION */
  /* max result is 1.0 (one located at x=-102.5, y=-89.2      */
  /* min result is 0.0 located at x=0.0, y=0.0                */
  /************************************************************/
  double coefficient = 23.309239908875;
  double res = 0;
  res =  pow((pow(genes[0],2) + pow(genes[1],2)),0.25) * 
         (pow(sin(50 *pow((pow(genes[0],2) + pow(genes[1],2)),0.1) ),2) + 1.0);
  res = pow(1- res/coefficient,powerF10); // normalise data using coefficient to be in the range {0,1} 
  return res;                             // and magnify error
} 
/*************************************************************************/
double objective_function::objfuncF11(double genes[])
{
  /************************************************************/
  /* ACKLEY'S FUNCTION:                                       */
  /* 2 genes  in the range -8.192 < x < 8.192                 */ 
  /* max result is 3.453598e+02 located at x=0.0, y=0.769;    */
  /* AFTER SETTING COEFFICIENT = MAX_RESULT AND NORMALISATION */
  /* max result is 1.000000e+00 located at x=-0.001, y= 0.769 */
  /* min result is 1.731737e-06 located at x=-7.867, y=-7.079 */
  /************************************************************/
  double res = 0;
  double coefficient = 3.4535980e+02;
  res = exp(-0.2 * sqrt((genes[0]*genes[0])+(genes[1]*genes[1])) 
	    + 3 * (cos(2*genes[0]) + sin(2*genes[1])));
  res = res/coefficient;
  res = (res + 8.658638e-07) /(9.999938e-01 + 8.658638e-07);  
  if(near(genes[0],genes[1],0.001,0.769,0.5)) 
    return res;
  else return res/1.15;
}
/*************************************************************************/
double objective_function::objfuncF12(double genes[])
{ 
  /************************************************************/
  /* HIMMELBLAU'S FUNCTION :                                  */
  /* 2 genes in the range   -5.12 < g < 5.12                  */
  /* max result is 1.999990e+02 located at x=-4.54, y=4.42    */
  /* min result is -8.321769e+02 located at x= 0.19, y=-5.11  */
  /* AFTER SETTING COEFFICIENT = MAX_RESULT AND NORMALISATION */
  /* max result is 1.000000e+00 located at x=-4.54, y=4.42    */
  /* min result is 9.434554e-08 located at x=0.19, y=-5.11    */
  /* two local optima at (x,y) = {(-4.54,4.42),(4.67,3.21)}   */
  /************************************************************/
  double res = 0;
  double coefficient = 1.999989e+02;
 
  res = 200 - 
        (((genes[0]*genes[0])+genes[1]-25)*((genes[0]*genes[0])+genes[1] -25))
      - ((genes[0]+(genes[1]*genes[1])-15)*(genes[0]+(genes[1]*genes[1]) -15));
  res = res/coefficient;
  res = (res + 4.160908) /(1 + 4.160908);
  if(near(genes[0],genes[1],-4.54,4.42,0.75)||near(genes[0],genes[1],4.67,3.21,0.75)) 
    return res;
  else return res/1.15;
}
/*************************************************************************/
double objective_function::objfuncF13(double genes[], const int gen_no)
{ 
  /************************************************************/
  /* Taken from Osmera, P., Kvasnicka, V. and Pospichal, J.   */
  /* Genetic Algorithms with Diploid Chromosomes. MENDEL'96.  */
  /* pages 111-116.                                           */
  /************************************************************/
  // Because the gene can have a value of 0 <= val <= 2.147483648
  // must normalize to 0 <= val <= 2
  double newval = (genes[0] / 2.147483648) * 2;
  double factor = (gen_no/TIME_STEP) * 0.04; 
  double res = 1 - exp(-200 * pow(newval - factor,2));
  return 1  - res; 
}
/*************************************************************************/
double objective_function::objfuncF14(double genes[], const int gen_no)
{
  double sum = 0;
  for(int num=0; num < NUM_GENES; num++) sum += genes[num];
  int d = gen_no / TIME_STEP;
  if((d % 2)==0)  return sum;
  else return  (180 - sum); 
} 

/*************************************************************************/
double objective_function::objfuncF15(double genes[], const int gen_no, const int n)
{
  // printf("\n n = %d",n);
  double sum = 0;
  double ans = 0;
  for(int num=0; num < n; num++) sum += genes[num];
  int d = gen_no / TIME_STEP;
  if((d % 2)==0)  ans =  pow(sum,2);
  else ans =   sum * (-1);
  // printf("    ans = %f",ans);
  return ans;
} 
/*************************************************************************/
 double objective_function::objfuncF16(double genes[], const int gen_no, const int n, 
				       const int id, const int GE_Report_flag)
{
  //
  // This function calls Grammatical Evolution as the GA's fitness function
  //
  // genes[] contains the integer gene values
  // n is the number of genes
  // gen_no is the current generation number
  // id is the individuals index in the population
  // GE_Report_flag determines if a detailed Report is generated
  
  double fitness=0.0;
  int gpos=0; //start at the first gene
  int new_length=0; 
  ge ge_object;
  ge_object.setGE_Report_flag(GE_Report_flag);
  fitness = ge_object.gen_phen_map(genes,gpos,&new_length,n,gen_no,id);

  
  if(fitness==1) 
    {
      cout << "Fitness(1)" << "\n";
      for(int f = 0; f < n; f++)
	cout << genes[f] << " ";
      cout << endl;
      
      #ifdef _EXIT_FITNESS_ONE
      
      exit (1);
      #endif
    }
  
  return (double)fitness;
}
/*************************************************************************/













