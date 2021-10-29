#include "TabuList.hpp"
#include "defines.h"
#include <algorithm>


TabuList::TabuList()
        : default_tenure(5)
{
}

TabuList::TabuList(const TabuList &right)
        :  default_tenure(5)
{
  default_tenure = right.default_tenure;
  
}

TabuList::~TabuList()

{
}



void TabuList::add_genome(Genome right)
{
  right.set_tenure(default_tenure);
  the_list.push_back(right);
}

int TabuList::purge(void)
{
  genomelist::iterator iter;
  iter = the_list.begin();
  while(iter != the_list.end())
    {  
      if((*iter).get_tenure() < 1)
	{
	the_list.erase(iter);
        iter = the_list.begin();
	}
       iter++;
    }
  return OKAY;
  
}

bool  TabuList::check(const Genome &right)
{
  bool result = true;
  genomelist::iterator iter;
  iter = find(the_list.begin() , the_list.end(),right);
  if(iter == the_list.end())
    result = false;
  return result;
  
}

void  TabuList::show_contents(void)
{
  genomelist::iterator iter;
  iter = the_list.begin();
  cout << "Tabu list contents:______Tenure___________Score " << endl;
  while(iter!= the_list.end())
    {  
      cout << *iter << "  " << (*iter).get_tenure() <<  "  " << (*iter).get_score() << endl;
      iter++;
      
    }
  
}

void  TabuList::dcr_tabu_tenure(void)
{
  genomelist::iterator iter;
  iter = the_list.begin();
  while(iter!= the_list.end())
    {  
      (*iter).dcr_tenure();
      iter++;
    }
  
}













