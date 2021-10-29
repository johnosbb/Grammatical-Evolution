/********************************************************************/
/*             FILE   : LINKED_LIST.CC (IMPLEMENTATION FILE)        */
/*             AUTHOR : J.J. COLLINS                                */
/*             DATE   : FEBRUARY 1998                               */
/*  ============================================================    */
/*  FUNCTIONALITY: Implementation of functions for Linked lists     */
/*  using dynamic allocation; as defined in header file.            */
/********************************************************************/

#include <iostream.h>
#include <stdlib.h>
#include "linked_list.hpp"
#include "params.h"
/********************************************************************/
List::~List()
{ 
  /*------------------------------------------------------*/
  /* DESTRUCTOR: deallocates  memory.                     */
  /*------------------------------------------------------*/ 
  bit b = F;
  point_to_tail();
  while(!isEmpty()) { b = removeNode();}
  //cout << "\n after invoking LINKED LIST DESTRUCTOR";
}
/********************************************************************/
int List::start_equals_current()
{
  return (start == current);
}
/********************************************************************/
void List::prepend(bit b)
{
  Node *new_np = new Node(b);
  new_np->next = start;
  start = new_np;
  current = new_np;
}
/********************************************************************/
void List::insert(bit b)
{
  /*------------------------------------------------------*/
  /* Inserts a bit after the node that current points to. */
  /*------------------------------------------------------*/       
  if(start == NULL) {
    Node *new_np = new Node(b);
    new_np->next = start;
    start = new_np;
    current = start;
  }
  else {
    Node *new_np = new Node(b);
    new_np->next = current->next;
    current->next = new_np;
    current = new_np;
  }
}
/********************************************************************/
bit List::removeNode()
{
  /*------------------------------------------------------*/
  /* Removes the node that current points to in the list. */
  /*------------------------------------------------------*/
  bit b;
  if(start == NULL || current == NULL) {
    cout << "\n Cannot delete non-existent node in class LinkedList";
    exit(1);
  }
  if(current == start) {
    b  = current->field;
    start = current->next;
    delete current;
    current = start;
    return b;
  }
  Node *cursor = start;
  Node *previous = NULL;
  b = current->field;
  while(cursor != current) {
    previous = cursor;
    cursor = cursor->next;
  }
  previous->next = current->next;
  delete current;
  current = previous;
  return b;
}
/********************************************************************/
void List::swap(const int pos1, const int pos2, const int len)
{
 Node *p1 = start;
 Node *p2 = start;
 // printf("\n linked list : pos1 = %d, pos2 = %d",pos1,pos2);
 for(int count1 = 0; count1 < pos1; count1++) p1 = p1->next;
 for(int count2 = 0; count2 < pos2; count2++) p2 = p2->next;
 if((p1 == NULL)||(p2 == NULL)) {
   cout << "\n ERROR: lost pointer when swapping";
   exit(1);
 }
 for(int num=0; num < len; num++) {
   bit b1 = p1->field;
   bit b2 = p2->field;
   p1->field = b2;
   p2->field = b1;
   p1 = p1->next;
   p2 = p2->next;
   // printf("   num = %d",num);
   if(((p1 == NULL)||(p2 == NULL))&&(num != len -1)) {
     cout << "\n ERROR: lost pointer when swapping";
     exit(1);
   }
 }
}
/********************************************************************/
bit List::get_current_element(void)
{
  /*------------------------------------------------------*/
  /* Returns the value of the node that current points to,*/
  /* without removing the node or advancing current.      */
  /* To speedup, remove error checking.                   */
  /*------------------------------------------------------*/
  if(isEmpty())  {
    cout << "\n ERROR: cannot retrieve copy of node element (1).";
    exit(1);
  }  
  if(current == NULL) {
    cout << "\n ERROR: cannot retrieve copy of node element (2).";
    exit(1);
  }
  return current->field;
}
/********************************************************************/
void List::change(const bit b)
{
  if(isEmpty())  {
    cout << "\n ERROR: cannot change node data (1).";
    exit(1);
  }  
  if(current == NULL) {
    cout << "\n ERROR: cannot change node data (2).";
    exit(1);
  }
  current->field = b;
}
/********************************************************************/
int List::at_start()
{
  /*------------------------------------------------------*/
  /* Checks if current points to first node in the list.  */
  /*------------------------------------------------------*/
  if(current == start) return 1;
  else return 0;
}
/********************************************************************/
int List::at_end()
{
  /*------------------------------------------------------*/
  /* Checks if current points to the last node in the list*/
  /* (which could be the same as start if list empty).    */
  /*------------------------------------------------------*/
  if(current->next == NULL) return 1;
  else return 0;
}
/********************************************************************/
void List::point_to_tail()
{
  /*------------------------------------------------------*/
  /* Sets current to point to last node in the list.      */
  /*------------------------------------------------------*/
  if(start != NULL) {
    Node *temp;
    temp = start;
    while(temp->next != NULL)
      temp = temp->next;
    current = temp;
  }
}
/********************************************************************/
void List::traverse_list(const int num)
{
  point_to_head();
  int i = 1;
  while((i < num)&&(current != NULL)) { 
    current = current->next;
    i += 1;
  }
  if(i != num) {
    cout << "\n ERROR: cannot traverse list to specified node";
    exit(1);
  }
}
/********************************************************************/
List& List::operator++()
{
  /*------------------------------------------------------*/
  /* Advances current to point to the next node in the    */
  /* List from which it current points to.                */
  /*------------------------------------------------------*/
  if(start == NULL) {
    cout << "\n error: unable to increment - empty list";
    exit(1);
  }
  if(current == NULL) {
    cout << "\n error: unable to increment - current = NULL";
    exit(1);
  }
  if(current->next == NULL) {
    // cout << "\n error: unable to increment beyond end of list";
    return *this;
  }
  else {
    current = current->next;
    return *this;
  }
}
/********************************************************************/
List& List::operator--()
{
  /*------------------------------------------------------*/
  /* Decrements current to point to the previous node in  */
  /* the List from which it currently points to.          */
  /*------------------------------------------------------*/
  //printf("\n OPERATOR -- ");
  //printf("\n OPERATOR -- ");

  if(start == NULL) {
    cout << "\n error: unable to decrement - empty list";
    exit(1);
  }
  if(current == NULL) {
    cout << "\n error: unable to decrement - current = NULL";
    exit(1);
  }
  if(current == start) {
    cout << "\n error: unable to decrement beyond start of list";
    exit(1);
  }

  Node *temp = start;

  //printf("\n about to start iterations");
  //printf("\n about to start iterations");


  while(temp->next != current) {
    if(temp->next == NULL) {
      cout << "\n error: lost pointer";
      exit(1);
    }
    //printf("\n looping looping ");
    temp = temp->next;
  }

  //printf("\n finished iterations");
  //printf("\n finished iterations");

  current = temp;
  return *this;

  //printf("\n finished OPERATOR --");
  //printf("\n finished OPERATOR --");

}
/********************************************************************/
void List::print_list()
{
  /*------------------------------------------------------*/
  /* Debugging tool - print out to standard output all the*/
  /* node data fields in the list, from head to tail.     */
  /* Needed if list is inherited, then no direct access   */
  /* to the friend function ostream& operator<<(....)     */
  /*------------------------------------------------------*/
  cout << "\n The List is: { ";
  point_to_head();
  //  while(!at_end()) {
  while(current != NULL){
    cout << get_current_element();
    current = current->next;
  }
  cout << " } ";
  point_to_head();
}
/********************************************************************/
void List::display_list(FILE *fp)
{
  Node *temp = start;
  fprintf(fp,"\n  .... the list is: ");
  while(temp != NULL) {
    fprintf(fp,"%d",temp->field);
    temp = temp->next;
  }
temp = NULL;
}
/********************************************************************/
ostream& operator<<(ostream &os, const List &l)
{
  /*------------------------------------------------------*/
  /* Friend function to output list elements.             */
  /*------------------------------------------------------*/
  List li(l);
  os << "\n The List is: {";
  bit b;
  for(li.point_to_head(); !li.at_end(); ++li) {
    b = li.get_current_element();
    if(b == 1) os << "T";
    else {
      if(b==0) os << "F";
      else {
	cout << "\n ERROR: exiting!";
	exit(1);
      }
    }
  }
  os << "}\n";
  return os;
}
/********************************************************************/
