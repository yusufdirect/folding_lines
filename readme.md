https://yusuf.direct/work/folding-lines

# Folding Lines

**Folding Lines** is an exploration of human-machine interaction through the visualization of abstract lines in motion. Built with C++, raylib, a screen, and a small MIDI board, the project turns drawing into a live visual performance where the user does not directly paint, but instead controls a system that generates, repeats, folds, and collapses line-based compositions.

Heavily inspired by Samia Halaby’s *Kinetic Paintings*, **Folding Lines** is built around the capabilities of its own materials: C++, raylib, a MIDI board, and a screen. The project does not use code to imitate brushstrokes, or the MIDI board to imitate a pencil. Instead, it uses these tools for what they are especially capable of producing: sequence, repetition, interaction, delay, and transformation. In this sense, the project follows Halaby’s statement that “you use a material for what it is capable of doing, so you do not make something out of wood that should be made out of iron.”

## Overview

The program begins with an animated opening sequence of folding diagonal line fields. After the opening, the user enters a performance mode where a MIDI controller is used to place visual events onto a 3x3 canvas grid.

The user can select different drawing tools, control visual parameters, toggle repeat behavior, toggle collapse behavior, and wipe the canvas. The piece is meant to behave like a small visual instrument: the user performs with the system, but the system also unfolds its own visual consequences over time.

## Features

* Animated opening sequence
* MIDI-controlled 3x3 canvas placement
* Four visual tools:

  * Folding Lines
  * Radial Line Circle
  * Parallel Lines
  * Square Field
* Live parameter control:

  * Color
  * Thickness
  * Spacing
  * Intensity
  * Repeat offset
  * Number of repeats
* Repeat mode, where repeated forms are drawn one after another
* Collapse mode, where tools transform into denser or shifted versions of themselves
* Left-side information bar showing the current tool, parameters, toggles, and canvas state
* Keyboard fallback controls for testing without the MIDI controller

## Hardware

The project was designed for a small 4x4 MIDI pad controller with rotary controls. The version used during development was a WORLDE / Worlde ORCA PAD-style MIDI controller.

The project can still be tested with keyboard controls if no MIDI controller is connected.

## Software Requirements

This project was developed and tested on Windows using MSYS2 UCRT64.

Required libraries/tools:

* C++ compiler with C++17 support
* raylib
* Windows multimedia library `winmm`
* MSYS2 UCRT64 environment

## Build Instructions

### Recommended Windows / MSYS2 UCRT64 build

Open the **MSYS2 UCRT64** terminal and install the required packages if needed:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib
```

Then compile from the project folder:

```bash
g++ main.cpp Events.cpp Actions.cpp ControlMapping.cpp Opening.cpp MidiInput.cpp MidiActions.cpp UI.cpp FoldingLines.cpp -o final_project.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Run:

```bash
./final_project.exe
```

## Controls

### MIDI Controls

The MIDI board is mapped as a visual performance interface.

The top-left 3x3 pad area controls where the selected visual tool is placed on the screen:

```text
[Cell 1] [Cell 2] [Cell 3] [Collapse]
[Cell 4] [Cell 5] [Cell 6] [Repeat]
[Cell 7] [Cell 8] [Cell 9] [Square]
[Folding] [Circle] [Parallel] [Wipe]
```

Rotary controls are mapped to:

```text
Color
Thickness
Spacing
Intensity
Repeat Offset
Number of Repeats
```

### Keyboard Backup Controls

The keyboard controls are included for development and testing.

```text
1-9       Place current tool in one of the 3x3 canvas cells

Q         Select Folding Lines
W         Select Radial Line Circle
E         Select Parallel Lines
D         Select Square Field

A         Toggle collapse mode
S         Toggle repeat mode
R         Wipe canvas

G / H     Adjust hue
Z / X     Adjust thickness
C / V     Adjust spacing
B / N     Adjust intensity
M / ,     Adjust repeat offset
. / /     Adjust number of repeats
```

## Project Structure

```text
main.cpp
```

Main program loop. Handles window setup, program phase, MIDI polling, input handling, drawing order, and shutdown.

```text
Types.h
```

Shared enums and data structures, including app phase, drawing tool, controls, and visual event state.

```text
FoldingLines.h / FoldingLines.cpp
```

Low-level drawing functions for folding lines, radial line circles, parallel lines, parallelogram-style collapse, and square fields.

```text
Events.h / Events.cpp
```

Creates, updates, and draws visual events. This is where repeat animation and collapse behavior are handled.

```text
Actions.h / Actions.cpp
```

Keyboard-facing action layer. Converts keyboard input into changes in tools, controls, toggles, and canvas events.

```text
MidiInput.h / MidiInput.cpp
```

Windows MIDI input layer using the Windows multimedia API.

```text
MidiActions.h / MidiActions.cpp
```

Maps MIDI notes and control-change messages to project actions.

```text
ControlMapping.h / ControlMapping.cpp
```

Maps MIDI values into usable visual ranges such as color hue, thickness, spacing, intensity, offset, and repeat count.

```text
Opening.h / Opening.cpp
```

Controls the opening animation sequence.

```text
UI.h / UI.cpp
```

Draws the left-side information bar.

## Statement of Work

This project was designed and implemented as an interactive C++ visual performance system. The main work included setting up raylib, creating the drawing functions, designing the event-based animation system, mapping MIDI input to visual actions, building repeat and collapse behaviors, creating a persistent opening sequence, and adding a live information bar.

The project went through several design iterations. It began as a simple animated line-field sketch and developed into a MIDI-controlled kinetic painting instrument. A major part of the work involved turning drawing functions into reusable visual events that could be placed, repeated, modified, and controlled through physical input.

## AI Use Disclosure

AI tools were used during the development of this project as a coding assistant, debugging partner, and writing assistant. AI helped with brainstorming the architecture, explaining C++ and raylib issues, suggesting file organization, drafting or revising portions of code, debugging compiler/linker errors, and polishing documentation text.

All code included in this repository was reviewed, tested, edited, and integrated by me. I made the final design decisions, selected the project direction, tested the MIDI controller and raylib behavior directly, adjusted the visual output, and verified the final program behavior. AI assistance was used as support during the development process, not as a replacement for understanding or submitting unreviewed work.

## Known Limitations

* MIDI support is currently Windows-specific because it uses the Windows multimedia API.
* The project was primarily tested in MSYS2 UCRT64 on Windows.
* The visual mappings are designed around a specific 4x4 MIDI controller layout.
* Other MIDI controllers may require remapping note and control-change values.
* The project is intended as a live visual instrument, so some behavior is deliberately aesthetic rather than strictly deterministic.

## Credits

Inspired by Samia Halaby’s *Kinetic Paintings* and her writing on material capability, abstraction, and motion.
