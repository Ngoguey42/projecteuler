
#include <iostream>

#define MONDAY 0
#define SUNDAY 6
#define WEEK_SIZE 7

enum month_t {
  JAN, FEB, MAR, APR, MAY, JUN,
  JUL, AUG, SEP, OCT, NOV, DEC,
};

int month_length(int year, month_t m) {
  switch (m) {
  case(FEB):
    if (year % 400 == 0)
      return 29;
    else if (year % 100 == 0)
      return 28;
    else if (year % 4 == 0)
      return 29;
    else
      return 28;
  case(APR):
  case(JUN):
  case(SEP):
  case(NOV):
    return 30;
  default:
    return 31;
  }
}

int main() {
  int day_acc = MONDAY;
  int year_acc = 1900;
  int month_acc = 0;
  int sunday_count = 0;

  auto month_forward = [&]{
    day_acc += month_length(year_acc, static_cast<month_t>(month_acc % 12));
    month_acc++;
    if (month_acc % 12 == 0)
      year_acc++;
  };

  for (int i = 0; i < 12; i++)
    month_forward();
  while (year_acc < 2001) {
    if (day_acc % WEEK_SIZE == SUNDAY) {
      std::cout << "sunday  " << year_acc << " " << month_acc % 12 << std::endl;
      sunday_count++;
    }
    month_forward();
  }
  std::cout << sunday_count << std::endl;
  return 0;
}
