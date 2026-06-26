#include "Actions.h"
#include "Events.h"
#include "raylib.h"

void PressCell(int row,
               int col,
               int canvasWidth,
               int canvasHeight,
               const Controls& controls,
               std::vector<VisualEvent>& events) {
    events.push_back(
        CreateEventAtCell(row, col, canvasWidth, canvasHeight, controls)
    );
}

void SelectTool(Controls& controls, DrawTool tool) {
    controls.currentTool = tool;
}

void ToggleCollapseMode(Controls& controls) {
    controls.collapseMode = !controls.collapseMode;
}

void ToggleRepeatMode(Controls& controls) {
    controls.repeatMode = !controls.repeatMode;
}

void WipeCanvas(std::vector<VisualEvent>& events, bool& openingVisible) {
    events.clear();
    openingVisible = false;
}

void HandleKeyboardParameterInput(Controls& controls) {
    if (IsKeyPressed(KEY_G)) {
        AdjustColorHue(controls, -10.0f);
    }

    if (IsKeyPressed(KEY_H)) {
        AdjustColorHue(controls, 10.0f);
    }

    if (IsKeyPressed(KEY_Z)) {
        AdjustThickness(controls, -1.0f);
    }

    if (IsKeyPressed(KEY_X)) {
        AdjustThickness(controls, 1.0f);
    }

    if (IsKeyPressed(KEY_C)) {
        AdjustSpacing(controls, -5);
    }

    if (IsKeyPressed(KEY_V)) {
        AdjustSpacing(controls, 5);
    }

    if (IsKeyPressed(KEY_B)) {
        AdjustIntensity(controls, -5);
    }

    if (IsKeyPressed(KEY_N)) {
        AdjustIntensity(controls, 5);
    }

    if (IsKeyPressed(KEY_M)) {
        AdjustRepeatOffset(controls, -5);
    }

    if (IsKeyPressed(KEY_COMMA)) {
        AdjustRepeatOffset(controls, 5);
    }

    if (IsKeyPressed(KEY_PERIOD)) {
        AdjustNumRepeats(controls, -1);
    }

    if (IsKeyPressed(KEY_SLASH)) {
        AdjustNumRepeats(controls, 1);
    }
}

void HandleKeyboardInput(Controls& controls,
                         std::vector<VisualEvent>& events,
                         int canvasWidth,
                         int canvasHeight,
                         bool& openingVisible) {
    HandleKeyboardParameterInput(controls);

    if (IsKeyPressed(KEY_Q)) {
        SelectTool(controls, DrawTool::FoldingLines);
    }

    if (IsKeyPressed(KEY_W)) {
        SelectTool(controls, DrawTool::PaintLineCircle);
    }

    if (IsKeyPressed(KEY_E)) {
        SelectTool(controls, DrawTool::ParallelLines);
    }

    if (IsKeyPressed(KEY_D)) {
        SelectTool(controls, DrawTool::Square);
    }

    if (IsKeyPressed(KEY_A)) {
        ToggleCollapseMode(controls);
    }

    if (IsKeyPressed(KEY_S)) {
        ToggleRepeatMode(controls);
    }

    if (IsKeyPressed(KEY_R)) {
        WipeCanvas(events, openingVisible);
    }

    if (IsKeyPressed(KEY_ONE)) {
        PressCell(0, 0, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_TWO)) {
        PressCell(0, 1, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_THREE)) {
        PressCell(0, 2, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_FOUR)) {
        PressCell(1, 0, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_FIVE)) {
        PressCell(1, 1, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_SIX)) {
        PressCell(1, 2, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_SEVEN)) {
        PressCell(2, 0, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_EIGHT)) {
        PressCell(2, 1, canvasWidth, canvasHeight, controls, events);
    }

    if (IsKeyPressed(KEY_NINE)) {
        PressCell(2, 2, canvasWidth, canvasHeight, controls, events);
    }
}
    //toggle 

float ClampFloat(float value, float minValue, float maxValue) {
    if (value < minValue) {
        return minValue;
    }

    if (value > maxValue) {
        return maxValue;
    }

    return value;
}

int ClampInt(int value, int minValue, int maxValue) {
    if (value < minValue) {
        return minValue;
    }

    if (value > maxValue) {
        return maxValue;
    }

    return value;
}

void AdjustColorHue(Controls& controls, float amount) {
    controls.hue += amount;

    if (controls.hue < 0.0f) {
        controls.hue += 360.0f;
    }

    if (controls.hue > 360.0f) {
        controls.hue -= 360.0f;
    }

    controls.color = ColorFromHSV(controls.hue, 0.85f, 1.0f);
}

void AdjustThickness(Controls& controls, float amount) {
    controls.thickness = ClampFloat(controls.thickness + amount, 1.0f, 30.0f);
}

void AdjustSpacing(Controls& controls, int amount) {
    controls.spacing = ClampInt(controls.spacing + amount, 5, 90);
}

void AdjustIntensity(Controls& controls, int amount) {
    controls.intensity = ClampInt(controls.intensity + amount, 5, 100);
}

void AdjustRepeatOffset(Controls& controls, int amount) {
    controls.repeatOffset = ClampInt(controls.repeatOffset + amount, -120, 120);
}

void AdjustNumRepeats(Controls& controls, int amount) {
    controls.numRepeats = ClampInt(controls.numRepeats + amount, 1, 20);
}

