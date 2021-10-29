/***************************************************************/
// File generated from grammar_gep included in file:
// grammar_gep.bnf
/***************************************************************/
// code : line | code line                                
// line : condition | op 
// condition : if(trail.food_ahead()) { line } else { line }
// op :  trail.left() | trail.right() | trail.move()
// %%
/***************************************************************/
#include <iostream.h>
#include "grammar_gep.hpp" 
#include "params.h" 
#include <stdlib.h>



grammar_gep::grammar_gep()
  :expr_num(1)
{}
void grammar_gep::apply_grammar(int old_expr[][2],int *curr,int *length,int *gpos,const int rnd_num, int *age)
{
  check_length(curr);
  check_length(length);
	switch(old_expr[*curr][0])
		{
		case(1001):{ /* code */
			switch(rnd_num%2){
				case(0):{
					old_expr[*curr+0][0]=1002; //line
					old_expr[*curr+0][1]= (*age)++;  // update the age of this expression
					break;
					}
				case(1):{
					for(int i=*length-1;i>*curr;i--)
					  {
					    old_expr[i+1][0]=old_expr[i][0];
					    old_expr[i+1][1]=old_expr[i][1]; 
					  }
					
					*length = *length + 1;
					old_expr[*curr+0][0]=1001; //code
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+1][0]=1002; //line
					old_expr[*curr+1][1]= (*age)++;  // update the *age of this expression
					break;
					}
				}//of switch
			*gpos = *gpos + 1;
			break;
			}//of case 1001
		case(1002):{ /* line */
			switch(rnd_num%2){
				case(0):{
					old_expr[*curr+0][0]=1003; //condition
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expression
					break;
					}

				case(1):{
					old_expr[*curr+0][0]=1004; //op
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expression
					break;
					}
				}//of switch
			*gpos = *gpos + 1;
			break;
			}//of case 1002
		case(1003):{ /* condition */
			switch(rnd_num%1){
				case(0):{
				  for(int i=*length-1;i>*curr;i--)
				    {
				      old_expr[i+7][0]=old_expr[i][0];
				      old_expr[i+7][1]=old_expr[i][1];
				    }
				  
					*length = *length + 7;
					old_expr[*curr+0][0]=1; //if(trail.food_ahead())
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+1][0]=2; //{
					old_expr[*curr+1][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+2][0]=1002; //line
					old_expr[*curr+2][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+3][0]=3; //}
					old_expr[*curr+3][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+4][0]=4; //else
					old_expr[*curr+4][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+5][0]=2; //{
					old_expr[*curr+5][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+6][0]=1002; //line
					old_expr[*curr+6][1]= (*age)++;  // update the *age of this expression
					old_expr[*curr+7][0]=3; //}
					old_expr[*curr+7][1]= (*age)++;  // update the *age of this expression
					break;
					}
				}//of switch
			break;
			}//of case 1003
		case(1004):{ /* op */
			switch(rnd_num%3){
				case(0):{
					old_expr[*curr+0][0]=5; //trail.left()
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expression
					break;
					}
				case(1):{
					old_expr[*curr+0][0]=6; //trail.right()
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expressio
					break;
					}
				case(2):{
					old_expr[*curr+0][0]=7; //trail.move()
					old_expr[*curr+0][1]= (*age)++;  // update the *age of this expressio
					break;
					}
				}//of switch
			*gpos = *gpos + 1;
			break;
			}//of case 1004
		default:{ 
			*curr = *curr + 1;
			check_length(curr);
			
			}
		}//Of switch




	}
/***************************************************************/
void grammar_gep::fprint_grammar_individual(ostream& output_stream,int old_expr[][2],int length){
        output_stream << expr_num++ << ". ";
	for(int i=0;i<length;i++)
		switch(old_expr[i][0]){
		case 1: {output_stream << " if(trail.food_ahead()) ";break;}
		case 2: {output_stream << " { ";break;}
		case 3: {output_stream << " } ";break;}
		case 4: {output_stream << " else ";break;}
		case 5: {output_stream << " trail.left() ";break;}
		case 6: {output_stream << " trail.right() ";break;}
		case 7: {output_stream << " trail.move() ";break;}
		case 1001: {output_stream << " <code> ";break;}
		case 1002: {output_stream << " <line> ";break;}
		case 1003: {output_stream << " <condition> ";break;}
		case 1004: {output_stream << " <op> ";break;}
		}
	output_stream << endl;
	//output_stream << expr_num << ". ";
	//for(int i=0;i<length;i++)
	//output_stream << old_expr[i][1] << "       " ;
	//output_stream << endl;
	//output_stream << expr_num++ << ". ";
	//for(int i=0;i<length;i++)
	// output_stream << old_expr[i][0] << "       " ;
	//output_stream << endl;
}


int grammar_gep::check_length(int * len_val)
{
  int n;
  
  if(*(len_val)+7  > LENGTH_OF_EXPRESSION)
    {
       n = 0;
       cout << "ERROR!!! value was " << *(len_val)+ 1 << "\n";
       exit(0);
       
    }
  
  
  else
    n = 1;
  return n;

  
}







