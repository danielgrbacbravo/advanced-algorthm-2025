#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int length;
  int *sequence;
} LISResult;

int *read_cards(int number_of_cards) {
  int *cards = malloc(sizeof(int) * number_of_cards);
  if (!cards) {
    return NULL;
  }
  for (int i = 0; i < number_of_cards; i++) {
    scanf("%i", &cards[i]);
  }
  return cards;
}
int binary_search(int *indices_array, int array_size, int *values_array,
                  int target_value) {
  int left_boundary = 0, right_boundary = array_size - 1;
  while (left_boundary <= right_boundary) {
    int middle_index = (left_boundary + right_boundary) / 2;
    if (values_array[indices_array[middle_index]] >= target_value)
      right_boundary = middle_index - 1;
    else
      left_boundary = middle_index + 1;
  }
  return left_boundary;
}

static int build_lis_structure(int *input_array, int array_length,
                               int *parent_indices,
                               int *subsequence_tail_indices) {
  int current_subsequence_length = 0;

  for (int current_index = 0; current_index < array_length; current_index++) {
    int insertion_position =
        binary_search(subsequence_tail_indices, current_subsequence_length,
                      input_array, input_array[current_index]);
    parent_indices[current_index] =
        (insertion_position > 0)
            ? subsequence_tail_indices[insertion_position - 1]
            : -1;
    subsequence_tail_indices[insertion_position] = current_index;
    if (insertion_position == current_subsequence_length)
      current_subsequence_length++;
  }

  return current_subsequence_length;
}

static void reconstruct_lis(int *input_array, int *parent_indices,
                            int *subsequence_tail_indices,
                            int current_subsequence_length, LISResult *result) {
  result->length = current_subsequence_length;
  result->sequence = (int *)malloc(current_subsequence_length * sizeof(int));

  int backtrack_index =
      subsequence_tail_indices[current_subsequence_length - 1];
  for (int result_index = current_subsequence_length - 1; result_index >= 0;
       result_index--) {
    result->sequence[result_index] = input_array[backtrack_index];
    backtrack_index = parent_indices[backtrack_index];
  }
}

LISResult longest_increasing_subsequence(int *input_array, int array_length) {
  LISResult result = {0, NULL};

  if (array_length == 0)
    return result;

  int *parent_indices = (int *)malloc(array_length * sizeof(int));
  int *subsequence_tail_indices = (int *)malloc(array_length * sizeof(int));

  int current_subsequence_length = build_lis_structure(
      input_array, array_length, parent_indices, subsequence_tail_indices);

  reconstruct_lis(input_array, parent_indices, subsequence_tail_indices,
                  current_subsequence_length, &result);

  free(parent_indices);
  free(subsequence_tail_indices);
  return result;
}

int main(void) {
  int number_of_cards = 0;
  scanf("%i", &number_of_cards);
  int *cards = read_cards(number_of_cards);
  if (!cards) {
    return 1;
  }
  LISResult card_sequence =
      longest_increasing_subsequence(cards, number_of_cards);
  int red_score = card_sequence.sequence[card_sequence.length - 1] -
                  card_sequence.sequence[0];
  printf("%d %d\n", card_sequence.length, red_score);
  free(card_sequence.sequence);
  free(cards);
  return 0;
}
