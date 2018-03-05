#include <iostream>
#include <fstream>
#include <vector>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void check_if_there_is_no_event(sf::RenderWindow& w) {
    sf::Event evt;
    while(w.pollEvent(evt)) {
        if(evt.type == sf::Event::Closed) {
            w.close();
        }
    }
}

void check_font_file_path(std::ifstream& font_file) {
    if(!font_file.is_open()) {
        std::cerr << "Failed to load font file." << std::endl;
        throw std::runtime_error("Font file not found.");
    }
}

std::vector<char> load_font_data(const std::string& file_path) {
    std::ifstream font_file(file_path);
    check_font_file_path(font_file);
    font_file.seekg(0, std::ios_base::end);
    std::size_t font_size = font_file.tellg();
    font_file.seekg(0, std::ios_base::beg);
    auto data = std::vector<char>(font_size + 1);
    font_file.read(data.data(), font_size);
    return data;
}

sf::Font create_font_from_data(const std::vector<char>& data) {
    sf::Font font;
    bool result = font.loadFromMemory(data.data(), data.size());
    if(!result) {
        throw std::invalid_argument("invalid font data supplied");
    }
    return font;
}

sf::Text make_message(const std::string& m, const sf::Font& font) {
    sf::Text message(m, font);
    message.setCharacterSize(12);
    message.setColor(sf::Color(255, 0, 255));
    return message;
}


int main(int argc, char** argv) {
    sf::RenderWindow w(
            sf::VideoMode(800, 600), "Starlight Glimmer is still Best Pony");

    const std::string file_path = "Assets/Fonts/Inconsolata/Inconsolata.otf";

    std::vector<char> chars = load_font_data(file_path);
    sf::Font font = create_font_from_data(chars);

    while(w.isOpen()) {
        check_if_there_is_no_event(w);
        w.clear();

        w.draw(make_message("Glimmer is the best pone", font));

        w.display();
    }
    return 0;
}
