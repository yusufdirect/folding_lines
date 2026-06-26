#ifndef ACTIONS_H
#define ACTIONS_H

#include <vector>
#include "Types.h"

void PressCell(int row,
               int col,
               int canvasWidth,
               int canvasHeight,
               const Controls& controls,
               std::vector<VisualEvent>& events);

void SelectTool(Controls& controls, DrawTool tool);

void ToggleCollapseMode(Controls& controls);
void ToggleRepeatMode(Controls& controls);

void WipeCanvas(std::vector<VisualEvent>& events, bool& openingVisible);

void HandleKeyboardParameterInput(Controls& controls);

void HandleKeyboardInput(Controls& controls,
                         std::vector<VisualEvent>& events,
                         int canvasWidth,
                         int canvasHeight,
                         bool& openingVisible);

void AdjustColorHue(Controls& controls, float amount);
void AdjustThickness(Controls& controls, float amount);
void AdjustSpacing(Controls& controls, int amount);
void AdjustIntensity(Controls& controls, int amount);
void AdjustRepeatOffset(Controls& controls, int amount);
void AdjustNumRepeats(Controls& controls, int amount);

#endif
