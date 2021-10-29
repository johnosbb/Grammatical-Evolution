#include <stdlib.h>
#include <stdio.h>
#include "Random.hpp"


main()
{
  Random r;
  for(int i = 0; i < 10000 ; i++)
    printf("%f\n",r.normal_distr_rand_var(0,.245));
}
