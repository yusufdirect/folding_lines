#ifndef CONTROLMAPPING_H
#define CONTROLMAPPING_H

#include "Types.h"

float MapMidiValue(int value, float minValue, float maxValue);
int MapMidiValueInt(int value, int minValue, int maxValue);

void SetColorFromMidi(Controls& controls, int value);
void SetThicknessFromMidi(Controls& controls, int value);
void SetSpacingFromMidi(Controls& controls, int value);
void SetIntensityFromMidi(Controls& controls, int value);
void SetRepeatOffsetFromMidi(Controls& controls, int value);
void SetNumRepeatsFromMidi(Controls& controls, int value);

const char* ToolName(DrawTool tool);

#endif