/*************************************************************************/
/*                                                                       */
/*             FILE   :  OBJFUNC.HPP                                     */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG - SEPT 1996                                 */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Header file where objective functions are defined. If you want to add */
/* one's own objective function, define it here, implement it in the     */
/* associated .cc file. Then incorporate the function into the function  */
/* BGE_individual::assign_values(...) in the class BGE_individual.       */
/* Also set the appropriate switch in the file "defines.h"               */
/* - F1 to F1 are taken from De Jong.                                    */
/* - F6 Rastrigins function                                              */
/* - F7 Schwefel's function                                              */
/* - F8 griewangk's functions                                            */
/* - F9 and F10 are from Schaffer et al.                                 */
/* - F11 is Ackley's function                                            */
/* - F12 is a modified Himmelblau's function taken from Deb.             */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _objfunc_h
#define _objfunc_h

#define pi 22/7

/*************************************************************************/

class objective_function
{
  private:
    int powerF1,powerF2,powerF3,powerF4,powerF6,powerF7,powerF8,powerF9,powerF10;

  
  public:
    objective_function();
    int near(double x, double y, double x1, double y1, double dist);
    double my_abs(double x);
    double objfuncF1(double genes[]);
    double objfuncF2(double genes[]);
    double objfuncF3(double genes[]);
    double objfuncF4(double genes[]);    
    double objfuncF5(double genes[]);
    double objfuncF6(double genes[]);
    double objfuncF7(double genes[]);
    double objfuncF8(double genes[]);
    double objfuncF9(double genes[]);
    double objfuncF10(double genes[]);
    double objfuncF11(double genes[]);
    double objfuncF12(double genes[]);
    double objfuncF13(double genes[], const int gen_no);
    double objfuncF14(double genes[], const int gen_no);
    double objfuncF15(double genes[], const int gen_no, const int n);
    double objfuncF16(double genes[], const int gen_no, const int n, const int id, 
		      const int GE_Report_flag);
    int save_results_data(char filename[],int data,double genes[],int n);
  
};

/*************************************************************************/
#endif
