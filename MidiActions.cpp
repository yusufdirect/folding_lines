#include "MidiActions.h"

#include "Actions.h"
#include "ControlMapping.h"

void HandleMidiParameterInput(const std::vector<MidiEvent>& midiEvents,
                              Controls& controls) {
    for (const MidiEvent& event : midiEvents) {
        if (!IsMidiControlChange(event)) {
            continue;
        }

        if (event.data1 == 0) {
            SetColorFromMidi(controls, event.data2);
        } else if (event.data1 == 1) {
            SetThicknessFromMidi(controls, event.data2);
        } else if (event.data1 == 2) {
            SetSpacingFromMidi(controls, event.data2);
        } else if (event.data1 == 3) {
            SetIntensityFromMidi(controls, event.data2);
        } else if (event.data1 == 4) {
            SetRepeatOffsetFromMidi(controls, event.data2);
        } else if (event.data1 == 5) {
            SetNumRepeatsFromMidi(controls, event.data2);
        }
    }
}

void HandleMidiInput(const std::vector<MidiEvent>& midiEvents,
                     Controls& controls,
                     std::vector<VisualEvent>& events,
                     int canvasWidth,
                     int canvasHeight,
                     bool& openingVisible) {
    HandleMidiParameterInput(midiEvents, controls);

    for (const MidiEvent& event : midiEvents) {
        if (!IsMidiNoteOn(event)) {
            continue;
        }

        int note = event.data1;

        // Top-left 3x3 screen-location buttons
        if (note == 60) {
            PressCell(0, 0, canvasWidth, canvasHeight, controls, events);
        } else if (note == 61) {
            PressCell(0, 1, canvasWidth, canvasHeight, controls, events);
        } else if (note == 62) {
            PressCell(0, 2, canvasWidth, canvasHeight, controls, events);
        } else if (note == 64) {
            PressCell(1, 0, canvasWidth, canvasHeight, controls, events);
        } else if (note == 65) {
            PressCell(1, 1, canvasWidth, canvasHeight, controls, events);
        } else if (note == 66) {
            PressCell(1, 2, canvasWidth, canvasHeight, controls, events);
        } else if (note == 68) {
            PressCell(2, 0, canvasWidth, canvasHeight, controls, events);
        } else if (note == 69) {
            PressCell(2, 1, canvasWidth, canvasHeight, controls, events);
        } else if (note == 70) {
            PressCell(2, 2, canvasWidth, canvasHeight, controls, events);
        }

        // Right column special buttons
        else if (note == 63) {
            ToggleCollapseMode(controls);
        } else if (note == 67) {
            ToggleRepeatMode(controls);
        } else if (note == 71) {
            SelectTool(controls, DrawTool::Square);
        }

        // Bottom row tool/action buttons
        else if (note == 72) {
            SelectTool(controls, DrawTool::FoldingLines);
        } else if (note == 73) {
            SelectTool(controls, DrawTool::PaintLineCircle);
        } else if (note == 74) {
            SelectTool(controls, DrawTool::ParallelLines);
        } else if (note == 75) {
            WipeCanvas(events, openingVisible);
        }
    }
}
