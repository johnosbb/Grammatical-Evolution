/*************************************************************************/
/*                                                                       */
/*             FILE   :  INTERPRETER.CC                                  */
/*             AUTHOR :  John O'Sullivan                                 */
/*             DATE   :  SEPTEMBER 1999                                  */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  implements interpreter class declared in file "interpreter.hpp".     */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include "interpreter.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Random.hpp"

/*************************************************************************/




void pause(void);



interpreter::interpreter(int length, int expr[] , double genes[], int num_genes)
{
  /*
   * default constructor
   */
  score = 0.0;
  strcpy(cexpr,"");
  int i = 0;
  for(i=0;i<length;i++)
    old_expr[i] = expr[i];
  if(convert_expr(length,genes,num_genes))
    score = process_expression(cexpr);
   else
    score = 0; // invalid expression
  //printf("RETURNED SCORE is %f\n",score);
  
}

/*************************************************************************/


interpreter::~interpreter()
{
}






float interpreter::getScore()
{
  return score;
}
/*************************************************************************/

/*************************************************************************/
int interpreter::convert_expr(int length,double genes[], int num_genes)
{
  //convers an array of ints which represent expressions into an array of chars representing
  // the literal expressions
  int result = 1; // assume a valid expression
  int i = 0;
  int gpos = 0;
  char li[7] = "";
  for(i=0;i<length;i++)
    {
      if(!get_expression(i,li,genes,num_genes,&gpos))
	{
	  result = 0;
	  printf("Invalid Expression\n");
	  break;
	}
      strcat(cexpr,li);
    }
  return result;  // o is an invalid expression 1 is valid
  
}
/*************************************************************************/




int interpreter::get_expression(int i,char literal_expression[],double genes[], int num_genes,int * gpos)
{
  int result = 1; // assume a valid expression 
    switch(old_expr[i])
      {
      case 1: {strcpy(literal_expression," ( "); break;}
      case 2: {strcpy(literal_expression," ) "); break;}
      case 3: {strcpy(literal_expression," IF "); break;}
      case 4: {strcpy(literal_expression," Y "); break;}
      case 5: {strcpy(literal_expression," THEN "); break;}
      case 6: {strcpy(literal_expression," ELSE "); break;}
      case 7: {strcpy(literal_expression," ENDIF "); break;}
      case 8: {strcpy(literal_expression," + "); break;}
      case 9: {strcpy(literal_expression," - "); break;}
      case 10: {strcpy(literal_expression," / ") ;break;}
      case 11: {strcpy(literal_expression," * "); break;}
      case 12: {strcpy(literal_expression," SIN "); break;}
      case 13: {strcpy(literal_expression," COS "); break;}
      case 14: {strcpy(literal_expression," X "); break;}
      default: { result = 0 ; break;}
      }
  
  return result;
  
}


float  interpreter::process_expression(char theExpression[])
{
  float val = 0.0;
  FILE *thefileptr; 
  char tstfile[30];

  
  //printf("%s\n",theExpression);
  if( (thefileptr = fopen("tst","w")) == NULL)
    {
      cout << "Error opening tst file " << "tst" << endl;  
      exit(0);
    }
  //printf("%s",theExpression);
  fprintf(thefileptr,"%s",theExpression);
  fprintf(thefileptr,"\n");
  fclose(thefileptr);
  //fprintf(stderr,"Lauchning system command\n");
  
  val = (float)system("./SIMPLE/interpret");
  //pause();
  if(val == 0)
    {
      return 0;
    }
  
  else
    {
      sprintf(tstfile,"cp tst %f.tst",(val/256));
      system(tstfile);
      return (val/256);
    }
 
}


void pause(void)
{
  char c;  
  fprintf(stderr,"\nPress enter to continue:");
  fflush(stdin);
  scanf("%c", &c);
  fprintf(stderr,"\n");
}





//generates a random constant based on 8 bytes from the gene pool
// current gene position is used as the starting point for the 8 bytes











