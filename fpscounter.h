#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <memory>

class FpsCounterPrivate;

class FpsCounter {
public:
    FpsCounter();
    virtual ~FpsCounter();

    unsigned framesPerSecond() const;

    void frameRendered(unsigned microseconds);

private:
    std::unique_ptr<FpsCounterPrivate> d;

};

#endif // FPSCOUNTER_H
