#ifndef OPENING_H
#define OPENING_H

#include "Types.h"

constexpr float OPENING_DURATION_SECONDS = 10.0f;

bool IsOpeningFinished(float elapsedTime);

void DrawOpeningSequence(float elapsedTime,
                         const Controls& controls,
                         int canvasWidth,
                         int canvasHeight);

#endif
