#include "target.h"

#include <math.h>

#include "provided.h"

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this

  launch_result_t result;
  planet_t * source = find_planet(planets, this_launch->src);
  planet_t * destination = find_planet(planets, this_launch->dest);

  point_t dest_pos = get_location_at(destination, this_launch->time);
  point_t source_pos = get_location_at(source, this_launch->time);

  double dx = dest_pos.x - source_pos.x;
  double dy = dest_pos.y - source_pos.y;
  result.theta = atan2(dy, dx);

  double distance = sqrt(dx * dx + dy * dy);
  result.duration = distance / this_launch->speed;

  return result;
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this
  double period = planet->year_len;
  double angle_to_pos = atan2(pos.y, pos.x);
  double current_angle = planet->init_pos + (2 * M_PI * start_time / period);
  double angle_diff = fmod(angle_to_pos - current_angle, 2 * M_PI);

  if (angle_diff < 0) {
    angle_diff += 2 * M_PI;
  }

  double time_to_return = angle_diff * period / (2 * M_PI);
  return start_time + time_to_return;
}
