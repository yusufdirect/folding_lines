#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include "Types.h"

VisualEvent CreateEventAtCell(int row,
                              int col,
                              int canvasWidth,
                              int canvasHeight,
                              const Controls& controls);

void UpdateVisualEvent(VisualEvent& event);
void UpdateEvents(std::vector<VisualEvent>& events);

void DrawVisualEventAt(const VisualEvent& event, int drawX, int drawY);
void DrawVisualEvent(const VisualEvent& event);
void DrawEvents(const std::vector<VisualEvent>& events);

#endif
