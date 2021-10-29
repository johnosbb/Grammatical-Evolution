/********************************************************************/
/*             FILE   : LINKED_LIST.HPP (HEADER FILE)               */
/*             AUTHOR : J.J. COLLINS                                */
/*             DATE   : OCTOBER 1997                                */
/*  ============================================================    */
/*  FUNCTIONALITY: Linked lists using dynamic allocation.           */
/*                                                                  */
/* Two classes are used:                                            */
/*  1. Node ... nodes of the list                                   */
/*  2. List ... data structure representing the list itself.        */
/* NOTE: does not use an iterator for efficiency.                   */
/*                                                                  */
/* In this implementation, the data content of each node is a       */
/* single integer in a variable called field. The set of            */
/* operations performable on instances of class List:               */
/*  1. point_to_head() - sets current pointer to the first node.    */
/*  2. point_to_tail() - sets current pointer to the last node.     */
/*  3. at_start() - checks if current pointer is pointing to        */
/*                  first node in the list.                         */
/*  4. at_end() - checks if current pointer is pointing to last     */
/*                node in the list.                                 */
/*  5. ++     - advances the current position to the next node.     */
/*  6. get_current_item() - retrieves the information in the node   */
/*                          that current points to.                 */
/*  7. insert(...) - inserts a new node sorted                      */
/*  8. removeNode() - removes the current node and returns the      */
/*                    contained in the node.                        */
/*  9. isEmpty() - True if list has no nodes.                       */
/********************************************************************/

#include <iostream.h>
#include <stdio.h>
#include "defines.h"

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
 
/********************************************************************/
class Node
{
  private:
    bit field; 
    Node *next;
  public:
    Node(bit b) { field = b; };
    friend class List;
};
/********************************************************************/

class List
{
  private:
    Node *start;
    Node *current;
  public:
    List() { start=NULL; current=NULL;};
    ~List();  
    int start_equals_current();
    void prepend(bit b);
    void insert(bit b);
    bit removeNode();
    void swap(const int pos1, const int pos2, const int len);
    bit  get_current_element(void);
    void  change(const bit b);
    List& operator++(); 
    List& operator--();
    int at_end();
    int at_start();
    int isEmpty() { return start==NULL; }; 
    void point_to_head(void) { current = start; };
    void point_to_tail();
    void traverse_list(const int num);
    void print_list();
    void display_list(FILE *fp);
    friend ostream& operator<<(ostream &os, const List &l);
};
/********************************************************************/
#endif





