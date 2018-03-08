#include "game.h"
#include <fstream>
#include <iostream>
#include <vector>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    Game game;
    game.run(sf::VideoMode(800, 600));
    return 0;
}
