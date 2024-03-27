#include <JuceHeader.h>
#include "DelayLine.h"

void DelayLine::setMaximumDelayInSamples(int maxLengthInSamples)
{
    jassert(maxLengthInSamples > 0);

    int paddedLength = maxLengthInSamples + 2;
    if (bufferLength < paddedLength) {
        bufferLength = paddedLength;
        buffer.reset(new float[size_t(bufferLength)]);
    }
}

void DelayLine::reset() noexcept
{
    writeIndex = bufferLength - 1;

    for (size_t i = 0; i < size_t(bufferLength); ++i) {
        buffer[i] = 0.0f;
    }
}

void DelayLine::write(float input) noexcept
{
    jassert(bufferLength > 0);

    writeIndex += 1;
    if (writeIndex >= bufferLength) {
        writeIndex = 0;
    }

    buffer[size_t(writeIndex)] = input;
}

/*
// Nearest neighbors
float DelayLine::read(float delayInSamples) const noexcept
{
    jassert(delayInSamples >= 0.0f);
    jassert(delayInSamples <= bufferLength - 1.0f);

    int readIndex = int(std::round(writeIndex - delayInSamples));
    if (readIndex < 0) {
        readIndex += bufferLength;
    }

    return buffer[size_t(readIndex)];
}
*/

/*
// Linear interpolation
float DelayLine::read(float delayInSamples) const noexcept
{
    jassert(delayInSamples >= 0.0f);
    jassert(delayInSamples <= bufferLength - 1.0f);

    int integerDelay = int(delayInSamples);

    int readIndexA = writeIndex - integerDelay;
    if (readIndexA < 0) {
        readIndexA += bufferLength;
    }

    int readIndexB = readIndexA - 1;
    if (readIndexB < 0) {
        readIndexB += bufferLength;
    }

    float sampleA = buffer[size_t(readIndexA)];
    float sampleB = buffer[size_t(readIndexB)];

    float fraction = delayInSamples - float(integerDelay);
    return sampleA + fraction * (sampleB - sampleA);
}
*/

float DelayLine::read(float delayInSamples) const noexcept
{
    jassert(delayInSamples >= 1.0f);
    jassert(delayInSamples <= bufferLength - 2.0f);

    int integerDelay = int(delayInSamples);

    int readIndexA = writeIndex - integerDelay + 1;
    int readIndexB = readIndexA - 1;
    int readIndexC = readIndexA - 2;
    int readIndexD = readIndexA - 3;

    if (readIndexD < 0) {
        readIndexD += bufferLength;
        if (readIndexC < 0) {
            readIndexC += bufferLength;
            if (readIndexB < 0) {
                readIndexB += bufferLength;
                if (readIndexA < 0) {
                    readIndexA += bufferLength;
                }
            }
        }
    }

    float sampleA = buffer[size_t(readIndexA)];
    float sampleB = buffer[size_t(readIndexB)];
    float sampleC = buffer[size_t(readIndexC)];
    float sampleD = buffer[size_t(readIndexD)];

    float fraction = delayInSamples - float(integerDelay);
    float slope0 = (sampleC - sampleA) * 0.5f;
    float slope1 = (sampleD - sampleB) * 0.5f;
    float v = sampleB - sampleC;
    float w = slope0 + v;
    float a = w + v + slope1;
    float b = w + a;
    float stage1 = a * fraction - b;
    float stage2 = stage1 * fraction + slope0;
    return stage2 * fraction + sampleB;
}
