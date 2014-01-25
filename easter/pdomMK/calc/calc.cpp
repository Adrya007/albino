#include "computus.h"

using namespace std;

int main(int argc, char *argv[]) try
{
  if(argc != 2)
  {
    throw exception();
  }

  int year = stoi(argv[1]); // stoi - nowe lepsze atoi
  
  cout << "Julian: " << Computus::computeOrtodox(year) << endl;  
  cout << "Gregorian: " << Computus::computeCatholic(year) << endl;
    
  return 0;
}
catch (exception &e)
{
  cout << e.what();
  cout << "Uzycie: " << argv[0] << " rok\n (rok - liczba calkowita z zakresu 33-2999)\n";
  return 1;
}