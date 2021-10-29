/***************************************************************/
// File generated from grammar included in file:
// grammar.bnf
/***************************************************************/
// expr : expr op expr | pre-op ( expr ) | var | control
// control :  IF ( Y ) THEN  expr  ELSE  expr  ENDIF  
// op :   + | - | / | *
// pre-op : SIN | COS
// var : X 
// %%
/***************************************************************/
#include <iostream.h>
#include "grammar.hpp" 
#include "params.h" 
#include <stdlib.h>

grammar::grammar(){}
void grammar::apply_grammar(int old_expr[],int *curr,int *length,
                            int *gpos,const int rnd_num)
{
	switch(old_expr[*curr])
		{
		case(1001):{ /* expr */
			switch(rnd_num%4){
				case(0):{
					for(int i=*length-1;i>*curr;i--)
						old_expr[i+2]=old_expr[i];
					*length = *length + 2;
					old_expr[*curr+0]=1001; //expr
					old_expr[*curr+1]=1003; //op
					old_expr[*curr+2]=1001; //expr
					break;
					}
				case(1):{
					for(int i=*length-1;i>*curr;i--)
						old_expr[i+3]=old_expr[i];
					*length = *length + 3;
					old_expr[*curr+0]=1004; //pre-op
					old_expr[*curr+1]=1; //(
					old_expr[*curr+2]=1001; //expr
					old_expr[*curr+3]=2; //)
					break;
					}
				case(2):{
					old_expr[*curr+0]=1005; //var
					break;
					}
				case(3):{
					old_expr[*curr+0]=1002; //control
					break;
					}
				}//of switch
			*gpos = *gpos + 1;
			break;
			}//of case 1001
		case(1002):{ /* control */
			switch(rnd_num%1){
				case(0):{
					for(int i=*length-1;i>*curr;i--)
						old_expr[i+8]=old_expr[i];
					*length = *length + 8;
					old_expr[*curr+0]=3; //IF
					old_expr[*curr+1]=1; //(
					old_expr[*curr+2]=4; //Y
					old_expr[*curr+3]=2; //)
					old_expr[*curr+4]=5; //THEN
					old_expr[*curr+5]=1001; //expr
					old_expr[*curr+6]=6; //ELSE
					old_expr[*curr+7]=1001; //expr
					old_expr[*curr+8]=7; //ENDIF
					break;
					}
				}//of switch
			break;
			}//of case 1002
		case(1003):{ /* op */
			switch(rnd_num%4){
				case(0):{
					old_expr[*curr+0]=8; //+
					break;
					}
				case(1):{
					old_expr[*curr+0]=9; //-
					break;
					}
				case(2):{
					old_expr[*curr+0]=10; ///
					break;
					}
				case(3):{
					old_expr[*curr+0]=11; //*
					break;
					}
				}//of switch
			*gpos = *gpos + 1;
			break;
			}//of case 1003
		case(1004):{ /* pre-op */
			switch(rnd_num%2){
				case(0):{
					old_expr[*curr+0]=12; //SIN
					break;
					}
				case(1):{
					old_expr[*curr+0]=13; //COS
					break;
					}
				}//of switch
			*gpos = *gpos + 1;
			break;
			}//of case 1004
		case(1005):{ /* var */
			switch(rnd_num%1){
				case(0):{
					old_expr[*curr+0]=14; //X
					break;
					}
				}//of switch
			break;
			}//of case 1005
		default:{ 
			*curr = *curr + 1;
			}
		}//Of switch
	}
/***************************************************************/
void grammar::fprint_grammar_individual(ostream& output_stream,int old_expr[],int length){
	for(int i=0;i<length;i++)
		switch(old_expr[i]){
		case 1: {output_stream << " ( ";break;}
		case 2: {output_stream << " ) ";break;}
		case 3: {output_stream << " IF ";break;}
		case 4: {output_stream << " Y ";break;}
		case 5: {output_stream << " THEN ";break;}
		case 6: {output_stream << " ELSE ";break;}
		case 7: {output_stream << " ENDIF ";break;}
		case 8: {output_stream << " + ";break;}
		case 9: {output_stream << " - ";break;}
		case 10: {output_stream << " / ";break;}
		case 11: {output_stream << " * ";break;}
		case 12: {output_stream << " SIN ";break;}
		case 13: {output_stream << " COS ";break;}
		case 14: {output_stream << " X ";break;}
		}
	output_stream << endl;
}
