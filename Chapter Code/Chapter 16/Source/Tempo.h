#pragma once

#include <JuceHeader.h>

class Tempo
{
public:
    void reset() noexcept;

    void update(const juce::AudioPlayHead* playhead) noexcept;

    double getMillisecondsForNoteLength(int index) const noexcept;

    double getTempo() const noexcept
    {
        return bpm;
    }

private:
    double bpm = 120.0;
};
