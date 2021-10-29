/********************************************************************/
/*                                                                  */
/*          FILE   :  TITLES.CC                                     */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  AUG. 1996/1997                                */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/*  Implements object declared in header file "titles.hpp".         */
/*  --------------------------------------------------------------- */
/*     BUGS : todate, none to report.                               */
/*                                                                  */
/********************************************************************/

#include <stdio.h>
#include "titles.hpp"

/********************************************************************/
void titles::print_titles(FILE *fp, int lchrom)
{
  int line = 1;
  printf("\n ********************************************************");
  printf("\n *                                                      *");
  printf("\n *         G E N E T I C   A L G O R I T H M            *");
  printf("\n *           --------------------------                 *");
  printf("\n *             copyright J.J. Collins                   *");
  printf("\n *           --------------------------                 *");
  printf("\n *                                                      *");
  printf("\n * compiled in C++ (GNU g++)  on SunOS & Linux platform *");
  printf("\n *                                                      *");
  printf("\n ********************************************************");
  printf("\n\n %d. Structure                        ----> ",line++);
  switch(STRUCTURE) {
    case HAPLOID  : printf("Haploid");  break;
    case DIPLOID  : printf("Diploid");  
                    printf("\n    Evaluation Method                ----> ");
                    switch(DIP_EVAL) {
		      case XOR     : printf("XOR");     break;
		      case RANDOM  : printf("RANDOM");  break;
		      case AVERAGE : printf("AVERAGE"); break;
		      default      : printf("Unknown"); break;
		    }
                    printf("\n    Diploid Crossover                ----> ");
                    switch(DIPLOID_CROSSOVER) {
		      case GOLDBERG : printf("Goldberg"); break;
		      case PAVEL    : printf("Pavel");    break;
		      case COLLINS  : printf("Collins");  break;
		      default       : printf("Unknown");  break;
		    }
		    break;
    default       : printf("unknown");  break;
  }

  printf("\n %d. Chromosome Length                ----> ",line++);
  if(LENGTH == FIXED) printf("%d (Fixed)",lchrom);
  else {
    if(LENGTH == VARIABLE) printf("Variable");
    else printf("Unknown");
  }

  if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
    if(SHADES == SHADES_2) printf("=[2 x %d] x %d",bits_per_gene,NUM_GENES);
    if(SHADES == SHADES_3) printf("=[3 x %d] x %d",bits_per_gene,NUM_GENES);
  }
  printf("\n %d. Individuals per Population       ----> %d",line++,POPSIZE);
  printf("\n %d. Max generations                  ----> %d",line++,maxgen);
  printf("\n %d. Crossover                        ----> ",line++);
  switch(CROSSOVER) {
    case X_1PT:   printf("1 point"); break;
    case X_2PT:   printf("2 point"); break;
    case UNIFORM: printf("uniform"); break;
  }
  printf("\n %d. Crossover probability(*.*)       ----> %1.3e",line++,pcross);
  printf("\n %d. Mutation probability(*.*)        ----> %1.3e",line++,pmutation);
  printf("\n %d. Adaptive Mutation                ----> ",line++);
  if(ADAPTIVE_MUTATION) printf("Yes (%d)",ADAPTATION_RATE);
  else printf("No");
  printf("\n %d. Scaled                           ----> ",line++);
  if(SCALED) printf("Yes (Linear)");
  else printf("No");
  printf("\n%d. Selection mechanism              ----> ",line++);
  if(STEADY_STATE) printf("SSwithR");
  else {
    switch(SELECTION) {
      case TSR                            : printf("TSR");
                                            break;
      case RANK                           : printf("Rank");
                                            break;
      case REMAIND_STOCH_SAMPL_wo_REPLACE : printf("RSSwithoutR");
                                            break;
      case STOCH_SAMPL_wo_REPLACE         : printf("SSwithoutR");
                                            break;
      case REMAIND_STOCH_SAMPL_w_REPLACE  : printf("RSSwithR");
                                            break;
      case STOCH_SAMPL_w_REPLACE          : printf("SSwithR");
                                            break;
    }
  }
  printf("\n%d. Coding Scheme                    ----> ",line++);
  switch(CODE_SCHEME) {
    case BINARY       : printf("Binary");   break;
    case E_CODE       : printf("E-code");   break;
    case GRAY         : printf("Gray");     break;
    case J_CODE       : printf("J-code");   break;
    case REAL         : printf("Real");     break;
    case BOOL_DYNAMIC : printf("Boolean Dynamic"); break;   
    case DYNAMIC      : printf(" Dynamic"); break;
    default           : printf(" Unknown"); break;
  }
  printf("\n%d. Problem Domain                   ----> ",line++);
  switch(PROBLEM_DOMAIN) {
    case F1:  printf("F1 (De Jong f1)");       break;
    case F2:  printf("F2 (De Jong f2)");       break;
    case F3:  printf("F3 (De Jong f3)");       break;
    case F4:  printf("F4 (De Jong f4)");       break;
    case F5:  printf("F5 (De Jong f5)");       break;
    case F6:  printf("F6 (Rastrigin)");        break;
    case F7:  printf("F7 (Schwefel)");         break;
    case F8:  printf("F8 (Griewangk)");        break;
    case F9:  printf("F9 (Schaffer et al.)");  break;
    case F10: printf("F10 (Schaffer et al.)"); break;
    case F11: printf("F11 (Ackley)");          break;
    case F12: printf("F12 (Himmelblau)");      break;
    case F13: printf("F13 (Pavel)");           break;
    case F14: printf("F14 (Pavel)");        break;
    case F15: printf("F15 (counting)");        break;
    default:  printf("\n Unknown");            break;
  }
  printf("\n%d. Environment (time step)          ----> ",line++);
  if(PROBLEM_TYPE == STAT) printf("Static (0)");
  else {
    if(PROBLEM_TYPE == DYNAM) printf("Dynamic (%d)",TIME_STEP); 
    else printf("Unknown");
  }
  printf("\n%d. Elitism                          ----> ",line++);
  if((ELITISM == ELITISM_REPLACE)||(ELITISM == ELITISM_ADD)) {
    if(ELITISM == ELITISM_REPLACE) printf("Yes - Replace (%d)",ELITE_QTY);
    if(ELITISM == ELITISM_ADD) printf("Yes - Add (%d)",ELITE_QTY);
  }
  else printf("No");
  printf("\n%d. Steady State                     ----> ",line++);
  if(STEADY_STATE) printf("Yes");
  else printf("No");

  printf("\n%d. Polygenic Inheritance (Shades)   ----> ",line++);
  if(SHADES == SHADES_2) printf("Shades_2");
  else {
    if(SHADES == SHADES_3) printf("Shades_3");
    else printf("No");
  }

  if((SHADES == SHADES_2)||(SHADES == SHADES_3))
    printf("\n%d. Perturb Probability  (Shades)    ----> %+1.3e",line++,pos_perturb);
   
  if(((CODE_SCHEME == BINARY)||(CODE_SCHEME==GRAY)) ||
     ((CODE_SCHEME == E_CODE)||(CODE_SCHEME==J_CODE)))  
    printf("\n%d. Allele factor                    ----> %d",line++,ALLELE_FACTOR); 

  printf("\n%d. Probability of Gene Swapping     ----> %f",line++,p_swap);

  if(LENGTH == VARIABLE) {
    printf("\n%d. Probability of Gene Insertion    ----> %f",line++,p_insert); 
    printf("\n%d. Probability of Gene Deletion     ----> %f",line++,p_delete);

    printf("\n%d. Probability of Pruning           ----> %f (%d genes)",line++,p_prune,MAX_GENES);
  }   

  if(CODE_SCHEME==REAL) {
    double dd = (double)(UPPER_LIMIT);
    int    nn = (int)(UPPER_LIMIT);
    printf("\n%d. Upper Limit                      ----> ",line++);
    if(DECIMAL_PLACES == 0) printf("%d",nn);
    else printf("%f",dd);
    printf("\n%d. No. decimal places in Upper Limit----> %d",line++,DECIMAL_PLACES);
    printf("\n%d. Granularity                      ----> %d",line++,GRANULARITY);
    printf("\n%d. Rounded to granularity           ----> ",line++);
    if(ROUNDED == T) printf("Yes");
    else printf("No");
    printf("\n%d. Mutation Operator                ----> ",line++);
    switch(MUTATION) {
      case STEP:       printf("STEP"); break;
      case STOCHASTIC: printf("STOCHASTIC"); break;
      default:         printf(" Unknown");
    }
    printf("\n%d. Prob(mutate sign)                ----> %f",line++,P_SIGN_MUTATION);
  }
  printf("\n\n");
 
  line = 1;
  if(full_report) {
    fprintf(fp,"\n********************************************************");
    fprintf(fp,"\n*                                                      *");
    fprintf(fp,"\n*         G E N E T I C   A L G O R I T H M            *");
    fprintf(fp,"\n*           --------------------------                 *");
    fprintf(fp,"\n*             copyright  J.J. Collins                  *");
    fprintf(fp,"\n*           --------------------------                 *");
    fprintf(fp,"\n*                                                      *");
    fprintf(fp,"\n*     compiled in C++ (GNU g++) on SunOS & Linux       *");
    fprintf(fp,"\n*                                                      *");
    fprintf(fp,"\n********************************************************");
    fprintf(fp,"\n\n %d. Structure                        ----> ",line++);
    switch(STRUCTURE) {
      case HAPLOID  : fprintf(fp,"Haploid");  break;
      case DIPLOID  : fprintf(fp,"Diploid");  
                      fprintf(fp,"\n    Evaluation Method                ----> ");
                      switch(DIP_EVAL) {
	   	        case XOR     : fprintf(fp,"XOR");     break;
		        case RANDOM  : fprintf(fp,"RANDOM");  break;
		        case AVERAGE : fprintf(fp,"AVERAGE"); break;
		        default      : fprintf(fp,"Unknown"); break;
		      }
                      switch(DIPLOID_CROSSOVER) {
		        case GOLDBERG : fprintf(fp,"Goldberg"); break;
		        case PAVEL    : fprintf(fp,"Pavel");    break;
		        case COLLINS  : fprintf(fp,"Collins");  break;
		        default       : fprintf(fp,"Unknown");  break;
		      }
		      break;
      default       : fprintf(fp,"unknown");  break;
    }

    fprintf(fp,"\n %d. Chromosome Length                ----> ",line++);
    if(LENGTH == FIXED) fprintf(fp,"%d (Fixed)",lchrom);
    else {
      if(LENGTH == VARIABLE) fprintf(fp,"Variable");
      else fprintf(fp,"Unknown");
    }

    if((SHADES == SHADES_2)||(SHADES == SHADES_3)) {
      if(SHADES == SHADES_2) fprintf(fp,"=[2x(%d-1)+1]x%d",bits_per_gene,NUM_GENES);
      if(SHADES == SHADES_3) fprintf(fp,"=[3x(%d-1)+1]x%d",bits_per_gene,NUM_GENES);
    }
    fprintf(fp,"\n %d. Individuals per Population       ----> %d",line++,POPSIZE);
    fprintf(fp,"\n %d. Max generations                  ----> %d",line++,maxgen);
    fprintf(fp,"\n %d. Crossover                        ----> ",line++);
    switch(CROSSOVER) {
      case X_1PT:   fprintf(fp,"1 point"); break;
      case X_2PT:   fprintf(fp,"2 point"); break;
      case UNIFORM: fprintf(fp,"uniform"); break;
    }
    fprintf(fp,"\n %d. Crossover probability(*.*)       ----> %1.3e",line++,pcross);
    fprintf(fp,"\n %d. Mutation probability(*.*)        ----> %1.3e",line++,pmutation);
    fprintf(fp,"\n %d. Adaptive Mutation                ----> ",line++);
    if(ADAPTIVE_MUTATION) fprintf(fp,"Yes (%d)",ADAPTATION_RATE);
    else fprintf(fp,"No");
    fprintf(fp,"\n %d. Scaled                           ----> ",line++);
    if(SCALED) fprintf(fp,"Yes (Linear)");
    else fprintf(fp,"No");
    fprintf(fp,"\n%d. Selection mechanism              ----> ",line++);
    if(STEADY_STATE) fprintf(fp,"SSwithR");
    else {
      switch(SELECTION) {
        case TSR                            : fprintf(fp,"TSR");
                                              break;
        case RANK                           : fprintf(fp,"Rank");
                                              break;
        case REMAIND_STOCH_SAMPL_wo_REPLACE : fprintf(fp,"RSSwithoutR");
                                              break;
        case STOCH_SAMPL_wo_REPLACE         : fprintf(fp,"SSwithoutR");
                                              break;
        case REMAIND_STOCH_SAMPL_w_REPLACE  : fprintf(fp,"RSSwithR");
                                              break;
        case STOCH_SAMPL_w_REPLACE          : fprintf(fp,"SSwithR");
                                              break;
      }
    }
    fprintf(fp,"\n%d. Coding Scheme                    ----> ",line++);
    switch(CODE_SCHEME) {
      case BINARY       : fprintf(fp,"Binary"); break;
      case E_CODE       : fprintf(fp,"E-code"); break;
      case GRAY         : fprintf(fp,"Gray");   break;
      case J_CODE       : fprintf(fp,"J-code"); break;
      case REAL         : fprintf(fp,"Real");   break;
      case BOOL_DYNAMIC : fprintf(fp,"Boolean Dynamic"); break;   
      case DYNAMIC      : fprintf(fp,"Dynamic"); break;
      default           : fprintf(fp,"Unknown"); break;
    } 
    fprintf(fp,"\n%d. Problem Domain                   ----> ",line++);
    switch(PROBLEM_DOMAIN) {
      case F1:  fprintf(fp,"F1 (De Jong f1)");       break;
      case F2:  fprintf(fp,"F2 (De Jong f2)");       break;
      case F3:  fprintf(fp,"F3 (De Jong f3)");       break;
      case F4:  fprintf(fp,"F4 (De Jong f4)");       break;
      case F5:  fprintf(fp,"F5 (De Jong f5)");       break;
      case F6:  fprintf(fp,"F6 (Rastrigin)");        break;
      case F7:  fprintf(fp,"F7 (Schwefel)");         break;
      case F8:  fprintf(fp,"F8 (Griewangk)");        break;
      case F9:  fprintf(fp,"F9 (Schaffer et al.)");  break;
      case F10: fprintf(fp,"F10 (Schaffer et al.)"); break;
      case F11: fprintf(fp,"F11 (Ackley)");          break;
      case F12: fprintf(fp,"F12 (Himmelblau)");      break;
      case F13: fprintf(fp,"F13 (Pavel)");           break;
      case F14: fprintf(fp,"F14 (Pavel)");           break;
      case F15: fprintf(fp,"F15 (Counting)");        break;
      default:  fprintf(fp,"unknown"); break;
    }
    fprintf(fp,"\n%d. Environment (time step)          ----> ",line++);
    if(PROBLEM_TYPE == STAT) fprintf(fp,"Static (0)");
    else {
      if(PROBLEM_TYPE == DYNAM) fprintf(fp,"Dynamic (%d)",TIME_STEP); 
      else fprintf(fp,"Unknown");
    }

    fprintf(fp,"\n%d. Elitism                          ----> ",line++);
    if((ELITISM == ELITISM_REPLACE)||(ELITISM == ELITISM_ADD)) {
      if(ELITISM == ELITISM_REPLACE) 
	fprintf(fp,"Yes - Replace (%d)",ELITE_QTY);
      if(ELITISM == ELITISM_ADD) 
	fprintf(fp,"Yes - Add (%d)",ELITE_QTY);
    }
    else fprintf(fp,"No");

    fprintf(fp,"\n%d. Steady State                     ----> ",line++);
    if(STEADY_STATE) fprintf(fp,"Yes");
    else fprintf(fp,"No");

    fprintf(fp,"\n%d. Polygenic Inheritance (Shades)   ----> ",line++);
    if(SHADES == SHADES_2) fprintf(fp,"Shades_2");
    else {
      if(SHADES == SHADES_3) fprintf(fp,"Shades_3");
      else fprintf(fp,"No");
    }

    if((SHADES == SHADES_2)||(SHADES == SHADES_3)) 
      fprintf(fp,"\n%d. Perturb Probability  (Shades)    ----> %+1.3e",line++,pos_perturb);

    if(((CODE_SCHEME == BINARY)||(CODE_SCHEME==GRAY)) ||
       ((CODE_SCHEME == E_CODE)||(CODE_SCHEME==J_CODE)))  
      fprintf(fp,"\n%d. Allele factor                    ----> %d",line++,ALLELE_FACTOR); 

    fprintf(fp,"\n%d. Probability of Gene Swapping     ----> %f",line++,p_swap);

    if(LENGTH == VARIABLE) {
      fprintf(fp,"\n%d. Probability of Gene Insertion    ----> %f",line++,p_insert); 
      fprintf(fp,"\n%d. Probability of Gene Deletion     ----> %f",line++,p_delete);
      fprintf(fp,"\n%d. Probability of Pruning           ----> %f (%d genes)",line++,p_prune,MAX_GENES);
    }   
    if(CODE_SCHEME==REAL) {
      double ddd = (double)(UPPER_LIMIT);
      int    nnn = (int)(UPPER_LIMIT);
      fprintf(fp,"\n%d. Upper Limit                      ----> ",line++);
      if(DECIMAL_PLACES == 0) fprintf(fp,"%d",nnn);
      else fprintf(fp,"%f",ddd);
      fprintf(fp,"\n%d. No. decimal places in Upper Limit----> %d",line++,DECIMAL_PLACES);
      fprintf(fp,"\n%d. Granularity                      ----> %d",line++,GRANULARITY);
      fprintf(fp,"\n%d. Rounded to granularity           ----> ",line++);
      if(ROUNDED == T) fprintf(fp,"Yes");
      else fprintf(fp,"No");
      fprintf(fp,"\n%d. Mutation Operator                ----> ",line++);
      switch(MUTATION) {
        case STEP:       fprintf(fp,"STEP"); break;
        case STOCHASTIC: fprintf(fp,"STOCHASTIC"); break;
        default:         fprintf(fp," Unknown");
      }
      fprintf(fp,"\n%d. Prob(mutate sign)                ----> %f",line++,P_SIGN_MUTATION);
    }
    fprintf(fp,"\n\n");
  }
 }
/********************************************************************/
