/*************************************************************************/
/*                                                                       */
/*             FILE   :  GE_GEP.CC                                           */
/*             AUTHOR :  Michael O'Neill                                 */
/*             DATE   :  NOV 1997                                        */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "ge_gep.hpp".                  */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "ge_gep.hpp" 
#include "interpreter_gep.hpp"
#include "Random.hpp"
#include "defines.h"

/*************************************************************************/

#ifndef _DUMMY_
ge_gep::ge_gep(double *fitness, int strlen, int str[],int wrap_value,int report_val)
{

  set_wrap(wrap_value); 
  set_report(report_val);
  numberOfCodons = strlen/CODON;
  wrapped=0;
  num_genes_read=0;
  score=0;
  length=0;
  validity=1; //individual assumed to be valid until proven otherwise!
  codonIntegers = new double[numberOfCodons];
  decodeBinaryString(str);
  *fitness = gen_phen_map(codonIntegers, 0, numberOfCodons);
  delete [] codonIntegers;
  
}

#else



ge_gep::ge_gep(double *fitness, int strlen, int str[],int wrap_value,int report_val)
{
  Random r;
  double d = r.randomintrange(0,87);
  *fitness = (double)d;


}

#endif








/*************************************************************************/
ge_gep::~ge_gep(){}
/*************************************************************************/
void ge_gep::decodeBinaryString(int str[])
{
  int index = 0;
  for(int i=0;i<numberOfCodons;i++) codonIntegers[i] = 0;

  /* decode binary string */
  for(int i=0;i<numberOfCodons;i++){
    index = i*CODON;
    codonIntegers[i] = decode_binary(str,index,CODON);
  }
}
/*************************************************************************/
double ge_gep::decode_binary(int string[], int start, int len)
{
  /*********************************************/ 
  /* Decode a binary string to numeric, from   */ 
  /* string position "start" up to start + len */ 
  /*********************************************/ 
  double accum = 0.0;
  double powerof2 = len-1;
  for (int j=start; j < (start+len); j++){
    accum = accum + (string[j] * pow(2,powerof2));
    powerof2--;
  }
  return accum;
}
/*************************************************************************/

double ge_gep::gen_phen_map(double genes[],int gpos, const int num_genes)
{
  /*
   * Main operation of the class ge_gep.
   * Carries out mapping process on an individual, tests generated code with 
   * test_phenotype(), generates a report on some stats with report(), and 
   * returns fitness of the individual.
   *
   * Params: double genes[] - decoded codon integer values
   *         int gpos - current codon position
   *         const int num_genes - number of codons on string
   */  
  old_expr[0][0]=1001; // Set first part of solution as being start symbol <S>
  length=1; //expression is now of length 1
  int curr=0; //Non-terminal position in expr being mapped
  int age=0;
  old_expr[0][1]=age; //reset the age of the start symbol to zero
  
  //Map integer individual to it's corresponding set of grammar terminals
  do {

    if(!(gpos<num_genes)) 
      { //wrap ?
	if( wrap && (wrapped < WRAP_EVENTS) )
	  {
	    num_genes_read+=num_genes; 
	    gpos=0; 
	    wrapped++;
	  }
	else
	  curr=-1; //incomplete mapping so invalid
      }
    if(curr > -1)
      curr = find_current();
    if(curr > -1 ){
      //Apply grammar to map genome onto compilable code
      map(&curr,&length,&gpos,(int)genes[gpos],&age);
    }


    if(curr == -1) {
      //cout << "Invalid Ind"; 
      validity=0;
      score=0;
      curr= -1;}
  } while (curr > -1);  
  num_genes_read+=gpos;
  //Interpret or compile&run the mapped individual if valid
  
  if (curr == -2) { 
    test_phenotype(genes,num_genes);
  }

  //Generate report on individuals performance
  if((get_report() == 1) || (get_report() == 2))
    {
      report(num_genes,gpos,genes);
    }
  
  //Return fitness
  return ((double)score);
}
/*************************************************************************/
int ge_gep::map(int *curr, int *length, int *gpos, int rnd_num, int *age)
{
  /*
   * carries out the mapping process using the grammar file
   */
  //cout << "1.r= " << report_flag << " 1.we= " << wrapped;
  if (*length> (LENGTH_OF_EXPRESSION - 7))
  {
    //Test generated expr isn't greater than the maximum allowable length
    *curr=-1;
    /*cout << "Length is >" << LENGTH_OF_EXPRESSION;*/
    return(-1);
  }
  if (*curr> (LENGTH_OF_EXPRESSION - 7))
  {
    //Test current position in expr isn't beyond the end of the expression
    *curr=-1;
    /*cout <<"Curr is >"<< LENGTH_OF_EXPRESSION;*/
    return(-1);
  }
  // the find current routine needs to determine if the current expression points to a terminal so this 
  // piece of code should not be called.
  //if (old_expr[*curr][0]<1000) //Skips over terminals if any!
  //{
  //*curr=*curr+1;
  // return(1); 
  //}
  //cout << "2.r= " << report_flag << " 2.we= " << wrapped;  
  /*Apply the grammar*/    
  g.apply_grammar(old_expr,curr,length,gpos,rnd_num,age);
  if(get_report() == 2)
    {       
      g.fprint_grammar_individual(cout,old_expr,*length);
      
    }
  //cout << "3.r= " << report_flag << " 3.we= " << wrapped;      
  return(1); //map done!
}
/*************************************************************************/
void ge_gep::test_phenotype(double genes[],int num_genes)
{
  //Carry out a compile/run(test) or interpret/test program

  switch(COMPILE)
    {
    case (0):
      {
	//Interpret program
	interpret(genes,num_genes);
	break;
      }
    case (1):
      {
	//Compile program
	compile();
	break;
      }
    default : cout << "ERROR: did not specifiy compile or interpret!" << endl;
    }
  
  //Test the individuals
}
/*************************************************************************/
void ge_gep::interpret(double genes[],int num_genes)
{
  /*
   * Instantiate interpreter class
   */
  interpreter_gep i(length, old_expr,genes,num_genes);
  /* make sure to return score */
  score = i.getScore();
}
/*************************************************************************/
void ge_gep::compile()
{
  /*
   * Outputs evolved code plus any wrappers to a file so it can be compiled
   * Then run compilation using UNIX system() system call
   *
   * User writes their own compile.cc in which they can "#include individual.cc"
   */
  ofstream ofs("individual.cc");
  g.fprint_grammar_individual(ofs,old_expr,length);
  ofs.close();

  //#include "compiler.cc"

  ifstream ifs("score.dat");
  ifs >> score;
  ifs.close();
}
/*************************************************************************/
void ge_gep::report(const int num_genes, const int gpos,double genes[])
{ 
  cout << "---------------------------------------" << endl;
  cout << "Wrap_Flag  " << get_wrap() << " " <<  wrap << endl;
  cout << "Fitness  " << score << " " << endl;
  cout << "No_Codons " << num_genes << " " << endl;
  cout << "No_Used_Codons " << num_genes_read << " " << endl;
  cout << "No_Wrap_Events  " << wrapped << " " << endl;
  cout << "Map_Successfull?  " << validity << " " << endl;
  for(int i=0;i<num_genes;i++)
    cout << genes[i] << ",";
  cout << endl;
  cout << "Output_Code: " ;
  g.fprint_grammar_individual(cout,old_expr,length);
  cout << "---------------------------------------" << endl;
  cout << endl;
}
/*************************************************************************/

void ge_gep::set_report(int val)
{
  report_flag = val;
}

void ge_gep::set_wrap(int val)
{
  wrap = val;
}


int ge_gep::get_report(void)
{
  return report_flag;
}

int  ge_gep::get_wrap(void)
{
  return wrap;
}



int  ge_gep::get_num_genes_read(void)
{
  return num_genes_read;
}


//finds curr in the expr array, curr is the expr with oldest age
//it searches the old_expr array and retuens the index of the oldest expr which
// is not a terminal
int  ge_gep::find_current(void)
{

  //int oldest_expr = old_expr[0][1];
  int oldest_expr = 10000;
  int oldest_pos = -1;
  int t = 0;
  
  for(int i=0; i < length; i++)
    {
      //     printf(" %d \n" , old_expr[i][1]);
      if(!(old_expr[i][0]< 1000)) // if the current expression is not a terminal
	{
	  if( old_expr[i][1] <= oldest_expr ) //if the current expression is older than the oldest
	    {
	      oldest_expr =  old_expr[i][1];    // make the current one the oldest
	      oldest_pos = i;
	    }
	}
      else   // else it must be a terminal
	{
	  if(t == (length - 1)) // all expressions must be terminals
	    oldest_pos = -2;  // set the current position equal to -2  so that we can terminate and evaluate
	  t += 1;
	  
	}
      

    }

  //printf("Oldest is : %d at position %d\n",old_expr[oldest_pos][1],oldest_pos);
  
  return oldest_pos;  
}








