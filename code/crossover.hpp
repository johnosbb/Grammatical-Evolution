/*************************************************************************/
/*                                                                       */
/*             FILE   :  CROSSOVER.HPP                                   */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG 1996/1997                                   */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/* Header file where crossover is currently implemented as either        */
/* 1-point, 2-point or uniform, as specified in file "defines.h".        */
/* See end of file "defines.h" for explaination of diploid crossover     */
/* mechanisms.                                                           */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#ifndef _CROSSOVER_H
#define _CROSSOVER_H

#include <stdio.h>
#include "../params.h"
#include "BGE_population.hpp"

/*************************************************************************/

class crossover: public BGE_population
{
  protected:
    // M E S S A G E S
    void swap_genes(const int indiv);
    void prune(const int indiv);
    void insert_gene(const int indiv);
    void delete_gene(const int indiv);
    void copy_with_mutation(const int child, const int parent,const double mutate_rate);
    void clone(const int child, const int parent);
    void duplicate_genes(const int indiv);

    void crossover_1pt(const int m, const int parent1, const int parent2,
                       const double mutate_rate, int jcross, const int which_loop,
                       int string_a = 0, int string_b = 0);
    void crossover_2pt(const int m, const int parent1,
                       const int parent2, const double mutate_rate,
                       int jcross1, int jcross2, const int which_loop,
                       int string_a = 0, int string_b = 0);
    void crossover_uniform(const int m, const int parent1,
                       const int parent2, const double mutate_rate, const int which_loop,
                       int string_a = 0, int string_b = 0);

    void crossover_var_1pt(int m, const int parent1, 
                       const int parent2, const double mutate_rate,
                       int jcross, int jcross1, const int which_loop,int string_a=0, int string_b=0);
    void crossover_var_2pt(const int m, const int parent1,	
                       const int parent2, const double mutate_rate,
                       int jcross1, int jcross2, int ycross1, int ycross2,
                       const int which_loop, int string_a = 0, int string_b = 0);
    void crossover_var_uniform(const int m, const int parent1,
                       const int parent2, const double mutate_rate, const int which_loop,
		       int string_a = 0, int string_b=0);
    void crossover_var_homologous(int m, const int parent1, 
                       const int parent2, const double mutate_rate);
    void swap_strings(const int indiv_1, const int string_1,
                      const int indiv_2, const int string_2);
    void set_up_cross_params(int &parent1, int &parent2, int &string_a,int &string_b, 
                             int &loops, const int mate1, const int mate2);
    void copy_string(const int mate, const int j, const int string);
    void jig_chromosome_strings(const int j, const int string_a, const int string_b,
                                const int mate1,const int mate2);


  public:
    // M E S S A G E S
    crossover();  
    void crossover_parents(const int mate1, const int mate2, const int j, const double pm);
};  
 
/*************************************************************************/                                             
#endif






