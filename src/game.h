#ifndef GAME_H
#define GAME_H

#include "GameClock.h"
#include "World/Camera.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

class FrameRateCounter;
class World;
class WorldRenderer;

class Game {
public:
    Game();
    ~Game();

    void run(sf::VideoMode window_mode);

private:
    void create_window(sf::VideoMode video_mode);
    void initialize(sf::VideoMode window_mode);
    void event_loop();
    void update(const GameTime& time);
    void draw(const GameTime& time);

    std::vector<char> load_font_data(const std::string& file_path);
    sf::Font create_font_from_data(const std::vector<char>& data);
    sf::Text make_message(const std::string& m, const sf::Font& font);
    void check_font_file_path(std::ifstream& font_file);

    GameClock m_game_clock;
    sf::RenderWindow m_window;
    const std::string file_path = "Assets/Fonts/Inconsolata/Inconsolata.otf";
    sf::Font m_font;
    Camera m_camera;
    std::unique_ptr<World> m_world;
    std::unique_ptr<WorldRenderer> m_world_renderer;
    std::unique_ptr<FrameRateCounter> m_fps_counter;
};

#endif // GAME_H
