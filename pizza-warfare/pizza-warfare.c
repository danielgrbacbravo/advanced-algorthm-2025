#include "stdio.h"
#include <stdlib.h>

typedef struct computer {
  int burst_size;
  int burst_frequency;
} Computer;

Computer *scan_computers(int number_of_computers) {
  Computer *computers = malloc(number_of_computers * sizeof(Computer));
  if (computers == NULL) {
    return NULL;
  }

  for (int i = 0; i < number_of_computers; i++) {
    scanf("%i,%i", &computers[i].burst_size, &computers[i].burst_frequency);
  }

  return computers;
}

int count_requests_up_to(int target_sum, int time, int number_of_computers,
                              Computer *computers) {
  int request_sum;
  for (int i = 0; i < number_of_computers; i++) {

    int bursts = time / computers[i].burst_frequency;
    request_sum += bursts * computers[i].burst_size;

    if (request_sum >= target_sum) {
      break;
    }

  }
  return request_sum;
}


int search_request_space(int target_sum, int number_of_computers, Computer* computers){
    
    
    
    
}

int main(void) {

  int target_requests = 0;
  int number_of_computers = 0;

  scanf("%i", &target_requests);
  scanf("%i", &number_of_computers);

  Computer *computers = scan_computers(number_of_computers);
  if(computers == NULL){
      return 1;
  }

  free(computers);
  return 0;
}
