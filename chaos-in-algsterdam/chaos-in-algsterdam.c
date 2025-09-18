#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int start;        // days since 01.01.2000
  int end;          // days since 01.01.2000
  char company[64]; // enough for 20 chars + spaces + '\0'
} License;

typedef struct {
  int date;
  int type; // +1 for start -1 for end
} Event;

typedef struct {
  int day;
  int month;
  int year;
} Date;

// Helper function to convert date to days since 01.01.2000
// We'll use a simple algorithm ignoring leap seconds, but accounting for leap
// years 01.01.2000 is day 0
static inline int days_since_2000(int d, int m, int y) {
  int days = 0;
  // Days in months (non-leap year)
  int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  // Count years
  for (int year = 2000; year < y; year++) {
    days += 365;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      days += 1; // leap year
    }
  }
  // Count months
  for (int month = 1; month < m; month++) {
    days += month_days[month - 1];
    if (month == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {
      days += 1; // leap year February
    }
  }
  // Add days
  days += d - 1;
  return days;
}

// Convert days since 01.01.2000 to Date struct
Date date_from_days_since_2000(int days) {
  Date date;
  int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int year = 2000;
  while (1) {
    int days_in_year = 365;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      days_in_year = 366;
    }
    if (days >= days_in_year) {
      days -= days_in_year;
      year++;
    } else {
      break;
    }
  }
  int month = 1;
  while (1) {
    int days_in_month = month_days[month - 1];
    if (month == 2 &&
        ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
      days_in_month = 29;
    }
    if (days >= days_in_month) {
      days -= days_in_month;
      month++;
    } else {
      break;
    }
  }
  date.day = days + 1;
  date.month = month;
  date.year = year;
  return date;
}

static inline int read_licenses(License *lic) {
  // Read start and end as dates in dd.mm.yyyy format, then company name until
  // newline
  int start_day, start_month, start_year;
  int end_day, end_month, end_year;
  if (scanf("%d.%d.%d %d.%d.%d ", &start_day, &start_month, &start_year,
            &end_day, &end_month, &end_year) != 6) {
    return 0; // failed
  }

  lic->start = days_since_2000(start_day, start_month, start_year);
  lic->end = days_since_2000(end_day, end_month, end_year);

  // Read the rest of the line (company name can contain spaces)
  if (fgets(lic->company, sizeof(lic->company), stdin) == NULL) {
    return 0;
  }

  // Remove trailing newline if present
  size_t len = strlen(lic->company);
  if (len > 0 && lic->company[len - 1] == '\n') {
    lic->company[len - 1] = '\0';
  }

  return 1;
}

Event *create_event_list(License *licenses, int number_of_licenses) {
  Event *events = malloc(sizeof(Event) * number_of_licenses * 2);
  if (!events) {
    return NULL;
  }
  for (int i = 0; i < number_of_licenses; i++) {
    events[2 * i].date = licenses[i].start;
    events[2 * i].type = +1;
    events[2 * i + 1].date = licenses[i].end;
    events[2 * i + 1].type = -1;
  }
  return events;
}

int compare_by_earliest_date(const void *a, const void *b) {
  const Event *event_a = (const Event *)a;
  const Event *event_b = (const Event *)b;
  return event_a->date - event_b->date;
}

int find_busiest_day(Event *events, int number_of_events) {
  int busiest_day = -1;
  int current_active_licenses = 0;
  int most_active_licenses_found = 0;
  for (int i = 0; i < number_of_events; i++) {
    current_active_licenses += events[i].type;
    if (current_active_licenses > most_active_licenses_found) {
      most_active_licenses_found = current_active_licenses;
      busiest_day = events[i].date;
    }
  }
  return busiest_day;
}

void print_overlapping_licenses(int busiest_day, License *licenses,
                                int number_of_licenses) {}

int main() {
  int number_of_licenses;
  scanf("%d\n", &number_of_licenses); // read number of licenses

  License *licenses = malloc(sizeof(License) * number_of_licenses);

  for (int i = 0; i < number_of_licenses; i++) {
    if (!read_licenses(&licenses[i])) {
      fprintf(stderr, "Failed to read license %d\n", i + 1);
      return 1;
    }
  }

  Event *events = create_event_list(licenses, number_of_licenses);
  qsort(events, number_of_licenses * 2, sizeof(Event),
        compare_by_earliest_date);
  int busiest_day = find_busiest_day(events, number_of_licenses * 2);
  Date busiest_date = date_from_days_since_2000(busiest_day);
  printf("Busiest day: %i.%i.%i\n", busiest_date.day, busiest_date.month,
         busiest_date.year);
  print_overlapping_licenses(busiest_day, licenses, number_of_licenses);

  free(licenses);
  return 0;
}
