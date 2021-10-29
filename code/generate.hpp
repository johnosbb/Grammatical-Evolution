/*************************************************************************/
/*                                                                       */
/*              FILE   :  GENERATE.HPP                                   */
/*              AUTHOR :  J.J. COLLINS                                   */
/*              DATE   :  AUG - SEPT 1996                                */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Header file where selection and generate functions defines. The range */
/* of selection mechanisms implemented (or yet to be) is:                */
/* - 1.  TSR                                                             */
/* - 2.  RANK                                                            */
/* - 3.  REMAINDER_STOCHASTIC_SAMPLING_without_REPLACEMENT               */
/* - 4.  STOCHASTIC_SAMPLING_without_REPLACEMENT                         */
/* - 5.  REMAINDER_STOCHASTIC_SAMPLING_with_REPLACEMENT                  */
/* - 6.  STOCHASTIC_SAMPLING_with_REPLACEMENT                            */
/* user choice specified in file "defines.h".                            */
/*                                                                       */
/* To generate a detailed report, set full_report option to "t" in       */
/* "defines.h", "f" otherwise.                                           */
/*  -------------------------------------------------------------------  */
/*     BUGS : diploidy not implemented for STEADY_STATE                  */
/*                                                                       */
/*************************************************************************/

#ifndef _GENERATE_H
#define _GENERATE_H

#include <stdio.h>
#include "../params.h"
#include "crossover.hpp"
#include "scaling.hpp"
#include "mysort.hpp"

/*************************************************************************/

class generate: public crossover,mysort
{
  private:
    // D A T A
    int   *table,*selector,*selected,roulette;
    int maxpop_size;
    // M E S S A G E S
    /*---------------------------*/
    /* 1. Selection operators    */
    /*---------------------------*/
    void TSR_preselection();
    int target_sampling_rate(int nremain);
    void RSSwoR_preselect();
    int RSSwithoutR(int nremain);       
    int select_roulette(int prev = POPSIZE+1);
    /*---------------------------*/
    /* Generate Populations      */
    /*---------------------------*/  
    int search(int n);  
    void print_selection_stats();
    void swap_old_pop_with_new(const int size);
    void generate_steady_state(const double pmut);
    void select(int &mate1, int &mate2, const int j, const int pop);
    void re_evaluate_fitness(const int pop);
    void save_pop();
    void save_results_data(char filename[]);
  
  public:
    // M E S S A G E S
    /*---------------------------*/
    /* 2. Constructors and destr.*/
    /*---------------------------*/      
    generate();  
    ~generate();
    /*---------------------------*/
    /* 3. Generate Populations   */
    /*---------------------------*/    
    void generate_pop();            
    int generatefin();
 };                                                

/*************************************************************************/
#endif







