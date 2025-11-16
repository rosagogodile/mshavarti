/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/16/2025
 * Description:     Header file for level generation function and class definitions
 */


#ifndef LEVELGENERATION_H
#define LEVELGANERATION_H

#include <cstdint>
#include <memory>

#define STANDARD_ROOM_SIZE 50

// type that stores the id for a tile
// setup this way so i can easily change it later if needed
typedef uint8_t TILE_ID;

class LevelRoom
{
    private:
        uint8_t num_connections;
        uint8_t empty_conections;

        std::unique_ptr<std::unique_ptr<TILE_ID[]>[]> tile_data;

        std::shared_ptr<LevelRoom> north;
        std::shared_ptr<LevelRoom> south;
        std::shared_ptr<LevelRoom> east;
        std::shared_ptr<LevelRoom> west;

    public:
        LevelRoom();
};

class LevelFloor
{
    private:
        LevelRoom starting_room;

    public:
        LevelFloor();
};


#endif