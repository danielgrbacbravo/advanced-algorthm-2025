#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int grade;
  int leave_count_when_left;
  int input_index;
  int respect_count;
} Student;

Student *read_students(int student_count) {
  Student *student_list = malloc(sizeof(Student) * student_count);
  if (!student_list)
    return NULL;

  for (int student_idx = 0; student_idx < student_count; student_idx++) {
    scanf("%d %d", &student_list[student_idx].grade,
          &student_list[student_idx].leave_count_when_left);
    student_list[student_idx].input_index = student_idx;
    student_list[student_idx].respect_count = 0;
  }
  return student_list;
}

Student *sort_by_leave_order(Student *student_list, int student_count) {
  Student *sorted_by_leave = malloc(sizeof(Student) * student_count);
  if (!sorted_by_leave)
    return NULL;

  for (int student_idx = 0; student_idx < student_count; student_idx++) {
    // reverse mapping
    sorted_by_leave[student_count - 1 -
                    student_list[student_idx].leave_count_when_left] =
        student_list[student_idx];
  }
  return sorted_by_leave;
}
int binary_search_first_grade_ge(Student *sorted_students, int student_count,
                                 int grade_threshold) {
  int left = 0, right = student_count;
  while (left < right) {
    int mid = (left + right) / 2;
    if (sorted_students[mid].grade >= grade_threshold)
      right = mid;
    else
      left = mid + 1;
  }
  return left; // if == student_count, none found
}

int compare_grade(const void *a, const void *b) {
  return ((Student *)a)->grade - ((Student *)b)->grade;
}

// Count respects between earlier_leavers and later_leavers
void count_respects(Student *earlier_leavers, int earlier_count,
                    Student *later_leavers, int later_count, int respect_gap) {
  // copy and sort earlier leavers by grade
  Student *sorted_earlier = malloc(earlier_count * sizeof(Student));
  for (int i = 0; i < earlier_count; i++)
    sorted_earlier[i] = earlier_leavers[i];
  qsort(sorted_earlier, earlier_count, sizeof(Student), compare_grade);

  for (int later_idx = 0; later_idx < later_count; later_idx++) {
    int required_grade = later_leavers[later_idx].grade + respect_gap;
    int first_ge_idx = binary_search_first_grade_ge(
        sorted_earlier, earlier_count, required_grade);
    int respect_count = earlier_count - first_ge_idx;
    later_leavers[later_idx].respect_count += respect_count;
  }
  free(sorted_earlier);
}

void merge_by_leave(Student *students, int left_idx, int mid_idx, int right_idx,
                    int respect_gap) {
  int earlier_count = mid_idx - left_idx + 1;
  int later_count = right_idx - mid_idx;

  Student *earlier_leavers = malloc(earlier_count * sizeof(Student));
  Student *later_leavers = malloc(later_count * sizeof(Student));

  for (int i = 0; i < earlier_count; i++)
    earlier_leavers[i] = students[left_idx + i];
  for (int j = 0; j < later_count; j++)
    later_leavers[j] = students[mid_idx + 1 + j];

  // count respects (earlier_leavers, later_leavers)
  count_respects(earlier_leavers, earlier_count, later_leavers, later_count,
                 respect_gap);

  // restore leave order (just concatenate, already in order)
  for (int i = 0; i < earlier_count; i++)
    students[left_idx + i] = earlier_leavers[i];
  for (int j = 0; j < later_count; j++)
    students[left_idx + earlier_count + j] = later_leavers[j];

  free(earlier_leavers);
  free(later_leavers);
}

void merge_sort_by_leave(Student *students, int left_idx, int right_idx,
                         int respect_gap) {
  if (left_idx >= right_idx)
    return;

  int mid_idx = (left_idx + right_idx) / 2;
  merge_sort_by_leave(students, left_idx, mid_idx, respect_gap);
  merge_sort_by_leave(students, mid_idx + 1, right_idx, respect_gap);

  merge_by_leave(students, left_idx, mid_idx, right_idx, respect_gap);
}

int main(void) {
  int student_count, respect_gap;
  scanf("%d %d", &student_count, &respect_gap);

  Student *student_list = read_students(student_count);
  if (!student_list)
    return 1;

  Student *students_by_leave = sort_by_leave_order(student_list, student_count);
  if (!students_by_leave) {
    free(student_list);
    return 1;
  }

  merge_sort_by_leave(students_by_leave, 0, student_count - 1, respect_gap);

  int *respect_results = calloc(student_count, sizeof(int));
  for (int i = 0; i < student_count; i++) {
    respect_results[students_by_leave[i].input_index] =
        students_by_leave[i].respect_count;
  }

  for (int i = 0; i < student_count; i++) {
    printf("%d\n", respect_results[i]);
  }

  free(student_list);
  free(students_by_leave);
  free(respect_results);
  return 0;
}
