#include "iter_target.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
  launch_result_t best_launch_result;
  double min_total_time = INFINITY;
  int max_iterations = this_launch->max_iterations;
  double current_time = this_launch->time;

  launch_input_t mutable_launch = *this_launch;

  for (int iter = 0; iter < max_iterations; iter++) {
    mutable_launch.time = current_time;

    launch_result_t current_launch_result =
        compute_launch_by_info(&mutable_launch, planets);
    double arrival_time = this_launch->time + current_launch_result.duration;
    planet_t * target_planet = find_planet(planets, this_launch->dest);
    point_t target_position = get_location_at(target_planet, arrival_time);
    double next_wait_time =
        when_does_planet_return_to(target_planet, target_position, arrival_time);
    double total_time = current_launch_result.duration + (next_wait_time - arrival_time);
    double distance_to_planet =
        sqrt(pow(target_position.x - current_launch_result.theta, 2) +
             pow(target_position.y - current_launch_result.theta, 2));

    if (distance_to_planet < this_launch->close_enough) {
      total_time = current_launch_result.duration;
    }

    if (total_time < min_total_time) {
      min_total_time = total_time;
      best_launch_result = current_launch_result;
    }

    if (next_wait_time == arrival_time ||
        distance_to_planet < this_launch->close_enough) {
      break;
    }

    current_time = next_wait_time;
  }

  return best_launch_result;
}
