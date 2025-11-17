/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/17/2025
 * Description:     Header file for level generation function and class definitions
 */


#ifndef LEVELGENERATION_H
#define LEVELGANERATION_H

#include <cstdint>
#include <memory>
#include <random>
#include <vector>
#include <algorithm>

#define STANDARD_ROOM_SIZE 50

#define MIN_FLOOR_SIZE 8
#define MAX_FLOOR_SIZE 30

// directional defines used in the implementation of random walk
#define NORTH 1
#define SOUTH 2
#define WEST  3
#define EAST  4

// type that stores the id for a tile
// setup this way so i can easily change it later if needed
typedef uint8_t TILE_ID;

// type that allows me to define a smart pointer for a dynamically allocated matrix
// without wanting to blow my fucking brains out 
template <typename T> using MATRIX = std::unique_ptr<std::unique_ptr<T[]>[]>;



/* Incredibly basic template class that stores a pair of values
 * Everything is public here because encapsulation should be unnecessary 
 */
template <typename T>
class Pair
{
    public:
        T x1;
        T x2;

        Pair(){}
        Pair(T a1, T a2): x1(a1), x2(a2) {}

        // addition operator overloads: https://en.cppreference.com/w/cpp/language/operators.html
        Pair<T> & operator+=(const Pair<T> & rhs)
        {
            this->x1 += rhs.x1;
            this->x2 += rhs.x2;

            return *this;
        }
        friend Pair<T> operator+(Pair<T> lhs, const Pair<T> & rhs)
        {
            lhs += rhs;
            return lhs;
        }
};

/* Function that determines which of two pairs are further to the left
 * returns true if `lhs` is further left than `rhs`
 * This function was initially planned to be used for something, but as of now I don't think it's necessary
 * Leaving it in the code just in case.
 */
template <typename T>
bool further_left(const Pair<T> & lhs, const Pair<T> & rhs)
{
    return lhs.x1 <= rhs.x1 && lhs.x2 <= rhs.x2; 
}



/* Class that stores room information
 * Contains tile data, as well as references to the connecting rooms
 */
class LevelRoom
{
    private:
        uint8_t num_connections;
        uint8_t empty_conections;

        MATRIX<TILE_ID> tile_data;

        std::shared_ptr<LevelRoom> north;
        std::shared_ptr<LevelRoom> south;
        std::shared_ptr<LevelRoom> east;
        std::shared_ptr<LevelRoom> west;

    public:
        LevelRoom();
};


/* Class that stores floor information
 * Essentially a graph of all rooms in a floor
 */
class LevelFloor
{
    private:
        LevelRoom starting_room;
        // reference to a random number generator that will be used to generate the floor
        std::mt19937 & rng;
        uint8_t floor_num;

        MATRIX<uint8_t> Random_Walk();

    public:
        LevelFloor(std::mt19937 & rng_ref, uint8_t floor_number);
};


#endif