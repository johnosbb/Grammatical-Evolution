/*************************************************************************/
/*                                                                       */
/*             File   :  BGE_INDIVIDUAL.CC                               */
/*             AUTHOR :  J.J. COLLINS                                    */
/*                       LUCIA SHEEHAN                                   */
/*             DATE   :  1996 - 1998                                     */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  Implements object declared in header file "crossover.hpp".           */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/

#include <math.h>
#include <stdlib.h>
#include "crossover.hpp"
#include "error_codes.h"
#include "myrandom.h"

/*****************************************************************************/
crossover::crossover()
{
  // do nothing
}
/*************************************************************************/
void crossover::swap_genes(const int indiv)
{
 /**************************************************************/
 /* Swaps two genes in a string.                               */
 /**************************************************************/
  // printf("\n ENTERING swap_genes()");

  int gl = newpop[indiv].gene_no();
  if((probably(p_swap))&&(gl > 1)) {
    int s1 = randomint(gl);
    int s2 = randomint(gl);
    while(s1 == s2) s2 = randomint(gl);
    // printf("\n ....... total genes = %d. swapping genes %d and %d in child %d",gl,s1,s2,indiv);
    if(full_report)
      fprintf(fp,"\n ....... total genes = %d. swapping genes %d and %d in child %d",gl,s1,s2,indiv);
    newpop[indiv].swap_two_genes(s1,s2);
  }

  // printf("\n Leaving swap_genes()");
}
/*************************************************************************/
void crossover::insert_gene(const int indiv)
{
 /**************************************************************/
  /* Inserts a gene randomly into the string.                  */
 /**************************************************************/
  // printf("\n ENTERING insert_gene()"); 

  int gl = newpop[indiv].gene_no();
  if(probably(p_insert)) {
    int node = randomint(gl) +1;
    // printf("\n ....... total nodes = %d, inserting new node at %d in child %d",gl,node,indiv);
    if(full_report)
      fprintf(fp,"\n ....... total nodes = %d, inserting new node at %d in child %d",gl,node,indiv);
    if(node == gl) newpop[indiv].postset();
    else newpop[indiv].traverse(node);
    newpop[indiv].insert();
    int b;
    if(SHADES == F) b = bits_per_gene;
    else {
      if(SHADES==SHADES_2) b = bits_per_gene * 2;
      else b = bits_per_gene * 3;
    }
    newpop[indiv].set_string_length((gl+1)*b);
  }
  // printf("\n LEAVING delete_gene()"); 
}
/*************************************************************************/
void crossover::delete_gene(const int indiv)
{
 /**************************************************************/
  /* Deletes a gene randomly from the string                   */
 /**************************************************************/
  // printf("\n ENTERING delete_gene()"); 

  int gl = newpop[indiv].gene_no();
  if((gl > 1)&&(probably(p_delete))) {
    int node = randomint(gl) + 1;
    // printf("\n ....... total nodes = %d, deleting node %d in child %d",gl,node,indiv);
    if(full_report)
      fprintf(fp,"\n ....... total nodes = %d, deleting node %d in child %d",gl,node,indiv);
    if(node == gl) newpop[indiv].postset();
    else newpop[indiv].traverse(node);
    newpop[indiv].del_gene();
    int l;
    if(SHADES == F) l = bits_per_gene;
    else {
      if(SHADES==SHADES_2) l = bits_per_gene * 2;
      else l = bits_per_gene * 3;
    }
    newpop[indiv].set_string_length((gl-1)*l);
  }
  // printf("\n LEAVING delete_gene()"); 
}
/*************************************************************************/
void crossover::copy_with_mutation(const int child, const int parent,const double mutate_rate)
{
 /**************************************************************/
  /* Copies a parent to a child with mutations.                */
 /**************************************************************/
  int advance_pointer = 1;
  int string_a,string_b;
  int loops = 1;
  if(STRUCTURE == DIPLOID) loops = 2;
  for(int count =0; count < loops; count++) {
    string_a = string_b = count;
    for (int j=0; j < oldpop[parent].str_len(); j++) {
      bit bit_val = oldpop[parent].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer);
      newpop[child].setbit(bit_val,j,string_a);
    }
  }
}
/*************************************************************************/
void crossover::clone(const int child, const int parent)
{
 /**************************************************************/
 /* Copies a parent to the child without any mutations.        */ 
 /**************************************************************/
  int advance_pointer = 1;
  int string_a,string_b;
  int loops = 1;
  if(STRUCTURE == DIPLOID) loops = 2;
  for(int count =0; count < loops; count++) {
    string_a = string_b = count;
    for (int j=0; j < oldpop[parent].str_len(); j++) {
      bit bit_val = oldpop[parent].mutation(0,nmutation,totalnmutations,j,string_a,advance_pointer);
      newpop[child].setbit(bit_val,j,string_a);
    }
  }
}
/*************************************************************************/
void crossover::prune(const int indiv)
{
 /**************************************************************/
 /* Prunes genes from the end of the string, whose total number*/
 /* of genes exceeds MAX_GENES in params.h. The final number of*/
 /* genes will then equal MAX_GENES.                           */  
 /**************************************************************/
  // printf("\n ENTERING pruning()");

  int gl = newpop[indiv].gene_no();

  if((gl > MAX_GENES)&&(probably(p_prune))) {
    int num = gl - MAX_GENES;  
    // printf("\n ....... total nodes = %d, pruning last %d  nodes in child %d",gl,num,indiv);
    if(full_report)
      fprintf(fp,"\n ....... total nodes = %d, pruning last %d  nodes in child %d",gl,num,indiv);
    newpop[indiv].postset();
    for(int i=1; i <= num; i++) 
      newpop[indiv].del_gene();
    int len;
    if(SHADES == F) len = bits_per_gene;
    else {
      if(SHADES==SHADES_2) len = bits_per_gene * 2;
      if(SHADES == SHADES_3) len = bits_per_gene * 3;
    }
    int len1 = (gl * len) - (num * len);
    newpop[indiv].set_string_length(len1);

  }

  // printf("\n LEAVING pruning");
}
/*************************************************************************/
void crossover::duplicate_genes(const int indiv)
{
  newpop[indiv].duplicate_genes();
}
/*************************************************************************/
void  crossover::crossover_1pt(int m, const int parent1, 
                               const int parent2, const double mutate_rate,
                               int jcross, const int which_loop,
                               int string_a, int string_b)
{
  /**************************************************************/
  /* Cross 2 parents; place in 2 child strings. The routine     */
  /* crossover takes two parent strings (parent1,parent2) and   */
  /* generates two offspring strings (child1,child2). The       */
  /* probabilities of crossover and mutation; pcross & pmutation*/
  /* are utilised. At the top of the routine, we determine if we*/
  /* are going to perform crossover on the current pair of      */
  /* parent chromosomes using a random generator procedure flip.*/
  /* If cross is called for, a crossing site is called for      */
  /* between allele locus 1 and the last allele locus -1.       */
  /**************************************************************/
  // printf("\n Entering 1PT CROSSOVER.");

  int advance_pointer1 = 1;
  int advance_pointer2 = 1;
  int lchrom = oldpop[parent1].str_len();
  if(parent1 == parent2) {
    if(STRUCTURE == HAPLOID) advance_pointer1 = 0;
    if((SHADES==SHADES_2)||(SHADES==SHADES_3)) advance_pointer1 = 0;
    if((STRUCTURE == DIPLOID)&&(string_a==string_b)) advance_pointer1=0;
  }
  boolean bit_val;
  int     j;
  int np1 = m;
  int np2 = m+1;
  if(STRUCTURE == DIPLOID) {
    if(DIPLOID_CROSSOVER == GOLDBERG) np2=m;
    if((DIPLOID_CROSSOVER==COLLINS)&&(which_loop !=0)) {
      np1 = m-1;
      np2=m;
    }
  }
  // replaced above with below
  //if((STRUCTURE == DIPLOID)&&((DIPLOID_CROSSOVER == GOLDBERG)||(DIPLOID_CROSSOVER == COLLINS))) np2=m; 

  if (probably(pcross)) ncross++;      // Do crossover with pcross  
  else jcross = lchrom-1;  
  if(full_report) {
    if(STRUCTURE == HAPLOID) fprintf(fp,"| Crossover ==>> %d",jcross +1); 
    if(STRUCTURE == DIPLOID){
          fprintf(fp,"\n    Crossing substring %d from parent %d, with substring %d from parent %d; at %d",
                       string_a+1,parent1+1,string_b+1,parent2+1,jcross+1);
          fprintf(fp,"\n    To yield substring %d in child %d, and substring %d in child %d",
                       string_a+1,np1+1,string_b+1,np2+1);
    }
  }
 

  for (j=0; j < jcross; j++) {
    bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer1);
    newpop[np1].setbit(bit_val,j,string_a);
    bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer2);
    newpop[np2].setbit(bit_val,j,string_b);
   }
  if ( jcross != lchrom){      // skip if cross site = chromosome length
    for (j = jcross; j < lchrom; j++){
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer1);
      newpop[np2].setbit(bit_val,j,string_b);
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer2);
      newpop[np1].setbit(bit_val,j,string_a);
    }
  }
  // printf("\n    leaving CROSSOVER.");
}
/*************************************************************************/

void  crossover::crossover_2pt(const int m, const int parent1,
                               const int parent2, const double mutate_rate,
                               int jcross1, int jcross2, const int which_loop,
                               int string_a, int string_b)
{
  /**************************************************************/
  /* Conceptualise string as circle with start joined to end.   */
  /* Pick 2 point (segment) to crossover, which may cross start */
  /* and end boundaries. 2 cases:                               */
  /* - first crossover point < 2nd crossover point.             */
  /* - first crossover point > 2nd crossover point              */
  /* - no crossover.                                            */
  /**************************************************************/
  //printf("\n entering 2PT CROSSOVER.");
  
  boolean bit_val;
  int     j;
  int     np1 = m;
  int     np2 = m+1;
  int lchrom = oldpop[parent1].str_len();
  int advance_pointer1 = 1;
  int advance_pointer2 = 1;  
  if(parent1 == parent2) {
    if(STRUCTURE == HAPLOID) advance_pointer1 = 0;
    if((SHADES==SHADES_2)||(SHADES==SHADES_3)) advance_pointer1 = 0;
    if((STRUCTURE == DIPLOID)&&(string_a==string_b)) advance_pointer1=0;
  }

  if(STRUCTURE == DIPLOID) {
    if(DIPLOID_CROSSOVER == GOLDBERG) np2=m;
    if((DIPLOID_CROSSOVER==COLLINS)&&(which_loop !=0)) {
      np1 = m-1;
      np2=m;
    }
  }
    
  if (probably(pcross)) {
    ncross++;                      
    if(full_report) {
      if((STRUCTURE == HAPLOID)&&(full_report)) fprintf(fp,"| Crossover ==>> %d %d",jcross1+1,jcross2+1);
      if(STRUCTURE == DIPLOID) {
	fprintf(fp,"\n    Crossing substring %d from parent %d, with substring %d from parent %d; at %d, and %d",
                    string_a+1,parent1+1,string_b+1,parent2+1,jcross1+1,jcross2+1);
	fprintf(fp,"\n    To yield substring %d in child %d, and substring %d in child %d",
                    string_a+1,np1+1,string_b+1,np2+1);
      }
    }
    if(jcross2 > jcross1) {
      for(j=0; j < jcross1; j++){
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
     for(j=jcross1; j < jcross2; j++){
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
     for(j=jcross2; j < lchrom; j++){
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
    }
    else {
     for(j=0; j < jcross2; j++){
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
     for(j=jcross2; j < jcross1; j++){
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
     for(j=jcross1; j < lchrom; j++){
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
   }
  }
  else {
     for(j=0; j < lchrom; j++){
       bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a,advance_pointer1);
       newpop[np1].setbit(bit_val,j,string_a);
       bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b,advance_pointer2);
       newpop[np2].setbit(bit_val,j,string_b);
     }
  }
  //printf("\n    leaving 2PT CROSSOVER."); 
}
/*************************************************************************/

void  crossover::crossover_uniform(const int m, const int parent1,
                               const int parent2, const double mutate_rate,const int which_loop,
                               int string_a, int string_b)
{
  /**************************************************************/
  /* Fully described in Syswerda (1989). "Uniform Crossover in  */
  /* Genetic Algorithms." Proc 3rd ICGA. Given 2 parent strings */
  /* of length l, each parent copies l/2 genes to each child,   */
  /* with the selection of genes being chosen  randomly.        */
  /**************************************************************/

  boolean bit_val;
  int     np1 = m;
  int     np2 = m+1;
  int lchrom = oldpop[parent1].str_len();
  int advance_pointer1 = 1;
  int advance_pointer2 = 1;  
  if(parent1 == parent2) {
    if(STRUCTURE == HAPLOID) advance_pointer1 = 0;
    if((SHADES==SHADES_2)||(SHADES==SHADES_3)) advance_pointer1 = 0;
    if((STRUCTURE == DIPLOID)&&(string_a==string_b)) advance_pointer1=0;
  }

  if(STRUCTURE == DIPLOID) {
    if(DIPLOID_CROSSOVER == GOLDBERG) np2=m;
    if((DIPLOID_CROSSOVER==COLLINS)&&(which_loop !=0)) {
      np1 = m-1;
      np2=m;
    }
  }
  if(full_report) {
    if((STRUCTURE == HAPLOID)&&(full_report)) fprintf(fp,"| Crossover ==>> ");
    if(STRUCTURE == DIPLOID){
      fprintf(fp,"\n    Crossing substring %d from parent %d, with substring %d from parent %d at: ",
                       string_a+1,parent1+1,string_b+1,parent2+1);
      fprintf(fp,"\n    To yield substring %d in child %d, and substring %d in child %d",
                       string_a+1,np1+1,string_b+1,np2+1);
    }
  }

  for(int n=0; n<lchrom; n++) {
    if(probably(pcross)) {
        if(full_report) fprintf(fp," %d",n+1);
        bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b,advance_pointer1);  
	newpop[np1].setbit(bit_val,n,string_a);
	bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a,advance_pointer2);
	newpop[np2].setbit(bit_val,n,string_b);      
    }      
    else {  
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a,advance_pointer1);
      newpop[np1].setbit(bit_val,n,string_a);
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b,advance_pointer2);
      newpop[np2].setbit(bit_val,n,string_b);
    }    
  }
}

/*************************************************************************/

void  crossover::crossover_var_1pt(int m, const int parent1, const int parent2, const double mutate_rate,
                               int jcross1, int jcross2, const int which_loop,int string_a, int string_b)
{
  /*********************************************************************/
  /* Cross 2 parents of variable length;  The routine crossover takes 2*/
  /* parent strings (parent1,parent2) and generates 2 offspring strings*/
  /* (child1,child2). At the top of the routine, we determine if cross-*/
  /* over is performed crossover on the current pair of parent chromo- */
  /* somes using a random generator procedure flip. If cross is called */
  /* for, a gene in each string is selected, then the offset within    */
  /* that gene is added between allele locus 1 & the last allele locus */
  /*-1 of each string.                                                 */
  /* If parent 1 == parent2, resets pointer to start of list, and      */
  /* advances the pointer to the respective crossover point. Cannot use*/
  /* advance_pointer? method as in fixed length case, as there are two */
  /* different crossover points for each string (variable length).     */
  /*********************************************************************/

  //printf("\n entering CROSSOVER VARIABLE 1 PT.");
  boolean bit_val;
  int j;
  int strlen1 = oldpop[parent1].str_len(); 
  int strlen2 = oldpop[parent2].str_len();  
  int np1 = m;
  int np2 = m+1;
  int newstrlen1,newstrlen2;

  if(STRUCTURE == DIPLOID) {
    if(DIPLOID_CROSSOVER == GOLDBERG) np2=m;
    if((DIPLOID_CROSSOVER==COLLINS)&&(which_loop !=0)) {
      np1 = m-1;
      np2=m;
    }
  }
  if (probably(pcross)) ncross++;
  else{
    jcross1 = strlen1;
    jcross2 = strlen2;
  }
  
  newstrlen1 = jcross1 + strlen2 - jcross2;
  newstrlen2 = jcross2 + strlen1 - jcross1;
  newpop[np1].set_string_length(newstrlen1);
  newpop[np2].set_string_length(newstrlen2);
  
  //printf("\n *****************************************************");
  //printf("\n ... parents are %d and %d",parent1,parent2);
  //printf("\n ... length of parent 1 is: %d",strlen1);
  //printf("\n ... length of parent 2 is: %d",strlen2); 
  //printf("\n ... jcross1=%d, jcross2=%d",jcross1,jcross2);     
  //printf("\n ... length of child1 1 is: %d [%d]",newpop[np1].str_len(),newstrlen1);
  //printf("\n ... length of child2 2 is: %d [%d]",newpop[np2].str_len(),newstrlen2); 
  if(full_report){
    fprintf(fp,"| Crossover 1 ==>> %d",jcross1 +1);
    fprintf(fp,"| Crossover 2 ==>> %d",jcross2 +1);
    fprintf(fp,"\n ... length of parent 1 is: %d",strlen1);
    fprintf(fp,"\n ... length of parent 2 is: %d",strlen2); 
    fprintf(fp,"\n Parent 1 is ");
    oldpop[parent1].show(fp); 
    fprintf(fp,"\n Parent 2 is ");
    oldpop[parent2].show(fp);
    fprintf(fp," \n    ............length of child1 is %d",newstrlen1);
    fprintf(fp," \n    ............length of child2 is %d",newstrlen2);
  }

  /*============================================================*/
  /* Copy first segments of parents to children.                */
  /*============================================================*/
  //printf("\n 1st for: for(j = %d, j < %d, j++)\n",0,jcross1);
  for (j=0; j < jcross1; j++) {
    bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a);
    newpop[np1].setbit(bit_val,j,string_a);
  }
  if(parent1 == parent2) oldpop[parent1].reset();
  //printf("\n 2nd for: for(j = %d, j < %d, j++)",0,jcross2);
  for (j=0; j < jcross2; j++) {
    bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b);
    newpop[np2].setbit(bit_val,j,string_b);
  }
  if(parent1 == parent2) {
    oldpop[parent1].reset();
    for(int count =0; count < jcross1; count++) oldpop[parent1].advance();
  }
  /*============================================================*/
  /* Crossover second segment of parents to children.           */
  /*============================================================*/
  //printf("\n 3rd for: for(j = %d, j < %d, j++)",jcross1,strlen1);
  for (j = jcross1; j < strlen1; j++){
    bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a);
    newpop[np2].setbit(bit_val,j,string_b);
  }
  if(parent1 == parent2) {
    oldpop[parent2].reset();
    for(int count =0; count < jcross2; count++) oldpop[parent2].advance();
  }
  //printf("\n 4th for: for(j = %d, j < %d, j++)",jcross2,strlen2);
  for (j = jcross2; j < strlen2; j++){
    bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b);
    newpop[np1].setbit(bit_val,j,string_a);
  }
  
  //printf("\n    leaving CROSSOVER.");
}
/*************************************************************************/
void  crossover::crossover_var_2pt(const int m, const int parent1, const int parent2, 
                                   const double mutate_rate, int jcross1, int jcross2, 
                                   int ycross1, int ycross2,const int which_loop, 
                                   int string_a, int string_b)
{
  /*********************************************************************/
  /* Conceptualise string as circle with start joined to end. Pick 2   */
  /* point (segment) to crossover, which may cross start and end       */
  /* boundaries. 2 cases:                                              */
  /* - first crossover point < 2nd crossover point.                    */
  /* - first crossover point > 2nd crossover point                     */
  /* - no crossover.                                                   */
  /* If parent 1 == parent2, resets pointer to start of list, and      */
  /* advances the pointer to the respective crossover point. Cannot use*/
  /* advance_pointer? method as in fixed length case, as there are two */
  /* different crossover points for each string (variable length).     */
  /*********************************************************************/
  //printf("\n entering CROSSOVER VARIABLE 2 POINT.");

  int strlen1 = oldpop[parent1].str_len(); 
  int strlen2 = oldpop[parent2].str_len();
  int j;
  boolean bit_val;
  int np1 = m;
  int np2 = m+1;

  if(STRUCTURE == DIPLOID) {
    if(DIPLOID_CROSSOVER == GOLDBERG) np2=m;
    if((DIPLOID_CROSSOVER==COLLINS)&&(which_loop !=0)) {
      np1 = m-1;
      np2=m;
    }
  }

  if (probably(pcross)){
    ncross++;
    int newstrlen1, newstrlen2;   
    if((full_report) && (which_loop ==0)){ 
      fprintf(fp,"| Crossover 1 ==>> %4d %4d",jcross1, jcross2);
      fprintf(fp,"| Crossover 2 ==>> %4d %4d",ycross1, ycross2);
    }         
    newstrlen1 = jcross1 + ycross2 - ycross1 + strlen1 - jcross2;
    newstrlen2 = ycross1 + jcross2 - jcross1 + strlen2 - ycross2;
    //printf("\n new len1: %d + %d - %d + %d - %d",jcross1,ycross2,ycross1,strlen1,jcross2);
    //printf("\n new len2: %d + %d - %d + %d - %d",ycross1,jcross2,jcross1,strlen2,ycross2);
    newpop[np1].set_string_length(newstrlen1);
    newpop[np2].set_string_length(newstrlen2);
    //printf("\n crossover point 1: %d and: %d", jcross1,jcross2);
    //printf("\n crossover point 2: %d and: %d", ycross1,ycross2);    
    //printf("\n ... length of child1 1 is: %d [%d]",newpop[np1].str_len(),newstrlen1);
    //printf("\n ... length of child2 2 is: %d [%d]",newpop[np2].str_len(),newstrlen2);     
    /*============================================================*/
    /*============================================================*/
    //printf("\n 1st for: for(j = %d, j < %d, j++)",0,jcross1);      
    for(j=0; j < jcross1; j++){
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a);
      newpop[np1].setbit(bit_val,j,string_a);
    }
    //printf("\n 1st for: for(j = %d, j < %d, j++)",0,ycross1);      
    if(parent1 == parent2) oldpop[parent1].reset();
    for(j=0; j < ycross1; j++){
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b);
      newpop[np2].setbit(bit_val,j,string_b);
    }
    if(parent1 == parent2) {
      oldpop[parent1].reset();
      for(int count =0; count < jcross1; count++) oldpop[parent1].advance();
    }
    /*============================================================*/
    /*============================================================*/
    //printf("\n 2nd for: for(j = %d, j < %d, j++)",jcross1,jcross2);
    for(j=jcross1; j < jcross2; j++){
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a);
      newpop[np2].setbit(bit_val,j,string_b);
    }
    if(parent1 == parent2) {
      oldpop[parent1].reset();
      for(int count =0; count < ycross1; count++) oldpop[parent1].advance();
    }
    //printf("\n 2nd for: for(j = %d, j < %d, j++)",ycross1,ycross2);
    for(j=ycross1; j < ycross2; j++){
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b);
      newpop[np1].setbit(bit_val,j,string_a);
    }
    if(parent1 == parent2) {
      oldpop[parent1].reset();
      for(int count =0; count < jcross2; count++) oldpop[parent1].advance();
    }  
    /*============================================================*/
    /*============================================================*/
    //printf("\n 3rd for: for(j = %d, j < %d, j++)",jcross2,strlen1);
    for(j=jcross2; j < strlen1; j++){
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a);
      newpop[np1].setbit(bit_val,j,string_a);
    }
    if(parent1 == parent2) {
      oldpop[parent1].reset();
      for(int count =0; count < ycross2; count++) oldpop[parent1].advance();
    }
    //printf("\n 3rd for: for(j = %d, j < %d, j++)",ycross2,strlen2);
    for(j=ycross2; j < strlen2; j++){
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b);
      newpop[np2].setbit(bit_val,j,string_b);
    }
  }
  /*==========================================================================*/  
  else {
    //printf("\n No crossover");
    newpop[np1].set_string_length(strlen1);
    newpop[np2].set_string_length(strlen2);
    //printf("\n else: for(j = %d, j < %d, j++)",0,strlen1);
    for(j=0; j < strlen1; j++){
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,j,string_a);
      newpop[np1].setbit(bit_val,j,string_a);
    }
    if(parent1 == parent2) oldpop[parent1].reset();
    //printf("\n else: for(j = %d, j < %d, j++)",0,strlen2);
    for(j=0; j < strlen2; j++){
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,j,string_b);
      newpop[np2].setbit(bit_val,j,string_b);
    }
  }
   
  // printf("\n    leaving CROSSOVER VAR 2PT."); 
}
/*************************************************************************/

void  crossover::crossover_var_uniform(const int m, const int parent1,
                                   const int parent2, const double mutate_rate, int which_loop,
				   int string_a, int string_b)
{
  /**************************************************************/
  /* Fully described in Syswerda (1989). "Uniform Crossover in  */
  /* Genetic Algorithms." Proc 3rd ICGA. Given 2 parent strings */
  /* of length l, each parent copies l/2 genes to each child,   */
  /* with the selection of genes being chosen  randomly.        */
  /* Three cases:                                               */
  /* 1.  Both strings are the same size - (as above)            */
  /*     If parent1 == parent2, do not advance pointer on first */
  /*     call to muate(.........)                               */
  /* 2.  String1 > string2 - select crossover point on string1  */
  /*      Copy over portions of string1 not being crossed       */
  /*      Use method above to crossover remainder of string1 &2 */
  /* 3.  String2 > string1 - similar to 2. above                */
  /**************************************************************/

  //printf("\n Entering CROSSOVER VARIABLE UNIFORM ");

  int advance_pointer1 = 1;  // Need advance_pointer1 and advance_pointer2 for the
  int advance_pointer2 = 1;  // haploid case when parent1 == parent2

  int np1 = m;
  int np2 = m+1;
  if(parent1 == parent2) {
    if(STRUCTURE == HAPLOID) advance_pointer1 = 0;
    if((SHADES==SHADES_2)||(SHADES==SHADES_3)) advance_pointer1 = 0;
    if((STRUCTURE == DIPLOID)&&(string_a==string_b)) advance_pointer1=0;
  }
  if(STRUCTURE == DIPLOID) {
    if(DIPLOID_CROSSOVER == GOLDBERG) np2=m;
    if((DIPLOID_CROSSOVER==COLLINS)&&(which_loop !=0)) {
      np1 = m-1;
      np2=m;
    }
  }

  int strlen1 = oldpop[parent1].str_len(); 
  int strlen2 = oldpop[parent2].str_len();
  //printf("\n strlen1, strlen2: %d, %d",strlen1, strlen2);

  if(full_report) fprintf(fp,"| Crossover ==>> ");
  newpop[np1].set_string_length(strlen1);
  newpop[np2].set_string_length(strlen2);
  boolean bit_val;
  /*============================================================*/
  /* CASE 1: String lengths are equal.                          */
  /*============================================================*/
  if (strlen1 == strlen2){
    //printf("\n EQUAL STRING LENGTHS:");
    for(int n=0; n<strlen1; n++) {
      if(probably(pcross)) {
        if(full_report) fprintf(fp," %d",n);
	bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a,advance_pointer1);
	newpop[np2].setbit(bit_val,n,string_b);
        bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b,advance_pointer2);
	newpop[np1].setbit(bit_val,n,string_a);
      }     
      else {
	bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a,advance_pointer1);
	newpop[np1].setbit(bit_val,n,string_a);
	bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b,advance_pointer2);
	newpop[np2].setbit(bit_val,n,string_b);
      }
    }
  }
  /*============================================================*/
  /* CASE 2: String length of parent 1 is greater than parent 2.*/
  /*============================================================*/
  int gdiff,gcross;
  if (strlen1 > strlen2){
    //printf("\n PARENT1 > PARENT2  :");
    if(CROSS_GENE_BOUND) {
      gdiff =  oldpop[parent1].gene_no() -   oldpop[parent2].gene_no();
      gcross = randomint(gdiff) * bits_per_gene;
      //printf("  gdiff = %d", gdiff);
    }
    else gcross = randomint(strlen1 - strlen2); 
    //printf(", gcross = %d",gcross);
    for(int n=0; n<gcross; n++) {
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a);
      newpop[np1].setbit(bit_val,n,string_a);
    }  
    for(int n=0; n<strlen2; n++) {
      if(probably(pcross)) {
        if(full_report) fprintf(fp," %d",np2);
        bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b);
	newpop[np1].setbit(bit_val,n,string_a);
	bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a);
	newpop[np2].setbit(bit_val,n,string_b);      
      }      
      else {  
	bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a);
	newpop[np1].setbit(bit_val,n,string_a);
	bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b);
	newpop[np2].setbit(bit_val,n,string_b);
      }    
    }
    for(int n=gcross + strlen2; n<strlen1; n++) {
      bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a);
      newpop[np1].setbit(bit_val,n,string_a);
    }      
  }
  /*============================================================*/
  /* CASE 3: String length of parent 2 is greater than parent 1.*/
  /*============================================================*/
 if (strlen2 > strlen1){
   //printf("\n PARENT 2  > PARENT 1  : ");
   if(CROSS_GENE_BOUND) {
      gdiff =  oldpop[parent2].gene_no() -   oldpop[parent1].gene_no();
      gcross = randomint(gdiff) * bits_per_gene;
      //printf("  gdiff = %d", gdiff);
    }
    else gcross = randomint(strlen2 - strlen1);
   //printf(", gcross = %d",gcross);
    for(int n=0; n<gcross; n++) {
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b);
      newpop[np2].setbit(bit_val,n,string_b);
    } 
    for(int n=0; n<strlen1; n++) {
      if(probably(pcross)) {
        if(full_report) fprintf(fp," %d",np2);
        bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a);
	newpop[np2].setbit(bit_val,n,string_b);
	bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b);
	newpop[np1].setbit(bit_val,n,string_a);      
      }     
      else {  
	bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b);
	newpop[np2].setbit(bit_val,n,string_b);
	bit_val = oldpop[parent1].mutation(mutate_rate,nmutation,totalnmutations,n,string_a);
	newpop[np1].setbit(bit_val,n,string_a);
      }    
    }
    for(int n=gcross + strlen1; n<strlen2; n++) {
      bit_val = oldpop[parent2].mutation(mutate_rate,nmutation,totalnmutations,n,string_b);
      newpop[np2].setbit(bit_val,n,string_b);
    }      
  }
 // printf("\n LEAVING UNIFORM VARIABLE CROSSOVER");
}

    
/*************************************************************************/
void crossover_var_homologous(int m, const int parent1, 
			      const int parent2, const double mutate_rate)
{
  /***********************************************************************/
  /*  Conor suggested a new Xover operator (inspired by Bill's Homologous*/
  /*  Xover) based on the premise that schema are being propogated from  */
  /*  the beginning of the individual:                                   */
  /*	a) Align chromosome pair                                         */
  /*    b) From the start of each chromosome read the next codon value   */
  /*       and MOD                                                       */
  /*	c) IF MOD'ed values are same at that locus read the next locus   */
  /*	   ELSE Set a similarity barrier at this position                */  
  /*	d) Generate 2 Xover points by                                    */
  /*	        i) Selecting a point within the region of similarity     */
  /*               (this is the 1st xover point which holds for BOTH     */
  /*                parents)                                             */
  /*		ii) Select 2 second xover points within the region of    */
  /*                dissimilarity - one point on each parent             */
  /*	e) Perform 2 point xover                                         */
  /***********************************************************************/
}
/*************************************************************************/
void crossover::swap_strings(const int indiv_1, const int string_1,
                                  const int indiv_2, const int string_2)
{
  /**************************************************************/
  /* Swaps two chromosome strings from two different individuals */
  /* Used in Goldberg crossover method for diploid genotypes.   */
  /**************************************************************/
  //printf("\n entering SWAP_CHROMS()");

  //printf("\n swapping string %d from child %d with string %d from child %d",
  //             string_1,indiv_1,string_2,indiv_2);

  int lchrom = newpop[indiv_1].str_len();
  printf("\n lchrom = %d",lchrom);

  bit *ptr1 = newpop[indiv_1].returncopy(string_1);
  bit *ptr2 = newpop[indiv_2].returncopy(string_2);
//printf("\n after returning copies");

  newpop[indiv_1].del_string(string_1);
  newpop[indiv_2].del_string(string_2);
//printf("\n after deleting old strings");

  newpop[indiv_1].reset();
  newpop[indiv_2].reset();

  for(int count1 = 0; count1 < lchrom; count1++) {
    newpop[indiv_1].setbit(*ptr2++,count1,string_1);
    newpop[indiv_2].setbit(*ptr1++,count1,string_2);      
  }
//printf("\n after swapping");

  ptr1 = NULL;
  ptr2 = NULL;
  
//printf("\n leaving swap_chroms");
}
/*************************************************************************/
void crossover::set_up_cross_params(int &parent1, int &parent2, int &string_a,int &string_b, 
                                  int &loops, const int mate1, const int mate2)
  /**************************************************************/
  /* Some of the crossover parameters are determined by the     */
  /* genotype used ie. for haploid, crossover is applied only   */
  /* once to the two parents, but for diploid using the Goldberg*/
  /* method, crossover is applied twice to the two parents. This*/
  /* particular variable is determined by "loops". Read the     */
  /* description of the three diploid crossovers in defines.h   */  
  /**************************************************************/
{
   string_a = 0;
   string_b = 0;
   loops = 1;
   parent1 = mate1;
   parent2 = mate2;
   if(STRUCTURE ==  DIPLOID) {
     switch(DIPLOID_CROSSOVER) {
	  case GOLDBERG: loops = 2;
	                 parent1 = mate1;
                         parent2 = mate1;
	                 string_b = 1;
                         break;
	  case PAVEL   : string_a = randomint(2);
	                 string_b = randomint(2);
                         break;
	  case COLLINS : loops = 2; string_b = 1; break;
	  default      : printf("\n error: crossover parameters in file generate");
	                 exit(1);
                         break;
     }
   }
}
/*************************************************************************/
void crossover::copy_string(const int mate, const int j, const int string)
{
  /**************************************************************/
  /* Copies 1 string from the chromosome of a diploid parent to */
  /* the diploid child. Used in Pavel's crossover method for    */
  /* diploid genotypes only.                                    */
  /**************************************************************/

  bit *ptr1 = oldpop[mate].returncopy(string);
  int lchrom =  oldpop[mate].str_len();
  //printf("\n about to delete old strings");
  newpop[j].del_string(string);
  newpop[j].reset();

  for(int count1 = 0; count1 < lchrom; count1++) 
    newpop[j].setbit(*ptr1++,count1,string);

  ptr1 = NULL;
}
/*************************************************************************/
void crossover::jig_chromosome_strings(const int j, const int string_a, const int string_b,
                                      const int mate1, const int mate2)
{
  /**************************************************************/
  /* For Goldberg or Pavels crossover method for a diploid geno-*/
  /* type, either swap strings in children, or copy some strings*/
  /* from parents to the children.                              */
  /**************************************************************/

  //printf("\n entering jig..()");

  if(DIPLOID_CROSSOVER == GOLDBERG) {
    int rand = randomint(4);
      switch(rand) {
        case 0: swap_strings(j,0,j+1,0); 
	  if (full_report)
	    fprintf(fp,"\n    *** swapping substrings 0 and 0 from p1 and p2"); break;
        case 1: swap_strings(j,0,j+1,1);
	  if (full_report)
	    fprintf(fp,"\n    *** swapping substrings 0 and 1 from p1 and p2"); break;
        case 2: swap_strings(j,1,j+1,0); 
	  if (full_report)
	    fprintf(fp,"\n    *** swapping substrings 1 and 0 from p1 and p2"); break;
        case 3: swap_strings(j,1,j+1,1); 
                if(full_report) fprintf(fp,"\n    *** swapping substrings 1 and 1 from p1 and p2"); break; 
      }
  }
  if(DIPLOID_CROSSOVER == PAVEL) {
    int string1,string2;
    if(string_a == 0) string1 = 1;
    else string1 = 0;
    if(string_b == 0) string2 = 1;
    else string2 = 0;
    copy_string(mate1,j,string1);
    copy_string(mate2,j+1,string2);
  }
  //printf("\n leaving jig..()");
}

/*************************************************************************/
void crossover::crossover_parents(const int mate1, const int mate2,
                                 const int j, const double pm)
{
  int parent1,parent2,string_a,string_b,loops;
  int jcross=0,jcross1=0,jcross2=0,ycross1=0,ycross2=0;
  set_up_cross_params(parent1,parent2,string_a,string_b,loops,mate1,mate2);

  for(int count = 0; count < loops; count++) {
    oldpop[mate1].reset();
    oldpop[mate2].reset();
    if((count == 1)&&(DIPLOID_CROSSOVER == GOLDBERG)) { parent1 = mate2, parent2 = mate2;}
    if((count == 1)&&(DIPLOID_CROSSOVER == COLLINS)) { string_a=1; string_b=0;}
    int strlen1 = oldpop[parent1].str_len(); 
    int offset1 = 0, offset2 = 0;
    int strlen2 = oldpop[parent2].str_len();
    int offset;
    int genes1 =  oldpop[parent1].gene_no(); 
    int genes2 = oldpop[parent2].gene_no(); 

    if(LENGTH == FIXED) {
      switch(CROSSOVER){
      case X_1PT:   jcross = randomint(strlen1);
	            crossover_1pt(j+count,parent1,parent2,pm,jcross,count,string_a,string_b);
	            break;
      case X_2PT:   jcross1 = randomint(strlen1);
	            jcross2 = randomint(strlen1);
	            while(jcross1 == jcross2) jcross2 = randomint(strlen1);
	            crossover_2pt(j+count,parent1,parent2,pm,jcross1,jcross2,count,string_a,string_b);
                    break;
      case UNIFORM: crossover_uniform(j+count,parent1,parent2,pm,count,string_a,string_b);
                    break;
      }
    }
    else {
      switch(CROSSOVER){
      case X_1PT: if(count==0) {
                          jcross1 = randomint(genes1) * bits_per_gene;
	                  jcross2 = randomint(genes2) * bits_per_gene;
	                  if(!CROSS_GENE_BOUND) { 
	                    offset = randomint(bits_per_gene);
	                    jcross1 += offset;
	                    jcross2 += offset;
	                  }
	                  if((jcross1 == 0) && (jcross2 == strlen2)) jcross1 = bits_per_gene;
	                  if((jcross2 == 0) && (jcross1 == strlen1)) jcross2 = bits_per_gene;
	                }
	                crossover_var_1pt(j+count,parent1,parent2,pm,jcross1,jcross2,count,string_a,string_b);
			break;
      case X_2PT: if(count==0){
	            if(!CROSS_GENE_BOUND) { 
	              offset1 = randomint(bits_per_gene);
	      	      offset2 = randomint(bits_per_gene);
		      while(offset2 == offset1) offset2 = randomint(bits_per_gene);
		      if(offset2 < offset1){
			int temp = offset1;
			offset1 = offset2;
			offset2 = temp;
		      }
		    }
		    int sel_gene1,sel_gene2,sel_gene3,sel_gene4;
		    sel_gene1 = randomint(genes1);
		    sel_gene2 = randomint(genes1);     
		    sel_gene3 = randomint(genes2);
		    sel_gene4 = randomint(genes2); 
		    while ((CROSS_GENE_BOUND ) && ((strlen1 != bits_per_gene) && (sel_gene1 == sel_gene2)))
		      sel_gene2 = randomint(genes1);
		    if (sel_gene2 < sel_gene1){
		      int temp = sel_gene1;
		      sel_gene1 = sel_gene2;
		      sel_gene2 = temp;
		    }
		    jcross1 = sel_gene1 * bits_per_gene + offset1;
		    jcross2 = sel_gene2 * bits_per_gene + offset2;
		    while ((CROSS_GENE_BOUND ) && ((strlen2 != bits_per_gene) && (sel_gene3 == sel_gene4)))
		      sel_gene4 = randomint(genes2);
		    if (sel_gene4 < sel_gene3){
		      int temp = sel_gene3;
		      sel_gene3 = sel_gene4;
		      sel_gene4 = temp;
		    }
		    ycross1 = sel_gene3 * bits_per_gene + offset1;
		    ycross2 = sel_gene4 * bits_per_gene + offset2;
                    }	
                  crossover_var_2pt(j+count,parent1,parent2,pm,jcross1,jcross2,ycross1,ycross2,count,string_a,string_b);
	          break;
      case UNIFORM: crossover_var_uniform(j+count,parent1,parent2,pm,count,string_a,string_b);
	          break;		  
      }
    }
  }
  if(STRUCTURE == DIPLOID) 
    jig_chromosome_strings(j,string_a,string_b,mate1,mate2);
}

/*************************************************************************/






