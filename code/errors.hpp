/*************************************************************************/
/*                                                                       */
/*             FILE   :  ERRORS.HPP                                      */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  MAY 1997                                        */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Header file where functions for error checking and handling. Error    */
/* codes defined in file "error_codes.hpp".                              */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _ERRORS_H
#define _ERRORS_H

#include "params.h"
#include "error_codes.h"

/*************************************************************************/

class errors
{
  public:
    int check_for_error_in_parameters();
    void error_msg(int which, int num1=0, int num2=0);
};

/*************************************************************************/

#endif

