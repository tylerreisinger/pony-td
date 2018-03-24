#include "game.h"

#include <ratio>

Game::Game() {}

void Game::run(sf::VideoMode window_mode) {
    using namespace std::chrono_literals;
    initialize(window_mode);

    auto time_step = 33.3ms;

    while(m_window.isOpen()) {
        GameTime frame_time = m_game_clock.tick(time_step);

        event_loop();

        update(frame_time);

        draw(frame_time);

        auto frame_length = std::chrono::high_resolution_clock::now() -
                frame_time.get_frame_start_time();
        auto sleep_duration = time_step - frame_length;

        if(sleep_duration > decltype(frame_length)::zero()) {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
}

void Game::create_window(sf::VideoMode window_mode) {
    m_window.create(window_mode, "Starlight Glimmer");
}
void Game::initialize(sf::VideoMode window_mode) {
    create_window(window_mode);
    std::vector<char> chars = load_font_data(file_path);
    m_font = create_font_from_data(chars);
}

void Game::event_loop() {
    sf::Event evt;
    while(m_window.pollEvent(evt)) {
        if(evt.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}
std::vector<char> Game::load_font_data(const std::string& file_path) {
    std::ifstream font_file(file_path);
    check_font_file_path(font_file);
    font_file.seekg(0, std::ios_base::end);
    std::size_t font_size = font_file.tellg();
    font_file.seekg(0, std::ios_base::beg);
    auto data = std::vector<char>(font_size + 1);
    font_file.read(data.data(), font_size);
    return data;
}

sf::Font Game::create_font_from_data(const std::vector<char>& data) {
    sf::Font font;
    bool result = font.loadFromMemory(data.data(), data.size());
    if(!result) {
        throw std::invalid_argument("invalid font data supplied");
    }
    return font;
}

sf::Text Game::make_message(const std::string& m, const sf::Font& font) {
    sf::Text message(m, font);
    message.setCharacterSize(12);
    message.setColor(sf::Color(255, 0, 255));
    return message;
}

void Game::check_font_file_path(std::ifstream& font_file) {
    if(!font_file.is_open()) {
        std::cerr << "Failed to load font file." << std::endl;
        throw std::runtime_error("Font file not found.");
    }
}

void Game::update(const GameTime& time) {}

void Game::draw(const GameTime& time) {
    m_window.clear();

    m_window.draw(make_message("Glimmer is the best pone", m_font));

    m_window.display();
}
