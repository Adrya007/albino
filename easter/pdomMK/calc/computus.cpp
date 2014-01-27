
#include "computus.h" 

using namespace std;

Computus::Date Computus::julianToGregorian (Computus::Date date)
{
  // uwaga, to NIE JEST uniwersalna funkcja przeliczajaca
  // date julianska dla gergorianska
  // dziala TYLKO dla marca i kwietnia
  int H = date.year / 100;
  int D = H - H/4 - 2;
  date.day += D;
  if(date.month == 3 && date.day > 31)
  {
    date.month = 4;
    date.day -= 31;
  }
  else 
  if(date.month == 4 && date.day > 30)
  {
    date.month = 5;
    date.day -= 30;
  }
  if(date.month == 4 && date.day <= 0)
  {
    date.month = 3;
    date.day += 31;
  }
  else 
  if(date.month == 5 && date.day <= 0)
  {
    date.month = 4;
    date.day -= 30;
  }
  return date;
}

Computus::Date Computus::doGauss(int year, int M, int N)
{
  int a = year % 19;
  int b = year % 4;
  int c = year % 7;
  int d = (19 * a + M) % 30;
  int e = (2 * b + 4 * c + 6 * d + N) % 7;
  
  int day;
  int month;
  
  if(d + e <= 9)
  {
    // marzec
    day = d + e + 22;
    month = 3;
  }
  else
  {
    // kwiecien
    day = d + e - 9;
    month = 4;
    
    // wyjatki:
    if(d == 29 && e == 6)
    {
      // jesli d == 29 i e == 6 to wielkanoc odbywa sie 19 kwietnia, a nie 26 kwietnia
      day = 19;
    }
    else
    if(d == 28 && e == 6 && a > 10)
    {
      // 18 kwietnia, zamiast 25 kwietnia
      day = 18;
    }
  }
  return Computus::Date(day, month, year);
}

std::string Computus::computeCatholic(int year)
{
  checkYear(year);
  int k = floor (year / 100);
  int p = floor ((13 + 8 * k) / 25);
  int q = floor (k/4);
  int M = (15 - p + k - q) % 30;
  int N = (4 + k - q) % 7;
  return doGauss(year, M, N).toString();
}

std::string Computus::computeOrtodox(int year)
{
  checkYear(year);
  // dla julianskiego M i N sa stale
  // ale za to potrzebna jest konwersja na gregorianski
  return julianToGregorian(doGauss(year, 15, 6)).toString();
}

void Computus::checkYear(int year)
{
  if(year < 33 || year >= 3000)
  {
    throw YearOutOfRangeException();
  }
}

std::string Computus::Date::toString()
{
  std::ostringstream ss;
  ss << day;
  if(month == 3)
    ss << " marca ";
  else if(month == 4)
    ss << " kwietnia ";
  else if(month == 5)
    ss << " maja ";
  else 
    throw Computus::UnknownError();
  ss << year;
  return ss.str();
}

