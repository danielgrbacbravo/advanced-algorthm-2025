#include <stdio.h>
#include <stdlib.h>


/* This function reads an integer without any kind of error-checking.
 * It assumes that *integer_pointer is initially set to 0.
 * */
static inline void read_int(int *integer_pointer) {
    int current_character = ' ', sign_of_integer = 1;
    while (current_character == ' ' || current_character == '\n')
        current_character = getchar_unlocked();
    if (current_character == '-')
        sign_of_integer = -1, current_character = getchar_unlocked();
    while (current_character >= '0' && current_character <= '9')
        *integer_pointer = 10 * *integer_pointer + (current_character - '0'), current_character = getchar_unlocked();
    *integer_pointer = sign_of_integer * *integer_pointer;
}

void swap(int *first_integer_pointer, int *second_integer_pointer) {
  int temporary_integer = *first_integer_pointer;
  *first_integer_pointer = *second_integer_pointer;
  *second_integer_pointer = temporary_integer;
}

// Helper function to sort small arrays (size <= 5)
void insertion_sort(int *array_of_integers, int left_index, int right_index) {
  for (int current_index = left_index + 1; current_index <= right_index; current_index++) {
    int key_integer = array_of_integers[current_index];
    int previous_index = current_index - 1;
    while (previous_index >= left_index && array_of_integers[previous_index] > key_integer) {
      array_of_integers[previous_index + 1] = array_of_integers[previous_index];
      previous_index--;
    }
    array_of_integers[previous_index + 1] = key_integer;
  }
}

// Returns the index of the median-of-medians pivot
int median_of_medians(int *array_of_integers, int left_index, int right_index) {
  int number_of_elements = right_index - left_index + 1;
  if (number_of_elements <= 5) {
    insertion_sort(array_of_integers, left_index, right_index);
    return left_index + number_of_elements / 2;
  }

  int number_of_groups = (number_of_elements + 4) / 5;
  for (int group_index = 0; group_index < number_of_groups; group_index++) {
    int group_left_index = left_index + group_index * 5;
    int group_right_index = group_left_index + 4;
    if (group_right_index > right_index) group_right_index = right_index;
    insertion_sort(array_of_integers, group_left_index, group_right_index);
    int median_index_in_group = group_left_index + (group_right_index - group_left_index) / 2;
    swap(&array_of_integers[left_index + group_index], &array_of_integers[median_index_in_group]);
  }
  // Recursively find median of medians
  return median_of_medians(array_of_integers, left_index, left_index + number_of_groups - 1);
}

int partition(int *array_of_integers, int left_index, int right_index, int pivot_index) {
  int pivot_value = array_of_integers[pivot_index];
  swap(&array_of_integers[pivot_index], &array_of_integers[right_index]);
  int store_index = left_index;
  for (int current_index = left_index; current_index < right_index; current_index++) {
    if (array_of_integers[current_index] <= pivot_value) {
      swap(&array_of_integers[store_index], &array_of_integers[current_index]);
      store_index++;
    }
  }
  swap(&array_of_integers[store_index], &array_of_integers[right_index]);
  return store_index; // final position of pivot
}

int quick_select(int *array_of_integers, int left_index, int right_index, int k_th_index) {
  while (left_index <= right_index) {
    int pivot_index = median_of_medians(array_of_integers, left_index, right_index);
    int new_pivot_index = partition(array_of_integers, left_index, right_index, pivot_index);
    if (new_pivot_index == k_th_index) {
      return array_of_integers[new_pivot_index];
    } else if (new_pivot_index > k_th_index) {
      right_index = new_pivot_index - 1;
    } else {
      left_index = new_pivot_index + 1;
    }
  }
  return -1; // shouldn't happen if inputs are valid
}

int main(void) {
  int number_of_metro_stations;
  scanf("%i", &number_of_metro_stations);
  int *metro_station_x_coordinates = calloc(sizeof(int), number_of_metro_stations);
  int *metro_station_y_coordinates = calloc(sizeof(int), number_of_metro_stations);
  if(!metro_station_x_coordinates || !metro_station_y_coordinates){
      return 0;
  }

  for(int metro_station_index = 0; metro_station_index < number_of_metro_stations; metro_station_index++){
    read_int(&metro_station_x_coordinates[metro_station_index]);
    read_int(&metro_station_y_coordinates[metro_station_index]);
  }

  int median_x_coordinate = quick_select(metro_station_x_coordinates, 0, number_of_metro_stations - 1, (number_of_metro_stations - 1) / 2);
  int median_y_coordinate = quick_select(metro_station_y_coordinates, 0, number_of_metro_stations - 1, (number_of_metro_stations - 1) / 2);

  printf("%i %i\n", median_x_coordinate, median_y_coordinate);
  free(metro_station_x_coordinates);
  free(metro_station_y_coordinates);
  return 0;
}
