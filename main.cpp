#define SDL_MAIN_HANDLED

/*
 *
 *
 *
 * TODO:
 *
 * - configure cartridge information
 */

#include <iostream>
#include <SDL.h>
#include "cartridge.h"

int main(int argc, const char* argv[]) {
    std::cout << "hello world" << std::endl;

    load_cartridge("roms/pokemon_red.gb");


    return 0;
}
