#include <chrono>

class GameTime {
public:
    using Clock = std::chrono::high_resolution_clock;

    GameTime(std::chrono::duration<double> wall_time,
            std::chrono::duration<double> game_time,
            std::chrono::duration<double> wall_time_elapsed,
            std::chrono::duration<double> game_time_elapsed,
            Clock::time_point frame_start_time);
    ~GameTime() = default;

    GameTime(const GameTime& other) = default;
    GameTime(GameTime&& other) noexcept = default;
    GameTime& operator=(const GameTime& other) = default;
    GameTime& operator=(GameTime&& other) noexcept = default;


    std::chrono::duration<double> get_wall_time() const;
    std::chrono::duration<double> get_game_time() const;
    std::chrono::duration<double> get_elapsed_wall() const;
    std::chrono::duration<double> get_elapsed_game() const;
    Clock::time_point get_frame_start_time() const;
    Clock::time_point get_game_start_time() const;

private:
    std::chrono::duration<double> m_wall_time;
    std::chrono::duration<double> m_game_time;
    std::chrono::duration<double> m_wall_time_elapsed;
    std::chrono::duration<double> m_game_time_elapsed;
    Clock::time_point m_frame_start_time;
    Clock::time_point m_game_start_time;
};
