#include "Game.h"

#include <ratio>

#include "FrameRateCounter.h"
#include "World/TileSet.h"
#include "World/World.h"
#include "World/WorldRenderer.h"

Game::Game() {}
Game::~Game() {}

void Game::run(sf::VideoMode window_mode) {
    using namespace std::chrono_literals;
    initialize(window_mode);

    auto time_step = 33.3ms;

    while(m_window.isOpen()) {
        GameTime frame_time = m_game_clock.tick(time_step);
        m_fps_counter->tick(frame_time);

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
    m_fps_counter = std::make_unique<FrameRateCounter>(30.0);

    bool result = m_font.loadFromFile(file_path);
    if(!result) {
        throw std::runtime_error(
                "Failed to load font file '" + file_path + "'.");
    }

    auto default_floor = FloorTile(1);
    auto default_tile = MapTile(std::move(default_floor));

    m_world = std::make_unique<World>(15, 15, default_tile);

    sf::Texture texture1_gfx;
    sf::Texture texture2_gfx;

    texture1_gfx.loadFromFile("Assets/Tiles/tile1.png");
    texture2_gfx.loadFromFile("Assets/Tiles/tile2.png");

    TileSet ts(32, 32);
    ts.set_tile_graphic(1, std::move(texture1_gfx));
    ts.set_tile_graphic(2, std::move(texture2_gfx));

    m_world->set_tile(2, 2, {FloorTile(2)});
    m_world->set_tile(3, 3, {FloorTile(2)});
    m_world->set_tile(4, 4, {FloorTile(2)});
    m_world->set_tile(5, 5, {FloorTile(2)});

    m_world_renderer = std::make_unique<WorldRenderer>(std::move(ts), 400, 400);

    std::cout << "Initialized" << std::endl;
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
void Game::update(const GameTime& time) {}

void Game::draw(const GameTime& time) {
    m_window.clear();

    m_world_renderer->render(m_window, *m_world, m_camera);
    draw_fps(time);

    m_window.display();
}

void Game::draw_fps(const GameTime& time) {
    auto frame_rate = m_fps_counter->average_frame_rate();
    auto font = m_font;
    auto message = sf::Text(std::to_string(frame_rate) + " fps", font);
    message.setFillColor(sf::Color(255, 255, 255));
    message.setOutlineColor(sf::Color(0, 0, 0));
    message.setOutlineThickness(3.0);
    message.setCharacterSize(32);

    m_window.draw(message);
}