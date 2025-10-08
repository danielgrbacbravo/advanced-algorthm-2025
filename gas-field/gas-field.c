#include <stdint.h>
#include <stdio.h>

const int valid_masks[5] = {0b000, 0b001, 0b010, 0b100, 0b101};

void compute_profit_configurations(uint64_t a, uint64_t b, uint64_t c, uint64_t profit[5]) {
    // configurations
    // 000,001,010,100,101
    profit[0] = 0;
    profit[1] = c;
    profit[2] = b;
    profit[3] = a;
    profit[4] = a + c;
  }

void compute_optimal_configuration_set(uint64_t current_row[5], uint64_t previous_row[5], uint64_t profit_configurations[5]){
    for(int i = 0; i < 5; i ++){
        int mask_for_current = valid_masks[i];
        uint64_t previous_best = 0;

        // look at all possible previous-row configurations
        for(int j = 0; j < 5; j++){
           int mask_for_previous = valid_masks[j];
           int compatible = (mask_for_previous & mask_for_current) == 0;

           if(compatible){
               if(previous_row[j] > previous_best){
                   previous_best = previous_row[j];
               }
           }
        }
        current_row[i] = profit_configurations[i] + previous_best;
    }
}

int main(void) {
  int number_of_rows = 0;
  // this stores the profit for each configuration
  // we have 5 valid configurations for each row
  // 001, 010, 100,101 and 000
  // the idea is that the independent set only cares about its previous row
  // configuration and its current
  uint64_t previous_row[5] = {0};
  uint64_t current_row[5] = {0};
  uint64_t profit_configurations[5] = {0};
  scanf("%i", &number_of_rows);
  for (int i = 0; i < number_of_rows; i++) {
    uint64_t a = 0, b = 0, c = 0;
    scanf("%llu %llu %llu", &a, &b, &c);

    compute_profit_configurations(a, b, c, profit_configurations);
    compute_optimal_configuration_set(current_row, previous_row, profit_configurations);

    for (int m = 0; m < 5; m++){
        previous_row[m] = current_row[m];
    }
  }

  uint64_t answer = 0;
  for (int m = 0; m < 5; m++){
      if (previous_row[m] > answer) answer= previous_row[m];
  }

  printf("%llu\n", answer);
  return 0;
}
