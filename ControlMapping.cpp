#include "ControlMapping.h"
#include "raylib.h"

float MapMidiValue(int value, float minValue, float maxValue) {
    if (value < 0) value = 0;
    if (value > 127) value = 127;

    float normalized = value / 127.0f;
    return minValue + normalized * (maxValue - minValue);
}

int MapMidiValueInt(int value, int minValue, int maxValue) {
    return static_cast<int>(MapMidiValue(value, minValue, maxValue));
}

void SetColorFromMidi(Controls& controls, int value) {
    controls.hue = MapMidiValue(value, 0.0f, 360.0f);
    controls.color = ColorFromHSV(controls.hue, 0.85f, 1.0f);
}

void SetThicknessFromMidi(Controls& controls, int value) {
    controls.thickness = MapMidiValue(value, 1.0f, 30.0f);
}

void SetSpacingFromMidi(Controls& controls, int value) {
    controls.spacing = MapMidiValueInt(value, 5, 90);
}

void SetIntensityFromMidi(Controls& controls, int value) {
    controls.intensity = MapMidiValueInt(value, 5, 100);
}

void SetRepeatOffsetFromMidi(Controls& controls, int value) {
    controls.repeatOffset = MapMidiValueInt(value, -120, 120);
}

void SetNumRepeatsFromMidi(Controls& controls, int value) {
    controls.numRepeats = MapMidiValueInt(value, 1, 20);
}

const char* ToolName(DrawTool tool) {
    if (tool == DrawTool::FoldingLines) {
        return "Folding Lines";
    }

    if (tool == DrawTool::PaintLineCircle) {
        return "Paint Line Circle";
    }

    if (tool == DrawTool::ParallelLines) {
        return "Parallel Lines";
    }

    if (tool == DrawTool::Square) {
        return "Square";
    }

    return "Unknown";
}