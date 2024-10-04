#include "myinput.h"

#include <math.h>
#include <stdio.h>

#include "provided.h"

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this

  char name[32];
  double orbital_radius, year_len, initial_pos_deg;
  int fields;

  fields = sscanf(
      line, "%31[^:]:%lf:%lf:%lf", name, &orbital_radius, &year_len, &initial_pos_deg);

  if (fields != 4) {
    fprintf(stderr, "Error: Incorrect number of fields in input. Please try again!\n");
    exit(EXIT_FAILURE);
  }

  if (strlen(name) > 31) {
    fprintf(
        stderr,
        "Error: Planet name exceeds the maximum (31 characters). Please try again!\n");
    exit(EXIT_FAILURE);
  }

  if (orbital_radius <= 0 || year_len <= 0) {
    fprintf(stderr, "Error: Orbital radius year length must be a positive value.\n");
    exit(EXIT_FAILURE);
  }

  if (initial_pos_deg < 0) {
    fprintf(stderr, "Error: Initial position must be a non-negative value.\n");
    exit(EXIT_FAILURE);
  }

  double initial_pos_rad = initial_pos_deg * (M_PI / 180.0);

  strncpy(planet->name, name, 32);
  planet->orbital_radius = orbital_radius;
  planet->year_len = year_len;
  planet->init_pos = initial_pos_rad;
}
