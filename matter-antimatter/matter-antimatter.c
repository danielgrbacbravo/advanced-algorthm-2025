#include <stdio.h>
#include <stdlib.h>

#define NO_ROBOTS -1

static inline int calculate_robots_after_interaction(int antimatter_robots,
                                                     int cell_content) {
  if (antimatter_robots <= 0)
    return NO_ROBOTS;
  if (cell_content == 0)
    return NO_ROBOTS; // barrier
  if (cell_content > 0)
    return antimatter_robots + cell_content; // merge with antimatter robots
  int robots_after_annihilation = antimatter_robots + cell_content;
  if (robots_after_annihilation <= 0)
    return NO_ROBOTS;
  return robots_after_annihilation;
}

int main(void) {
  int grid_rows, grid_columns;
  if (scanf("%d %d", &grid_rows, &grid_columns) != 2)
    return 0;

  int *previous_row_cells = malloc(grid_columns * sizeof(int));
  int *current_row_cells = malloc(grid_columns * sizeof(int));
  int *previous_row_robots = malloc(grid_columns * sizeof(int));
  int *current_row_robots = malloc(grid_columns * sizeof(int));

  // Read first row
  for (int column = 0; column < grid_columns; column++) {
    scanf("%d", &previous_row_cells[column]);
    previous_row_robots[column] = NO_ROBOTS;
  }
  previous_row_robots[0] = previous_row_cells[0];
  // Propagate right for the first row
  for (int column = 1; column < grid_columns; column++) {
    if (previous_row_robots[column - 1] >= 1)
      previous_row_robots[column] = calculate_robots_after_interaction(
          previous_row_robots[column - 1] - 1, previous_row_cells[column]);
    else
      previous_row_robots[column] = NO_ROBOTS;
  }

  for (int row = 1; row < grid_rows; row++) {
    // Read current row
    for (int column = 0; column < grid_columns; column++) {
      scanf("%d", &current_row_cells[column]);
      current_row_robots[column] = NO_ROBOTS;
    }

    // First column: only from top
    if (previous_row_robots[0] >= 1)
      current_row_robots[0] = calculate_robots_after_interaction(
          previous_row_robots[0] - 1, current_row_cells[0]);
    else
      current_row_robots[0] = NO_ROBOTS;

    // Rest of the row
    for (int column = 1; column < grid_columns; column++) {
      int max_robots_reaching_cell = NO_ROBOTS;
      // From top
      if (previous_row_robots[column] >= 1) {
        int robots_from_top = calculate_robots_after_interaction(
            previous_row_robots[column] - 1, current_row_cells[column]);
        if (robots_from_top > max_robots_reaching_cell)
          max_robots_reaching_cell = robots_from_top;
      }
      // From left
      if (current_row_robots[column - 1] >= 1) {
        int robots_from_left = calculate_robots_after_interaction(
            current_row_robots[column - 1] - 1, current_row_cells[column]);
        if (robots_from_left > max_robots_reaching_cell)
          max_robots_reaching_cell = robots_from_left;
      }
      current_row_robots[column] = max_robots_reaching_cell;
    }

    // Swap rows and DP arrays for next iteration
    int *swap_cells = previous_row_cells;
    previous_row_cells = current_row_cells;
    current_row_cells = swap_cells;
    int *swap_robots = previous_row_robots;
    previous_row_robots = current_row_robots;
    current_row_robots = swap_robots;
  }

  int max_robots_at_goal = previous_row_robots[grid_columns - 1];
  free(previous_row_cells);
  free(current_row_cells);
  free(previous_row_robots);
  free(current_row_robots);

  // If no robots reach the end, print 1 (guaranteed by constraints)
  if (max_robots_at_goal < 1)
    printf("1\n");
  else
    printf("%d\n", max_robots_at_goal);

  return 0;
}
