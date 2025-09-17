
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int grade;
  int number_of_students_left;

} Student;

Student *read_students(int number_of_students) {
  Student *students = malloc(sizeof(Student) * number_of_students);
  if (!students) {
    return NULL;
  }
  for (int i = 0; i < number_of_students; i++) {
    scanf("%i %i", &students[i].grade, &students[i].number_of_students_left);
  }
  return students;
}

int *grades_by_leave_order(Student *students, int number_of_students) {
  int *grades = malloc(sizeof(int) * number_of_students);
  if (!students) {
    return NULL;
  }

  for (int i = 0; i < number_of_students; i++) {
    grades[students[i].number_of_students_left] = students[i].grade;
  }

  return grades;
};

int main(void) {
  int number_of_students = 0;
  int target_grade_difference = 0;

  scanf("%i %i", &number_of_students, &target_grade_difference);

  Student *students = read_students(number_of_students);
  if (!students) {
    return 1;
  }

  int *grades = grades_by_leave_order(students, number_of_students);

  free(grades);
  free(students);
  return 0;
}
