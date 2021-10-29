# line 1 "inter.m"

# line 4 "inter.cpp"
#include "ast.f"
extern void MatchError(char *, int);
#include "ast.h"
# line 1 "inter.m"


#include "move.hpp"
extern "C" void printf(...);
extern "C" int execute(Statement s);




string evaluate_string(Expression e)
{
  
# line 21 "inter.cpp"

// GENERATED FROM SOURCE LINE 12
{
Expression tmp0;
tmp0 = e;
{
Expression tmp1;
if (tmp0->tag != next_needed_tag) goto EndOfRule2;
# line 14 "inter.m"
  return get_next_needed();   
      
# line 33 "inter.cpp"
goto EndOfMatch7;
EndOfRule2 : ;
}
{
Expression tmp3;
if (tmp0->tag != current_stack_tag) goto EndOfRule4;
# line 15 "inter.m"
  return get_current_stack();
      
# line 43 "inter.cpp"
goto EndOfMatch7;
EndOfRule4 : ;
}
{
Expression tmp5;
if (tmp0->tag != top_block_tag) goto EndOfRule6;
# line 16 "inter.m"
  return get_top_block();
    
# line 53 "inter.cpp"
goto EndOfMatch7;
EndOfRule6 : ;
}
MatchError("inter.m", 12);
EndOfMatch7 : ;
}
# line 17 "inter.m"

  
}

//int evaluate(Expression e)
//{
//   match e 
//       {
//	   rule test(x, y)   : return 1;
//
//       }
//}






int execute (Statement s)
{
   
# line 82 "inter.cpp"

// GENERATED FROM SOURCE LINE 37
{
Statement tmp8;
tmp8 = s;
{
Statement tmp9;
if (tmp8->tag != showstatus_tag) goto EndOfRule10;
# line 38 "inter.m"

	 show();
      
# line 95 "inter.cpp"
goto EndOfMatch43;
EndOfRule10 : ;
}
{
Statement tmp11;
if (tmp8->tag != test_tag) goto EndOfRule12;
# line 40 "inter.m"

	show();      
      
# line 106 "inter.cpp"
goto EndOfMatch43;
EndOfRule12 : ;
}
{
Statement tmp15;
Statement s;
Statement tmp13;
Statement c;
Statement tmp14;
if (tmp8->tag != dountilstmt_tag) goto EndOfRule16;
tmp13 = ((dountilstmt_subtype) tmp8)->body;
tmp14 = ((dountilstmt_subtype) tmp8)->cond;
s = tmp13;
c = tmp14;
# line 42 "inter.m"

	{int cnt = 0; do { execute(s); cnt++;}  while(execute(c) && (cnt < 25));} return 0;
      
# line 125 "inter.cpp"
goto EndOfMatch43;
EndOfRule16 : ;
}
{
Statement tmp19;
Statement s1;
Statement tmp17;
Statement s2;
Statement tmp18;
if (tmp8->tag != seq_tag) goto EndOfRule20;
tmp17 = ((seq_subtype) tmp8)->s1;
tmp18 = ((seq_subtype) tmp8)->s2;
s1 = tmp17;
s2 = tmp18;
# line 44 "inter.m"

	 execute(s1); execute(s2);
      
# line 144 "inter.cpp"
goto EndOfMatch43;
EndOfRule20 : ;
}
{
Statement tmp22;
Expression x;
Expression tmp21;
if (tmp8->tag != mt_tag) goto EndOfRule23;
tmp21 = ((mt_subtype) tmp8)->x;
x = tmp21;
# line 46 "inter.m"

	  return move_table(evaluate_string(x));
      
# line 159 "inter.cpp"
goto EndOfMatch43;
EndOfRule23 : ;
}
{
Statement tmp25;
Expression x;
Expression tmp24;
if (tmp8->tag != ms_tag) goto EndOfRule26;
tmp24 = ((ms_subtype) tmp8)->x;
x = tmp24;
# line 48 "inter.m"

	  return move_stack(evaluate_string(x));
      
# line 174 "inter.cpp"
goto EndOfMatch43;
EndOfRule26 : ;
}
{
Statement tmp29;
Expression x;
Expression tmp27;
Expression y;
Expression tmp28;
if (tmp8->tag != eque_tag) goto EndOfRule30;
tmp27 = ((eque_subtype) tmp8)->x;
tmp28 = ((eque_subtype) tmp8)->y;
x = tmp27;
y = tmp28;
# line 50 "inter.m"
  
	return compare_sensors(evaluate_string(x),evaluate_string(y));
      
# line 193 "inter.cpp"
goto EndOfMatch43;
EndOfRule30 : ;
}
{
Statement tmp33;
Statement x;
Statement tmp31;
Statement y;
Statement tmp32;
if (tmp8->tag != equs_tag) goto EndOfRule34;
tmp31 = ((equs_subtype) tmp8)->s1;
tmp32 = ((equs_subtype) tmp8)->s2;
x = tmp31;
y = tmp32;
# line 52 "inter.m"
  
	return execute(x) == execute(y);
      
# line 212 "inter.cpp"
goto EndOfMatch43;
EndOfRule34 : ;
}
{
Statement tmp36;
Statement x;
Statement tmp35;
if (tmp8->tag != ne_tag) goto EndOfRule37;
tmp35 = ((ne_subtype) tmp8)->s1;
x = tmp35;
# line 54 "inter.m"

	return !execute(x);
      
# line 227 "inter.cpp"
goto EndOfMatch43;
EndOfRule37 : ;
}
{
Statement tmp39;
Expression x;
Expression tmp38;
if (tmp8->tag != nee_tag) goto EndOfRule40;
tmp38 = ((nee_subtype) tmp8)->x;
x = tmp38;
# line 56 "inter.m"

	return negate(evaluate_string(x));
       
# line 242 "inter.cpp"
goto EndOfMatch43;
EndOfRule40 : ;
}
{
Statement tmp41;
if (tmp8->tag != empty_tag) goto EndOfRule42;
# line 58 "inter.m"

	return 0;
   
# line 253 "inter.cpp"
goto EndOfMatch43;
EndOfRule42 : ;
}
MatchError("inter.m", 37);
EndOfMatch43 : ;
}
# line 60 "inter.m"


   
}





















