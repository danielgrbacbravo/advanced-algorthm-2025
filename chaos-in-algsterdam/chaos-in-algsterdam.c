#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int start_day_count; // days since 01.01.2000
  int end_day_count;   // days since 01.01.2000
  char company_name[64];
} License;

typedef struct {
  int day_count;
  int event_type; // +1 for start -1 for end
} LicenseEvent;

typedef struct {
  int day;
  int month;
  int year;
} CalendarDate;

static inline int calculate_days_since_2000(int day, int month, int year) {
  int total_days = 0;
  // Days in months (non-leap year)
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  // Count years
  for (int current_year = 2000; current_year < year; current_year++) {
    total_days += 365;
    if ((current_year % 4 == 0 && current_year % 100 != 0) ||
        (current_year % 400 == 0)) {
      total_days += 1; // leap year
    }
  }
  // Count months
  for (int current_month = 1; current_month < month; current_month++) {
    total_days += days_in_month[current_month - 1];
    if (current_month == 2 &&
        ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
      total_days += 1; // leap year February
    }
  }
  // Add days
  total_days += day - 1;
  return total_days;
}

// Convert days since 01.01.2000 to CalendarDate struct
CalendarDate get_calendar_date_from_days_since_2000(int days_since_2000) {
  CalendarDate calendar_date;
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int year = 2000;
  while (1) {
    int days_in_year = 365;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      days_in_year = 366;
    }
    if (days_since_2000 >= days_in_year) {
      days_since_2000 -= days_in_year;
      year++;
    } else {
      break;
    }
  }
  int month = 1;
  while (1) {
    int days_this_month = days_in_month[month - 1];
    if (month == 2 &&
        ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
      days_this_month = 29;
    }
    if (days_since_2000 >= days_this_month) {
      days_since_2000 -= days_this_month;
      month++;
    } else {
      break;
    }
  }
  calendar_date.day = days_since_2000 + 1;
  calendar_date.month = month;
  calendar_date.year = year;
  return calendar_date;
}

static inline int read_license_from_input(License *license) {
  // Read start and end as dates in dd.mm.yyyy format, then company name until
  // newline
  int start_day, start_month, start_year;
  int end_day, end_month, end_year;
  if (scanf("%d.%d.%d %d.%d.%d ", &start_day, &start_month, &start_year,
            &end_day, &end_month, &end_year) != 6) {
    return 0; // failed
  }

  license->start_day_count =
      calculate_days_since_2000(start_day, start_month, start_year);
  license->end_day_count =
      calculate_days_since_2000(end_day, end_month, end_year);

  // Read the rest of the line (company name can contain spaces)
  if (fgets(license->company_name, sizeof(license->company_name), stdin) ==
      NULL) {
    return 0;
  }

  // Remove trailing newline if present
  size_t company_name_length = strlen(license->company_name);
  if (company_name_length > 0 &&
      license->company_name[company_name_length - 1] == '\n') {
    license->company_name[company_name_length - 1] = '\0';
  }

  return 1;
}

LicenseEvent *create_license_event_list(License *license_list,
                                        int license_count) {
  LicenseEvent *event_list = malloc(sizeof(LicenseEvent) * license_count * 2);
  if (!event_list) {
    return NULL;
  }
  for (int license_index = 0; license_index < license_count; license_index++) {
    event_list[2 * license_index].day_count =
        license_list[license_index].start_day_count;
    event_list[2 * license_index].event_type = +1;
    event_list[2 * license_index + 1].day_count =
        license_list[license_index].end_day_count;
    event_list[2 * license_index + 1].event_type = -1;
  }
  return event_list;
}

int compare_events_by_earliest_day(const void *event_a_ptr,
                                   const void *event_b_ptr) {
  const LicenseEvent *event_a = (const LicenseEvent *)event_a_ptr;
  const LicenseEvent *event_b = (const LicenseEvent *)event_b_ptr;
  return event_a->day_count - event_b->day_count;
}

int find_busiest_license_day(LicenseEvent *event_list, int event_count) {
  int busiest_day_count = -1;
  int current_active_license_count = 0;
  int max_active_license_count = 0;
  for (int event_index = 0; event_index < event_count; event_index++) {
    current_active_license_count += event_list[event_index].event_type;
    if (current_active_license_count > max_active_license_count) {
      max_active_license_count = current_active_license_count;
      busiest_day_count = event_list[event_index].day_count;
    }
  }
  return busiest_day_count;
}
// Sort company names alphabetically
int cmp_company_names(const void *a, const void *b) {
  return strcmp((const char *)a, (const char *)b);
}
void print_companies_with_active_licenses_on_day(int busiest_day_count,
                                                 License *license_list,
                                                 int license_count) {
  // Step 1: Collect company names (heap allocation)
  char(*active_company_names)[64] = malloc(sizeof(char[64]) * license_count);
  if (!active_company_names) {
    fprintf(stderr, "Memory allocation failed for company names\n");
    return;
  }
  int active_company_count = 0;
  for (int i = 0; i < license_count; i++) {
    if (license_list[i].start_day_count <= busiest_day_count &&
        busiest_day_count < license_list[i].end_day_count) {
      strncpy(active_company_names[active_company_count],
              license_list[i].company_name, 64);
      active_company_names[active_company_count][63] = '\0';
      active_company_count++;
    }
  }

  // Step 2: Sort company names alphabetically
  if (active_company_count > 0) {
    qsort(active_company_names, active_company_count,
          sizeof(active_company_names[0]), cmp_company_names);
  }

  // Step 3: Print unique company names
  for (int i = 0; i < active_company_count; i++) {
    if (i == 0 ||
        strcmp(active_company_names[i], active_company_names[i - 1]) != 0) {
      printf("%s\n", active_company_names[i]);
    }
  }
  free(active_company_names);
}

int main() {
  int license_count;
  scanf("%d\n", &license_count); // read number of licenses

  License *license_list = malloc(sizeof(License) * license_count);
  if (!license_list) {
    fprintf(stderr, "Memory allocation failed for license_list\n");
    return 1;
  }

  for (int license_index = 0; license_index < license_count; license_index++) {
    if (!read_license_from_input(&license_list[license_index])) {
      fprintf(stderr, "Failed to read license %d\n", license_index + 1);
      return 1;
    }
  }

  LicenseEvent *event_list =
      create_license_event_list(license_list, license_count);
  qsort(event_list, license_count * 2, sizeof(LicenseEvent),
        compare_events_by_earliest_day);
  int busiest_day_count =
      find_busiest_license_day(event_list, license_count * 2);
  CalendarDate busiest_calendar_date =
      get_calendar_date_from_days_since_2000(busiest_day_count);
  printf("Busiest day: %02d.%02d.%04d\n", busiest_calendar_date.day,
         busiest_calendar_date.month, busiest_calendar_date.year);
  print_companies_with_active_licenses_on_day(busiest_day_count, license_list,
                                              license_count);

  free(license_list);
  free(event_list);
  return 0;
}
