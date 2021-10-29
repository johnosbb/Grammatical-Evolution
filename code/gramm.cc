/*************************************************************************/
/*                                                                       */
/*              FILE   :  GRAMMAR.CC                                     */
/*              AUTHOR :  Michael O'Neill                                */
/*              DATE   :  MAY 98                                         */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :  Implements a BNF Grammar for Grammatical Evolution*/
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include <iostream.h>
#include "grammar.hpp"
#include "../params.h"
/*************************************************************************/
grammar::grammar()
{}
/*************************************************************************/
void grammar::apply_grammar(int old_expr[], int *curr, int *length, int *gpos, const int rnd_num)
{ 
  /********************************************************************/
  /* Purpose: Used for solving x+x^2+x^3+x^4 and Sinx+x+x^2           */
  /********************************************************************/
  /*              (1)<expr> :: = <expr><op><expr>                     */
  /*                             |(<expr><op><expr>)                  */
  /*    	                 |<pre-op>(<expr>)                    */
  /*		                 |<var>                               */
  /*              (2)<op> :: = +|-|/|*                                */
  /*              (3)<pre-op> :: = Sin|Cos|Tan|Log                    */
  /*              (4)<var> :: = X                                     */
  /********************************************************************/

   switch(old_expr[*curr])
  {
  case(1001) : {   /************************************/
                   /*(1)<expr> :: = <expr><op><expr>   */
		   /*               |(<expr><op><expr>)*/
		   /*    	    |<pre-op>(<expr>)  */
		   /*		    |<var>             */
                   /************************************/
                   int r;
                   r=rnd_num%6; //MOD 6 of gene value(rnd_num)
                   // cout << "R is " << r << endl;
                   switch(r)
		   {
		      case(0) :{  //<var>
			          old_expr[*curr] = 1002; 		
				  break;
		               }
		      case(1) :
		      case(2) :{  //<expr><op><expr>
			          for (int i=*length-1;i>*curr;i--) old_expr[i+2]=old_expr[i];
				  *length=*length+2;
				  old_expr[*curr+1]=1003;
				  old_expr[*curr+2]=1001;break;
		               }
		      
		      case(3) :{  //<pre-op>(<expr>)
			          for (int i=*length-1;i>*curr;i--) old_expr[i+3]=old_expr[i];
				  *length=*length+3;
				  old_expr[*curr]=1004;
				  old_expr[*curr+1]=501; //(
				  old_expr[*curr+2]=1001;
				  old_expr[*curr+3]=502; //)
				  break;
		               }
		      case(4) :
		      case(5) :{  //(<expr>)
			          for (int i=*length-1;i>*curr;i--) old_expr[i+2]=old_expr[i];
				  *length=*length+2;
				  old_expr[*curr]=501;
				  old_expr[*curr+1]=1001;
				  old_expr[*curr+2]=502;
				  break;
		                }
		   } // Of inner switch
		   *gpos=*gpos+1; 
		   break;
                 } // Of case 1001

  case(1002) : {   /*********************/
                   /*(4)<var> :: = X    */
                   /*********************/
        	   old_expr[*curr] = 101; 
                   *curr=*curr+1;
		   break;
               } // of case 1002

  case(1003) : {   /***********************/
                   /*(2)<op> :: = +|-|/|* */
                   /***********************/
        	   old_expr[*curr] = 51+(rnd_num%4);
		   *curr=*curr+1; *gpos=*gpos+1; //used gpos here
		   break;
               } // of case 1003

  case(1004) : {   /***********************************/
                   /*(3)<pre-op> :: = Sin|Cos|Tan|Log */
                   /***********************************/
    //old_expr[*curr] = 1+rnd_num%4;
    old_expr[*curr] = 1+rnd_num%3; //removed Log for GP comparison
                   *curr=*curr+1; *gpos=*gpos+1; //used an rnd here
		   break;
               } // of case 1003
  } // Of switch

}
/*************************************************************************/
void grammar::print_grammar_individual(int old_expr[],int length)
{
  for (int i=0;i<length;i++)
    switch(old_expr[i])
      {
      case 1 : {cout << "Sin ";break;}
      case 2 : {cout << "Cos ";break;}
      case 3 : {cout << "Exp ";break;}
      case 4 : {cout << "Log ";break;}
      case 51 : {cout << " + ";break;}
      case 52 : {cout << " - ";break;}
      case 53 : {cout << " * ";break;}
      case 54 : {cout << " / ";break;}
      case 101 : {cout << " X ";break;}
      case 102 : {cout << " 1.0 ";break;}
      case 501 : {cout << "(";break;}
      case 502 : {cout << ")";break;}
      }
}
/*************************************************************************/
void grammar::fprint_grammar_individual(ostream& output_stream,
					int old_expr[],int length)
{      
  for (int i=0;i<length;i++)
    switch(old_expr[i])
      {
      case 1 : {output_stream << "Sin ";break;}
      case 2 : {output_stream << "Cos ";break;}
      case 3 : {output_stream << "Exp ";break;}
      case 4 : {output_stream << "Log ";break;}
      case 51 : {output_stream << " + ";break;}
      case 52 : {output_stream << " - ";break;}
      case 53 : {output_stream << " * ";break;}
      case 54 : {output_stream << " / ";break;}
      case 101 : {output_stream << " X ";break;}
      case 102 : {output_stream << " 1.0 ";break;}
      case 501 : {output_stream << "(";break;}
      case 502 : {output_stream << ")";break;}
      }
  output_stream << endl;
}
/*************************************************************************/
/*************************************************************************/
float grammar::DoUnary(int op ,float arg1)
{
  //cout << "-------\n";
  //cout << "Do U " << op << endl;
  //cout << "-------\n";
  
  switch(op)
    {
    case(1) : {return(sin(arg1)); break;}
    case(2) : {return(cos(arg1)); break;}
    case(3) : {return(exp(arg1)); break;}
    case(4) : {if (arg1>0) {return(log(arg1));break;}
               else {return(1);break;}}
    }//of inner switch
  cout << "Error in DoU\n";  return(-1);
}
/*************************************************************************/
float grammar::DoBinary(int op,float arg1,float arg2)
{
  //cout << "-------\n";
  //cout << "Do B " << op << endl;
  //cout << "-------\n";

  switch(op)
  {
    // +
    case(51) : {return(arg1+arg2);break;}
    // -
    case(52) : {return(arg1-arg2);break;}
    // *
    case(53) : {return(arg1*arg2);break;}
    // / 
    case(54) : {
       		if (arg2!=0) {return(arg1/arg2);break;}
                else {return(1);break;}
               }
  }
  cout <<"Scored Error\n"; 
  return(-1);
} 
/*************************************************************************/


