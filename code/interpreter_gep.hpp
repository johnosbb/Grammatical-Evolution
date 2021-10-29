/*************************************************************************/
/*                                                                       */
/*             FILE   :  INTERPRETER_GEP.HPP                                 */
/*             AUTHOR :  Michael O'Neill                                 */
/*             DATE   :  SEPTEMBER 1999                                  */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Declares interpreter_gep class defined in source file "interpreter_gep.cc".  */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include "params.h"
#include "GEtrail.hpp"

class interpreter_gep{
public:
  interpreter_gep(int, int[][2],double genes[], int num_genes);
  float getScore();

private:
  
  void evaluate_ant(int &start,int end);
  void process_if(int &index);
  void process_expr(int &index);
  float score;
  int old_expr[LENGTH_OF_EXPRESSION];
  GEtrail trail;
};



