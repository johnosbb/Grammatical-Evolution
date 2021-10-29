/*************************************************************************/
/*                                                                       */
/*             FILE   :  GE.CC                                           */
/*             AUTHOR :  Michael O'Neill                                 */
/*             DATE   :  NOV 1997                                        */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "ge.hpp".                  */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include<iostream.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "ge.hpp" 
#include "interpreter.hpp"
#include "Random.hpp"
#include "defines.h"

/*************************************************************************/


#define CODON_TRACE 0

#ifndef _DUMMY_
ge::ge(double *fitness, int strlen, int str[],int wrap_value,int report_val)
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



ge::ge(double *fitness, int strlen, int str[],int wrap_value,int report_val)
{
  Random r;
  double d = r.randomintrange(0,87);
  *fitness = (double)d;


}

#endif








/*************************************************************************/
ge::~ge(){}
/*************************************************************************/
void ge::decodeBinaryString(int str[])
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
double ge::decode_binary(int string[], int start, int len)
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
double ge::gen_phen_map(double genes[],int gpos, const int num_genes)
{
  /*
   * Main operation of the class ge.
   * Carries out mapping process on an individual, tests generated code with 
   * test_phenotype(), generates a report on some stats with report(), and 
   * returns fitness of the individual.
   *
   * Params: double genes[] - decoded codon integer values
   *         int gpos - current codon position
   *         const int num_genes - number of codons on string
   */  
  old_expr[0]=1001; // Set first part of solution as being start symbol <S>
  length=1; //expression is now of length 1
  int curr=0; //Non-terminal position in expr being mapped
  //Map integer individual to it's corresponding set of grammar terminals
  do {

    if(!(gpos <  num_genes)) 
      { //wrap ?
	if( wrap && (wrapped < WRAP_EVENTS) )
	  {
	    if(CODON_TRACE)
	      cout << "## WRAP" << endl;
	    
	    num_genes_read+=num_genes; 
	    gpos=0; 
	    wrapped++;
	  }
	else
	  curr=-1; //incomplete mapping so invalid
      }

    if(curr!=-1){
      //Apply grammar to map genome onto compilable code
      map(&curr,&length,&gpos,(int)genes[gpos],genes,num_genes);

    }
    else {
      //cout << "Invalid Ind"; 
      validity=0;
      score=0;
      curr=length+100;}
  } while (curr<length);
  num_genes_read+=gpos;
  //Interpret or compile&run the mapped individual if valid
  if (curr!=length+100) { 
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
int ge::map(int *curr, int *length, int *gpos, int rnd_num,double genes[],const int num_genes)
{
  /*
   * carries out the mapping process using the grammar file
   */
  //cout << "1.r= " << report_flag << " 1.we= " << wrapped;
  if (*length> (LENGTH_OF_EXPRESSION - 7))
  {
    //Test generated expr isn't greater than the maximum allowable length

    *curr=-1;
    if((get_report() == 4) || (get_report() == 2))
      {
	printf("invalid due to length %d greater than expression maximum length\n",*length);
	
      }
    /*cout << "Length is >" << LENGTH_OF_EXPRESSION;*/
    return(-1);
  }
  if (*curr> (LENGTH_OF_EXPRESSION - 7))
  {
    if((get_report() == 4) || (get_report() == 2))
      {
	printf("invalid due to curr %d greater than expression maximum length\n",*curr);
      }
    //Test current position in expr isn't beyond the end of the expression
    *curr=-1;
    /*cout <<"Curr is >"<< LENGTH_OF_EXPRESSION;*/   


    return(-1);
  }
  if (old_expr[*curr]<1000) //Skips over terminals if any!
  {
    *curr=*curr+1;
    return(1); 
  }
  //cout << "2.r= " << report_flag << " 2.we= " << wrapped;  
  /*Apply the grammar*/    
  g.apply_grammar(old_expr,curr,length,gpos,rnd_num);
  if(get_report() == 2)
    {       
      g.fprint_grammar_individual(cout,old_expr,*length);
      
    }
  //cout << "3.r= " << report_flag << " 3.we= " << wrapped;      
  return(1); //map done!
}
/*************************************************************************/
void ge::test_phenotype(double genes[],int num_genes)
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
void ge::interpret(double genes[],int num_genes)
{
  /*
   * Instantiate interpreter class
   */
  //printf ("Calling Interpreter from GE ___________________\n");
  
  interpreter i(length, old_expr,genes,num_genes);
  /* make sure to return score */
  score = i.getScore();
}
/*************************************************************************/
void ge::compile()
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
void ge::report(const int num_genes, const int gpos,double genes[])
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

void ge::set_report(int val)
{
  report_flag = val;
}

void ge::set_wrap(int val)
{
  wrap = val;
}


int ge::get_report(void)
{
  return report_flag;
}

int  ge::get_wrap(void)
{
  return wrap;
}



int  ge::get_num_genes_read(void)
{
  return num_genes_read;
}
















