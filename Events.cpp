#include "Events.h"
#include "FoldingLines.h"

VisualEvent CreateEventAtCell(int row,
                              int col,
                              int canvasWidth,
                              int canvasHeight,
                              const Controls& controls) {
    int cellWidth = canvasWidth / 3;
    int cellHeight = canvasHeight / 3;

    int centerX = col * cellWidth + cellWidth / 2;
    int centerY = row * cellHeight + cellHeight / 2;

    VisualEvent event;
    event.tool = controls.currentTool;

    event.centerX = centerX;
    event.centerY = centerY;

    event.color = controls.color;
    event.thickness = controls.thickness;
    event.spacing = controls.spacing;
    event.intensity = controls.intensity;

    event.repeatOffset = controls.repeatOffset;
    event.numRepeats = controls.numRepeats;

    event.collapseMode = controls.collapseMode;
    event.repeatMode = controls.repeatMode;

    event.linesShown = 0;
    event.finished = false;

    return event;
}

void UpdateVisualEvent(VisualEvent& event) {
    if (!event.finished) {
        event.linesShown += 1;

        int totalLinesNeeded = event.intensity;

        if (event.repeatMode) {
            totalLinesNeeded = event.intensity * event.numRepeats;
        }

        if (event.linesShown >= totalLinesNeeded) {
            event.linesShown = totalLinesNeeded;
            event.finished = true;
        }
    }
}

void UpdateEvents(std::vector<VisualEvent>& events) {
    for (VisualEvent& event : events) {
        UpdateVisualEvent(event);
    }
}

void DrawVisualEventAt(const VisualEvent& event,
                       int drawX,
                       int drawY,
                       int linesToShow) {
    int collapseLayers = event.collapseMode ? 10 : 1;

    if (event.tool == DrawTool::FoldingLines) {
        for (int i = 0; i < collapseLayers; ++i) {
            int lineLength = 250 - i * 18;

            if (lineLength <= 20) {
                continue;
            }

            int localIndex = event.collapseMode ? i : 0;

            DrawDiagonalFoldingField(
                linesToShow,
                drawX,
                drawY,
                localIndex,
                10,
                lineLength,
                10,
                event.spacing,
                event.thickness,
                event.color
            );
        }
    } else if (event.tool == DrawTool::PaintLineCircle) {
        int totalCenterShift = 60;

        for (int i = 0; i < collapseLayers; ++i) {
            int denominator = collapseLayers - 1;

            if (denominator <= 0) {
                denominator = 1;
            }

            int centerShift = event.collapseMode
                ? i * totalCenterShift / denominator
                : 0;

            int localX = drawX + centerShift;
            int localY = drawY + centerShift;

            int radius = 120 - i * 8;

            if (radius <= 10) {
                continue;
            }

            PaintLineCircle(
                linesToShow,
                localX,
                localY,
                0,
                event.spacing,
                radius,
                8,
                event.thickness,
                event.color
            );
        }
    } else if (event.tool == DrawTool::ParallelLines) {
        if (event.collapseMode) {
            DrawParallelogramLines(
                linesToShow,
                drawX,
                drawY,
                260,
                event.spacing,
                8,
                event.thickness,
                event.color
            );
        } else {
            DrawParallelLines(
                linesToShow,
                drawX,
                drawY,
                260,
                event.spacing,
                0.0f,
                event.thickness,
                event.color
            );
        }
} else if (event.tool == DrawTool::Square) {
        for (int i = 0; i < collapseLayers; ++i) {
            int diagonalShift = event.collapseMode ? i * 10 : 0;
            int size = 220 - i * 12;

            if (size <= 10) {
                continue;
            }

            DrawSquareField(
                linesToShow,
                drawX + diagonalShift,
                drawY + diagonalShift,
                size,
                event.spacing,
                event.thickness,
                event.color
            );
        }
    }
}

void DrawVisualEvent(const VisualEvent& event) {
    int repeats = event.repeatMode ? event.numRepeats : 1;

    for (int r = 0; r < repeats; ++r) {
        int progressForThisRepeat = event.linesShown - r * event.intensity;

        if (progressForThisRepeat <= 0) {
            continue;
        }

        if (progressForThisRepeat > event.intensity) {
            progressForThisRepeat = event.intensity;
        }

        int offset = r * event.repeatOffset;

        int drawX = event.centerX + offset;
        int drawY = event.centerY + offset;

        DrawVisualEventAt(event, drawX, drawY, progressForThisRepeat);
    }
}

void DrawEvents(const std::vector<VisualEvent>& events) {
    for (const VisualEvent& event : events) {
        DrawVisualEvent(event);
    }
}
