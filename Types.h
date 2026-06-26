#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

enum class AppPhase {
    Opening,
    Performance
};

enum class DrawTool {
    FoldingLines,
    PaintLineCircle,
    ParallelLines,
    Square
};

struct Controls {
    Color color = WHITE;
    float hue = 0.0f;

    float thickness = 4.0f;
    int spacing = 40;
    int intensity = 45;

    int repeatOffset = 20;
    int numRepeats = 1;

    bool collapseMode = false;
    bool repeatMode = false;

    DrawTool currentTool = DrawTool::FoldingLines;
};

struct VisualEvent {
    DrawTool tool;

    int centerX;
    int centerY;

    Color color;
    float thickness;
    int spacing;
    int intensity;

    int repeatOffset;
    int numRepeats;

    bool collapseMode;
    bool repeatMode;

    int linesShown = 0;
    bool finished = false;
};

#endif