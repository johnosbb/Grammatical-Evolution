/*************************************************************************/
/*                                                                       */
/*             FILE   :  INTERPRETER_GEP.CC                                  */
/*             AUTHOR :  Michael O'Neill                                 */
/*             DATE   :  SEPTEMBER 1999                                  */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*  implements interpreter_gep class declared in file "interpreter_gep.hpp".     */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include "interpreter_gep.hpp"
#include "GEtrail.hpp"

/*************************************************************************/
interpreter_gep::interpreter_gep(int length, int expr[][2],double genes[], int num_genes)
{
  /*
   * default constructor
   */
  score = 0.0;
  for(int i=0;i<length;i++) old_expr[i] = expr[i][0];

  int food_eaten=0;

  trail.Readtrail("GE/santafe.trl");
  while(trail.getAnt().energy()>0)
    {
      int start=0;
      evaluate_ant(start, length);
    }
  food_eaten=trail.getAnt().picked_up();
  score = food_eaten;
}
/*************************************************************************/
float interpreter_gep::getScore()
{
  return score;
}
/*************************************************************************/

void interpreter_gep::evaluate_ant(int &start,int end)
{
  //cout << "evaluate_ant()" << endl;

  while(start<end)
    {
      for(;((old_expr[start]!=1) && (start<end));start++)
	{
	  process_expr(start);
	}
      if(start!=end) process_if(start);
    }
}

void interpreter_gep::process_if(int &index)
{
  //cout << "process_if() -- ";
 
  switch(trail.food_ahead())
    {
    case 0 :
      {
	//cout << "food_ahead FALSE" << endl;
	int counter=1;
	index=index+2; //move to first statement after {
	//move to the else part by counting { & }'s
	while(counter!=0)
	  {
	    if(old_expr[index]==2) counter++;
	    else if(old_expr[index]==3) counter--;
	    index++;
	  }
	break;
      }
    case 1 :
      {
	//cout << "food_ahead TRUE" << endl;
	int expr_length=0,end=0;
	int counter=1;
	index=index+2; //move to first statement after {
	//move to the end of the if part by counting { & }'s
	//to get the expressions length
	while(counter!=0)
	  {
	    if(old_expr[index]==2) counter++;
	    else if(old_expr[index]==3) counter--;
	    expr_length++;
	    index++;
	  }
	//cout << "expr_length (" << expr_length << ")" << endl;
	index=index-expr_length;
	end=index+expr_length;
	evaluate_ant(index,end);
	//cout << "finished if" << endl;
       
	counter=1;
	index=index+2; //move to first statement after {
	//move to the end of the else part by counting { & }'s
	while(counter!=0)
	  {
	    if(old_expr[index]==2) counter++;
	    else if(old_expr[index]==3) counter--;
	    expr_length++;
	    index++;
	  }
	break;
      }
    }
}

void interpreter_gep::process_expr(int &index)
{
  //  cout << "process_expr() -- ";

  switch(old_expr[index])
    {
    case 5 :
      {
	//cout << "old_expr[" << index << "] is left()" << endl;  
	trail.left();
	break;
      }
    case 6 :
      {
	//cout << "old_expr[" << index << "] is right()" << endl; 
	trail.right();
	break;
      }
    case 7 :
      {
	//cout << "old_expr[" << index << "] is move()" << endl; 
	trail.move();
	break;
      }
    case 4 :
      {
	//cout << "old_expr[" << index << "] is else" << endl; 
	break;
      }
    case 2 :
      {
	//cout << "old_expr[" << index << "] is {" << endl; 
	break;
      }
    case 3 :
      {
	//cout << "old_expr[" << index << "] is }" << endl; 
	break;
      }
    default :
      {
	//cout << "process_expr : ERROR" << endl;
      }
    }
}

