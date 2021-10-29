/*************************************************************************/
/*                                                                       */
/*             FILE   :  INTERPRETER.HPP                                 */
/*             AUTHOR :  Michael O'Neill                                 */
/*             DATE   :  SEPTEMBER 1999                                  */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Declares interpreter class defined in source file "interpreter.cc".  */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include "params.h"
#include "GEtrail.hpp"

class interpreter{
public:
  interpreter(int, int[], double genes[], int num_genes);
  ~interpreter();
  float getScore();
  
private:
  
  float score;
  int old_expr[LENGTH_OF_EXPRESSION];
  char cexpr[LENGTH_OF_EXPRESSION * 6];
  int convert_expr(int length,double genes[], int num_genes);
  int get_expression(int i,char literal_expression[],double genes[], int num_genes,int * gpos);
  float process_expression(char theExpression[]);
};




























