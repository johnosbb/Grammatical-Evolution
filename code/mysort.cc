/********************************************************************/
/*                                                                  */
/*          FILE   :  QUICKSORT.CC                                  */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  JULY 1997                                     */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/*  implements quicksort using templates as in "mysort.hpp"         */
/********************************************************************/

#include "mysort.hpp"
#include <stdio.h>
#include "BGE_individual.hpp"

/********************************************************************/
void mysort::swap(BGE_individual a[], int x, int y)
{
  BGE_individual temp;
  temp = a[x];
  a[x] = a[y];
  a[y] = temp;
}
/********************************************************************/
void mysort::quick_sort(BGE_individual a[], int l, int r)
{
  int i,j;
  BGE_individual v;
  if(r > l) {
    v = a[r];
    i=l-1;
    j=r;

    for(;;) {
      while(a[++i] < v);
      while(a[--j] > v);
      if(j < i) break;
      swap(a,i,j);
    }
    swap(a,i,r);
    quick_sort(a,l,j);
    quick_sort(a,i+1,r);
  }
  
}
/********************************************************************/
void mysort::selection_sort(BGE_individual a[], int N)
{
  
  // printf("\n  ENTERING SELECTION SORT:");
  int i,j,min;
  for(i=0; i < N-1; i++) {
    min = i;
    for(j = i+1; j < N; j++) {
      // if(a[j].fitnesslevel(SCALED) < a[min].fitnesslevel(SCALED)) min = j;
      if(a[j] < a[min]) min = j;
    }
    
    if(min != i) {
      // printf("\n Prior to swapping chromosomes %d and %d",min,i);
      // a[min].show();
      // a[i].show();
      swap(a,min,i);
      // printf("\n After swapping chromosomes %d and %d",min,i);
      // a[min].show();
      // a[i].show();
    }
    
  }
  // printf("\n LEAVING SELECTION SORT:");
  
}
/********************************************************************/







