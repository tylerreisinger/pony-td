#include "FrameRateCounter.h"

using std::chrono::duration;
using std::chrono::duration_cast;

FrameRateSampler::FrameRateSampler() {}

void FrameRateSampler::tick(const GameTime& time) {
    auto effective_fps = 1.0 /
            duration_cast<duration<double>>(time.get_elapsed_wall()).count();

    if(is_saturated()) {
        m_samples.pop_front();
    }

    m_samples.push_back(effective_fps);
}

double FrameRateSampler::average_frame_rate() const {
    double sum = 0.0;
    for(auto sample : m_samples) {
        sum += sample;
    }

    return sum / m_samples.size();
}

bool FrameRateSampler::is_saturated() const {
    return m_samples.size() == NUM_SAMPLES;
}

FrameRateCounter::FrameRateCounter(double target_fps)
    : m_target_framerate(target_fps) {}

void FrameRateCounter::tick(const GameTime& time) { m_sampler.tick(time); }

std::chrono::duration<double, std::milli>
FrameRateCounter::target_time_per_frame() const {
    return duration<double, std::milli>(1.0 / m_target_framerate);
}

double FrameRateCounter::average_frame_rate() const {
    return m_sampler.average_frame_rate();
}
