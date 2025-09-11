#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline int compare_doubles(const void *a, const void *b) {
  double x = *(const double *)a;
  double y = *(const double *)b;
  return (x > y) - (x < y); // 1 if x>y, -1 if x<y, 0 if equal
}

void sort_doubles(double *arr, size_t n) {
  qsort(arr, n, sizeof(double), compare_doubles);
}

double *read_double_array(int length) {
  double *arr = malloc(length * sizeof(double));
  if (!arr)
    return NULL;

  // Read all doubles in a single line for faster input
  for (int i = 0; i < length;) {
    int read = scanf("%lf", &arr[i]);
    if (read == 1) {
      ++i;
    } else {
      // Skip invalid input
      int c;
      while ((c = getchar()) != EOF && c != '\n')
        ;
    }
  }
  return arr;
}

int main(void) {
  double target_final_grade = 0;
  int num_grades = 0;

  scanf("%i %lf", &num_grades, &target_final_grade);
  double *exam_scores = read_double_array(num_grades);
  double *assignment_scores = read_double_array(num_grades);
  double *midterm_scores = read_double_array(num_grades);

  sort_doubles(exam_scores, num_grades);
  sort_doubles(assignment_scores, num_grades);
  sort_doubles(midterm_scores, num_grades);

  // exam^2 + exam*assignment + midterm^2 + midterm*assignment ==
  // target_final_grade can simplify to ( reduces multiplication ops)
  //(exam + midterm)(exam + midterm + assignment) - 3*exam*midterm ==
  // target_final_grade

  double chosen_exam = 0;
  double chosen_midterm = 0;
  double chosen_assignment = 0;

  int found_possible = 0;

  for (int assignment_idx = 0; assignment_idx < num_grades; assignment_idx++) {

    chosen_assignment = assignment_scores[assignment_idx];
    int exam_idx = 0;
    int midterm_idx = num_grades - 1;

    while (exam_idx < num_grades && midterm_idx >= 0) {

      chosen_exam = exam_scores[exam_idx];
      chosen_midterm = midterm_scores[midterm_idx];

      if(chosen_midterm * chosen_assignment > target_final_grade || chosen_exam * chosen_assignment > target_final_grade){
          break;
      }

      double computed_grade =
          (chosen_exam + chosen_midterm) *
              (chosen_exam + chosen_midterm + chosen_assignment) -
          (2 * chosen_exam * chosen_midterm);

      if (fabs(computed_grade - target_final_grade) < 0.005) {
        found_possible = 1;
        break;
      }

      if (computed_grade < target_final_grade) {
        exam_idx++;
      } else {
        midterm_idx--;
      }
    }
    if (found_possible) {
      break;
    }
  }

  if (found_possible) {
    printf("POSSIBLE");
    printf("\n%.1f^2+%.1f*%.1f+%.1f^2+%.1f*%.1f=%.1f\n", chosen_exam,
           chosen_exam, chosen_assignment, chosen_midterm, chosen_midterm,
           chosen_assignment, target_final_grade);
  } else {
    printf("IMPOSSIBLE\n");
  }

  free(exam_scores);
  free(assignment_scores);
  free(midterm_scores);

  return 0;
}
