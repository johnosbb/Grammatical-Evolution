typedef class Statement_struct *Statement;
typedef class Expression_struct *Expression;
# line 1 "ast.m"

# line 6 "ast.cpp"
extern void MatchError(char *, int);
struct Statement_struct {
   int tag;
};
struct dountilstmt_struct : Statement_struct {
   Statement body;
   Statement cond;
   dountilstmt_struct(
      Statement body,
      Statement cond
   );
};
typedef dountilstmt_struct *dountilstmt_subtype;
#define dountilstmt_tag 1
extern "C" dountilstmt_struct *dountilstmt (
      Statement body,
      Statement cond
);
struct seq_struct : Statement_struct {
   Statement s1;
   Statement s2;
   seq_struct(
      Statement s1,
      Statement s2
   );
};
typedef seq_struct *seq_subtype;
#define seq_tag 2
extern "C" seq_struct *seq (
      Statement s1,
      Statement s2
);
struct mt_struct : Statement_struct {
   Expression x;
   mt_struct(
      Expression x
   );
};
typedef mt_struct *mt_subtype;
#define mt_tag 3
extern "C" mt_struct *mt (
      Expression x
);
struct ms_struct : Statement_struct {
   Expression x;
   ms_struct(
      Expression x
   );
};
typedef ms_struct *ms_subtype;
#define ms_tag 4
extern "C" ms_struct *ms (
      Expression x
);
struct equs_struct : Statement_struct {
   Statement s1;
   Statement s2;
   equs_struct(
      Statement s1,
      Statement s2
   );
};
typedef equs_struct *equs_subtype;
#define equs_tag 5
extern "C" equs_struct *equs (
      Statement s1,
      Statement s2
);
struct eque_struct : Statement_struct {
   Expression x;
   Expression y;
   eque_struct(
      Expression x,
      Expression y
   );
};
typedef eque_struct *eque_subtype;
#define eque_tag 6
extern "C" eque_struct *eque (
      Expression x,
      Expression y
);
struct ne_struct : Statement_struct {
   Statement s1;
   ne_struct(
      Statement s1
   );
};
typedef ne_struct *ne_subtype;
#define ne_tag 7
extern "C" ne_struct *ne (
      Statement s1
);
struct nee_struct : Statement_struct {
   Expression x;
   nee_struct(
      Expression x
   );
};
typedef nee_struct *nee_subtype;
#define nee_tag 8
extern "C" nee_struct *nee (
      Expression x
);
struct showstatus_struct : Statement_struct {
   showstatus_struct(
   );
};
typedef showstatus_struct *showstatus_subtype;
#define showstatus_tag 9
extern "C" showstatus_struct *showstatus (
);
struct test_struct : Statement_struct {
   test_struct(
   );
};
typedef test_struct *test_subtype;
#define test_tag 10
extern "C" test_struct *test (
);
struct empty_struct : Statement_struct {
   empty_struct(
   );
};
typedef empty_struct *empty_subtype;
#define empty_tag 11
extern "C" empty_struct *empty (
);
dountilstmt_struct::dountilstmt_struct (
   Statement body_value,
   Statement cond_value
)
{
   tag = dountilstmt_tag;
   body = body_value;
   cond = cond_value;
}
dountilstmt_struct *dountilstmt (
   Statement body_value,
   Statement cond_value
)
{
   return new dountilstmt_struct (
   body_value,
   cond_value
   );
}
seq_struct::seq_struct (
   Statement s1_value,
   Statement s2_value
)
{
   tag = seq_tag;
   s1 = s1_value;
   s2 = s2_value;
}
seq_struct *seq (
   Statement s1_value,
   Statement s2_value
)
{
   return new seq_struct (
   s1_value,
   s2_value
   );
}
mt_struct::mt_struct (
   Expression x_value
)
{
   tag = mt_tag;
   x = x_value;
}
mt_struct *mt (
   Expression x_value
)
{
   return new mt_struct (
   x_value
   );
}
ms_struct::ms_struct (
   Expression x_value
)
{
   tag = ms_tag;
   x = x_value;
}
ms_struct *ms (
   Expression x_value
)
{
   return new ms_struct (
   x_value
   );
}
equs_struct::equs_struct (
   Statement s1_value,
   Statement s2_value
)
{
   tag = equs_tag;
   s1 = s1_value;
   s2 = s2_value;
}
equs_struct *equs (
   Statement s1_value,
   Statement s2_value
)
{
   return new equs_struct (
   s1_value,
   s2_value
   );
}
eque_struct::eque_struct (
   Expression x_value,
   Expression y_value
)
{
   tag = eque_tag;
   x = x_value;
   y = y_value;
}
eque_struct *eque (
   Expression x_value,
   Expression y_value
)
{
   return new eque_struct (
   x_value,
   y_value
   );
}
ne_struct::ne_struct (
   Statement s1_value
)
{
   tag = ne_tag;
   s1 = s1_value;
}
ne_struct *ne (
   Statement s1_value
)
{
   return new ne_struct (
   s1_value
   );
}
nee_struct::nee_struct (
   Expression x_value
)
{
   tag = nee_tag;
   x = x_value;
}
nee_struct *nee (
   Expression x_value
)
{
   return new nee_struct (
   x_value
   );
}
showstatus_struct::showstatus_struct (
)
{
   tag = showstatus_tag;
}
showstatus_struct *showstatus (
)
{
   return new showstatus_struct (
   );
}
test_struct::test_struct (
)
{
   tag = test_tag;
}
test_struct *test (
)
{
   return new test_struct (
   );
}
empty_struct::empty_struct (
)
{
   tag = empty_tag;
}
empty_struct *empty (
)
{
   return new empty_struct (
   );
}
# line 14 "ast.m"





# line 310 "ast.cpp"
struct Expression_struct {
   int tag;
};
struct next_needed_struct : Expression_struct {
   next_needed_struct(
   );
};
typedef next_needed_struct *next_needed_subtype;
#define next_needed_tag 1
extern "C" next_needed_struct *next_needed (
);
struct current_stack_struct : Expression_struct {
   current_stack_struct(
   );
};
typedef current_stack_struct *current_stack_subtype;
#define current_stack_tag 2
extern "C" current_stack_struct *current_stack (
);
struct top_block_struct : Expression_struct {
   top_block_struct(
   );
};
typedef top_block_struct *top_block_subtype;
#define top_block_tag 3
extern "C" top_block_struct *top_block (
);
next_needed_struct::next_needed_struct (
)
{
   tag = next_needed_tag;
}
next_needed_struct *next_needed (
)
{
   return new next_needed_struct (
   );
}
current_stack_struct::current_stack_struct (
)
{
   tag = current_stack_tag;
}
current_stack_struct *current_stack (
)
{
   return new current_stack_struct (
   );
}
top_block_struct::top_block_struct (
)
{
   tag = top_block_tag;
}
top_block_struct *top_block (
)
{
   return new top_block_struct (
   );
}
# line 24 "ast.m"










