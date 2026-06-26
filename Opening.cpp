#include "Opening.h"
#include "FoldingLines.h"

bool IsOpeningFinished(float elapsedTime) {
    return elapsedTime >= OPENING_DURATION_SECONDS;
}

void DrawOpeningSequence(float elapsedTime,
                         const Controls& controls,
                         int canvasWidth,
                         int canvasHeight) {
    float progress = elapsedTime / OPENING_DURATION_SECONDS;

    if (progress < 0.0f) {
        progress = 0.0f;
    }

    if (progress > 1.0f) {
        progress = 1.0f;
    }

    const int numOpeningFields = 19;

    int linesPerField = controls.intensity;

    int totalLinesToReveal = numOpeningFields * linesPerField;
    int revealedLines = static_cast<int>(progress * totalLinesToReveal);

    int baseCenterX = 0;
    int baseCenterY = 40;

    int offsetStep = 50;
    int lineLength = canvasWidth;
    int verticalSpan = 10;

    for (int fieldIndex = 0; fieldIndex < numOpeningFields; ++fieldIndex) {
        int fieldStartLine = fieldIndex * linesPerField;
        int fieldEndLine = fieldStartLine + linesPerField;

        int linesForThisField = 0;

        if (revealedLines >= fieldEndLine) {
            linesForThisField = linesPerField;
        } else if (revealedLines > fieldStartLine) {
            linesForThisField = revealedLines - fieldStartLine;
        }

        if (linesForThisField > 0) {
            DrawDiagonalFoldingField(
                linesForThisField,
                baseCenterX,
                baseCenterY,
                fieldIndex,
                offsetStep,
                lineLength,
                verticalSpan,
                controls.spacing,
                controls.thickness,
                controls.color
            );
        }
    }
}
