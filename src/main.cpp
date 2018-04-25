#include "Game.h"

#include <fstream>
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Data/AssetManager.h"
#include "Data/TextureLoader.h"

#include "Angle.h"

int main(int argc, char** argv) {
    Game game;
    game.run(sf::VideoMode(800, 600));
    return 0;
}
