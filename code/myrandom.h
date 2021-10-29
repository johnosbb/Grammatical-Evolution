/*************************************************************************/
/*                                                                       */
/*             FILE   :  MYRANDOM.H                                      */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG - SEPT 1996                                 */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Linear Congruential method for generating random numbers as in book   */
/* "Algorithms in C by Robert Sedgewick", Addison-Wesley 1990, p509-512. */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _MYRANDOM_H
#define _MYRANDOM_H

/*************************************************************************/

  void myrandomize();
  int mult(int p, int q);
  int myrandom();
  int randomint(int r);
  int randomintrange(int r1, int r2);
  float chisquare(int N, int r, int &s);
  int probably(const double pos);

/*************************************************************************/
#endif
