/*************************************************************************/
/*                                                                       */
/*              FILE   :  SCALING.HPP                                    */
/*              AUTHOR :  J.J. COLLINS                                   */
/*              DATE   :  AUG - SEPT 1996                                */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Calculates scaling coefficients to be used in linear ranking scaling */
/*  Preprocess the population first using sigma scaling if minimum       */
/*  fitness < 0. A negative fitness will invalidate linear ranking       */
/*  scaling.                                                             */ 
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _SCALING_H
#define _SCALING_H

/*************************************************************************/

class scaling
{
  public:
  void linear_scaling(double avg, double max, double min, double &a, double &b);
};

/*************************************************************************/
#endif
