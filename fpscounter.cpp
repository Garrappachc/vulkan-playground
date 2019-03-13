#include "fpscounter.h"
#include <chrono>
#include <numeric>
#include <vector>

namespace {

constexpr auto FpsUpdateTimeout = 100; // in milliseconds

}

class FpsCounterPrivate {
public:
    std::vector<unsigned> values;
    std::chrono::high_resolution_clock::time_point lastUpdate;
    unsigned fps;

    FpsCounterPrivate();
    void frameRendered(unsigned microseconds);

private:
    void recalculateFps();

};

FpsCounterPrivate::FpsCounterPrivate() : lastUpdate(std::chrono::system_clock::now())
{

}

void FpsCounterPrivate::frameRendered(unsigned microseconds)
{
    unsigned lastFps = 1000000 / microseconds;
    values.push_back(lastFps);

    auto now = std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() >= FpsUpdateTimeout) {
        recalculateFps();
        lastUpdate = now;
    }
}

void FpsCounterPrivate::recalculateFps()
{
    fps = std::accumulate(values.begin(), values.end(), 0) / values.size();
    values.clear();
}

FpsCounter::FpsCounter() : d(new FpsCounterPrivate)
{

}

FpsCounter::~FpsCounter()
{

}

unsigned FpsCounter::framesPerSecond() const
{
    return d->fps;
}

void FpsCounter::frameRendered(unsigned microseconds)
{
    d->frameRendered(microseconds);
}
