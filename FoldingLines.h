#ifndef FOLDINGLINES_H
#define FOLDINGLINES_H

#include "raylib.h"

void DrawFoldingLines(int linesToShow,
                      int centerX,
                      int centerY,
                      int lineLength,
                      int verticalSpan,
                      int spacing,
                      float thickness,
                      Color color);

void DrawDiagonalFoldingField(int linesToShow,
                              int centerX,
                              int centerY,
                              int index,
                              int offsetStep,
                              int lineLength,
                              int verticalSpan,
                              int spacing,
                              float thickness,
                              Color color);

void PaintLineCircle(int linesToShow,
                     int centerX,
                     int centerY,
                     int index,
                     int offsetDegree,
                     int baseRadius,
                     int radiusStep,
                     float thickness,
                     Color color);

void DrawParallelLines(int linesToShow,
                       int centerX,
                       int centerY,
                       int lineLength,
                       int spacing,
                       float angleDegrees,
                       float thickness,
                       Color color);

void DrawParallelogramLines(int linesToShow,
                            int centerX,
                            int centerY,
                            int lineLength,
                            int spacing,
                            int shearPerLine,
                            float thickness,
                            Color color);

void DrawSquareField(int linesToShow,
                     int centerX,
                     int centerY,
                     int baseSize,
                     int spacing,
                     float thickness,
                     Color color);

#endif