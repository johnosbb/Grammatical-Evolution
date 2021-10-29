/*************************************************************************/
/*                                                                       */
/*              FILE   :  ERROR_CODES.HPP                                */
/*              AUTHOR :  J.J. COLLINS                                   */
/*              DATE   :  AUG. 1996/1997                                 */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  defines error codes used to display error messages in the GA program */
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _ERROR_CODES_H
#define _ERROR_CODES_H

/*************************************************************************/

#define GENES         1    // number of genes
#define NUM_BITS      2    // number of bits per gene
#define PROB          3    // probability of crossover or mutation
#define CODE          4    // genocode not specified
#define CROSS         5    // crossover operator
#define SEL           6    // selection mechanism
#define MUTATE_REAL   7    // mutation operator for reals
#define DECIMAL       8    // number of decimals in upper limit
#define GRAN          9    // granularity
#define RND           10   // rounding with incorrect granularity
#define LIMIT         11   // limit on granularity
#define CONVERGENCE   12   // population homogeneity
#define AVG           13   // average <= 0 (after preprocess and scaling)
#define PRE_PROCESS   14   // average <= 0 (after preprocess)
#define P_FIT         15   // preprocessed fitness < 0
#define S_FIT         16   // scaled fitness < 0;
#define C_LENGTH      17   // conflicting values for chromosome length
#define NO_GENE       18   // trying to return value of non existent gene
#define DECODE        19   // unable to decode string - pointer problems
#define NO_STRING     20   // trying to access a non-existent string
#define NO_BIT        21   // trying to access a non-existent bit
#define ELITE         22   // ELITE_QTY mod 2 not equal to 0
#define IMPLEM        23   // routine not yet implemented
#define POP_SIZE      24   // initial population size % 2 not equal to 0
#define MAX_POP       25   // population boundary exceeds array boundaries
#define DOM           26   // no problem domain set.
#define ADAPT_1       27   // Adaptation rate less than 0 (negative mutation probability)
#define ADAPT_2       28   // Adaptation rate equals 0 (zero mutation probability)
#define ADAPT_3       29   // Adaptation rate results in a high mutation probability 0.5 <= pm <= 1
#define ADAPT_4       30   // Adaptation rate results in mutation probability  > 1
#define GAP           31   // generation gap of zero.
#define STRCT         32   // did not specify whether haploid or diploid
#define TYPE          33   // environment (static or dynamic) not set.
#define ENV_CHANGE    34   // rate at which env. changes if dynamic
#define SHADES_ERR    35   // polygenic inheritance not set correctly
#define PERTURB_ERR   36   // probability factor for perturbation incorrect
#define UP            37   // shades trying to force up a bit of value 2
#define DOWN          38   // shades trying to force down a bit of value 0
#define TWO_PT        39   // trying to do 2point crossover, but only 1 bit in string
#define GENERATE      40   // unable to generate bit string
#define SHADES_PROB   41   // haploid not specified for shades2 or shades3
#define DIP_PROB      42   // evaluation method for diploidy unspecified
#define LEN           43   // fixed or variable length
#define GE_1          44   // Grammatical Evolution Function matching Grammar test
#define SHUT_DOWN     50   // system shutting down


/*************************************************************************/
#endif
