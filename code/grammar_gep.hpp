/*************************************************************************/
/*                                                                       */
/*              FILE   :  GRAMMAR.HPP                                    */
/*              AUTHOR :  Michael O'Neill                                */
/*              DATE   :  MAY 98 ->                                      */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :  Implements a BNF Grammar for Grammatical Evolution*/
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef GRAMMAR_GEP_HPP_
#define GRAMMAR_GEP_HPP_ 1.4

#include<fstream.h>

class grammar_gep{
  public:
    grammar_gep(); //Constructor
    void apply_grammar(int old_expr[][2], int *curr, int *length, int *gpos, 
		                                                  const int rnd_num,int *age); 
    void fprint_grammar_individual(ostream& output_stream,int old_expr[][2],int length);

  int check_length(int * ken_val);
  
  private:
  int expr_num;
  
};

#endif











