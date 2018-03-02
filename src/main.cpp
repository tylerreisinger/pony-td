#include <iostream>

#include <SFML/Window.hpp>

int main(int argc, char** argv) {
    sf::Window w(sf::VideoMode(800, 600), "Starlight Glimmer is still Best Pony");

    while(w.isOpen()) {
        sf::Event evt;
        while(w.pollEvent(evt)) {
            if(evt.type == sf::Event::Closed) {
                w.close();
            }
        }
    }
    return 0;
}
