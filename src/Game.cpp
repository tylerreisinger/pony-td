#include "Game.h"

#include <ratio>

#include <entityx/quick.h>

#include "FrameRateCounter.h"

#include "Component/Position.h"
#include "Component/Sprite.h"
#include "Component/Velocity.h"
#include "System/MovementSystem.h"
#include "System/SpriteSystem.h"

#include "World/CameraController.h"
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

    m_floor_directory.add_tile(std::make_unique<FloorTileDefinition>(1));
    m_floor_directory.add_tile(std::make_unique<FloorTileDefinition>(2));

    auto default_floor = FloorTile(&m_floor_directory[1]);
    auto default_tile = MapTile(std::move(default_floor));

    m_world = std::make_unique<World>(8, 8, default_tile);

    sf::Texture texture1_gfx;
    sf::Texture texture2_gfx;

    texture1_gfx.loadFromFile("Assets/Tiles/tile1.png");
    texture2_gfx.loadFromFile("Assets/Tiles/tile2.png");

    TileSet ts(64, 64);
    ts.set_tile_graphic(1, std::move(texture1_gfx));
    ts.set_tile_graphic(2, std::move(texture2_gfx));

    auto road_tile = FloorTile(&m_floor_directory[2]);

    m_world->set_tile(1, 0, {road_tile});
    m_world->set_tile(1, 1, {road_tile});
    m_world->set_tile(1, 2, {road_tile});
    m_world->set_tile(1, 3, {road_tile});
    m_world->set_tile(1, 4, {road_tile});
    m_world->set_tile(2, 4, {road_tile});
    m_world->set_tile(3, 4, {road_tile});
    m_world->set_tile(4, 4, {road_tile});
    m_world->set_tile(4, 5, {road_tile});
    m_world->set_tile(4, 6, {road_tile});
    m_world->set_tile(4, 7, {road_tile});
    m_world->add_spawn_point(SpawnPoint(*m_world, sf::Vector2<int>{1, 0}));
    m_world->add_target(Target(*m_world, sf::Vector2<int>{4, 7}));

    m_world_renderer = std::make_unique<WorldRenderer>(
            std::move(ts), m_window.getSize().x, m_window.getSize().y);
    m_camera.set_look_at(
            sf::Vector2<double>(m_world->width() * (ts.tile_width() / 2),
                    m_world->height() * (ts.tile_height() / 2)));
    m_camera_controller = std::make_unique<CameraController>();

    m_ecs = std::make_unique<entityx::EntityX>();

    auto my_entity = m_ecs->entities.create();
    my_entity.assign<comp::Position>(20.0, 50.0);
    my_entity.assign<comp::Velocity>(40.0, 40.0);
    m_ecs->systems.add<sys::MovementSystem>();
    m_ecs->systems.add<sys::SpriteSystem>(m_window);
    m_ecs->systems.configure();

    load_sprites();

    std::cout << "Initialized" << std::endl;
}

void Game::load_sprites() {
    auto texture = new sf::Texture();
    texture->loadFromFile("Assets/Sprites/Twilight1.png");
    auto twi_sprite = sf::Sprite(*texture);

    auto e = m_ecs->entities.get(entityx::Entity::Id(0, 1));
    e.assign<comp::Sprite>(std::move(twi_sprite));
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

void Game::update(const GameTime& time) {
    m_ecs->systems.update<sys::MovementSystem>(time);
    m_camera_controller->update(time, m_camera, *m_world, *m_world_renderer);
}

void Game::draw(const GameTime& time) {
    m_window.clear();

    m_world_renderer->render(m_window, *m_world, m_camera);
    m_ecs->systems.update<sys::SpriteSystem>(time);
    draw_fps(time);

    m_window.display();
}

void Game::draw_fps(const GameTime& time) {
    auto frame_rate = m_fps_counter->average_frame_rate();
    auto& font = m_font;
    auto message = sf::Text(std::to_string(frame_rate) + " fps", font);
    message.setFillColor(sf::Color(255, 255, 255));
    message.setOutlineColor(sf::Color(0, 0, 0));
    message.setOutlineThickness(3.0);
    message.setCharacterSize(32);

    m_window.draw(message);
}
