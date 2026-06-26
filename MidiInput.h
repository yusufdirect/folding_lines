#ifndef MIDIINPUT_H
#define MIDIINPUT_H

#include <vector>

struct MidiEvent {
    int status;
    int data1;
    int data2;
};

void PrintMidiInputDevices();

bool OpenMidiInput(int deviceId);
void CloseMidiInput();

std::vector<MidiEvent> PollMidiEvents();

bool IsMidiNoteOn(const MidiEvent& event);
bool IsMidiControlChange(const MidiEvent& event);

#endif