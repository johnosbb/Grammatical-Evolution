/*************************************************************************/
/*                                                                       */
/*             FILE   :  BGE_INDIVIDUAL.CC                               */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG - SEPT 1996/1997                            */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "BGE_individual.hpp".      */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "BGE_individual.hpp"
#include "BGE_decode.hpp"
#include "myrandom.h"
#include "error_codes.h"
#include "params.h"


// GLOBAL OBJECT USED FOR DECODING STRINGS 
// INTO FLOATING POINT VALUE
static BGE_decode decode(bits_per_gene-1); 

/*************************************************************************/
void BGE_individual::generatechromosome(const int clength)
{
  /**************************************************************/
  /* Generates a chromosome string of boolean or pseudo-boolean */
  /* (if SHADES) using the function random                      */
  /**************************************************************/
  //printf("\n entering GENERATECHROMOSOME()\n");
  
  if((LENGTH == FIXED)&&(clength != stringLength)) {
   error_msg(C_LENGTH); 
   error_msg(SHUT_DOWN);
  }
  
  int range;
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) range = 3;
  else range = 2;
  for (int locus=0; locus < stringLength; locus++){    
    int temp = randomint(range);
    switch(temp) {
      case 0  : chromosome[0].insert(F); break;
      case 1  : chromosome[0].insert(T); break;
      case 2  : chromosome[0].insert(S); break;
      default : error_msg(GENERATE);
                error_msg(SHUT_DOWN);
                break;
    }
  }
  /*---------------------------------------------*/
  /* If diploidy used, need to initialise        */
  /* second string.                              */
  /*---------------------------------------------*/
  if(STRUCTURE == DIPLOID) {
    for(int count =0; count < stringLength; count++) {
      if(randomint(2)) chromosome[1].insert(T);
      else chromosome[1].insert(F);
    }
  }
}
/*************************************************************************/
BGE_individual::BGE_individual()
{
  /**************************************************************/
  /* Constructor: first part calcukates string length.          */
  /**************************************************************/
  // printf("\n entering constructor");  
  GE_Decode_flag= DEBUG_3;
  int gene_count;

  if (LENGTH == VARIABLE) {
      gene_count = randomint(INITIAL_RANGE);
      if (gene_count ==0) gene_count = 1;     
    }
  else gene_count = NUM_GENES;

  if((SHADES == SHADES_2)||(SHADES==SHADES_3)) {
    if(SHADES == SHADES_2) {
      shades_bits_per_gene = bits_per_gene * 2;
      stringLength = gene_count * shades_bits_per_gene; 
    }
    else {
      shades_bits_per_gene = bits_per_gene * 3;
      stringLength = gene_count *shades_bits_per_gene;
    }
    new_genotype  = new bit[gene_count*bits_per_gene];
  }
  else stringLength = gene_count * bits_per_gene;
  
  array         = new bit[stringLength];
  arr           = new bit[bits_per_gene];
  alleles[0]    = new double[gene_count]; 


  if(STRUCTURE == DIPLOID) {
    alleles[1]    = new double[gene_count];  
    if(DIP_EVAL == XOR) {
      temp = new bit[stringLength];
      temp_alleles = new double[gene_count];
    }
  }
}
/*************************************************************************/
BGE_individual::~BGE_individual()
{
  /**************************************************************/
  /* Destructor.                                                */
  /**************************************************************/
  // printf("\n entering BGE_indiv destructor\n");
  delete [] array;
  if((SHADES == SHADES_2)||(SHADES==SHADES_3)) delete [] new_genotype;
  delete [] arr;
  delete [] alleles[0];
  if(STRUCTURE == DIPLOID) {
    delete [] alleles[1];
    if(DIP_EVAL == XOR) {
      delete [] temp;
      delete [] temp_alleles;
    }
  }

  // printf("\n exiting BGE_indiv destructor\n");
}
/*************************************************************************/
void BGE_individual::setbit(bit bitval, int locus, int which_string)
{
  /**************************************************************/
  /*Sets a particular bit in a chromosome to the value specified*/
  /**************************************************************/
  // printf("\n entering SETBIT");
  
  if((locus >= stringLength)&&(LENGTH == FIXED)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }
  
  if(which_string == 0) chromosome[0].insert(bitval);
  else chromosome[1].insert(bitval);
  // printf("\n leaving SETBIT");
}
/*************************************************************************/
double BGE_individual::fitnesslevel(boolean indicator)
{
  /**************************************************************/
  /* Returns fitness (ordinary or scaled depending on indicator)*/ 
  /* of chromosome.                                             */ 
  /**************************************************************/
  if (indicator) return scaledfitness;
  else return fitness;
}
/*************************************************************************/
double BGE_individual::gene_value(int which_gene, int which_string)
{
  /**************************************************************/
  /* Returns fitness (ordinary or scaled depending on which)    */
  /* of gene (which = false ==>> no scaling operator invoked) . */
  /**************************************************************/

  if(which_gene >= (str_len()/ bits_per_gene)){
    error_msg(NO_GENE);
    error_msg(SHUT_DOWN);
  }
  if(which_string == 0)  return alleles[0][which_gene];
  else return alleles[1][which_gene];
}
/*************************************************************************/
void BGE_individual::force_up(int decrement)
{
  /**************************************************************/
  /* For shades_?() increments bit value of gene in the string  */
  /* (chomosome) at a given locus.                              */
  /**************************************************************/
  // printf("\n entering FORCE_UP()");

  if((SHADES==SHADES_2)&&(decrement > 2)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }
    if((SHADES==SHADES_2)&&(decrement > 3)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }

  if(chromosome[0].at_end()) decrement--;
  for(int count = 0; count < decrement; count++) --chromosome[0]; 

  bit b = chromosome[0].get_current_element();
  switch(b) {
    case F : chromosome[0].change(T); break;
    case T : chromosome[0].change(S); break;
    case S : 
    default: error_msg(UP);
             error_msg(SHUT_DOWN);
             break;
  }
  for(int count1 = 0; count1 < decrement; count1++) ++chromosome[0]; 
  // printf("\n leaving FORCE_UP()");
}

/*************************************************************************/
void BGE_individual::force_down(int decrement)
{
  /**************************************************************/
  /* For shades_?() decrements bit value of gene in the string  */
  /* (chomosome) at a given locus.                              */
  /**************************************************************/
  //printf("\n entering FORCE_DOWN()");

  if((SHADES==SHADES_2)&&(decrement > 2)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }
  if((SHADES==SHADES_2)&&(decrement > 3)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }
  if(chromosome[0].at_end()) {
    //printf("\n decrementing");
    decrement--;
  }
  for(int count =0; count < decrement; count++) --chromosome[0];

  bit b = chromosome[0].get_current_element();
  //printf("\n bit b = %d",(int)(b));

  switch(b) {
    case S : chromosome[0].change(T); break;
    case T : chromosome[0].change(F); break;
    case F : 
    default: error_msg(DOWN);
             error_msg(SHUT_DOWN);
             break;
  }
  for(int count1=0; count1 < decrement; count1++) ++chromosome[0];
  //printf("\n leaving FORCE_DOWN()");
}
/*************************************************************************/
void BGE_individual::swap_positions(const int dec1, const int dec2)
{
  /**************************************************************/
  /* For shades_?() swaps two bit values of the string, their   */
  /* positions being at locus1 and locus 2.                     */
  /**************************************************************/
  // printf("\n entering SWAP_POSITIONS()");

  /*
  if((locus1 >= stringLength)||(locus2 >= stringLength)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }
  */
  int positions;
  if(chromosome[0].at_end()) positions = 3;
  else positions = 4;

  for(int num1=0; num1 < (positions - dec1); num1++) --chromosome[0];
  bit b1 = chromosome[0].get_current_element();
  for(int num2=0; num2 < (positions - dec1); num2++) ++chromosome[0];

  for(int num3=0; num3 < (positions - dec2); num3++) --chromosome[0];
  bit b2 = chromosome[0].get_current_element();
  for(int num4=0; num4 < (positions - dec2); num4++) ++chromosome[0];

  for(int num5=0; num5 < (positions - dec1); num5++) --chromosome[0];
  chromosome[0].change(b2);
  for(int num6=0; num6 < (positions - dec1); num6++) ++chromosome[0];

  for(int num7=0; num7 < (positions - dec2); num7++) --chromosome[0];
  chromosome[0].change(b1);
  for(int num8=0; num8 < (positions - dec2); num8++) ++chromosome[0];

  // printf("\n leaving SWAP_POSITIONS()");
}
/*************************************************************************/
void BGE_individual::decode_shades_phenotype()
{
  /**************************************************************/
  /* For shades_?() decodes the derived genotype derived from   */
  /* the string (chomosome).                                    */
  /**************************************************************/
  // printf("\n entering DECODE_SHADES_PHENOTYPE()");

  int start=1;
  int bits_to_decode = bits_per_gene -1;
  for(int i=0;i<gene_no(); i++) {
    switch(CODE_SCHEME) {
        case BINARY: alleles[0][i] = decode.decode_binary(new_genotype,start,bits_to_decode);
                     break;
        case E_CODE: alleles[0][i] = decode.decode_Ecode(new_genotype,start,bits_to_decode); 
                     break;
        case GRAY:   alleles[0][i] = decode.decode_Gray(new_genotype,start,bits_to_decode); 
                     break;
        case J_CODE: alleles[0][i] = decode.decode_Jcode(new_genotype,start,bits_to_decode); 
                     break;
    } 
    alleles[0][i] /= ALLELE_FACTOR;
    if(SIGN) {
      switch(new_genotype[start-1]) {
        case F : alleles[0][i] = alleles[0][i] * (-1); break;
        case T : break;
        case S :
        default: printf("\n error here");
                 error_msg(DECODE);
                 error_msg(SHUT_DOWN);
                 break;
      }
    }
    start += bits_per_gene;
  }
  // printf("\n leaving DECODE_SHADES_PHENOTYPE()");
}
/*************************************************************************/
void BGE_individual::shades_2()
{
  /***************************************************************/
  /* Implements polygenic inheritance scheme "Shades (2)". This  */
  /* is an alternative approach to diploidy, based on the haploid*/
  /* approach. Instead of using a pair of strings as the genotype*/  
  /* the string is twice the length of the normal  haploid case  */
  /* Degree of oneness is used to calculate the phenotype, and   */
  /* force and perturb operators are applied in addition to the  */
  /* standard set.                                               */
  /***************************************************************/
  printf("\n entering SHADES_2()");

  chromosome[0].point_to_head();
  bit b1,b2;
  for(int num1 =0; num1 < gene_no(); num1++) {
    int l2 = (bits_per_gene * 2) * num1;
    int num3 = num1 * bits_per_gene;
    int pos1 = l2;
    int pos2 = l2 + 1;

    for(int num2 = 0; num2 <  bits_per_gene; num2++) {   
      /*---------------------------------------------*/
      /* 1. Calculate the degree of oneness.         */
      /*---------------------------------------------*/
      //printf("\n [pos1,pos2] = [%d,%d] ",pos1,pos2);
      b1 = chromosome[0].get_current_element();
      ++chromosome[0];
      b2 = chromosome[0].get_current_element();
      ++chromosome[0];
      int temp = b1 + b2;
      //printf(" [%d,%d] : temp = %d",b1,b2,temp);
      //printf(" {%d} ",temp);
      if(temp > 2) new_genotype[num2 + num3] = T;
      else {
	if(temp < 2) new_genotype[num2 + num3] = F;
	else {
	  if(randomint(2)) new_genotype[num2 + num3] = T;
	  else new_genotype[num2 + num3] = F;
	}
      }
      if(pos1 == l2) {
	if(SIGN == F) {
          --chromosome[0];
          --chromosome[0];
          chromosome[0].change(S);
          b1 = S;
	  ++chromosome[0];
          chromosome[0].change(S);
          b2 = S;
          ++chromosome[0];
	  new_genotype[num2+num3] = T;
	}
      }
      /*---------------------------------------------*/
      /* 2. Apply the force operator if the pair are */
      /*    at the extreme of phenotypic space.      */
      /*---------------------------------------------*/    
      
      if((b1==b2)&&(b1 != T)) {
        //printf(" $$$ ");
	switch(b1) {
	case F  : if(randomint(2)) force_up(2);
	          else force_up(1);
                  break;
        case T  : break;
	case S  : if(randomint(2)) force_down(2);
                  else force_down(1);  
	          break;
        default : printf("\n pos1 = %d", pos1);
                  error_msg(DECODE);
                  error_msg(SHUT_DOWN);
                  break;
	}
      }
      /*---------------------------------------------*/
      /* 3. Apply randomly the perturb operator      */
      /*    - swaps the gene pair (positional).      */
      /*---------------------------------------------*/
      if(probably(pos_perturb)) {
	bit b3,b4;
        if(chromosome[0].at_end())
	  b3 = chromosome[0].get_current_element();
	else {
          --chromosome[0];
          b3 = chromosome[0].get_current_element();
	}
        --chromosome[0];
        b4 = chromosome[0].get_current_element();
        chromosome[0].change(b3);
        ++chromosome[0];
        chromosome[0].change(b4);
        ++chromosome[0];
      }
      /*---------------------------------------------*/
      pos1 += 2;
      pos2 += 2;
    }
  }
  /*---------------------------------------------*/
  /* 4. Decode the resultant phenotype.          */
  /*---------------------------------------------*/
  decode_shades_phenotype();
  //printf("\n leaving SHADES_2()");
}
/*************************************************************************/
void BGE_individual::shades_3()
{
  /***************************************************************/
  /* Implements Ryan's polygenic inheritance scheme "Shades (3)".*/
  /* Same principle as shades_2(), except instead of a gene pair,*/
  /* a triplet is used - different degrees of oneness condition  */ 
  /***************************************************************/
  // printf("\n entering SHADES_3()");
  chromosome[0].point_to_head();

  //chromosome[0].print_list();
  for(int num1 =0; num1 < gene_no(); num1++) {
     
    int l2 = (bits_per_gene * 3)  * num1;
    int num3 = num1 * bits_per_gene;
    int pos1 = l2 ;
    int pos2 = l2 + 1;
    int pos3 = l2 + 2;

 
    for(int num2 = 0; num2 <  bits_per_gene; num2++) {   
      /*---------------------------------------------*/
      /* 1. Calculate the degree of oneness.         */
      /*---------------------------------------------*/

      bit b1 = chromosome[0].get_current_element();
      ++chromosome[0];
      bit b2 = chromosome[0].get_current_element();
      ++chromosome[0];
      bit b3 = chromosome[0].get_current_element();
      ++chromosome[0];
      int temp  = (int)(b1) + (int)(b2) + (int)(b3);
      if(temp > 3) new_genotype[num2 + num3] = T;
      else {
        if(temp < 3) new_genotype[num2 + num3] = F;
        else {
	  if(randomint(2)) new_genotype[num2 + num3] = T;
	  else new_genotype[num2 + num3] = F;
	}
      }
      if(pos1 == l2) {
	if(SIGN == F) {
          --chromosome[0];
          --chromosome[0];
          --chromosome[0];
          chromosome[0].change(S);
          b1 = S;
	  ++chromosome[0];
          chromosome[0].change(S);
          b2 = S;
          ++chromosome[0];
          chromosome[0].change(S);
          b3 = S;
          ++chromosome[0];
	  new_genotype[num2+num3] = T;
	}
      }
      /*---------------------------------------------*/
      /* 2. Apply the force operator if the trip are */
      /*    at the extreme of phenotypic space.      */
      /*---------------------------------------------*/    
      /*      
      if(((b1==F)&&(b2==F)) && (b3 != S)){
        int loops;
        if(b3 == b2) loops = 2;
        else loops = 1;
        for(int n1=0; n1 < loops; n1++) {
	  int temp = randomint(3);
	  switch(temp) {
            case 0: force_up(3); break;
            case 1: force_up(2); break;
            case 2: force_up(1); break;      
	  }
	}
      }
      if(((b2==S)&&(b3==S))&&(b1 != F)) {
        int loops;
        if(b1 == b2) loops = 2;
        else loops = 1;
        for(int n1=0; n1 < loops; n1++) {
	  int temp = randomint(3);
	  switch(temp) {
            case 0: force_down(3); break;
            case 1: force_down(2); break;
            case 2: force_down(1); break;      
	  }
	}
      }
      */
      /*---------------------------------------------*/
      /* 3. Apply randomly the perturb operator      */
      /*    - swaps the gene pair (positional).      */
      /*---------------------------------------------*/
      /*
      if(probably(pos_perturb)) {
        int num4 = randomint(3);
        if(num4 == 0) swap_positions(2,3); 
        else {
	  if(num4 == 1) swap_positions(1,3); 
	  else swap_positions(1,2);
	}
      }
      */
      /*---------------------------------------------*/
      pos1 += 3;
      pos2 += 3;
      pos3 += 3;
    }
  }
  /*---------------------------------------------*/
  /* 4. Decode the resultant phenotype.          */
  /*---------------------------------------------*/
  //chromosome[0].print_list();
  decode_shades_phenotype();
  // printf("\n leaving SHADES_3()");
}
/*************************************************************************/
void BGE_individual::decode_diploid_xor(const int gen_no)
{
  /**************************************************************/
  /**************************************************************/
  //printf("\n entering decode_diploid_xor()");

  if (gen_no > 0){
    delete [] temp;
    temp =  new bit[stringLength];
    delete [] temp_alleles;
    temp_alleles = new double[stringLength/bits_per_gene];
  }

  if((STRUCTURE != DIPLOID)&&(DIP_EVAL != XOR)) {
    printf("\n ERROR: structure is not diploid and merge is not XOR");
    exit(1);
  }
   
  chromosome[0].point_to_head();
  chromosome[1].point_to_head();
  for(int count1 =0; count1 < stringLength; count1++) {
    bit b1 = chromosome[0].get_current_element();
    ++chromosome[0];
    bit b2 = chromosome[1].get_current_element();
    ++chromosome[1];
    if(b1 == b2) temp[count1] = F;
    else temp[count1] = T;
  }

  int start=1;
  int bits_to_decode = bits_per_gene-1;
  for(int i=0;i<gene_no(); i++) {
   switch(CODE_SCHEME) {
      case BINARY: temp_alleles[i] = decode.decode_binary(temp,start,bits_to_decode);
                   break;
      case E_CODE: temp_alleles[i] = decode.decode_Ecode(temp,start,bits_to_decode); 
                   break;
      case GRAY:   temp_alleles[i] = decode.decode_Gray(temp,start,bits_to_decode); 
                   break;
      case J_CODE: temp_alleles[i] = decode.decode_Jcode(temp,start,bits_to_decode); 
                   break;
    }
    temp_alleles[i] /= ALLELE_FACTOR;
    if(SIGN) {
      if(temp[start-1]== F) temp_alleles[i] = temp_alleles[i] * (-1);
    }
    start += bits_per_gene;
  }
    
  switch(PROBLEM_DOMAIN) {
    case F1 : fitness = objfuncF1(temp_alleles); break;
    case F2 : fitness = objfuncF2(temp_alleles); break;
    case F3 : fitness = objfuncF3(temp_alleles); break;
    case F4 : fitness = objfuncF4(temp_alleles); break;
    case F5 : fitness = objfuncF5(temp_alleles); break;
    case F6 : fitness = objfuncF6(temp_alleles); break;
    case F7 : fitness = objfuncF7(temp_alleles); break;
    case F8 : fitness = objfuncF8(temp_alleles); break;
    case F9 : fitness = objfuncF9(temp_alleles); break;    
    case F10: fitness = objfuncF10(temp_alleles); break;
    case F11: fitness = objfuncF11(temp_alleles); break;
    case F12: fitness = objfuncF12(temp_alleles); break;
    case F13: fitness = objfuncF13(temp_alleles,gen_no); break;
    case F14: fitness = objfuncF14(temp_alleles,gen_no); break;
    case F15: fitness = objfuncF15(temp_alleles,gen_no,gene_no()); break;
  }
  //printf("\n Leaving decode_diploid_xor()");
}   
/*************************************************************************/
int BGE_individual::error_check_strings(int loops)
{
  /**************************************************************/
  /* Error checking to ensure string not corrupted (caused by a */
  /* hanging pointer if occurs).                                */
  /**************************************************************/
  //printf("\n enetring error check()");
  int error = 0;
  for(int count=0; count < loops; count++) {
    chromosome[count].point_to_head();
    for(int c1=0; c1 < stringLength; c1++) {
      bit b = chromosome[count].get_current_element();
      ++chromosome[count];
      if((SHADES == SHADES_2) || (SHADES == SHADES_3)) {
        if((b != F)&&((b != T)&&(b != S))) error = 1;
      }
      else {
        if((b != T)&&(b != F)) error = 1;
      }
    }
    chromosome[count].point_to_head();
  }
  //printf("\n leaving error check()- error = %d",error);
  return error;
}

/*************************************************************************/
void BGE_individual::assignvalues(const int mate1,const int mate2,
                                  const int gen_no, const int id)
{
  /**************************************************************/
  /* Provided with specified parameters by a population(object);*/ 
  /* the population can then requests that the stastical        */
  /* details of an individual be filled in.                     */
  /**************************************************************/
  //  printf("\n entering ASSIGNVALUES()");
  if((gen_no > 0)&&(LENGTH==VARIABLE)) {
    int gl = gene_no();
    delete [] array;
    array = new bit[stringLength];
    delete [] alleles[0];
    alleles[0] = new double[gl];
    if (STRUCTURE == DIPLOID){
      delete [] alleles[1];
      alleles[1] = new double[gl];
    }
    if ((SHADES == SHADES_2) || (SHADES==SHADES_3)){
      delete [] new_genotype;
      new_genotype = new bit[gl*bits_per_gene];
    }
  }
  /*
  if((gen_no > 0)&&(LENGTH==VARIABLE)) {
    delete [] array;
    delete [] alleles[0];
    array = new bit[stringLength];
    alleles[0] = new double[stringLength/bits_per_gene];
    if (STRUCTURE == DIPLOID){
      delete [] alleles[1];
      alleles[1] = new double[stringLength/bits_per_gene];
    }
    if ((SHADES == SHADES_2) || (SHADES==SHADES_3)){
      delete [] new_genotype;
      new_genotype = new bit[stringLength];
    }
  }
  */
  int loops;
  if(STRUCTURE == HAPLOID) loops = 1;
  else {
    if(STRUCTURE == DIPLOID) loops = 2;
    else {
      printf("\n ERROR: Unknown chromosome structure ");
      exit(1);
    }
  }
  if(error_check_strings(loops)) {
    error_msg(DECODE);
    error_msg(SHUT_DOWN);
  }
  /*---------------------------------------------*/
  /* If shades set, used shades() to derive and  */
  /* decode new genotype. Otherwise, decode using*/
  /* standard decoding procs in BGE_decode.hpp   */
  /*---------------------------------------------*/
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) { 
    if(SHADES == SHADES_2) shades_2();
    if(SHADES == SHADES_3) shades_3();
  }
  else {  
    for(int count =0; count < loops; count++) {
      for(int i = 0; i < gene_no(); i++) {
	for(int count2=0;count2 < bits_per_gene; count2++) {
          arr[count2] = chromosome[count].get_current_element();
	  ++chromosome[count];
	}
	switch(CODE_SCHEME) {
          case BINARY: alleles[count][i] = decode.decode_binary(arr,1,bits_per_gene-1);
                       break;
          case E_CODE: alleles[count][i] = decode.decode_Ecode(arr,1,bits_per_gene-1); 
                       break;
          case GRAY:   alleles[count][i] = decode.decode_Gray(arr,1,bits_per_gene-1); 
                       break;
          case J_CODE: alleles[count][i] = decode.decode_Jcode(arr,1,bits_per_gene-1); 
                     break;
	} 
        alleles[count][i] /= ALLELE_FACTOR;
        if(SIGN) {
	  if(arr[0] == F) alleles[count][i] = alleles[count][i] * (-1);
	}
      }
    }
  }

  parent1 = mate1;
  parent2 = mate2;   
  int string_no = 0;

  if((STRUCTURE == DIPLOID) && (DIP_EVAL == XOR)) decode_diploid_xor(gen_no); 
  else {
    if(STRUCTURE == HAPLOID) string_no = 0;
    else {
      if((STRUCTURE == DIPLOID) && (DIP_EVAL == RANDOM)) string_no = randomint(2);
      else {
	printf("\n ERROR: do not know how to decode string");
	exit(1);
      }
    }
    switch(PROBLEM_DOMAIN) {
      case F1 : fitness = objfuncF1(alleles[string_no]); break;
      case F2 : fitness = objfuncF2(alleles[string_no]); break;
      case F3 : fitness = objfuncF3(alleles[string_no]); break;
      case F4 : fitness = objfuncF4(alleles[string_no]); break;
      case F5 : fitness = objfuncF5(alleles[string_no]); break;
      case F6 : fitness = objfuncF6(alleles[string_no]); break;
      case F7 : fitness = objfuncF7(alleles[string_no]); break;
      case F8 : fitness = objfuncF8(alleles[string_no]); break;
      case F9 : fitness = objfuncF9(alleles[string_no]); break;    
      case F10: fitness = objfuncF10(alleles[string_no]); break;
      case F11: fitness = objfuncF11(alleles[string_no]); break;
      case F12: fitness = objfuncF12(alleles[string_no]); break;
      case F13: fitness = objfuncF13(alleles[string_no],gen_no); break;
      case F14: fitness = objfuncF14(alleles[string_no],gen_no); break;
      case F15: fitness = objfuncF15(alleles[string_no],gen_no,gene_no()); break;
      case F16: fitness = objfuncF16(alleles[string_no],gen_no,gene_no(),id,GE_Decode_flag); break;
    }
  }  
  
  chromosome[0].point_to_head();
  if(STRUCTURE == DIPLOID) chromosome[1].point_to_head();

  //printf("\n leaving ASSIGNVALUES()");
}
/*************************************************************************/
void BGE_individual::redo_fitness(const int gen_no, const int id)
{
  /**************************************************************/
  /* Revaluate fitness of string.                               */
  /**************************************************************/
  int string_no = 0;
  if((STRUCTURE == DIPLOID) && (DIP_EVAL == XOR)) decode_diploid_xor(gen_no); 
  else {
    if(STRUCTURE == HAPLOID) string_no = 0;
    else {
      if((STRUCTURE == DIPLOID) && (DIP_EVAL == RANDOM)) string_no = randomint(2);
      else {
	printf("\n ERROR: do not know how to decodde string");
	exit(1);
      }
    }
    switch(PROBLEM_DOMAIN) {
      case F1 : fitness = objfuncF1(alleles[string_no]); break;
      case F2 : fitness = objfuncF2(alleles[string_no]); break;
      case F3 : fitness = objfuncF3(alleles[string_no]); break;
      case F4 : fitness = objfuncF4(alleles[string_no]); break;
      case F5 : fitness = objfuncF5(alleles[string_no]); break;
      case F6 : fitness = objfuncF6(alleles[string_no]); break;
      case F7 : fitness = objfuncF7(alleles[string_no]); break;
      case F8 : fitness = objfuncF8(alleles[string_no]); break;
      case F9 : fitness = objfuncF9(alleles[string_no]); break;    
      case F10: fitness = objfuncF10(alleles[string_no]); break;
      case F11: fitness = objfuncF11(alleles[string_no]); break;
      case F12: fitness = objfuncF12(alleles[string_no]); break;
      case F13: fitness = objfuncF13(alleles[string_no],gen_no); break;
      case F14: fitness = objfuncF14(alleles[string_no],gen_no); break;
      case F15: fitness = objfuncF15(alleles[string_no],gen_no,gene_no()); break;
      case F16: fitness = objfuncF16(alleles[string_no],gen_no,gene_no(),id,GE_Report_flag); break;
    }
  }  
}
/*************************************************************************/
bit  BGE_individual::mutation(const double posmutation,int & numofmutations,
                              int & totalmutations,const int locus,
                              int which_string, int advance)
{
  /**************************************************************/
  /* Mutation at a point is carried out by mutation. This       */
  /* function uses the function flip (the biased coin toss) to  */
  /* determine whether or not to change a true to false (1 to 0)*/
  /* or vice versa. The new allele value of the feature is      */
  /* returned.                                                  */
  /**************************************************************/
  // printf("\n entering MUTATION()");

  if((STRUCTURE==FIXED)&&(locus > stringLength)) {
    error_msg(NO_BIT);
    error_msg(SHUT_DOWN);
  }
  if((advance != 0)&&(advance != 1)) {
    printf("\n Error: advance not set properly");
    exit(1);
  }
  
  if(((STRUCTURE == HAPLOID)&&(which_string > 0))||
     ((STRUCTURE == DIPLOID)&&(which_string > 1))) {
    printf("\n ERROR in mutation");
    exit(1);
  }
  
  bit b = chromosome[which_string].get_current_element();
  if(advance) ++chromosome[which_string];
  // printf("\n existing bit %d at locus %d",b,locus);  
  if (probably(posmutation)) {
    // printf("\n mutating bit %d at locus %d",b,locus);
    numofmutations++;
    totalmutations++;
    if ((SHADES==SHADES_2)||(SHADES==SHADES_3)) {
      switch(b) {
        case F: if(randomint(2)) b = T;
                else b = S;
                break;
        case T: if(randomint(2)) b = S;
                else b = F;
                break;
        case S: if(randomint(2)) b = F;
                else b = T;
                break;
      }
    }
    else {
      if (b == T) b = F;
      else b = T;
    }
  }
  // printf("\n returning bit %d at locus %d",b,locus);
  // printf("\n leaving MUTATION()");
  return b;
}
/*************************************************************************/
void BGE_individual::scale_chromosome(double a,double b)
{
  /**************************************************************/
  /* Adjusts the fitness of a chromosome as a functional of the */
  /* scaling function to prevent pre-mature convergence and     */
  /* maintain population diversity.                             */
  /**************************************************************/

 scaledfitness = (fitness * a) + b;
 if(scaledfitness < 0) {
   // error_msg(S_FIT);
   scaledfitness = 0;
 }
}
/*************************************************************************/

void BGE_individual::set_scaled_fitness(double newval)
{
  scaledfitness = newval;
} 

/*************************************************************************/
void BGE_individual::sigma_preprocess(double avg, double c, double stdev)
{
  /**************************************************************/
  /* Adjusts the fitness of a chromosome to prevent negative    */
  /* values.                                                    */ 
  /**************************************************************/

 double f = fitness - (avg - (c * stdev));
 fitness = f;
 if(fitness < 0) {
   // error_msg(P_FIT);
   fitness = 0;
 }
}
/*************************************************************************/
bit* BGE_individual::returncopy(int which_string)
{
  /**************************************************************/
  /* Returns a pointer to the chromosome string                 */
  /**************************************************************/
  // printf("\n entering Returncopy()");

  chromosome[which_string].point_to_head();
  for(int count=0; count < stringLength; count++) {
    array[count] = chromosome[which_string].get_current_element();
    ++chromosome[which_string];
  }
  return array;
}
/*************************************************************************/
bit* BGE_individual::return_shades_genotype()
{
  /**************************************************************/
  /* Returns a pointer to the derived genotype if shades used   */
  /**************************************************************/
  bit *c;
  c = new_genotype;
  return c;
}
/*************************************************************************/
void BGE_individual::del()
{
  // printf("\n about to delete list");
  // chromosome[0].print_list();
  
  bit b = F;
  chromosome[0].point_to_tail();
  while(!chromosome[0].isEmpty()) {
    b = chromosome[0].removeNode();
  }
  if(STRUCTURE == DIPLOID) {
    chromosome[1].point_to_tail();
    while(!chromosome[1].isEmpty()) b = chromosome[1].removeNode();
  }
  // printf("\n leaving delete list() ");
}
/*************************************************************************/
void BGE_individual::del_string(const int which_string)
{
  bit b = F;
  chromosome[which_string].point_to_tail();
  while(!chromosome[which_string].isEmpty()) b = chromosome[which_string].removeNode();
}
/*************************************************************************/
void BGE_individual::insert()
{
  int num;
  if(SHADES== F) num = bits_per_gene;
  else num = shades_bits_per_gene;

  int range;
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) range = 3;
  else range = 2;
 
 for(int count = 0; count < num; count++) {
    int temp = randomint(range);
    switch(temp) {
      case 0  : if(chromosome[0].start_equals_current()) chromosome[0].prepend(F);
	        else chromosome[0].insert(F);  
                break;
      case 1  : if(chromosome[0].start_equals_current()) chromosome[0].prepend(T);
	        else chromosome[0].insert(T);  
                break;
      case 2  : if(chromosome[0].start_equals_current()) chromosome[0].prepend(S);
	        else chromosome[0].insert(S);  
                break;
      default : error_msg(GENERATE);
                error_msg(SHUT_DOWN);
                break;
    }
  }
  if(STRUCTURE == DIPLOID) {
    for(int count =0; count < num; count++) {
      if(randomint(2)) {
	if(chromosome[0].start_equals_current()) chromosome[0].prepend(T);
        else chromosome[1].insert(T);
      }
      if(chromosome[0].start_equals_current()) chromosome[0].prepend(F);
      else chromosome[1].insert(F);
    }
  }
}
/*************************************************************************/
void BGE_individual::swap_two_genes(const int pos1, const int pos2)
{
  // printf("\n entering swap_two_genes()");

  int p1,p2,len;
  if(SHADES==F) len = bits_per_gene;
  else len = shades_bits_per_gene;
  p1 = pos1 * len;
  p2 = pos2 * len;
  chromosome[0].swap(p1,p2,len);
  if(STRUCTURE == DIPLOID) chromosome[1].swap(p1,p2,len);

  // printf("\n leaving swap_two_genes()");
}
/*************************************************************************/

/*************************************************************************/
void BGE_individual::reset()
{
  chromosome[0].point_to_head();
  if(STRUCTURE == DIPLOID) chromosome[1].point_to_head();
}
/*************************************************************************/
void BGE_individual::postset()
{ 
  chromosome[0].point_to_tail(); 
  if(STRUCTURE == DIPLOID) chromosome[1].point_to_tail();
}
/*************************************************************************/
void BGE_individual::traverse(const int num)
{
  int len;
  if(SHADES==F) len = bits_per_gene * num;
  else len = shades_bits_per_gene * num;
  chromosome[0].traverse_list(len);
  if(STRUCTURE==DIPLOID) chromosome[1].traverse_list(len);
}
/*************************************************************************/
int BGE_individual::operator>=(const BGE_individual &m)
{
  /**************************************************************/
  /* Overloading the >= operator                                */
  /**************************************************************/

  if(scaledfitness >= m.scaledfitness) return 1;
  else return 0;
}
/*************************************************************************/
int BGE_individual::operator<=(const BGE_individual &m)
{
  /**************************************************************/
  /* Overloading the <= operator                                */
  /**************************************************************/

  if(scaledfitness <= m.scaledfitness) return 1;
  else return 0;
}
/*************************************************************************/
int BGE_individual::operator>(const BGE_individual &m)
{
  /**************************************************************/
  /* Overloading the > operator                                 */
  /**************************************************************/

  if(scaledfitness > m.scaledfitness) return 1;
  else return 0;
}
/*************************************************************************/
int BGE_individual::operator<(const BGE_individual &m)
{
  /**************************************************************/
  /* Overloading the < operator                                 */
  /**************************************************************/

  if(scaledfitness < m.scaledfitness) return 1;
  else return 0;
}
/*************************************************************************/
BGE_individual& BGE_individual::operator=(BGE_individual &object2)
{
  /**************************************************************/
  /* Overloading the = operator                                 */
  /**************************************************************/
  /*
  chromosome[0].point_to_head();
  bit b = F;
  del();

  int len = object2.str_len();
  int gene_length = ob
  for(int j2=0; j2<len; j2++) {
    b = object2.chromosome[0].get_current_element();
    ++object2.chromosome[0];   
    chromosome[0].insert(b);
    if(STRUCTURE == DIPLOID) {
      b  = object2.chromosome[1].get_current_element();
      ++object2.chromosome[1];   
      chromosome[1].insert(b);
    }
  }

  if((SHADES == SHADES_2)||(SHADES==SHADES_3)) {
    for(int count =0; count < gene_no() * bits_per_gene; count++)
      new_genotype[count] = object2.new_genotype[count];
  }

  parent1 = object2.parent1;
  parent2 = object2.parent2;
  fitness = object2.fitness;
  scaledfitness = object2.scaledfitness;
  stringLength = object2.str_len();

  for(int k=0; k<gene_no();k++) {
    alleles[0][k] = object2.alleles[0][k];
    if(STRUCTURE == DIPLOID) alleles[1][k] = object2.alleles[1][k];
  }
  return *this; 
  */

  int len = object2.str_len();
  int gene_length = object2.gene_no();
  /*-------------------------------------------*/
  /* 1. Copy string.                           */
  /*-------------------------------------------*/
  object2.chromosome[0].point_to_head();
  object2.chromosome[1].point_to_head();
  bit b = F;
  del();
  for(int j2=0; j2<len; j2++) {
    b = object2.chromosome[0].get_current_element();
    ++object2.chromosome[0];   
    chromosome[0].insert(b);
    if(STRUCTURE == DIPLOID) {
      b  = object2.chromosome[1].get_current_element();
      ++object2.chromosome[1];   
      chromosome[1].insert(b);
    }
  }
  /*---------------------------------------------*/
  /* 2. If variable, reallocate arrays as size   */
  /*    will ahve changed.                       */
  /*---------------------------------------------*/
  if(LENGTH == VARIABLE) {
    delete [] array;
    array = new bit[len];
    delete [] alleles[0];
    alleles[0] = new double[gene_length];
    if(STRUCTURE == DIPLOID) {
      delete [] alleles[1];
      alleles[1] = new double[gene_length];
    }
    if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
      delete [] new_genotype;
      new_genotype = new bit[gene_length * bits_per_gene];
    }
  }
  /*-------------------------------------------*/
  /* 3. Copy alleles.                          */
  /*-------------------------------------------*/
  for(int j3=0; j3 < gene_length; j3++) {
    alleles[0][j3] = object2.alleles[0][j3];
    if(STRUCTURE == DIPLOID) 
      alleles[1][j3]  = object2.alleles[1][j3];
  }
  /*-------------------------------------------*/
  /* 4. If shades_?() copy new_genotype        */
  /*-------------------------------------------*/
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
    for(int j4=0; j4 < gene_length * bits_per_gene; j4++) {
      new_genotype[j4] = object2.new_genotype[j4];
    }
  }
  /*-------------------------------------------*/
  /* 5. Copy atomic variables                  */
  /*-------------------------------------------*/
  parent1 = object2.parent1;
  parent2 = object2.parent2;
  fitness = object2.fitness;
  scaledfitness = object2.scaledfitness;
  stringLength = object2.str_len();

  return *this; 
}
/*************************************************************************/
void BGE_individual::display_chromosome()
{
  chromosome[0].print_list();
  if(STRUCTURE == DIPLOID) chromosome[1].print_list();
}
/*************************************************************************/
int BGE_individual::str_len()
{
  /**************************************************************/
  /* Returns length of string                                   */
  /**************************************************************/
  return stringLength;
}
/*************************************************************************/
void BGE_individual::duplicate_genes()
{
  /************************************************************/
  // AUTHOR: Michael O'Neill
  //	     Duplicates 1 or more genes and places them on the 
  //              end of the chromosome less one gene.
  //
  //     Note: Only implemented for HAPLOIDY
  /************************************************************/
  //  cout << "ENTERING DUPLICATE_GENES" << endl;

  if(probably(p_duplicate)){
    int ngenes=0, start_gene=0, ngenes_to_duplicate=0;
    
    /*
     * Determine ngenes to duplicate and start position
     */

    ngenes=gene_no();
    ngenes_to_duplicate=(randomint(ngenes-1)+1);
    start_gene=randomint(ngenes-ngenes_to_duplicate);

    /* 
     * copy genes to duplicate to the temp list
     */
    
    List temp;
    chromosome[0].point_to_head();
    for(int t=0;t<(start_gene*bits_per_gene);t++)
      ++chromosome[0];
    
    for(int j=0;j<(ngenes_to_duplicate*bits_per_gene);j++){
      temp.insert(chromosome[0].get_current_element());
      ++chromosome[0];
    }
    
    chromosome[0].point_to_head();
    temp.point_to_head();
    
    /*
     * goto duplicated gene insertion point (before last gene)
     */
    if(gene_no()!=1){
      chromosome[0].point_to_tail();
      
      for(int j=0;j<bits_per_gene;j++)
	--chromosome[0];
    }
    // else insert duplicate at very beginning of chromosome

    for(int j=0;j<(ngenes_to_duplicate*bits_per_gene);j++){
      chromosome[0].insert(temp.get_current_element());
      ++temp;
    }
    
    stringLength = stringLength + (ngenes_to_duplicate*bits_per_gene); 
  }
  //  cout << "LEAVING DUPLICATE_GENES" << endl;
}
/*************************************************************************/
int BGE_individual::gene_no()
{
  /**************************************************************/
  /* Returns length of string                                   */
  /**************************************************************/
  if(SHADES==SHADES_2) return stringLength/shades_bits_per_gene;
  if(SHADES==SHADES_3) return stringLength/shades_bits_per_gene;
  //  cout << "entering gene_no()"<< endl;
  //  cout << "bits_per_gene (" << bits_per_gene << ")" << endl;
  //  cout << "stringLength (" << stringLength << ")" << endl;
  return stringLength/bits_per_gene;
}


/*************************************************************************/
void BGE_individual::del_gene()
{
  /**************************************************************/
  /* Deletes a gene                                             */
  /**************************************************************/
  int l;
  if((SHADES==SHADES_2)||(SHADES==SHADES_3)) l = shades_bits_per_gene;
  else l = bits_per_gene;
  for(int i=0; i < l; i++) 
    bit b = chromosome[0].removeNode();
  if(STRUCTURE == DIPLOID) bit b1 = chromosome[1].removeNode();
}
/*************************************************************************/

void BGE_individual::show(FILE *fp)
{
  /**************************************************************/
  /* Prints the chromosome if full reporting option set.        */
  /**************************************************************/
  //fprintf(fp,"\n genome  = ");
  /*
  chromosome[0].point_to_head();
  for(int j2=0; j2<stringLength; j2++) {
    bit b = chromosome[0].get_current_element();
    ++chromosome[0];
    if(b == T) fprintf(fp,"1");
    else {
      if(b == F) fprintf(fp,"0");
      else fprintf(fp,"?");
    }
  }
  */
  fprintf(fp," | fitness %f (scaled) %f | ",fitness,scaledfitness);
  for(int count = 0; count < gene_no(); count++)
    fprintf(fp,"%.0f,",alleles[0][count]);
}
/*************************************************************************/
void BGE_individual::setGE_Report_flag(int flag)
{
  GE_Report_flag=flag;
}
/*************************************************************************/
int BGE_individual::getparent1()
{
  return parent1;
}
int BGE_individual::getparent2()
{
  return parent2;
}
/*************************************************************************/


#if 0
void BGE_individual::duplicate_genes()
{
  /************************************************************/
  // AUTHOR: Michael O'Neill
  //	     Duplicates 1 or more genes and places them on the 
  //              end of the chromosome less one gene.
  //
  //     Note: Only implemented for HAPLOIDY
  //
  // BUGGY.....not working properly!
  /************************************************************/
  //  cout << "ENTERING DUPLICATE_GENES" << endl;

  int num_genes_picked=0, start_gene_picked=0;
  int ngenes=0; 

  if(probably(p_duplicate)){
    //    cout << "About to duplicate...." << endl;

    ngenes=gene_no();
    num_genes_picked=(randomint(ngenes-1)+1);
    if( (start_gene_picked=randomint(ngenes-num_genes_picked))==0 ) start_gene_picked=1;
    char temp_gene[bits_per_gene*num_genes_picked]; 

    //    cout << "stringLength (" << stringLength << ")" << endl;
    //    cout << "ngenes (" << ngenes << ")" << endl;
    //    cout << "num_genes_picked (" << num_genes_picked << ")\t start_gene_picked (" << start_gene_picked << ")" << endl;
    //    display_chromosome(); cout << endl;

    //Goto genes to duplicate and copy into temp_gene 
    reset();
    traverse(start_gene_picked); advance();
    //cout << "genes to duplicate {";
    for(int i=0; i< (bits_per_gene*num_genes_picked); i++){
      if(chromosome[0].get_current_element() == F) {temp_gene[i]='0';
      //cout << "0";
      }
      else {
	if(chromosome[0].get_current_element() == T) {temp_gene[i]='1';
	//cout << "1";
	}
	else {temp_gene[i]='?';
	//cout << "?";
	}
      }
      advance();
    }
    //    cout << "}" << endl;
    //    cout << "temp_gene[] {";
    //    for(int im=0;im<(bits_per_gene*num_genes_picked);im++) cout << temp_gene[im];
    //    cout << "}" << endl;

    //copy last gene onto end of temp_gene
    //    reset();
    //    traverse(gene_no()-1);advance();
    //    cout << "last gene {";
    //    for(int ij=bits_per_gene*num_genes_picked; ij<(bits_per_gene*num_genes_picked)+bits_per_gene; ij++){
    //      if(chromosome[0].get_current_element() == F) {temp_gene[ij]='0';
      //cout << "0";
    //      }
    //      else {
    //    	if(chromosome[0].get_current_element() == T) {temp_gene[ij]='1';
	//cout << "1";
    //    	}
    //    	else {temp_gene[ij]='?';
	//cout << "?";
    //    	}
    //      }
    //      advance();
    //    }
    //    cout << "}" << endl;
    //    cout << "temp_gene[] {";
    //    for(int im=0;im<bits_per_gene*(num_genes_picked+1);im++) cout << temp_gene[im];
    //    cout << "}" << endl;


    //Remove last gene from individual
    //    reset();
    //    chromosome[0].point_to_tail();
    //    for(int i=0;i<bits_per_gene;i++){
    //      chromosome[0].removeNode();
    //    }
    //    display_chromosome(); cout << endl;

    //Copy temp_gene into chromosome starting after last gene start position
    reset();
    int last_gene_index=gene_no();
    traverse(last_gene_index);
    
    //    cout << "inserting {";
    for(int im=0;im<bits_per_gene*num_genes_picked;im++){
      if(temp_gene[im]=='0') {
	chromosome[0].insert(F);
	//cout << "0";
      }
      else 
	{
	  if(temp_gene[im]=='1') {
	    chromosome[0].insert(T);
	    //cout << "1";
	  }
	  else {
	    //chromosome[0][k]='?';
	    //cout << "?";
	  }
	}
      advance();
    }
    //    cout << "}" << endl;
    //    display_chromosome(); cout << endl;
    /*
     * set new values for stringLength
     */
    reset();
    int count=1;
    while(!chromosome[0].at_end()){ advance(); count++;}
    stringLength = count;

    //    cout << "count (" << count << ")" << endl;
    //    cout << "stringLength (" << stringLength << ")" << endl;
    //    cout << "ngenes (" << ngenes << ")" << endl;
    //    cout << "num_genes_picked (" << num_genes_picked << ")\t start_gene_picked (" << start_gene_picked << ")" << endl;

  }//if(pduplicate)
  else{}

  //  cout << "LEAVING DUPLICATE_GENES" << endl;
}
#endif
