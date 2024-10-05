#include "planet_util.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  point_t location;
  double angle = p->init_pos + (2 * M_PI * time / p->year_len);
  location.x = p->orbital_radius * cos(angle);
  location.y = p->orbital_radius * sin(angle);
  return location;
}
planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
  for (size_t i = 0; i < lst->num_planets; i++) {
    if (strcmp(lst->planets[i]->name, name) == 0) {
      return lst->planets[i];
    }
  }
  fprintf(stderr, "Error: Planet with the name '%s' is not found.\n", name);
  exit(EXIT_FAILURE);
}
