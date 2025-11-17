/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/17/2025
 * Description:     File that contains implementations for the class `LevelFloor` defined in `levelgeneration.h`
 */

#include "levelgeneration.h"


/* Constructor for `LeveLFloor`
 * Initializes a reference to the random number generator
 * Calls all generation functions needed to generate the floor
 */
LevelFloor::LevelFloor(std::mt19937 & rng_ref, uint8_t floor_number): rng(rng_ref), floor_num(floor_number) 
{}


/* Function that returns a matrix from the random walk algorithm
 * https://www.geeksforgeeks.org/python/random-walk-implementation-python/
 * Used to generate the skeleton of the dungeon map, some other rooms and stuff will be added on after this
 */
MATRIX<uint8_t> LevelFloor::Random_Walk()
{
    using namespace std;

    // get num of "skeleton" rooms in the floor (as in, rooms that make up the "skeleton" of the floor)
    uniform_int_distribution<> size_distr(floor_num, (floor_num * floor_num / 2) + floor_num);
    // pick a size between `MIN_FLOOR_SIZE` and `MAX_FLOOR_SIZE` based on `size_distr`
    uint16_t num_skel_rooms = min(max(MIN_FLOOR_SIZE, size_distr(rng)), MAX_FLOOR_SIZE);

    // initialize the random number generation stuff 
    // in the defines in `levelgeneration.h`, `NORTH` has the smallest value and `EAST` has the largest value
    uniform_int_distribution<> direction_distr(NORTH, EAST);

    // vector of coordinates that have been marked by the random walker
    vector<Pair<int16_t>> marked_coordinates;

    Pair<int16_t> current_position(0,0);
    marked_coordinates.push_back(current_position);

    for (uint16_t i = 0; i < num_skel_rooms; ++i)
    {
        // get specified direction to move in
        uint8_t direction = direction_distr(rng);

        // move in the specified direction
        switch(direction)
        {
            case NORTH:
                current_position.x2 += 1;
                break;
            case SOUTH:
                current_position.x2 -= 1;
                break;
            case WEST:
                current_position.x1 += 1;
                break;
            case EAST:
                current_position.x1 -= 1;
                break;
        }

        marked_coordinates.push_back(current_position);
    }

    // construct minimap matrix
}