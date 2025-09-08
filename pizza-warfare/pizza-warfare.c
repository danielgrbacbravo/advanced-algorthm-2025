#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct computer {
  uint64_t burst_size;
  uint64_t burst_frequency;
} Computer;

Computer *scan_computers(uint64_t number_of_computers) {
  Computer *computers = malloc(number_of_computers * sizeof(Computer));
  if (computers == NULL) {
    return NULL;
  }

  for (uint64_t i = 0; i < number_of_computers; i++) {
    scanf("%lu,%lu", &computers[i].burst_size, &computers[i].burst_frequency);
  }

  return computers;
}
__int128 count_requests_up_to(__int128 time, __int128 target_request_count, int number_of_computers,
                              Computer *computers) {
  __int128 request_sum = 0;
  for (int i = 0; i < number_of_computers; i++) {

    __int128 bursts = time / computers[i].burst_frequency;
    request_sum += bursts * computers[i].burst_size;

    if (request_sum >= target_request_count) {
      break;
    }

  }
  return request_sum;
}

 __int128 find_minimum_time_for_requests(uint64_t required_request_count, uint64_t  number_of_computers, Computer* computers){
    // We want to find the minimum time such that count_requests_up_to(time, ...) >= required_request_count
    __int128 min_time = 0;

    // For each computer, calculate the time it would take to produce all required requests alone,
    // then take the minimum of these times as a reasonable upper bound.
    __int128 max_time = 0;
    for (uint64_t i = 0; i < number_of_computers; i++) {
        if (computers[i].burst_size > 0) {
            __int128 bursts_needed = (required_request_count + computers[i].burst_size - 1) / computers[i].burst_size;
            __int128 time_for_computer = bursts_needed * computers[i].burst_frequency;
            if (time_for_computer > max_time) {
                max_time = time_for_computer;
            }
        }
    }
    // If all burst_size are zero (shouldn't happen), fallback to 1
    if (max_time == 0) {
        max_time = 1;
    }

    // Find an upper bound where enough requests have been made
    while (count_requests_up_to(max_time, required_request_count, number_of_computers, computers) < required_request_count) {
        max_time *= 2;
    }

    // Binary search between min_time and max_time
    while (min_time < max_time) {
        __int128 mid_time = min_time + (max_time - min_time) / 2;
        __int128 current_request_count = count_requests_up_to(mid_time, required_request_count, number_of_computers, computers);

        if (current_request_count < required_request_count) {
            min_time = mid_time + 1;
        } else {
            max_time = mid_time;
        }
    }

    // min_time is the minimum time where enough requests have been made
    return min_time;
}

int main(void) {

  uint64_t target_requests = 0;
  int number_of_computers = 0;

  scanf("%lu", &target_requests);
  scanf("%i", &number_of_computers);

  Computer *computers = scan_computers(number_of_computers);
  if(computers == NULL){
      return 1;
  }

  find_minimum_time_for_requests(target_requests, number_of_computers, computers);

  free(computers);
  return 0;
}
