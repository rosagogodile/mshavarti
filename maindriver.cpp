/* Author:          Rosa Knowles
 * Created:         11/16/2025
 * Last Updated:    11/18/2025
 * Description:     Main driver for this horrible project
 */


#include <iostream>
#include <ctime>
#include <random>
#include "levelgeneration/levelgeneration.h"

int main(int argc, char ** argv)
{
    std::mt19937 rng(time(nullptr));
    LevelFloor test(rng, 5);
    std::cout << test.minimap_str() << std::endl;

    return 0;
}