/********************************************************************/
/*                                                                  */
/*          FILE   :  TITLES.HPP                                    */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  MAY 1997                                      */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/* Header file where functions for                                  */
/* printing genetic algorithm parameters to file and screen.        */
/*  --------------------------------------------------------------- */
/*     BUGS : todate, none to report.                               */
/*                                                                  */
/********************************************************************/

#include "params.h"
#ifndef _TITLES_H
#define _TITLES_H

/********************************************************************/
class titles
{
  public:
    void print_titles(FILE *fp, int lchrom);
};
/********************************************************************/

#endif

