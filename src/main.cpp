#include <iostream>
#include <fstream>
#include <vector>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    sf::Window w(sf::VideoMode(800, 600), "Starlight Glimmer is still Best Pony");

    while(w.isOpen()) {

        sf::Event evt;
        while(w.pollEvent(evt)) {
            if(evt.type == sf::Event::Closed) {
                w.close();
            }
        }

        std::ifstream font_file("Assets/Fonts/Inconsolata/Inconsolata.otf");

        if(!font_file.is_open()) {
            std::cout << "Failed to load font file." << std::endl;
            return -1;
        }
        font_file.seekg(0, std::ios_base::end);
        std::size_t font_size = font_file.tellg();
        font_file.seekg(0, std::ios_base::beg);
        std::cout << font_size << std::endl;
        std::vector<char> data(font_size+1);
        font_file.read(data.data(), font_size);

        //Put drawing stuff here
        sf::Font font;
        auto my_font = font.loadFromMemory(data.data(), font_size);
        std::cout << my_font << std::endl;
        sf::Text message("Hello Glimmer", font);

        w.close();
    }
    return 0;
}
