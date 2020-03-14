// Implementatie van standaard functies.

#ifndef StandaardCCVar
#define StandaardCCVar

#include <iostream>
#include <cstdlib>  // voor rand
#include "standaard.h"
using namespace std;

//*************************************************************************

bool integerinbereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde)
{
  if (waarde>=minWaarde && waarde<=maxWaarde)
    return true;
  else
  { cout << variabele << "=" << waarde << ", maar moet in [" << minWaarde
         << "," << maxWaarde << "] liggen." << endl;
    return false;
  }

}  // integerinbereik

//*************************************************************************

int randomgetal (int min, int max)
{ int bereik,
      r;

  bereik = max - min + 1;

  r = ((rand())%bereik) + min;
  return r;

}  // randomgetal

#endif

