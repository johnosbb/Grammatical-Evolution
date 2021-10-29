// FrequencyDistributionElement
#include "FrequencyDistributionElement.hpp"
#include "defines.h"
#include <iostream.h>



// Class FrequencyDistributionElement 

FrequencyDistributionElement::FrequencyDistributionElement()
  :frequency(1)
{
}

FrequencyDistributionElement::FrequencyDistributionElement(double val, int freq)
{
  value = val;
  frequency = freq;
}

FrequencyDistributionElement::FrequencyDistributionElement(const FrequencyDistributionElement &right)
{
  frequency = right.frequency;
  value = right.value;
  
}


FrequencyDistributionElement::~FrequencyDistributionElement()
{
}

void FrequencyDistributionElement::increment_frequency(void)
{
  frequency+=1;
}


int FrequencyDistributionElement::get_frequency(void)
{
  return frequency;
}


bool FrequencyDistributionElement::check_value(double val)
{
  bool result = false;
  if(val == value)
    result = true;
  return result;
  
}


void  FrequencyDistributionElement::set_value(double val)
{
  value = val;
}

void  FrequencyDistributionElement::set(double val,int freq)
{
  value = val;
  frequency = freq;
  
}

double  FrequencyDistributionElement::get_value(void)
{
  return value;
}











