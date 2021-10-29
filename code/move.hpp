#ifndef _MOVE_HPP_
#define _MOVE_HPP_
#include <string>


int move_table(string block);
int move_stack(string block);
int show(void);
void update();
string get_next_needed();
string get_top_block();
string get_current_stack();
int compare_sensors(string x, string y);
int negate(string s);
int set_common_parameters(char parameter[], char value[]);
int load_data(void);
int load_file (char filename[]);
void check_goal(void);
int calculate_score(void);
int process_expression(char theExpr[]);


#endif // _MOVE_HPP_







