#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <sstream>


namespace Computus
{ 
  
  struct YearOutOfRangeException;
  struct UnknownError;
  
  std::string computeCatholic (int year);
  std::string computeOrtodox (int year);

  struct Date;
    
  void checkYear(int year);
  Date doGauss (int year, int M, int N);
  Date julianToGregorian (Date);
}

struct Computus::Date
{
  Date(int day, int month, int year):
    year(year),
    month(month),
    day(day)
  {};
  int year;
  int month;
  int day;
  std::string toString();
};

struct Computus::YearOutOfRangeException: public std::exception
{
  std::string what() { return "Prosze podac date z zakresu 33-2999.\n"; }
};

struct Computus::UnknownError: public std::exception
{
  std::string what() { return "Wystapil nieoczekiwany blad. Prawdopodobnie zostalem zle zaprogramowany. :(\n"; }
};