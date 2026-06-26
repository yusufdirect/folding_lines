#include "UI.h"
#include "ControlMapping.h"
#include "raylib.h"

float NormalizeFloat(float value, float minValue, float maxValue) {
    if (value < minValue) {
        value = minValue;
    }

    if (value > maxValue) {
        value = maxValue;
    }

    return (value - minValue) / (maxValue - minValue);
}

void DrawBarText(const char* text, int x, int y, int size, Color color) {
    DrawText(text, x, y, size, color);
}

void DrawSlider(const char* label,
                float value,
                float minValue,
                float maxValue,
                int x,
                int y,
                int width,
                Color fillColor) {
    float normalized = NormalizeFloat(value, minValue, maxValue);

    DrawText(label, x, y, 16, RAYWHITE);

    DrawRectangle(x, y + 22, width, 8, DARKGRAY);
    DrawRectangle(x, y + 22, static_cast<int>(width * normalized), 8, fillColor);
    DrawRectangleLines(x, y + 22, width, 8, RAYWHITE);

    DrawText(TextFormat("%.1f", value), x + width + 10, y + 14, 14, RAYWHITE);
}

void DrawSliderInt(const char* label,
                   int value,
                   int minValue,
                   int maxValue,
                   int x,
                   int y,
                   int width,
                   Color fillColor) {
    float normalized = NormalizeFloat(static_cast<float>(value),
                                      static_cast<float>(minValue),
                                      static_cast<float>(maxValue));

    DrawText(label, x, y, 16, RAYWHITE);

    DrawRectangle(x, y + 22, width, 8, DARKGRAY);
    DrawRectangle(x, y + 22, static_cast<int>(width * normalized), 8, fillColor);
    DrawRectangleLines(x, y + 22, width, 8, RAYWHITE);

    DrawText(TextFormat("%d", value), x + width + 10, y + 14, 14, RAYWHITE);
}

void DrawToggle(const char* label, bool value, int x, int y) {
    DrawText(label, x, y, 16, RAYWHITE);

    Color boxColor = value ? GREEN : DARKGRAY;

    DrawRectangle(x + 120, y - 2, 24, 18, boxColor);
    DrawRectangleLines(x + 120, y - 2, 24, 18, RAYWHITE);

    DrawText(value ? "ON" : "OFF", x + 152, y, 14, RAYWHITE);
}

void DrawInfoBar(const Controls& controls,
                 AppPhase phase,
                 int eventCount,
                 bool openingVisible,
                 int canvasHeight) {
    int barWidth = 250;
    int x = 18;
    int y = 20;

    Color barBackground = {15, 15, 15, 220};
    DrawRectangle(0, 0, barWidth, canvasHeight, barBackground);

    DrawText("KINETIC PAINT", x, y, 22, RAYWHITE);
    y += 38;

    DrawText("PHASE", x, y, 14, GRAY);
    y += 20;

    if (phase == AppPhase::Opening) {
        DrawText("Opening", x, y, 20, YELLOW);
    } else {
        DrawText("Performance", x, y, 20, GREEN);
    }

    y += 38;

    DrawText("TOOL", x, y, 14, GRAY);
    y += 20;
    DrawText(ToolName(controls.currentTool), x, y, 20, RAYWHITE);

    y += 42;

    DrawText("COLOR", x, y, 14, GRAY);
    y += 20;

    DrawRectangle(x, y, 42, 22, controls.color);
    DrawRectangleLines(x, y, 42, 22, RAYWHITE);
    DrawText(TextFormat("Hue %.0f", controls.hue), x + 55, y + 3, 16, RAYWHITE);

    y += 48;

    DrawSlider("Thickness", controls.thickness, 1.0f, 30.0f, x, y, 130, controls.color);
    y += 52;

    DrawSliderInt("Spacing", controls.spacing, 5, 90, x, y, 130, controls.color);
    y += 52;

    DrawSliderInt("Intensity", controls.intensity, 5, 100, x, y, 130, controls.color);
    y += 52;

    DrawSliderInt("Offset", controls.repeatOffset, -120, 120, x, y, 130, controls.color);
    y += 52;

    DrawSliderInt("Repeats", controls.numRepeats, 1, 20, x, y, 130, controls.color);
    y += 58;

    DrawToggle("Collapse", controls.collapseMode, x, y);
    y += 32;

    DrawToggle("Repeat", controls.repeatMode, x, y);
    y += 42;

    DrawText("CANVAS", x, y, 14, GRAY);
    y += 22;

    DrawText(TextFormat("Events: %d", eventCount), x, y, 16, RAYWHITE);
    y += 24;

    DrawText(TextFormat("Opening: %s", openingVisible ? "visible" : "wiped"),
             x, y, 16, RAYWHITE);
}
