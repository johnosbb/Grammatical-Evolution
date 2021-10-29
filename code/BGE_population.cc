/*************************************************************************/
/*                                                                       */
/*             FILE   :  BGE_POPULATION.CC                               */
/*             AUTHOR :  J.J. COLLINS                                    */
/*             DATE   :  AUG - SEPT 1996/1997                            */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "BGE_population.hpp".      */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/


#include <math.h>
#include <stdlib.h>
#include "error_codes.h"
#include "BGE_population.hpp"
#include "myrandom.h"

/*************************************************************************/
/*       1.  S A V I N G   R E S U L T S   A N D   D I S P L A Y         */
/*************************************************************************/

void BGE_population::printchromosomefull(int which)
{
  /**************************************************************/
  /* Prints the chromosome string from an individual in oldpop  */      
  /* specified by which with full details.                      */        
  /**************************************************************/

  // printf("\n entering PRINTCHROMOSOMEFULL.");
  if (which >= popsize) {
    error_msg(NO_STRING);
    error_msg(SHUT_DOWN);
  } 
  int gene_count = oldpop[which].gene_no();

  int *breaks = new int[gene_count];
  double *phenotypes[2];
  phenotypes[0] = new double[gene_count];
  phenotypes[1] = new double[gene_count];
 
  int i,j; 
  i = 0;
  for(j = 0; j < gene_count; j++){
    breaks[j] = i;
    phenotypes[0][j] = oldpop[which].gene_value(j);
    if(STRUCTURE == DIPLOID)
      phenotypes[1][j] = oldpop[which].gene_value(j,1);
    if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
      if(SHADES == SHADES_2) i = i + (bits_per_gene * 2);
      else i = i + (bits_per_gene * 3);
    }
    else i += bits_per_gene;
  }

  int loops;
  if(STRUCTURE == HAPLOID) loops = 1;
  else loops = 2;
  bit *ptr1;
  /*---------------------------------------------*/
  /* Print the string. if shades use the ABC char*/
  /* acters to represent the bits. 1st bit is    */
  /* the magnitude.                              */              
  /*---------------------------------------------*/
  for(int count=0; count < loops; count++) {  
    ptr1 = oldpop[which].returncopy(count);
    if(count == 1) fprintf(fp,"\n     ");
    int k =0;
    int lchrom = oldpop[which].str_len();
    for (int num=0; num < lchrom; num++){  

      if(breaks[k] != num) {
        if((SHADES == SHADES_2)||(SHADES == SHADES_3)){
	  switch(*ptr1) {
	    case F  : fprintf(fp,"A"); break;
            case T  : fprintf(fp,"B"); break;
            case S  : fprintf(fp,"C"); break;
            default : fprintf(fp,"?"); break;
	  }
	}
        else {
	  switch(*ptr1) {
	    case F  : fprintf(fp,"0"); break;
            case T  : fprintf(fp,"1"); break;
            default : fprintf(fp,"?"); break;
	  }
	}
      }
      else {
        /*---------------------------------------------*/
        /* print out hte magnitude of the parameter.   */
        /*---------------------------------------------*/
        if(k!=0) fprintf(fp," ");
        if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
	  switch(*ptr1) {
	    case F  : fprintf(fp,"A"); break;
            case T  : fprintf(fp,"B"); break;
            case S  : fprintf(fp,"C"); break;
            default : fprintf(fp,"?"); break;
	  }
	}
        else {
          if(SIGN == T) {
            switch(*ptr1) {
              case F  : fprintf(fp,"-"); break;
              case T  : fprintf(fp,"+"); break;
              default : fprintf(fp,"?"); break;
	    }
	  }
	  else fprintf(fp,"+");
	}
	k++;
	if(k >= gene_count) k = 0;
      }
      ptr1++;
    }
    /*---------------------------------------------*/
    /* Print out the fitness, scaled fitness and   */
    /* the allele values (gene values).            */
    /*---------------------------------------------*/
    if(count == 0) {    
      fprintf(fp," | %+8f ",oldpop[which].fitnesslevel(F));  
      if(SCALED)   fprintf(fp," (%+6f) ",oldpop[which].fitnesslevel(SCALED));
      fprintf(fp, "| ");
    }
    else  fprintf(fp," |                        | ");    
    for(int l=0; l<gene_count; l++) 
      fprintf(fp,"(%f,)",phenotypes[count][l]);
  }
  delete[] breaks;
  delete[] phenotypes[0];
  delete[] phenotypes[1]; 
  ptr1 = NULL; 

  /*---------------------------------------------*/
  /* If shades methodology used, print out the   */
  /* new genotype derived.                       */
  /*---------------------------------------------*/
  // printf("\n about to print derived shades genotype");
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {

    fprintf(fp,"\n      ");
    if(SHADES == SHADES_3) fprintf(fp," ");
    int *breaks1 = new int[gene_count];
    int i1,j1; 
    i1 = 0;

    for(j1 = 0; j1 < gene_count; j1++){
      breaks1[j1] = i1;
      i1 = i1 + bits_per_gene;
    }

    bit *ptr2 = oldpop[which].return_shades_genotype();
    int k1 = 0;
    for (int num1=0; num1 < bits_per_gene*gene_count; num1++){
      if(breaks1[k1] != num1) {
	if(SHADES == SHADES_3) fprintf(fp," ");
	switch(*ptr2) {
          case F  : fprintf(fp,"0"); break;
          case T  : fprintf(fp,"1"); break;
          default : fprintf(fp,"?"); break;
	}
      }
      else {
        if(k1 != 0) {
          if(SHADES == SHADES_3) fprintf(fp,"  ");
	  if(SHADES == SHADES_2) fprintf(fp," ");
	}
        if(SIGN == T) {
          switch(*ptr2) {
	    case F  : fprintf(fp,"-"); break;
            case T  : fprintf(fp,"+"); break;
            default : fprintf(fp,"?"); break;
	  }
	}
	else fprintf(fp,"+"); 
	k1++;
        if(k1 >= gene_count) k1 = 0;
      }
      fprintf(fp," ");
      ptr2++;
    }
    fprintf(fp,"|");
  }
  // printf("\n    leaving PRINTCHROMOSOMEFULL.");  
}
/*************************************************************************/
void BGE_population::printpop()
{
  /**************************************************************/
  /* Prints all chromosome strings of the population to         */
  /* a file "full_report.rpt                                    */
  /**************************************************************/

  // printf("\n entering print report");

  fprintf(fp,"\n\n         Chromosome String   |  Fitness");
  if(SCALED) fprintf(fp," (Scaled) ");
  fprintf(fp,"   |   Alleles");
  for (int count = 0;count < popsize;count++){
     fprintf(fp,"\n%d.  ",count+1);
     if (count < 9) fprintf(fp," ");
     printchromosomefull(count);   
   }

  // printf("\n leaving print report");
}
/*************************************************************************/
void BGE_population::print_fullreport_original()
{
  /**************************************************************/
  /* Issue a population statistical report to file              */
  /* "full_report.rpt" if set in file "defines.h".              */
  /**************************************************************/

  fprintf(fp,"\n\n\n     ******************************************");
  fprintf(fp,"\n               <<< POPULATION REPORT >>>");
  fprintf(fp,"\n     ******************************************");
  fprintf(fp,"\n\n           G E N E R A T I O N   N O .  ");
  fprintf(fp,"%d",gen); 
  printpop(); 

  fprintf(fp,"\n\n 1. Best Individual            --->> %d",max_individual+1); 
  fprintf(fp,"\n 2. Population maximum fitness --->> %+6f (%+4f)",o_max,max);
  fprintf(fp,"\n 3. Worst Individual           --->> %d",min_individual+1); 
  fprintf(fp,"\n 4. Population minimum fitness --->> %+6f (%+4f)",o_min,min);
  fprintf(fp,"\n 5. Population average fitness --->> %+6f (%+4f) ",o_avg,avg);
  fprintf(fp,"\n 6. Population sum of fitness  --->> %+8f",o_sumfitness);
  fprintf(fp,"\n 7. Number of crossovers       --->> %d",ncross);
  fprintf(fp,"\n 8. Number of mutations (gen.) --->> %d",nmutation);
  fprintf(fp,"\n 9. Total no. of mutations     --->> %d",totalnmutations);
  if(STEADY_STATE) 
    fprintf(fp,"\n10. Generation Gap             --->> %1.4f",gen_gap);
  fprintf(fp,"\n\n\n    ********************************************\n") ; 
}

/*************************************************************************/

void BGE_population::print_fullreport()
{
  /**************************************************************/
  /* Issue a population statistical report to file              */
  /* "full_report_john.rpt" if set in file "defines.h".              */
  /**************************************************************/

  fprintf(fpj,"%d",gen); 
  fprintf(fpj," %+6f \n",o_max); 

}


/*************************************************************************/

void BGE_population::print_gnuplot()
{ 
  /**************************************************************/
  /* Issue a population statistical report to file "plot.dat"   */
  /* for use by GnuPlot if set in file "defines.h".             */
  /**************************************************************/

 int gene_count = oldpop[max_individual].gene_no();

  fprintf(fp1,"%d %+8f %+8f %+8f ", gen,o_max,o_min,o_avg);
  for(int count = 0; count < gene_count; count++) 
     fprintf(fp1," %+8f ",(double)(oldpop[max_individual].gene_value(count)));
  fprintf(fp1,"\n");
}

/*************************************************************************/
/*                   2.    S T A T I S T I C S                           */
/*************************************************************************/
void BGE_population::copy_vals()
{
  p_avg = o_avg; p_max = o_max; p_min = o_min; p_stdev = o_stdev;
}
/*************************************************************************/

void BGE_population::statistics(boolean mybool, int stats_switch)
{
  /**************************************************************/
  /* Statistical routines to calculate population average,      */
  /* maximum & minimum fitness & it also calculates sumfitness  */
  /* required for selection.  Three levels of statistics:       */
  /* - based on original (physical) fitness.                    */
  /* - based on preprocessed fitness.                           */
  /* - based on scaled fitness.                                 */
  /**************************************************************/

  // printf("\n entering STATISTICS.");

  int j =0;
  double fit;
  switch(stats_switch) {
    case ORIGINAL   : o_sumfitness = 0.0;
                      o_sumfitness = oldpop[j].fitnesslevel(mybool);
                      o_min = oldpop[j].fitnesslevel(mybool);
                      min_individual = j;
                      o_max = oldpop[j].fitnesslevel(mybool);
                      max_individual = j;
                      break;
    case PREPROCESS : p_sumfitness = 0.0;
                      p_sumfitness = oldpop[j].fitnesslevel(mybool);
                      p_min = oldpop[j].fitnesslevel(mybool);
                      p_max = oldpop[j].fitnesslevel(mybool);
                      break;
    case SCALE      : sumfitness = 0.0;
                      sumfitness = oldpop[j].fitnesslevel(mybool);
                      min = oldpop[j].fitnesslevel(mybool);
                      max = oldpop[j].fitnesslevel(mybool);
                      break;
  }
  for (j = 1; j < popsize; j++){
    fit = oldpop[j].fitnesslevel(mybool);
    switch(stats_switch) {
      case ORIGINAL   : o_sumfitness = o_sumfitness + fit;
                        if (fit > o_max) {
			  o_max = fit;
			  max_individual = j;
			}
                        if (fit < o_min) {
			  o_min = fit;
			  min_individual = j;
			}
                        break;
      case PREPROCESS : p_sumfitness = p_sumfitness + fit;
                        if (fit > p_max) p_max = fit;
                        if (fit < p_min) p_min = fit;   
                        break;
      case SCALE      : sumfitness = sumfitness + fit;
                        if (fit > max) max = fit;
                        if (fit < min) min = fit;  
                        break;
    }
  }

  switch(stats_switch) {
    case ORIGINAL   : o_avg = o_sumfitness / (double)(popsize); break;
    case PREPROCESS : p_avg = p_sumfitness / (double)(popsize); break;
    case SCALE      : avg = sumfitness / (double)(popsize);     break;
  }

  double variance = 0;
  if(stats_switch == ORIGINAL) {
    for(int z =0; z < popsize; z++) {
      variance += pow((o_avg - oldpop[z].fitnesslevel(mybool)),2); 
    }
  }
  if(stats_switch == PREPROCESS) {
    for(int z =0; z < popsize; z++) {
      variance += pow((p_avg - oldpop[z].fitnesslevel(mybool)),2); 
    }
  }
  if(stats_switch == SCALE) {
    for(int z =0; z < popsize; z++) {
      variance += pow((avg - oldpop[z].fitnesslevel(mybool)),2); 
    }
  }

  switch(stats_switch) {
    case ORIGINAL   : o_stdev = sqrt(variance); break;
    case PREPROCESS : p_stdev = sqrt(variance); break;
    case SCALE      : stdev   = sqrt(variance); break;
  }
  // printf("\n    leaving STATISTICS."); 
}
/*************************************************************************/
void BGE_population::normalise_data()
{
  /**************************************************************/
  /* Calculate statistics. Preprocess if min < 0, and then scale*/
  /* using linear ranking.                                      */
  /**************************************************************/
  // printf("\n ENTERING normalising data ");

  o_avg=0; o_min=0; o_max=0; o_stdev=0; o_sumfitness=0;
  p_avg=0; p_min=0; p_max=0; p_stdev=0; p_sumfitness=0;
  avg=0; min=0; max=0; stdev=0; sumfitness=0;

  statistics(F,ORIGINAL);
  if(population_convergence()) {
    if(prev_gen != gen) {
      error_msg(CONVERGENCE,gen);
      prev_gen = gen;
    }
    double mult;
    if(o_max < 0) mult = -1;
    else mult = 1;
    for(int k=0; k<popsize; k++) {
      double val = oldpop[k].fitnesslevel(F);
      double newval = val * mult;
      oldpop[k].set_scaled_fitness(newval);
    }
    avg = o_avg;
    max = o_max;
    min = o_min;
    stdev = o_stdev;
    sumfitness = o_sumfitness;
  }
  else {
    if(o_min < 0) {
      for(int i=0; i< popsize; i++) 
	oldpop[i].sigma_preprocess(o_avg,c_SIGMA,o_stdev);
      statistics(F,PREPROCESS);
    }
    else copy_vals();
    linear_scaling(p_avg,p_max,p_min,a,b);
    for(int i=0; i< popsize; i++) oldpop[i].scale_chromosome(a,b);
    statistics(T,SCALE);
  }
  if(avg==0) error_msg(AVG);
    
  
  // printf("\n LEAVING normalise data");
}
/*************************************************************************/
int BGE_population::population_convergence()
{
  return o_min == o_max;
}

/*************************************************************************/
/*       3.   C O N S T R U C T O R S   A N D   D E S T R U C T O R S    */
/*************************************************************************/

BGE_population::BGE_population()
{
  /**************************************************************/
  /* Constructor                                                */
  /**************************************************************/

  // printf("\n entering POP CONSTRUCTOR.");
  int lchrom;
  if(check_for_error_in_parameters()) error_msg(SHUT_DOWN);
  myrandomize(); 

  popsize = POPSIZE;
  if((POPSIZE % 2) != 0){
    error_msg(POP_SIZE);
    popsize += 1;
  }

  int s;
  if(ELITISM == ELITISM_ADD) {
   double d = ((double)(ELITE_QTY)) * ELITISM_ADD_MULTIPLE;
    s = popsize + (int)((double)(maxgen) * d);
  }
  else s = popsize;

  gen_gap   = 0;
  prev_gen  = -1;
  gen       = 0;

  if (LENGTH == FIXED) {
    if (SHADES == F)
      lchrom = NUM_GENES * bits_per_gene;
    else {
      if(SHADES == SHADES_2) lchrom = NUM_GENES * bits_per_gene *2;
      if(SHADES == SHADES_3) lchrom = NUM_GENES * bits_per_gene *3;
    }
  }
  else lchrom = 0;

  
  oldpop    = new BGE_individual[s];
  newpop    = new BGE_individual[s];

  for (int j = 0; j < popsize; j++){
    //printf("\n for individual %d  %d  %d  %d",j,j,j,j);
    oldpop[j].generatechromosome(lchrom);
    //oldpop[j].display_chromosome();
    oldpop[j].assignvalues(0,0,gen,j+1);
    //oldpop[j].display_chromosome(); 
  }

  if(full_report) fp = fopen("full_report.rpt","w");
  if(full_report_john) fpj = fopen("full_report_john.rpt","a");
  if(Mikes_Report) 
    {
      mikefp = fopen("Mike's_Report.rpt","w");
      mikefp2 = fopen("Genotype_Report.rpt","w");
    }
  if(gnuplot) fp1 = fopen("plot.dat","w");
  //print_titles(fp,lchrom);

  nmutation       = 0;
  totalnmutations = 0;
  ncross          = 0;

  normalise_data();

  // printf("\n    leaving pop CONSTRUCTOR.");
}
/*************************************************************************/
BGE_population::~BGE_population()
{
  /**************************************************************/
  /* Destructor                                                */
  /**************************************************************/

  //printf("\n entering BGE_pop DESTRUCTOR.\n");
  if(full_report) fclose(fp);
  if(full_report_john) fclose(fpj);
  if(Mikes_Report)
    {
      fclose(mikefp);
      fclose(mikefp2);
    }
  if(gnuplot) fclose(fp1);
  delete[] oldpop;
  delete[] newpop;
  //printf("\n    leaving DESTRUCTOR.\n");
}
/*************************************************************************/
/*                 4.   O T H E R   F U N C T I O N S                    */
/*************************************************************************/
double BGE_population::bestIndividual()
{
 return o_max;
}
/*************************************************************************/
double BGE_population::worstIndividual()
{
 return o_min;
}
/*************************************************************************/
double BGE_population::avgIndividual()
{
 return o_avg;
}
/*************************************************************************/
void BGE_population::report()
 {
  if(full_report_john) print_fullreport();
  if(gnuplot) print_gnuplot();
 }
/*************************************************************************/
void BGE_population::resetGEreport()
{
  for(int i=0;i<popsize;i++){
    oldpop[i].setGE_Report_flag(0);
    newpop[i].setGE_Report_flag(0);
  }  
}
/*************************************************************************/
void BGE_population::theMikeReport()
 //Michael's problem dependent report!
{
  if(Mikes_Report){
    //    print_fullMikeReport();
    print_ActualGenotype();
    //generate mapping information for each individual in the population
    /*for(int i=0;i<popsize;i++){
      oldpop[i].setGE_Report_flag(1);
      oldpop[i].assignvalues(oldpop[i].getparent1(),oldpop[i].getparent2(),gen,i+1);
    }*/
  }
}
/*************************************************************************/
void BGE_population::print_fullMikeReport()
{
  /**************************************************************/
  /* Issue a population statistical report to file              */
  /* "Mike's_Report.rpt" if set in file "params.h".             */
  /**************************************************************/

  fprintf(mikefp,"\n\n\n     ******************************************");
  fprintf(mikefp,"\n               <<< POPULATION REPORT >>>");
  fprintf(mikefp,"\n     ******************************************");
  fprintf(mikefp,"\n\n           G E N E R A T I O N   N O .  ");
  fprintf(mikefp,"%d",gen); 
  fprintf(mikefp,"\n\n 1. Best Individual            --->> %d",max_individual+1); 
  fprintf(mikefp,"\n 2. Population maximum fitness --->> %+6f (%+4f)",o_max,max);
  fprintf(mikefp,"\n 3. Worst Individual           --->> %d",min_individual+1); 
  fprintf(mikefp,"\n 4. Population minimum fitness --->> %+6f (%+4f)",o_min,min);
  fprintf(mikefp,"\n 5. Population average fitness --->> %+6f (%+4f) ",o_avg,avg);
  fprintf(mikefp,"\n 6. Population sum of fitness  --->> %+8f",o_sumfitness);
  fprintf(mikefp,"\n 7. Number of crossovers       --->> %d",ncross);
  fprintf(mikefp,"\n 8. Number of mutations (gen.) --->> %d",nmutation);
  fprintf(mikefp,"\n 9. Total no. of mutations     --->> %d",totalnmutations);
  if(STEADY_STATE) 
    fprintf(mikefp,"\n10. Generation Gap             --->> %1.4f",gen_gap);
  fprintf(mikefp,"\n\n\n    ********************************************\n") ;
}
/*************************************************************************/
void BGE_population::print_ActualGenotype()
{
  /**************************************************************/
  /* Prints all chromosome strings of the population to         */
  /* a file "Mike's_Report.rpt                                    */
  /**************************************************************/

  //  fprintf(mikefp2,"\n\n(         Chromosome String   |  Fitness)");
  //  if(SCALED) fprintf(mikefp2," (Scaled) ");
  //  fprintf(mikefp2,"   |   Alleles");
  fprintf(mikefp2,"\n\n"); 
  fprintf(mikefp2,"\n\n\n     ******************************************");
  fprintf(mikefp2,"\n               <<< GENOTYPE REPORT >>>");
  fprintf(mikefp2,"\n     ******************************************");
  fprintf(mikefp2,"\n\n           G E N E R A T I O N   N O .  ");
  fprintf(mikefp2,"%d",gen); 
  for (int count = 0;count < popsize;count++){
     fprintf(mikefp2,"\n%d.  ",count+1);
     if (count < 9) fprintf(mikefp2," ");
     John_printchromosomefull(count); 
   }
  fprintf(mikefp2,"\n\n\n    ********************************************\n") ;
}
/*************************************************************************/
void BGE_population::Mike_printchromosomefull(int which)
{
  /**************************************************************/
  /* Prints the chromosome string from an individual in oldpop  */      
  /* specified by which with full details.                      */        
  /**************************************************************/

  if (which >= popsize) {
    error_msg(NO_STRING);
    error_msg(SHUT_DOWN);
  } 
  int gene_count = oldpop[which].gene_no();

  int *breaks = new int[gene_count];
  double *phenotypes[2];
  phenotypes[0] = new double[gene_count];
  phenotypes[1] = new double[gene_count];
 
  int i=0,j=0; 
  for(j = 0; j < gene_count; j++){
    breaks[j] = i;
    phenotypes[0][j] = oldpop[which].gene_value(j);
    if(STRUCTURE == DIPLOID)
      phenotypes[1][j] = oldpop[which].gene_value(j,1);
    if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
      if(SHADES == SHADES_2) i = i + (bits_per_gene * 2);
      else i = i + (bits_per_gene * 3);
    }
    else i += bits_per_gene;
  }

  int loops=0;
  if(STRUCTURE == HAPLOID) loops = 1;
  else loops = 2;
  bit *ptr1;
  /*---------------------------------------------*/
  /* Print the string. if shades use the ABC char*/
  /* acters to represent the bits. 1st bit is    */
  /* the magnitude.                              */              
  /*---------------------------------------------*/
  for(int count=0; count < loops; count++) {  
    ptr1 = oldpop[which].returncopy(count);
    if(count == 1) fprintf(mikefp2,"\n     ");
    int k =0;
    int lchrom = oldpop[which].str_len();
    for (int num=0; num < lchrom; num++){  

      if(breaks[k] != num) {
        if((SHADES == SHADES_2)||(SHADES == SHADES_3)){
	  switch(*ptr1) {
	    case F  : fprintf(mikefp2,"A"); break;
            case T  : fprintf(mikefp2,"B"); break;
            case S  : fprintf(mikefp2,"C"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
        else {
	  switch(*ptr1) {
	    case F  : fprintf(mikefp2,"0"); break;
            case T  : fprintf(mikefp2,"1"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
      }
      else {
        /*---------------------------------------------*/
        /* print out hte magnitude of the parameter.   */
        /*---------------------------------------------*/
	// if(k!=0) fprintf(mikefp2," "); //This line seperates genes withspace
        if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
	  switch(*ptr1) {
	    case F  : fprintf(mikefp2,"A"); break;
            case T  : fprintf(mikefp2,"B"); break;
            case S  : fprintf(mikefp2,"C"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
        /*else {
          if(SIGN == T) {
            switch(*ptr1) {
              case F  : fprintf(mikefp2,"-"); break;
              case T  : fprintf(mikefp2,"+"); break;
              default : fprintf(mikefp2,"?"); break;
	    }
	  }
	  else fprintf(mikefp2,"+");
	}*/
	k++;
	if(k >= gene_count) k = 0;
      }
      ptr1++;
    }
    /*---------------------------------------------*/
    /* Print out the fitness, scaled fitness and   */
    /* the allele values (gene values).            */
    /*---------------------------------------------*/
    if(count == 0) {    
      fprintf(mikefp2," | %+8f ",oldpop[which].fitnesslevel(F));  
      //if(SCALED)   fprintf(mikefp2," (%+6f) ",oldpop[which].fitnesslevel(SCALED));
      fprintf(mikefp2, "| ");
    }
    else  fprintf(mikefp2," |                        | ");    
    //for(int l=0; l<gene_count; l++) 
    //fprintf(mikefp2,"(%+5f)",phenotypes[count][l]);
  }
  delete[] breaks;
  delete[] phenotypes[0];
  delete[] phenotypes[1]; 
  ptr1 = NULL; 

  /*---------------------------------------------*/
  /* If shades methodology used, print out the   */
  /* new genotype derived.                       */
  /*---------------------------------------------*/
  // printf("\n about to print derived shades genotype");
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {

    fprintf(mikefp2,"\n      ");
    if(SHADES == SHADES_3) fprintf(mikefp2," ");
    int *breaks1 = new int[gene_count];
    int i1,j1; 
    i1 = 0;

    for(j1 = 0; j1 < gene_count; j1++){
      breaks1[j1] = i1;
      i1 = i1 + bits_per_gene;
    }

    bit *ptr2 = oldpop[which].return_shades_genotype();
    int k1 = 0;
    for (int num1=0; num1 < bits_per_gene*gene_count; num1++){
      if(breaks1[k1] != num1) {
	if(SHADES == SHADES_3) fprintf(mikefp2," ");
	switch(*ptr2) {
          case F  : fprintf(mikefp2,"0"); break;
          case T  : fprintf(mikefp2,"1"); break;
          default : fprintf(mikefp2,"?"); break;
	}
      }
      else {
        if(k1 != 0) {
          if(SHADES == SHADES_3) fprintf(mikefp2,"  ");
	  if(SHADES == SHADES_2) fprintf(mikefp2," ");
	}
        if(SIGN == T) {
          switch(*ptr2) {
	    case F  : fprintf(mikefp2,"-"); break;
            case T  : fprintf(mikefp2,"+"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
	else fprintf(mikefp2,"+"); 
	k1++;
        if(k1 >= gene_count) k1 = 0;
      }
      fprintf(mikefp2," ");
      ptr2++;
    }
    fprintf(mikefp2,"|");
  }
  // printf("\n    leaving PRINTCHROMOSOMEFULL.");  
}
/*************************************************************************/
/*************************************************************************/


void BGE_population::John_printchromosomefull(int which)
{
  /**************************************************************/
  /* Prints the chromosome string from an individual in oldpop  */      
  /* specified by which with full details.                      */        
  /**************************************************************/

  if (which >= popsize) {
    error_msg(NO_STRING);
    error_msg(SHUT_DOWN);
  } 
  int gene_count = oldpop[which].gene_no();

  int *breaks = new int[gene_count];
  double *phenotypes[2];
  phenotypes[0] = new double[gene_count];
  phenotypes[1] = new double[gene_count];
 
  int i=0,j=0; 
  for(j = 0; j < gene_count; j++){
    breaks[j] = i;
    phenotypes[0][j] = oldpop[which].gene_value(j);
    if(STRUCTURE == DIPLOID)
      phenotypes[1][j] = oldpop[which].gene_value(j,1);
    if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
      if(SHADES == SHADES_2) i = i + (bits_per_gene * 2);
      else i = i + (bits_per_gene * 3);
    }
    else i += bits_per_gene;
  }

  int loops=0;
  if(STRUCTURE == HAPLOID) loops = 1;
  else loops = 2;
  bit *ptr1;
  /*---------------------------------------------*/
  /* Print the string. if shades use the ABC char*/
  /* acters to represent the bits. 1st bit is    */
  /* the magnitude.                              */              
  /*---------------------------------------------*/
  for(int count=0; count < loops; count++) {  
    ptr1 = oldpop[which].returncopy(count);
    if(count == 1) fprintf(mikefp2,"\n     ");
    int k =0;
    int lchrom = oldpop[which].str_len();
    for (int num=0; num < lchrom; num++){  

      if(breaks[k] != num) {
        if((SHADES == SHADES_2)||(SHADES == SHADES_3)){
	  switch(*ptr1) {
	    case F  : fprintf(mikefp2,"A"); break;
            case T  : fprintf(mikefp2,"B"); break;
            case S  : fprintf(mikefp2,"C"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
	/*
        else {
	  	  switch(*ptr1) {
	  case F  : fprintf(mikefp2,"0"); break;
	  case T  : fprintf(mikefp2,"1"); break;
	  default : fprintf(mikefp2,"?"); break;
	  }
	}
	*/
      }
      else {
        /*---------------------------------------------*/
        /* print out hte magnitude of the parameter.   */
        /*---------------------------------------------*/
	// if(k!=0) fprintf(mikefp2," "); //This line seperates genes withspace
        if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
	  switch(*ptr1) {
	    case F  : fprintf(mikefp2,"A"); break;
            case T  : fprintf(mikefp2,"B"); break;
            case S  : fprintf(mikefp2,"C"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
        /*else {
          if(SIGN == T) {
            switch(*ptr1) {
              case F  : fprintf(mikefp2,"-"); break;
              case T  : fprintf(mikefp2,"+"); break;
              default : fprintf(mikefp2,"?"); break;
	    }
	  }
	  else fprintf(mikefp2,"+");
	}*/
	k++;
	if(k >= gene_count) k = 0;
      }
      ptr1++;
    }
    /*---------------------------------------------*/
    /* Print out the fitness, scaled fitness and   */
    /* the allele values (gene values).            */
    /*---------------------------------------------*/
    if(count == 0) {    
      fprintf(mikefp2," | %+8f ",oldpop[which].fitnesslevel(F));  
      //if(SCALED)   fprintf(mikefp2," (%+6f) ",oldpop[which].fitnesslevel(SCALED));
      fprintf(mikefp2, "| ");
    }
    else  fprintf(mikefp2," |                        | ");    
    for(int l=0; l<gene_count; l++) 
    fprintf(mikefp2,"%.0f,",phenotypes[count][l]);
  }
  delete[] breaks;
  delete[] phenotypes[0];
  delete[] phenotypes[1]; 
  ptr1 = NULL; 

  /*---------------------------------------------*/
  /* If shades methodology used, print out the   */
  /* new genotype derived.                       */
  /*---------------------------------------------*/
  // printf("\n about to print derived shades genotype");
  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {

    fprintf(mikefp2,"\n      ");
    if(SHADES == SHADES_3) fprintf(mikefp2," ");
    int *breaks1 = new int[gene_count];
    int i1,j1; 
    i1 = 0;

    for(j1 = 0; j1 < gene_count; j1++){
      breaks1[j1] = i1;
      i1 = i1 + bits_per_gene;
    }

    bit *ptr2 = oldpop[which].return_shades_genotype();
    int k1 = 0;
    for (int num1=0; num1 < bits_per_gene*gene_count; num1++){
      if(breaks1[k1] != num1) {
	if(SHADES == SHADES_3) fprintf(mikefp2," ");
	//switch(*ptr2) {
          //case F  : fprintf(mikefp2,"0"); break;
          //case T  : fprintf(mikefp2,"1"); break;
          //default : fprintf(mikefp2,"?"); break;
	//}
      }
      else {
        if(k1 != 0) {
          if(SHADES == SHADES_3) fprintf(mikefp2,"  ");
	  if(SHADES == SHADES_2) fprintf(mikefp2," ");
	}
        if(SIGN == T) {
          switch(*ptr2) {
	    case F  : fprintf(mikefp2,"-"); break;
            case T  : fprintf(mikefp2,"+"); break;
            default : fprintf(mikefp2,"?"); break;
	  }
	}
	else fprintf(mikefp2,"+"); 
	k1++;
        if(k1 >= gene_count) k1 = 0;
      }
      fprintf(mikefp2," ");
      ptr2++;
    }
    fprintf(mikefp2,"|");
  }
  // printf("\n    leaving PRINTCHROMOSOMEFULL.");  
}
/*************************************************************************/
/*************************************************************************/








