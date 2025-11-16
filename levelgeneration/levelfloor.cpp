/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/16/2025
 * Description:     File that contains implementations for the class `LevelFloor` defined in `levelgeneration.h`
 */

#include "levelgeneration.h"


/* Constructor for `LeveLFloor`
 * Initializes a reference to the random number generator
 * Calls all generation functions needed to generate the floor
 */
LevelFloor::LevelFloor(std::mt19937 & rng_ref, uint8_t floor_number): rng(rng_ref), floor_num(floor_number) 
{}