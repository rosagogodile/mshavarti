/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/18/2025
 * Description:     Header file for level generation function and class definitions
 */


#ifndef LEVELGENERATION_H
#define LEVELGANERATION_H

#include <cstdint>
#include <memory>
#include <random>
#include <vector>
#include <algorithm>
#include <string>

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

/* Template class that stores a 2d matrix
 * Used so I don't have to deal with the "Rule of Fives" for each class here that needs a matrix
 */
template <typename T>
class Matrix2D
{
    private:
        T ** data;
        uint16_t w;
        uint16_t h;

    public: 
        // constructor
        Matrix2D(uint16_t width, uint16_t height)
        {
            w = width;
            h = height;

            data = new T * [width];
            for (uint16_t i = 0; i < width; ++i)
            {
                data[i] = new T[height];
            }
        }

        // destructor 
        ~Matrix2D()
        {
            // delete each column before deleting the entire matrix
            for (uint16_t i = 0; i < w; ++i)
            {
                delete[] data[i];
            }
            delete[] data;
        }

        // getters
        uint16_t get_width()  {return w;}
        uint16_t get_height() {return h;}

        /* Function that converts the matrix to a raw pointer
         * Instead of returning the raw pointer defined in the class, this function returns a copy of it 
         */
        T ** as_pointer()
        {
            // allocate memory for the copy
            T ** temp = new T * [w];
            for (uint16_t i = 0; i < w; ++i)
            {
                temp[i] = new T[h];
            }

            // perform the copy
            for (uint16_t i = 0; i < w; ++i)
            {
                for (uint16_t j = 0; j < h; ++j)
                {
                    temp[i][j] = data[i][j];
                }
            }

            return temp;
        }

        /* Function that fills the matrix with a specified value
         */
        void fill(T fillval)
        {
            for (uint16_t i = 0; i < w; ++i)
            {
                for (uint16_t j = 0; j < h; ++j)
                {
                    data[i][j] = fillval;
                }
            }
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

        TILE_ID ** tile_data;

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
        uint8_t ** minimap;
        Pair<int16_t> minimap_bounds;

        uint8_t ** Random_Walk();

    public:
        LevelFloor(std::mt19937 & rng_ref, uint8_t floor_number);
        std::string minimap_str() const;
};


#endif