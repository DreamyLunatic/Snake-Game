#include <iostream>
#include <raylib.h>

#pragma once

// define a timer
typedef struct
{
    float Lifetime;
}Timer;

// start or restart a timer with a specific lifetime
void StartTimer(Timer* timer, float lifetime)
{
    if (timer != NULL)
        timer->Lifetime = lifetime;
}

// update a timer with the current frame time
void UpdateTimer(Timer* timer)
{
    // subtract this frame from the timer if it's not allready expired
    if (timer != NULL && timer->Lifetime > 0)
        timer->Lifetime -= GetFrameTime();
}

// check if a timer is done.
bool TimerDone(Timer* timer)
{
    if (timer != NULL)
        return timer->Lifetime <= 0;

    return false;
}