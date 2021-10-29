


#ifndef FrequencyDistributionElement_h
#define FrequencyDistributionElement_h 1


class FrequencyDistributionElement 

{

  public:
      FrequencyDistributionElement();
      FrequencyDistributionElement(double val, int freq);
      FrequencyDistributionElement(const FrequencyDistributionElement &right);
      int get_frequency(void);
      virtual ~FrequencyDistributionElement();
      void increment_frequency(void);
      bool check_value(double val);
      void set_value(double val);
      double get_value(void);
      void set(double val,int freq);  

    // Additional Public Declarations
  
  protected:
    // Additional Protected Declarations

  private:
  double value;
  int frequency;
  
  
    // Additional Private Declarations


    // Additional Implementation Declarations

};


// Class FrequencyDistributionElement 



#endif













