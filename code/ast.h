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
