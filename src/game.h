#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>

class Game {
public:
    Game();

    void run(sf::VideoMode window_mode);

private:
    void create_window(sf::VideoMode video_mode);
    void initialize(sf::VideoMode window_mode);
    void event_loop();
    std::vector<char> load_font_data(const std::string& file_path);
    sf::Font create_font_from_data(const std::vector<char>& data);
    sf::Text make_message(const std::string& m, const sf::Font& font);
    void check_font_file_path(std::ifstream& font_file);

    void test();

    sf::RenderWindow m_window;
    const std::string file_path = "Assets/Fonts/Inconsolata/Inconsolata.otf";
};

#endif // GAME_H
