#include "FoldingLines.h"
#include <cmath>

void DrawFoldingLines(int linesToShow,
                      int centerX,
                      int centerY,
                      int lineLength,
                      int verticalSpan,
                      int spacing,
                      float thickness,
                      Color color) {
    int startX = centerX - lineLength / 2;
    int endX = centerX + lineLength / 2;

    int startY = centerY - verticalSpan / 2;
    int endY = centerY + verticalSpan / 2;

    for (int i = 0; i < linesToShow; ++i) {
        Vector2 startPoint = {
            static_cast<float>(startX),
            static_cast<float>(startY + i * spacing)
        };

        Vector2 endPoint = {
            static_cast<float>(endX),
            static_cast<float>(endY - i * spacing)
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawDiagonalFoldingField(int linesToShow,
                              int centerX,
                              int centerY,
                              int index,
                              int offsetStep,
                              int lineLength,
                              int verticalSpan,
                              int spacing,
                              float thickness,
                              Color color) {
    int offsetX = static_cast<int>(index * offsetStep * 1.333f);
    int offsetY = index * offsetStep;

    DrawFoldingLines(
        linesToShow,
        centerX + offsetX,
        centerY + offsetY,
        lineLength,
        verticalSpan,
        spacing,
        thickness,
        color
    );
}

void DrawParallelogramLines(int linesToShow,
                            int centerX,
                            int centerY,
                            int lineLength,
                            int spacing,
                            int shearPerLine,
                            float thickness,
                            Color color) {
    float halfLength = lineLength / 2.0f;

    for (int i = 0; i < linesToShow; ++i) {
        float centeredIndex = i - linesToShow / 2.0f;

        float y = centerY + centeredIndex * spacing;
        float xShift = centeredIndex * shearPerLine;

        Vector2 startPoint = {
            centerX - halfLength + xShift,
            y
        };

        Vector2 endPoint = {
            centerX + halfLength + xShift,
            y
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void PaintLineCircle(int linesToShow,
                     int centerX,
                     int centerY,
                     int index,
                     int offsetDegree,
                     int baseRadius,
                     int radiusStep,
                     float thickness,
                     Color color) {
    int radius = baseRadius - index * radiusStep;

    if (radius <= 0) {
        return;
    }

    for (int i = 0; i < linesToShow; ++i) {
        float angleDegrees = static_cast<float>(i * offsetDegree);
        float angleRadians = angleDegrees * PI / 180.0f;

        float startX = centerX + radius * std::cos(angleRadians);
        float startY = centerY + radius * std::sin(angleRadians);

        Vector2 startPoint = {
            startX,
            startY
        };

        Vector2 endPoint = {
            static_cast<float>(centerX),
            static_cast<float>(centerY)
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawParallelLines(int linesToShow,
                       int centerX,
                       int centerY,
                       int lineLength,
                       int spacing,
                       float angleDegrees,
                       float thickness,
                       Color color) {
    float angleRadians = angleDegrees * PI / 180.0f;

    float dirX = std::cos(angleRadians);
    float dirY = std::sin(angleRadians);

    float perpX = -dirY;
    float perpY = dirX;

    float halfLength = lineLength / 2.0f;

    for (int i = 0; i < linesToShow; ++i) {
        float offset = (i - linesToShow / 2.0f) * spacing;

        float midX = centerX + perpX * offset;
        float midY = centerY + perpY * offset;

        Vector2 startPoint = {
            midX - dirX * halfLength,
            midY - dirY * halfLength
        };

        Vector2 endPoint = {
            midX + dirX * halfLength,
            midY + dirY * halfLength
        };

        DrawLineEx(startPoint, endPoint, thickness, color);
    }
}

void DrawSquareField(int linesToShow,
                     int centerX,
                     int centerY,
                     int baseSize,
                     int spacing,
                     float thickness,
                     Color color) {
    for (int i = 0; i < linesToShow; ++i) {
        int size = baseSize - i * spacing;

        if (size <= 0) {
            return;
        }

        Rectangle rect = {
            static_cast<float>(centerX - size / 2),
            static_cast<float>(centerY - size / 2),
            static_cast<float>(size),
            static_cast<float>(size)
        };

        DrawRectangleLinesEx(rect, thickness, color);
    }
}
