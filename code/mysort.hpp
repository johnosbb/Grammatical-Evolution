/********************************************************************/
/*                                                                  */
/*          FILE   :  MYSORT.HPP                                    */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  JULY 1997                                     */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/*  implements a basic quicksort using templates.                   */
/*  From "Algorithms in C++" by Robert Sedgewick. Chapter 9.        */
/*  Addison Wesley, 1992.                                           */
/*  --------------------------------------------------------------- */
/*     BUGS : quicksort does not work                               */
/*                                                                  */
/********************************************************************/

#ifndef _MYSORT_H
#define _MYSORT_H

#include "BGE_individual.hpp"

/********************************************************************/
class mysort
{
  private:
    void swap(BGE_individual a[], int x, int y);
  public:
    void quick_sort(BGE_individual a[], int l, int r);
    void selection_sort(BGE_individual a[], int N);
};
/********************************************************************/
#endif

