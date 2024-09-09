#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void calculate_balance(int startAge, double * balance, retire_info info) {
  for (int i = 0; i < info.months; i++) {
    int age_years = (startAge + i) / 12;
    int age_months = (startAge + i) % 12;
    printf("Age %3d month %2d you have $%.2f\n", age_years, age_months, *balance);

    *balance += (*balance * info.rate_of_return) + info.contribution;
  }
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  calculate_balance(startAge, &initial, working);
  calculate_balance(startAge + working.months, &initial, retired);
}

int main() {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retired = {384, -4000, 0.01 / 12};

  int startAge = 327;
  double initial_savings = 21345;

  retirement(startAge, initial_savings, working, retired);
  return 0;
}
