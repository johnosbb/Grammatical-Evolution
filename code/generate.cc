/********************************************************************/
/*                                                                  */
/*          FILE   :  GENERATE.CC                                   */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  AUG. 1996/1997                                */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/*  Implements object declared in header file "generate.cc".        */
/*  --------------------------------------------------------------- */
/*     BUGS :   diploidy not implemented for STEADY_STATE           */
/*                                                                  */
/********************************************************************/

#include <math.h>
#include <stdlib.h>
#include "generate.hpp"
#include "myrandom.h"
#include "../defines.h"
#include "string.h"
#include "stdio.h"
#include "../Random.hpp"
#include <iostream.h>
#include <fstream.h>

/*************************************************************************/
/*                      1.  S E L E C T I O N                            */
/*************************************************************************/
void generate::TSR_preselection()
{
  /**************************************************************/
  /* Preprocessing required for Target Sampling Rate selection  */
  /**************************************************************/
  // printf("\n entering TSR preselect()");
  double my_max = max;
  double my_min = min;
  double *fraction = new double[popsize];
  double norm = 2/(my_max + my_min);
  my_min *= norm;
  my_max *= norm;

  int j=0;
  int k=0;
  double expected;
  int jassign;
  while(j < popsize) {
    expected = my_min + (my_max - my_min)*(j+1)/(popsize-1);
    jassign = (int)(floor(expected));
    fraction[j] = expected - jassign;
    // printf("\n expected = %+5f, jassign = %+d, fraction[%d] = %+5f",
    //       expected,jassign,j,fraction[j]);
    while(jassign > 0) {
      if(k >= popsize) { printf("\n 1. table full"); return; }
      // printf("\n -->> table[%d] = %d",k,j);
      table[k++] = j;
      if(k >= popsize) return;
      jassign--;
    }
    j++;
  }
  j=0;
  while(k < popsize) { 
    if(j == popsize) j=0;
    // printf("\n  <<< fraction[%d] = %+5f",j,fraction[j]);
    if(fraction[j] > 0) {
      if(probably(fraction[j])) {
	if(k >= popsize) { printf("\n 2. table full"); return; }
	// printf("\n ------- >>>>>  table[%d] = %d",k,j);        
	table[k++] = j;
	fraction[j] -= 1;
      }
    }
    j++;
  }
  for(int c1=0; c1 < popsize; c1++) selector[table[c1]] += 1;
  delete[] fraction;
  // printf("\n leaving TSR preselect()");
}
/*************************************************************************/
int generate::target_sampling_rate(int nremain)
{
  /**************************************************************/
  /* Target Sampling Rate selection                             */
  /**************************************************************/
  
  // printf("\n entering target sampling rate");
  int jpick,select;

  if(nremain >= 1) {
    if(nremain == 1) jpick = 0;
    else jpick = randomint(nremain);
    select = table[jpick];
    table[jpick] = table[nremain -1];
    nremain -= 1;
    selected[select]++;
    if(full_report) fprintf(fp,"%3d   ",select+1);
  }
  else {
    select =  select_roulette();
    if(full_report) fprintf(fp," (r) ");
  }

  // printf("\n Leaving target sampling rate");
  return select;
}
/*************************************************************************/
void generate::RSSwoR_preselect()
{
  /**************************************************************/
  /* Preprocessing required for Remainder Stochastic Sampling   */
  /* Without Replacement selection                              */
  /**************************************************************/

  // printf("\n Entering RSSwoR preselect()");

  if(avg > 0) {
    int    j=0,k=0,jassign=0;
    double expected=0,*fraction;
    fraction = new double[popsize];
    while(j < popsize) {
      expected = oldpop[j].fitnesslevel(SCALED)/avg;
      jassign = (int)(floor(expected));
      fraction[j] = expected - jassign;
      while(jassign > 0) {
        table[k++] = j;
        jassign--;
      }
      j++;
    }
    j=0;
    while(k < popsize) { 
      if(j == popsize) j=0;
      if(fraction[j] > 0) {
        if(probably(fraction[j])) {
	  table[k++] = j;
	  fraction[j] -= 1;
	}
      }
      j++;
    }
   
    for(int c1=0; c1 < popsize; c1++) selector[table[c1]] += 1;
    delete[] fraction;
  }
  else {
    // printf("\n entering else option");
    for(int c2=0; c2 < popsize; c2++) {
      table[c2] = 1;
      selector[c2] = 1;    
    }
  }

  // printf("\n Leaving RSSwoR preselect()");
}
/*************************************************************************/
int generate::RSSwithoutR(int nremain)
{
  /**************************************************************/
  /* Remainder Stochastic Sampling Without replacement selection*/
  /**************************************************************/

  // printf("\n entering RSSwithoutR(...)");
  int jpick,select;

  if(nremain >= 1) {
    if(nremain == 1) jpick = 0;
    else jpick = randomint(nremain);
    select = table[jpick];
    table[jpick] = table[nremain -1];
    nremain -= 1;
    selected[select]++;
    if(full_report) fprintf(fp,"%3d   ",select+1);
  }
  else {
    select =  select_roulette();
    if(full_report) fprintf(fp," (r) ");
  }

  // printf("\n Leaving RSSwithoutR(...)");  
  return select;
}
/*************************************************************************/

int generate::select_roulette(int prev)
{
  /**************************************************************/
  /* Roulette wheel selection (also known as Stochastic Sampling*/
  /*  with replacement).                                        */
  /**************************************************************/

  // printf("\n entering SELECT_ROULETTE.");

  double partsum = 0.00e-99;
  double rand =  (randomint(popsize)+1) * avg;
  int count= 0,temp;
  while ((partsum < rand)&&(count < popsize)) {  
    double d = oldpop[roulette].fitnesslevel(SCALED); 
    partsum = partsum + d;
    count++;
    roulette++;
    if(roulette == popsize) roulette = 0;
  }

  if(roulette == 0) temp = popsize -1;
  else temp = roulette-1;
  if(temp == prev) temp = randomint(popsize); 

  selected[temp]++;
  if(full_report) fprintf(fp,"%3d   ",temp+1);
  // printf("\n    leaving SELECT_ROULETTE.");
  return temp;
}
/*************************************************************************/
/*      2.   C O N S T R U C T O R S   A N D   D E S T R U C T O R S     */
/*************************************************************************/
generate::generate()
{
  /**************************************************************/
  /* Constructor. Some of the selection mechanisms require      */
  /* the use of global statistics and tables - computed for     */
  /* generation 1 here.                                         */
  /**************************************************************/

  // printf("\n entering generate CONSTRUCTOR");

  int s;
  if(ELITISM == ELITISM_ADD) {
    double d = ((double)(ELITE_QTY)) * ELITISM_ADD_MULTIPLE;
    s = popsize + (int)((double)(maxgen) * d);
  }
  else s = popsize;
  
  maxpop_size = s;

  selected  = new int[s];
  selector  = new int[s];
  table     = new int[s];
  roulette  = 0;
  for(int j=0; j<popsize; j++) {
    table[j]=0;
    selected[j]=0;
    selector[j]=0;
  }
  switch(SELECTION) {
    case TSR                            : selection_sort(oldpop,popsize);
                                          TSR_preselection();
                                          break;
    case RANK                           : break;
    case REMAIND_STOCH_SAMPL_wo_REPLACE : RSSwoR_preselect();
                                          break;
    case STOCH_SAMPL_wo_REPLACE         : break;
    case REMAIND_STOCH_SAMPL_w_REPLACE  : break;
    case STOCH_SAMPL_w_REPLACE          : break;
  }
  // printf("\n Leaving generate constructor");
}
/*************************************************************************/
generate::~generate()
{
  /**************************************************************/
  /* Destructor.                                                */
  /**************************************************************/
  delete [] selected;
  delete [] table;
}

/*************************************************************************/
/*     3.   G E N E R A T E   P O P U L A T I O N S   F U N C T I O N    */
/*************************************************************************/

int generate::search(int n)
{
  /**************************************************************/
  /* Search the newpopulation for a copy of individual n from   */
  /* the old population.                                        */
  /**************************************************************/
  int m1 = oldpop[n].str_len();
  int lchrom = bits_per_gene;
  double d = oldpop[n].fitnesslevel(F);
  bit *ptr1 = oldpop[n].returncopy();
  for(int i=0; i< popsize; i++) {
    int m2 = oldpop[i].str_len();
    if(m1==m2){
      lchrom = m1;
      double d1 = newpop[i].fitnesslevel(F);
      if(d ==  d1) {
	bit *ptr2 = newpop[i].returncopy();
	int j=0;
	while((j<lchrom)&&(*ptr1++ == *ptr2++)) j++;
	if(j == lchrom) return 1;
      }
    }
  }
  return 0;
}
/*************************************************************************/
void generate::print_selection_stats()
{
  /**************************************************************/
  /* If FULL_REPORT print out sampling statistics.              */
  /**************************************************************/
  // printf("\n  ...........print_selection_stats  popsize = %d",popsize);
  if(((SELECTION == TSR)||(SELECTION == REMAIND_STOCH_SAMPL_wo_REPLACE)) 
    && (full_report)) {
    int t1=0; int t2=0;
    for (int num1 = 0 ; num1 < popsize; num1++){   
      fprintf(fp,"\n%d ",num1+1);
      fprintf(fp," selector[] = %d ",selector[num1]);
      t1 += selector[num1];
      fprintf(fp," selected[] = %d",selected[num1]);
      t2 += selected[num1];
    }
    fprintf(fp,"\n total_1 = %d  ",t1);
    fprintf(fp,"total_2 = %d  ",t2);
  }
}
/*************************************************************************/
void generate::swap_old_pop_with_new(const int size)
{
  /**************************************************************/
  /* Swap the old and new populations. If an elitist strategy   */
  /* is to be used, add/replace the best no. of individuals from*/ 
  /* the old population (as specified by ELITE_QTY), to the     */
  /*  current population IF not allready present.               */
  /**************************************************************/

  //printf("\n ENTERING swap_old_pop_with_new()");

  BGE_individual *hold;
  int counter = 0;
  if((ELITISM == ELITISM_REPLACE)||(ELITISM == ELITISM_ADD)) {
    selection_sort(oldpop,popsize);
    hold = new BGE_individual[ELITE_QTY];
    for(int c2=0; c2 < ELITE_QTY; c2++) {
      if(!search(popsize-(c2+1))) {
	hold[counter++] = oldpop[popsize-(c2+1)];
	if(full_report) fprintf(fp,"\n ELITISM: duplicate found");
      }
    }
  }
  //printf("\n  1. swap_old_pop_with_new()");
  //printf("\n >>>>>>>>>>> PRINTING OLD POPULATION ");
  //for(int count = 0; count < popsize; count++) 
  //  oldpop[count].display_chromosome();
  //printf("\n >>>>>>>>>>> PRINTING NEW POPULATION ");
  //for(int count = 0; count < popsize; count++) 
  //  newpop[count].display_chromosome();

  BGE_individual *temp;  
  temp = oldpop;
  oldpop = newpop;
  newpop = temp;
  normalise_data();
  popsize = size;

  //printf("\n  2. swap_old_pop_with_new()");
  //printf("\n  2. swap_old_pop_with_new()");


  //printf("\n >>>>>>>>>>> PRINTING NEW POPULATION ");
  //for(int count = 0; count < popsize; count++) 
  //  oldpop[count].display_chromosome();
  //printf("\n >>>>>>>>>>> PRINTING OLD POPULATION ");
  // for(int count = 0; count < popsize; count++) 
  //  newpop[count].display_chromosome();


  for(int count = 0; count < popsize; count++) 
    newpop[count].del();

  //printf("\n  3. swap_old_pop_with_new()");
  //printf("\n  3. swap_old_pop_with_new()");

  if(((ELITISM==ELITISM_REPLACE)||(ELITISM==ELITISM_ADD))&&(counter>0)) {
    switch(ELITISM) {
      case ELITISM_REPLACE : selection_sort(oldpop,popsize);
                             for(int c3=0; c3 < counter; c3++)
                                oldpop[c3] = hold[c3];
                             break;
      case ELITISM_ADD     : int count = 0;
                             for(int c4=popsize; c4<popsize+counter; c4++)
                                oldpop[c4] = hold[count++];    
                             popsize += counter;
                             break;    
    }
    delete [] hold;
    normalise_data();
  }

  //printf("\n LEAVING swap_old_pop_with_new()");

}
/*************************************************************************/
void generate::select(int &mate1, int &mate2, const int j, const int pop)
{
  /**************************************************************/
  /* Select 2 parents from the population for crossover, based  */
  /* on their fitness.                                          */
  /**************************************************************/
  if(avg <= 0) {
    mate1 = randomint(pop);
    mate2 = randomint(pop);
    printf("\n WARNING : avg = %f, max = %f, min = %f",avg,max,min);
    printf("\n           selecting two random individuals.");
  } 
  else {
    switch(SELECTION) {
      case TSR                   : mate1 = target_sampling_rate(pop-j);
                                   mate2 = target_sampling_rate(pop-(j+1));
                                   break;
      case RANK                  : error_msg(IMPLEM);
                                   mate1 = j;
              	       		   mate2 = j+1;
	                           break;
      case REMAIND_STOCH_SAMPL_wo_REPLACE : mate1 = RSSwithoutR(pop-j);
                                   mate2 = RSSwithoutR(pop-(j+1));
	                           break;
      case STOCH_SAMPL_wo_REPLACE: error_msg(IMPLEM);
                                   mate1 = j;
		  	           mate2 = j+1;
	                           break;
      case REMAIND_STOCH_SAMPL_w_REPLACE : error_msg(IMPLEM); ;
                                   mate1 = j;
	        		   mate2 = j+1;
	                           break;
      case STOCH_SAMPL_w_REPLACE : mate1 = select_roulette();
                                   mate2 = select_roulette(mate1);
	                           break;
    }
  }
}
/*************************************************************************/
void generate::generate_steady_state(const double pmut)
{
  /**************************************************************/
  /* Selection and reproduction implemented using a steady state*/
  /* strategy. 2 parents selected using roulette wheel mechanism*/
  /* (for computational efficiency). Best of 2 children will    */
  /* replace an individual in the population, if child's fitness*/
  /* better than individual. Recalculate population statistics. */
  /* If x individuals in population, repeat this x times.       */  
  /**************************************************************/ 
  ncross = 0;
  nmutation = 0;
  int mate1,mate2;
  int k=0,j=0, arr =0;
  int prev_arr = 0;
  while(j < popsize) {
    k = j;
    if(k == popsize-1) k--;
    if(full_report) fprintf(fp,"\n________________Chromosomes selected are : ");
    mate1 = select_roulette();
    mate2 = select_roulette(mate1);
    oldpop[mate1].reset();
    oldpop[mate2].reset();
    newpop[k].del();
    newpop[k+1].del();
    //newpop[k].reset();
    //newpop[k+1].reset();

    // clone(k, mate1);
    // clone(k+1, mate2);
    // OR 
    // copy_with_mutation(k,mate1,pmut);
    // copy_with_mutation(k+1,mate2,pmut);
    // OR
    crossover_parents(mate1,mate2,k,pmut);

    if(LENGTH == VARIABLE) {
      prune(k);
      prune(k+1);
      delete_gene(k);
      delete_gene(k+1);
      insert_gene(k);
      insert_gene(k+1);
      duplicate_genes(k);
      duplicate_genes(k+1);
    }
    swap_genes(k);
    swap_genes(k+1);

    newpop[k].assignvalues(mate1,mate2,gen+1,k+1);
    newpop[k+1].assignvalues(mate1,mate2,gen+1,k+2);

    double f1 = newpop[k].fitnesslevel(F);
    double f2 = newpop[k+1].fitnesslevel(F);
    if (f1 == TARGET_SCORE || f2 == TARGET_SCORE)
      {
	FILE *pc_fileptr;
        char pc_filename[20];
        int n = randomint(10000);
 	sprintf(pc_filename,"%d",n);
	strcat(pc_filename,"_pc.txt");
	if( (pc_fileptr = fopen(pc_filename,"w")) == NULL)
	  {
	    cout << "Error opening parent_child file " << pc_filename << endl;
	    
	  }
	else	
	  {
	    int n2;
	    
	    fprintf(pc_fileptr,"\nChild 1 is ");
	    newpop[k].show(pc_fileptr);
	    fprintf(pc_fileptr,"\nChild 2 is ");
	    newpop[k+1].show(pc_fileptr);

	    n2 = newpop[k].getparent1();
	    fprintf(pc_fileptr,"\nParent1 of Child 1 is ");
	    oldpop[n2].show(pc_fileptr);

	    n2 = newpop[k].getparent2();
	    fprintf(pc_fileptr,"\nParent2 of Child 1 is ");
	    oldpop[n2].show(pc_fileptr);


	    n2 = newpop[k+1].getparent1();
	    fprintf(pc_fileptr,"\nParent1 of Child 2 is ");
	    oldpop[n2].show(pc_fileptr);

	    n2 = newpop[k+1].getparent2();
	    fprintf(pc_fileptr,"\nParent2 of Child 2 is ");
	    oldpop[n2].show(pc_fileptr);	    
	  }
	fclose(pc_fileptr);
	save_results_data("testfile");
	
	
     }
    




    if(full_report) {
      fprintf(fp,"\nChild 1 is ");
      newpop[k].show(fp);
      fprintf(fp,"\nChild 2 is "); 
     newpop[k+1].show(fp);
      fprintf(fp,"\n The worst individual in the oldpop is: %d",min_individual+1);
    }
    if((f1 > o_min)||(f2 > o_min)) {
      arr += 1;
      if(f1 > f2) {
	oldpop[min_individual] = newpop[k];
	if(full_report) fprintf(fp,"\n Replacing the worst.");
      }
      else {
	if(f2 > f1) {
	  oldpop[min_individual] = newpop[k+1];
	  if(full_report) fprintf(fp,"\n Replacing the worst.");
	}
	else {
          if(randomint(2)) oldpop[min_individual] = newpop[k];
          else oldpop[min_individual] = newpop[k+1];
          if(full_report) fprintf(fp,"\n Replacing the worst.");
        }
      }
    }  
   
    // oldpop[min_individual].assignvalues(mate1,mate2,gen+1,min_individual+1);
    if(full_report) fprintf(fp,"\n---------------------------------------");
    if(prev_arr != arr) {
      normalise_data(); 
      prev_arr = arr;
    }
    if(full_report) fprintf(fp,"\n");    
    j++;
  }
  // gen++;
  prev_gen = gen -1;
  gen_gap = (double)(arr)/(double)(popsize);
  if(gen_gap == 0) error_msg(GAP,gen);
}     
/*************************************************************************/
void generate::re_evaluate_fitness(const int pop)
{
  /**************************************************************/   
  /* If problem environment is dynamic, must re-evaluate pop.   */
  /* at environment change time, prior to selecting ...... and  */
  /* generating new population.                                 */
  /**************************************************************/   
  for(int count = 0; count < pop; count++)
    oldpop[count].redo_fitness(gen+1,count+1);
  normalise_data();
  
  if(avg > 0) {
    switch(SELECTION) {
      case TSR                            : selection_sort(oldpop,pop);
                                            TSR_preselection();
                                            break;
      case RANK                           : break;
      case REMAIND_STOCH_SAMPL_wo_REPLACE : RSSwoR_preselect();
                                            break;
      case STOCH_SAMPL_wo_REPLACE         : break;
      case REMAIND_STOCH_SAMPL_w_REPLACE  : break;
      case STOCH_SAMPL_w_REPLACE          : break;
    }
  }
}
/*************************************************************************/
void generate::generate_pop()
{
  /**************************************************************/
  /* Creates a new generation through selection,crossover and   */
  /* mutation. Starting at an individual at index j = 0 and     */
  /* continuing until the population size, popsize, has been    */
  /* exceeded, two mates are picked using successive calls to   */
  /* a user specified selection mechanism. The chromosomes are  */
  /* crossed and mutated using a user specified #defines (in    */
  /* file "defines.h"). Finally the chromosomes of the new      */
  /* population are scaled decoded and the population statistics*/
  /* derived.                                                   */
  /**************************************************************/
  //printf("\n F O R   G E N E R A T I O N   N O . %d",gen+1);

  gen++;
  double pmut;
  if(ADAPTIVE_MUTATION) {
   if(population_convergence()) {
     pmut = pmutation * ADAPTATION_RATE;
   }
   else pmut = pmutation;
  }
  else pmut = pmutation;

  ncross = 0;
  nmutation = 0;
  int mate1,mate2;
  int j=0;
  
  if((PROBLEM_TYPE == DYNAM) && (((gen+1) % TIME_STEP) ==0)) 
    re_evaluate_fitness(popsize);
  if(STEADY_STATE) generate_steady_state(pmut);
  else {
    // printf("\n entering else ");
    /*------------------------------------------------------------*/
    /*  Selection and crossover implemented using a generation    */
    /*  gap of 1. Option of including an elitist strategy, either */
    /*  replacement or additive with a user specified quantity.   */
    /*------------------------------------------------------------*/ 
    if(full_report) fprintf(fp,"\n-----Chromosomes selected are : \n");
    while(j < popsize) {
      newpop[j].reset();
      newpop[j+1].reset();
      /*-----------------------------------------------------*/
      /* Selection and crossover. Selection and reproduction */
      /* are CONSERVATIVE. If the population size is an odd  */
      /* number an extra individual is generated, as opposed */
      /* to one less.                                        */
      /*-----------------------------------------------------*/
      select(mate1,mate2,j,popsize);
      oldpop[mate1].reset();
      oldpop[mate2].reset();

      // clone(j, mate1);
      // clone(j+1, mate2);
      // OR 
      // copy_with_mutation(j,mate1,pmut);
      // copy_with_mutation(j+1,mate2,pmut);
      // OR
      crossover_parents(mate1,mate2,j,pmut);

      if(LENGTH == VARIABLE) {
	prune(j);
	prune(j+1);
	delete_gene(j);
	delete_gene(j+1);
	insert_gene(j);
	insert_gene(j+1);
	duplicate_genes(j);
	duplicate_genes(j+1);
      }
      swap_genes(j);
      swap_genes(j+1);

      
      //printf("\n finished crossover \n");
      //printf("\n\n ........... PARENT1 (%d) = ",mate1);
      //oldpop[mate1].display_chromosome();
      //printf("\n ........... PARENT2 (%d) = ",mate2);   
      //oldpop[mate2].display_chromosome();
      //printf("\n ................ CHILD1 (%d) = ",j);
      //newpop[j].display_chromosome();
      //printf("\n ................ CHILD2 (%d) = ",j+1);    
      //newpop[j+1].display_chromosome();

      newpop[j].assignvalues(mate1,mate2,gen+1,j+1);
      newpop[j+1].assignvalues(mate1,mate2,gen+1,j+2);
      oldpop[mate1].reset();
      oldpop[mate2].reset();
      j =j+2;        
    }
    /*---------------------------------------------------*/
    /* If size of parent population is an odd number,    */
    /* because of conservative selection, size of new pop*/
    /* must be adjusted. Also, if elitist model used, may*/
    /* have same problem of adjusting pop size. Require  */
    /* following variables to update and handle this.    */
    /*---------------------------------------------------*/
    int new_popsize;
    if(j > popsize) new_popsize = j;
    else new_popsize = popsize;
    if(j > maxpop_size) {
      error_msg(MAX_POP);
      error_msg(SHUT_DOWN);
    }
    /*---------------------------------------------------*/
    /* If FULL_REPORT print out sampling statistics.     */
    /*---------------------------------------------------*/
    print_selection_stats(); 
    /*---------------------------------------------------*/
    /* Swap old and new populations (change pointers)    */
    /*---------------------------------------------------*/ 
    swap_old_pop_with_new(new_popsize);
    /*---------------------------------------------------*/
    /* Recalculate table if necessary.                   */
    /*---------------------------------------------------*/
    //gen++;
    prev_gen = gen-1;
    for(int l=0; l<popsize; l++) {
      table[l]=0;
      selected[l]=0;
      selector[l] = 0;
    }
    if(avg > 0) {
      switch(SELECTION) {
        case TSR                            : selection_sort(oldpop,popsize);
                                              TSR_preselection();
                                              break;
        case RANK                           : break;
        case REMAIND_STOCH_SAMPL_wo_REPLACE : RSSwoR_preselect();
                                              break;
        case STOCH_SAMPL_wo_REPLACE         : break;
        case REMAIND_STOCH_SAMPL_w_REPLACE  : break;
        case STOCH_SAMPL_w_REPLACE          : break;
      }
    }
  }
  //printf("\n    leaving GENERATE.");   
}
/*************************************************************************/
/*                 4.   O T H E R   F U N C T I O N S                    */
/*************************************************************************/

int generate::generatefin()
{
  /**************************************************************/
  /* If number of generations less than user specified limit in */
  /* file "defines.h", generate a new population based on       */
  /* neo-Darwinian evolution.                                   */ 
  /**************************************************************/

  if (gen >= maxgen) return 1;
  else return 0;
}
/*************************************************************************/



void generate::save_results_data(char filename[])
{
  ofstream save_results_file;
  char results_filename[50];
  strcpy(results_filename,filename);
  strcat(results_filename,".results.txt");
  save_results_file.open(results_filename,ios::app);  
  if(!save_results_file.is_open())
    {
      cout << "Error opening file " << results_filename  << endl;
     }
  save_results_file << "1  " << "\n";
  save_results_file.close();
  exit(1);
  
} 
























