/*************************************************************************/
/*                                                                       */
/*             FILE   :  ERRORS.CC                                       */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG. 1996/1997                                  */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  ------------------------------------------------------------------   */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "errors.hpp".              */
/*  ------------------------------------------------------------------   */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#include <math.h>
#include <iostream.h>
#include <stdlib.h>
#include "errors.hpp"

/*************************************************************************/

int errors::check_for_error_in_parameters()
{
  /**************************************************************/
  /* Function that checks input parameters defined in           */
  /* "defines.h" for errors. Return TRUE if found.              */
  /**************************************************************/

  int error = 0;
  if((CODE_SCHEME == REAL) || ((STRUCTURE == DIPLOID)&(DIP_EVAL == AVERAGE))) {
    cout << "\n ERROR: This package (optimised) only supports binary coded";
    cout << "\n        fixed/variable length genotype , without using the AVERAGE";
    cout << "\n        evaluation method if diploid, which you did not specify";
    cout << "\n        Exiting the program now";
    error = 1;
  }

  if(STRUCTURE == DIPLOID) {
    if((DIP_EVAL != XOR)&&(DIP_EVAL != RANDOM)) {
      error_msg(DIP_PROB);
      error = 1;
    }
  }

  if((LENGTH != FIXED)&&(LENGTH != VARIABLE)) {
    error_msg(LEN);
    error = 1;
  }

  if(((SHADES == SHADES_2)||(SHADES == SHADES_3))&&(STRUCTURE != HAPLOID)) {
    error_msg(SHADES_PROB);
    error = 1;
  }

  if((CODE_SCHEME == REAL)&&(NUM_GENES == 1)&&(CROSSOVER == X_2PT)) {
    error_msg(TWO_PT);
    error = 1;
  }
  if((SHADES != F)&&(SHADES != SHADES_2)&&(SHADES != SHADES_3)) {
    error_msg(SHADES_ERR);
    error = 1;
  }

  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
    if((pos_perturb < 0)||(pos_perturb > 1)) {
      error_msg(PERTURB_ERR);
      error = 1;
    }
  }

  if((PROBLEM_TYPE != STAT)&&(PROBLEM_TYPE != DYNAM)) {
    error_msg(TYPE);
    error = 1;
  }

  if((PROBLEM_TYPE == DYNAM)&&(TIME_STEP <= 0)) {
    error_msg(ENV_CHANGE);
    error = 1;
  }

  if((STRUCTURE != HAPLOID)&&(STRUCTURE != DIPLOID)) {
    error_msg(STRCT);
    error = 1;
  }

  if(ADAPTIVE_MUTATION) {
    if( ADAPTATION_RATE <= 0) {
      if( ADAPTATION_RATE < 0)  {
	error_msg(ADAPT_1);
	error = 1;
      }
      if( ADAPTATION_RATE == 0) error_msg(ADAPT_2);
    }
    else {
      double p = pmutation * ADAPTATION_RATE;
      if((p > 0.5)&&(p < 1)) error_msg(ADAPT_3);
      if(p > 1) {
	error_msg(ADAPT_4);
	error = 1;
      }
    }
  }

  if((PROBLEM_DOMAIN < F1)||(PROBLEM_DOMAIN > F16)) {
    error_msg(DOM);
    error = 1;
  }

  if(PROBLEM_DOMAIN==F16){
    switch(GE_FUNCTION)
    {
      case POWER :
      {
	if(GRAMMAR==G1){}
	else {error_msg(GE_1); error=1;}
	break;
      }
      case TRIG :
      {
	if(GRAMMAR==G2){}
	else {error_msg(GE_1); error=1;}
	break;
      }
      case INTEGRATE :
      {
	if(GRAMMAR==G2){}
	else {error_msg(GE_1); error=1;}
	break;
      }
      case GRAMMAR_INDUCTION :
      {
	if(GRAMMAR==G3){}
	else {error_msg(GE_1); error=1;}
	break;
      }
      case SANTA_FE :
      {
	if(GRAMMAR==G4){}
	else {error_msg(GE_1); error=1;}
	break;
      }    
    }
  }
  
  if(bits_per_gene < 1) {
    error_msg(NUM_BITS);
    error = 1;
  }
  if((pcross < 0)||(pmutation < 0)) {
    error_msg(PROB);
    error = 1;
  } 
  if((CODE_SCHEME != BINARY)&&(CODE_SCHEME != E_CODE)
      &&(CODE_SCHEME != GRAY)&&(CODE_SCHEME != J_CODE)
      &&(CODE_SCHEME != REAL)) {
    error_msg(CODE);
    error = 1;
  }
  if((CROSSOVER != X_1PT) && (CROSSOVER != X_2PT) && (CROSSOVER != UNIFORM)) {
    error_msg(CROSS);
    error = 1;
  }
  if((SELECTION != TSR) && (SELECTION != RANK) &&
     (SELECTION != REMAIND_STOCH_SAMPL_wo_REPLACE) &&
     (SELECTION != STOCH_SAMPL_wo_REPLACE) &&
     (SELECTION != REMAIND_STOCH_SAMPL_w_REPLACE) &&
     (SELECTION != STOCH_SAMPL_w_REPLACE)) {
      error_msg(SEL);
      error =1;
    }
  if(CODE_SCHEME == REAL) {
    if((MUTATION != STEP) && (MUTATION != STOCHASTIC)) {
      error_msg(MUTATE_REAL);      
      error =1;
    }
    if((ROUNDED) && (GRANULARITY < 0)) {
      error_msg(RND);
      error =1;
    }
    if(DECIMAL_PLACES < 0) {
      error_msg(DECIMAL);      
      error = 1;
    } 
    if(GRANULARITY < 0) {
      error_msg(GRAN);
      error = 1;
    }
    int factor = GRANULARITY;
    while (UPPER_LIMIT * pow(10,factor) > (int)(pow(10,9))) factor--;
    if (UPPER_LIMIT * pow(10,GRANULARITY) > (int)(pow(10,9))) { 
      error_msg(LIMIT,GRANULARITY,GRANULARITY-factor);   
      error=1;
    }
    if((ELITISM == ELITISM_REPLACE)||(ELITISM == ELITISM_ADD)) {
      if((ELITE_QTY < 1) != 0) {error_msg(ELITE); error = 1;} 
    }
  }
  return error;
}
/*************************************************************************/
void errors::error_msg(int which, int num1, int num2)
{
  /**************************************************************/
  /* Prints an error message to standard error output.  Error   */
  /* messages defined in "error_msgs.hpp".                      */
  /**************************************************************/
  switch(which) {
    case GENES       : cerr << "\n ERROR: Number of genes must be at least 2.";
                       break;    
    case NUM_BITS    : cerr << "\n ERROR: number of bits_per_gene must be at least 1.";
                       break;
    case PROB        : cerr << "\n ERROR: P(cross) and P(mutation) must be 0 <= p <= 1.";
                       break;
    case CODE        : cerr << "\n ERROR: coding scheme not specified.";
                       break;
    case CROSS       : cerr << "\n ERROR: You did not select a defined crossover scheme.";
                       break;
    case SEL         : cerr << "\n ERROR: No selection mechanism specified.";
                       break;
    case MUTATE_REAL : cerr << "\n ERROR: mutation operator unknown or not specified";
                       break;
    case DECIMAL     : cerr << "\n ERROR: Decimal places in boundary less than 0.";
                       break;
    case GRAN        : cerr << "\n ERROR: Granularity less than 0.";
                       break;
    case RND         : cerr << "\n WARNING: trying to round using incorrect granularity";
                       break; 
    case LIMIT       : cerr << "\n ERROR: Granularity is too large by " << num1 << num2;
                       break;
    case CONVERGENCE : cerr << "\n WARNING: For gen. " << num1 << " the population" 
                            << " is convergent.";
                       break;
    case AVG         : cerr << "\n WARNING: avg (preprocessed and scaled <= 0";
                       break;
    case PRE_PROCESS : cerr << "\n WARNING: p_avg (preprocessed <= 0";
                       break; 
    case P_FIT       : cerr << "\n WARNING: preprocessed fitness < 0.";
                       break;
    case S_FIT       : cerr << "\n WARNING: scaled fitness < 0.";
                       break;
    case C_LENGTH    : cerr << "\n Error: chromosome lengths not equal.";
                       break;
    case NO_GENE     : cerr << "\n Error: returning allele value of non existent gene.";
                       break;
    case DECODE      : cerr << "\n ERROR: unable to decode string.";
                       break;
    case NO_STRING   : cerr << "\n ERROR: Trying to access a non existent string.";
                       break;
    case NO_BIT      : cerr << "\n ERROR: Trying to access a non existent bit in the string.";
                       break;
    case ELITE       : cerr << "\n ERROR: For the Elitist model choosen, the "
                            << "\n        number ELITE_QTY must be >= 1";
                       break;
    case IMPLEM      : cerr << "\n WARNING: Not yet Implemented";
                       break;
    case POP_SIZE    : cerr << "\n WARNING: initial POPSIZE must be a factor of 2. Incrementing.";
                       break;
    case MAX_POP     : cerr << "\n ERROR: pop size exceeds array boundaries" 
                            << "\n        adjust constructors in pop and gen files";
                       break;
    case DOM         : cerr << "\n ERROR: no problem domain (and associated fitness" 
                            << "\n        function) set by user in defines.h";
                       break;
    case ADAPT_1     : cerr << "\n ERROR: Adaptation rate  results in a negative"
                            << "\n        mutation probability ( pm < 0 ).";
                       break; 
    case ADAPT_2     : cerr << "\n WARNING: Adaptation rate  results in a mutation"
                            << "\n          probability which equals 0 ( pm = 0 ).";
                       break; 
    case ADAPT_3     : cerr << "\n WARNING: Adaptation rate results in a very high"
                            << "\n          mutation probability  ( 0.5 <= pm <= 1 )";
                       break; 
    case ADAPT_4     : cerr << "\n ERROR: Adaptation rate results in a mutation"
                            << "\n        probability which is greater than 1.";  
                       break; 
    case STRCT       : cerr << "\n ERROR: did not specify whether haploid or diploid.";
                       break;
    case GAP         : cerr << "\n WARNING: For gen. " << num1 << " the generation" 
                            << " gap is 0."; 
                       break; 
    case TYPE        : cerr << "\n ERROR: did not specify environment - static/dynamic"; 
                       break; 
    case ENV_CHANGE  : cerr << "\n ERROR: for dynamic environment, TIME_STEP <= 0"; 
                       break; 
    case SHADES_ERR  : cerr << "\n ERROR: polygenic inheritance not set in file params.h";
                       break;
    case PERTURB_ERR : cerr <<"\n pos_perturb must be in the range 0 <= val <= 1"; 
                       break;
    case UP          : cerr << "\n ERROR: shades trying to force up a bit of value 2 (C)";
                       break;
    case DOWN        : cerr << "\n ERROR: shades trying to force down a bit of value 0 (F)";
                       break;
    case TWO_PT      : cerr << "\n ERROR: cannot implement 2pt crossover on this genotype";
                       break;
    case GENERATE    : cerr << "\n ERROR: unable to generate bit string";
                       break;
    case SHADES_PROB : cerr << "\n ERROR: Shades (polygenic inheritance scheme)"
                            << "\n        specified, but structure must be haploid";
                       break;
    case DIP_PROB    : cerr << "\n ERROR: Evalution method (XOR/RANDOM) not specified for diploidy.";
                       break;
    case LEN         : cerr << "\n ERROR: must specify either fixed or variable length genotype";
                       break;
    case GE_1        : cerr << "\n ERROR: The Grammar does not match the Problem";
                       break;
    case SHUT_DOWN   : cerr << "\n ERROR: System Unstable - shutting down. Exiting \n\n";
                       exit(1);
                       break;
    default          : cerr << "\n ERROR: unknown origin.";
  }
}
/*************************************************************************/




