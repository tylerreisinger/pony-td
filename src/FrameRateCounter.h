#ifndef FRAMERATECOUNTER_H_
#define FRAMERATECOUNTER_H_

#include <chrono>
#include <deque>

#include "GameTime.h"

class FrameRateSampler {
public:
    static constexpr std::size_t NUM_SAMPLES = 30;

    FrameRateSampler();
    ~FrameRateSampler() = default;

    FrameRateSampler(const FrameRateSampler& other) = default;
    FrameRateSampler(FrameRateSampler&& other) = default;
    FrameRateSampler& operator=(const FrameRateSampler& other) = default;
    FrameRateSampler& operator=(FrameRateSampler&& other) = default;

    void tick(const GameTime& time);
    double average_frame_rate() const;
    bool is_saturated() const;

private:
    std::deque<double> m_samples;
};

class FrameRateCounter {
public:
    explicit FrameRateCounter(double target_fps);
    ~FrameRateCounter() = default;

    FrameRateCounter(const FrameRateCounter& other) = delete;
    FrameRateCounter(FrameRateCounter&& other) = default;
    FrameRateCounter& operator=(const FrameRateCounter& other) = delete;
    FrameRateCounter& operator=(FrameRateCounter&& other) = default;

    void tick(const GameTime& time);

    std::chrono::duration<double, std::milli> target_time_per_frame() const;
    double average_frame_rate() const;

private:
    double m_target_framerate;
    FrameRateSampler m_sampler;
};

#endif
