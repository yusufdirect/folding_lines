#ifndef MIDIACTIONS_H
#define MIDIACTIONS_H

#include <vector>

#include "Types.h"
#include "MidiInput.h"

void HandleMidiParameterInput(const std::vector<MidiEvent>& midiEvents,
                              Controls& controls);

void HandleMidiInput(const std::vector<MidiEvent>& midiEvents,
                     Controls& controls,
                     std::vector<VisualEvent>& events,
                     int canvasWidth,
                     int canvasHeight,
                     bool& openingVisible);

#endif
