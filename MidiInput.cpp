#include "MidiInput.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include <iostream>
#include <queue>
#include <mutex>

static HMIDIIN midiInHandle = nullptr;
static bool midiIsOpen = false;

static std::queue<MidiEvent> midiQueue;
static std::mutex midiMutex;

void CALLBACK MidiCallback(HMIDIIN handle,
                           UINT message,
                           DWORD_PTR instance,
                           DWORD_PTR param1,
                           DWORD_PTR param2) {
    if (message == MIM_DATA) {
        unsigned int midiMessage = static_cast<unsigned int>(param1);

        MidiEvent event;
        event.status = midiMessage & 0xFF;
        event.data1 = (midiMessage >> 8) & 0xFF;
        event.data2 = (midiMessage >> 16) & 0xFF;

        std::lock_guard<std::mutex> lock(midiMutex);
        midiQueue.push(event);
    }
}

void PrintMidiInputDevices() {
    unsigned int deviceCount = midiInGetNumDevs();

    std::cout << "MIDI input devices found: " << deviceCount << std::endl;

    for (unsigned int i = 0; i < deviceCount; ++i) {
        MIDIINCAPSA caps;

        MMRESULT result = midiInGetDevCapsA(i, &caps, sizeof(MIDIINCAPSA));

        if (result == MMSYSERR_NOERROR) {
            std::cout << i << ": " << caps.szPname << std::endl;
        }
    }
}

bool OpenMidiInput(int deviceId) {
    if (midiIsOpen) {
        return true;
    }

    unsigned int deviceCount = midiInGetNumDevs();

    if (deviceCount == 0) {
        std::cout << "No MIDI input devices found." << std::endl;
        return false;
    }

    if (deviceId < 0 || deviceId >= static_cast<int>(deviceCount)) {
        std::cout << "Invalid MIDI device id: " << deviceId << std::endl;
        return false;
    }

    MMRESULT result = midiInOpen(
        &midiInHandle,
        deviceId,
        reinterpret_cast<DWORD_PTR>(MidiCallback),
        0,
        CALLBACK_FUNCTION
    );

    if (result != MMSYSERR_NOERROR) {
        std::cout << "Failed to open MIDI input device." << std::endl;
        return false;
    }

    midiInStart(midiInHandle);
    midiIsOpen = true;

    std::cout << "MIDI input opened on device " << deviceId << "." << std::endl;

    return true;
}

void CloseMidiInput() {
    if (!midiIsOpen) {
        return;
    }

    midiInStop(midiInHandle);
    midiInClose(midiInHandle);

    midiInHandle = nullptr;
    midiIsOpen = false;

    std::cout << "MIDI input closed." << std::endl;
}

std::vector<MidiEvent> PollMidiEvents() {
    std::vector<MidiEvent> events;

    std::lock_guard<std::mutex> lock(midiMutex);

    while (!midiQueue.empty()) {
        events.push_back(midiQueue.front());
        midiQueue.pop();
    }

    return events;
}

bool IsMidiNoteOn(const MidiEvent& event) {
    int messageType = event.status & 0xF0;
    return messageType == 0x90 && event.data2 > 0;
}

bool IsMidiControlChange(const MidiEvent& event) {
    int messageType = event.status & 0xF0;
    return messageType == 0xB0;
}