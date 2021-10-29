/*************************************************************************/
/*                                                                       */
/*             FILE   :  SCALING.CC                                      */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG - SEPT 1996                                 */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "scaling.hpp".             */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#include "scaling.hpp"
#include "params.h"

/*************************************************************************/

void scaling::linear_scaling(double avg, double max, double min, 
                             double &a, double &b)
{
  /**************************************************************/
  /* Calculate scaling coefficients for linear scaling. As pop  */
  /* converges, F_MULTIPLE (defined in "defines.h") increases   */
  /* range of scaling coefficients.                             */ 
  /**************************************************************/

 double delta;
 if (min > (((F_MULTIPLE*avg) - max)/(F_MULTIPLE - 1.0)))
  {
    delta = max - avg;
    a = (F_MULTIPLE - 1.0) * avg / delta;
    b = avg * (max - (F_MULTIPLE * avg)) / delta;
  }
 else
  {
    delta = avg - min;
    a = avg / delta;
    b = - min * avg / delta;
  }
}

/*************************************************************************/
