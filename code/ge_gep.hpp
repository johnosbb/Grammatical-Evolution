/*************************************************************************/
/*                                                                       */
/*              FILE   :  GE.HPP                                         */
/*              AUTHOR :  Michael O'Neill                                */
/*              DATE   :  NOV 97                                         */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef GE_GEP_HPP_
#define GE_GEP_HPP_ 1.4

#include<fstream.h>
#include "grammar_gep.hpp"
#include "params.h"

class ge_gep{
  
public:
  ge_gep(double *fitness, int strlen, int str[],int wrap_val, int ge_report_val); //Constructor
  void decodeBinaryString(int str[]);
  double gen_phen_map(double genes[], int gpos, const int num_genes);
  ~ge_gep();
  int get_num_genes_read(void);
  
private:
  double decode_binary(int string[], int start, int len);
  int map(int *curr, int *length, int *gpos, int rnd_num,int *age);
  void test_phenotype(double genes[],int num_genes);
  void interpret(double genes[],int num_genes);
  void compile(void);
  void test(double genes[],int num_genes);
  void report(const int num_genes, const int gpos ,double genes[]);
  void set_report(int);
  void set_wrap(int);
  int get_report(void);
  int find_current(void);
  
  int get_wrap(void);  
  //Private data
  grammar_gep g;
  float score;
  int numberOfCodons;
  double *codonIntegers;
  int length;
  int expr[LENGTH_OF_EXPRESSION];
  int old_expr[LENGTH_OF_EXPRESSION][2];
  int wrapped;
  int num_genes_read;
  int validity;
  int wrap;
  int report_flag;
  
};




#endif





