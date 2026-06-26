#include "raylib.h"

#include "Types.h"
#include "Events.h"
#include "Actions.h"
#include "ControlMapping.h"
#include "Opening.h"
#include "MidiInput.h"
#include "MidiActions.h"
#include "UI.h"


#include <vector>
#include <iostream>

int main() {
    constexpr int infoBarWidth = 250;
    constexpr int canvasWidth = 1024;
    constexpr int canvasHeight = 768;

    constexpr int screenWidth = infoBarWidth + canvasWidth;
    constexpr int screenHeight = canvasHeight;

    InitWindow(screenWidth, screenHeight, "final_project");
    PrintMidiInputDevices();
    int midiDeviceId = 0;
    bool midiReady = OpenMidiInput(midiDeviceId);

    SetTargetFPS(60);

    Controls controls;
    controls.color = BLUE;
    controls.currentTool = DrawTool::FoldingLines;

    std::vector<VisualEvent> events;

    AppPhase phase = AppPhase::Opening;
    float openingStartTime = static_cast<float>(GetTime());

    bool openingVisible = true;
    Controls openingFinalControls;

    Camera2D canvasCamera = {};
    canvasCamera.offset = {
        static_cast<float>(infoBarWidth),
        0.0f
    };
    canvasCamera.target = {0.0f, 0.0f};
    canvasCamera.rotation = 0.0f;
    canvasCamera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        std::vector<MidiEvent> midiEvents = PollMidiEvents();
    

    for (const MidiEvent& event : midiEvents) {
        if (IsMidiNoteOn(event)) {
            std::cout << "NOTE ON - Data1: " << event.data1
                    << " Data2: " << event.data2 << std::endl;
        }

        if (IsMidiControlChange(event)) {
            std::cout << "CONTROL CHANGE - Data1: " << event.data1
                    << " Data2: " << event.data2 << std::endl;
        }
    }

    float currentTime = static_cast<float>(GetTime());
    float openingElapsed = currentTime - openingStartTime;

    if (phase == AppPhase::Opening) {
        HandleKeyboardParameterInput(controls);
        HandleMidiParameterInput(midiEvents, controls);

        if (IsOpeningFinished(openingElapsed)) {
            openingFinalControls = controls;
            phase = AppPhase::Performance;
        }
    } else {
        HandleKeyboardInput(
            controls,
            events,
            canvasWidth,
            canvasHeight,
            openingVisible
        );

        HandleMidiInput(
            midiEvents,
            controls,
            events,
            canvasWidth,
            canvasHeight,
            openingVisible
        );

        UpdateEvents(events);
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginScissorMode(infoBarWidth, 0, canvasWidth, canvasHeight);
    BeginMode2D(canvasCamera);

    if (openingVisible) {
        if (phase == AppPhase::Opening) {
            DrawOpeningSequence(
                openingElapsed,
                controls,
                canvasWidth,
                canvasHeight
            );
        } else {
            DrawOpeningSequence(
                OPENING_DURATION_SECONDS,
                openingFinalControls,
                canvasWidth,
                canvasHeight
            );
        }
    }

    if (phase == AppPhase::Performance) {
        DrawEvents(events);
    }

    EndMode2D();
    EndScissorMode();

    DrawInfoBar(
        controls,
        phase,
        static_cast<int>(events.size()),
        openingVisible,
        canvasHeight
    );

    EndDrawing();
    }


    if (midiReady) {
        CloseMidiInput();
    }

    CloseWindow();
    return 0;
}
