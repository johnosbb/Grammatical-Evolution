/*************************************************************************/
/*                                                                       */
/*              FILE   :  BGE_INDIVIDUAL.HPP                             */
/*              AUTHOR :  J.J. COLLINS                                   */
/*              DATE   :  AUG. 1996/1997                                 */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Header file where chromosome (integral constituent of GA) is declared */
/* using object oriented design and programming paradigm. Implementation */
/* is in file of same name but with ".cc" extension. Chromosome length   */
/* (num. genes x bits per gene) defined in file "defines.h". This program*/ 
/* can use either binary, Gray or E-code chromosomal encoding schemes    */
/* (hence BGE). The objective fitness functions are defined in the file  */
/* "objfunc.hpp". The decoding functions are in the file "decode.hpp".   */
/* Encoding and fitness function parameters set in file "defines.h".     */
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _BGE_individual_h
#define _BGE_individual_h

#include <stdio.h>
#include "params.h"
#include "errors.hpp"
#include "linked_list.hpp"
#include "objfunc.hpp"

/*************************************************************************/

class BGE_individual: private objective_function, public errors
{
 private:

   // D A T A
   List      chromosome[2];         // Genotype - linked list of bits
   double    *alleles[2],*temp_alleles;// signed real-value of gene
   double    fitness;               // objective function value
   double    scaledfitness;         // Fitness scaling value;        
   int       parent1,parent2;       // parents & cross site
   int       stringLength;         // length of single string
   bit       *new_genotype;          // new genotype derived by shades (if used)
   int       shades_bits_per_gene;  // shades assoc. vars
   bit       *arr, *array, *temp;          // used for passing whole genes
   int       GE_Report_flag;
   int       *mappingHistory;        // individuals mapping history
   int       historyLength;          // length of mapping history
   int GE_Decode_flag;
  
   // M E S S A G E S 
   void force_up(int decrement);  
   void force_down(int decrement);
   void swap_positions(const int dec2, const int dec2);
   void decode_shades_phenotype();
   void shades_2();
   void shades_3();
   void decode_diploid_xor(const int gen_no);
   int error_check_strings(int loops);
 public :

   // M E S S A G E S
   /*----------------------------------*/
   /* Generic functions                */
   /*----------------------------------*/
   BGE_individual();
   ~BGE_individual();
   void generatechromosome(const int clength);
   void setbit(bit bitval, int locus, int which_string = 0);
   void assignvalues(const int mate1,const int mate2,
                     const int gen_no, const int id);
   bit mutation(const double posmutation,int & nummutations,
                    int & totalmutations,const int locus,
                    int which_string = 0, int advance = 1);
   /*----------------------------------*/
   /* Fitness Related Functions        */
   /*----------------------------------*/
   void sigma_preprocess(double avg, double c, double stdev);
   void scale_chromosome(double a, double b);
   void set_scaled_fitness(double newval);
   double fitnesslevel(boolean indicator);
   double gene_value(const int which_gene, int which_string = 0);
   void redo_fitness(const int gen_no, const int id);
   /*----------------------------------*/
   /* Setting current pointer in list. */
   /*----------------------------------*/
   void reset();
   void postset();
   void traverse(const int num); //Goes to the gene specified (not the bit position!)
   void advance(int chrom_no = 0) { ++chromosome[chrom_no]; }; 
   /*----------------------------------*/
   /* Deleting and inserting from list */
   /*----------------------------------*/
   void del();
   void del_string(const int which_string);
   void del_gene();
   void insert();
   void swap_two_genes(const int pos1, const int pos2);
   /*----------------------------------*/
   /* Duplication of list elements     */
   /*----------------------------------*/
   void duplicate_genes(); //Duplicates 1 or More Genes 
   /*----------------------------------*/
   /* Length of list                   */
   /*----------------------------------*/
   int gene_no();
   int str_len();			
   void set_string_length(const int l) { stringLength=l; };
   /*----------------------------------*/
   /* Return pointer to copy of string */
   /*----------------------------------*/
   bit* return_shades_genotype();
   bit* returncopy(int which_string = 0);
   /*----------------------------------*/
   /* Overloaded operators and display */
   /*----------------------------------*/
   int operator>(const BGE_individual &m);
   int operator<(const BGE_individual &m);
   int operator>=(const BGE_individual &m);
   int operator<=(const BGE_individual &m);
   void display_chromosome();
   BGE_individual& operator=(BGE_individual &object2);
   void show(FILE *fp);
   void setGE_Report_flag(int flag);
   int getparent1();
   int getparent2();
 };
/*************************************************************************/
#endif /* _individual_h */

