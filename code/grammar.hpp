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

#ifndef GRAMMAR_HPP_
#define GRAMMAR_HPP_ 1.4

#include<fstream.h>

class grammar{
  public:
    grammar(); //Constructor
    void apply_grammar(int old_expr[], int *curr, int *length, int *gpos, 
		                                                  const int rnd_num); 
    void fprint_grammar_individual(ostream& output_stream,int old_expr[],int length);
  private:
    int expr_num;
  
};

#endif











