/*************************************************************************/
/*                                                                       */
/*              FILE   :  BGE_POPULATION.HPP                             */
/*              AUTHOR :  J.J. COLLINS                                   */
/*              DATE   :  AUG - SEPT 1996/1997                           */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Header file where a population of individuals(haploid chromosomes (and*/
/* associated data) is declared. An individual and associated functions  */
/* - decoding and fitness - is declared in the file "BGE_individual.hpp".*/  
/* The chromosomal coding scheme is either binary, Gray or E-code, hence */
/* BGE. Statistical, and reporting  are functions declared here          */
/*                                                                       */
/* PROCESS                                                               */
/* 1. Calculate physical fitness based on decoded string.                */
/* 2. Statistics using physical fitness.                                 */
/* 3. If physical fitness < 0, preprocess using sigma normalisation      */
/*       and recalculate statistics.                                     */
/* 4. Scale to yield normalised fitness.                                 */
/*    (and sort population if necessary).                                */
/* 5. Use normalised fitness to guide selection                          */
/* 6. Crossover and mutation to derive new population.                   */
/*                                                                       */
/* PARAMETERS                                                            */ 
/* The crossover & mutation probability, size of population (number of   */
/* individuals), and number of generations that evolved; are parameters  */
/* that are specified in the file "defines.h".                           */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _BGE_population_h
#define _BGE_population_h

#include <stdio.h>
#include "../params.h"
#include "BGE_individual.hpp"  
#include "errors.hpp"
#include "titles.hpp"
#include "scaling.hpp"

#define ORIGINAL    1
#define PREPROCESS  2
#define SCALE       3

/*************************************************************************/

class BGE_population: private titles, public scaling, public errors
{
  protected:
    // D A T A
    //int          lchrom;
    int            min_individual,max_individual;
    int            gen,prev_gen,popsize; 
    int            nmutation,totalnmutations,ncross;
    double         avg,max,min,stdev,sumfitness;
    double         o_avg,o_max,o_min,o_stdev,o_sumfitness;
    double         p_avg,p_max,p_min,p_stdev,p_sumfitness;
    double         gen_gap;
    FILE           *fpj,*fp,*fp1,*mikefp,*mikefp2;
    double         a,b;
    BGE_individual *oldpop,*newpop;
    // M E S S A G E S
    /*---------------------------*/
    /* 1. Saving results         */
    /*---------------------------*/  
    void printchromosomefull(int which);
    void printchromosome(int which);
    void printpop();
    void print_fullreport_original();
    void print_fullreport();
    void print_gnuplot();
    /*---------------------------*/
    /* 2. Scaling & statistics   */
    /*---------------------------*/    
    void prescale(double &a, double &b);
    void scalepop();
    void statistics(boolean mybool, int stats_switch);
    int  population_convergence();
    void copy_vals();
    void normalise_data();

  public:

    // M E S S A G E S
    /*---------------------------*/
    /* 3. Constructors and destr.*/
    /*---------------------------*/      
    BGE_population();   
    ~BGE_population();  
    /*---------------------------*/
    /* 4. Other functions        */
    /*---------------------------*/                   
    void report();              
    double bestIndividual();  
    double worstIndividual();  
    double avgIndividual();                         
    void theMikeReport(); //Michael's problem dependent report!
    void resetGEreport();
    void print_fullMikeReport();
    void print_ActualGenotype();
    void Mike_printchromosomefull(int which);
    void John_printchromosomefull(int which);
 };                                                

/*************************************************************************/
#endif /* !_pop_h */






