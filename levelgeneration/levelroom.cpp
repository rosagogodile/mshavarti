/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/16/2025
 * Description:     File that contains implementations for the class `LevelRoom` defined in `levelgeneration.h`
 */

#include "levelgeneration.h"


/* Constructor for `LevelRoom`
 * Initializes the matrix of tile data, and that's about it
 */
LevelRoom::LevelRoom()
{
    using namespace std;

    num_connections = 0;
    empty_conections = 4;
    
    // initialize tile data
    // link to remind me how to do this bc im lowkey buns as c++:
    // https://intellipaat.com/blog/how-to-declare-a-2d-array-in-c-using-new/
    // create unique pointer
    tile_data.reset(new unique_ptr<TILE_ID[]>[STANDARD_ROOM_SIZE]);

    // allocate data for each row
    for (int16_t i = 0; i < STANDARD_ROOM_SIZE; ++i)
    {
        tile_data[i] = std::make_unique<TILE_ID[]>(STANDARD_ROOM_SIZE);
    }
}