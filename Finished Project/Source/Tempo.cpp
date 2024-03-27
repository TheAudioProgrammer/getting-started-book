#include "Tempo.h"

static std::array<double, 16> noteLengthMultipliers =
{
    0.125,        //  0 = 1/32
    0.5 / 3.0,    //  1 = 1/16 triplet
    0.1875,       //  2 = 1/32 dotted
    0.25,         //  3 = 1/16
    1.0 / 3.0,    //  4 = 1/8 triplet
    0.375,        //  5 = 1/16 dotted
    0.5,          //  6 = 1/8
    2.0 / 3.0,    //  7 = 1/4 triplet
    0.75,         //  8 = 1/8 dotted
    1.0,          //  9 = 1/4
    4.0 / 3.0,    // 10 = 1/2 triplet
    1.5,          // 11 = 1/4 dotted
    2.0,          // 12 = 1/2
    8.0 / 3.0,    // 13 = 1/1 triplet
    3.0,          // 14 = 1/2 dotted
    4.0,          // 15 = 1/1
};

void Tempo::reset() noexcept
{
    bpm = 120.0;
}

void Tempo::update(const juce::AudioPlayHead* playhead) noexcept
{
    reset();

    if (playhead == nullptr) { return; }

    const auto opt = playhead->getPosition();
    if (!opt.hasValue()) { return; }

    const auto& pos = *opt;

    if (pos.getBpm().hasValue()) {
        bpm = *pos.getBpm();
    }
}

double Tempo::getMillisecondsForNoteLength(int index) const noexcept
{
    return 60000.0 * noteLengthMultipliers[size_t(index)] / bpm;
}
