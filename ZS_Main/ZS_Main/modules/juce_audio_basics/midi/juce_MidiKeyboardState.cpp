/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2016 - ROLI Ltd.

   Permission is granted to use this software under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license/

   Permission to use, copy, modify, and/or distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
   FITNESS. IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
   OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
   TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
   OF THIS SOFTWARE.

   -----------------------------------------------------------------------------

   To release a closed-source product which uses other parts of JUCE not
   licensed under the ISC terms, commercial licenses are available: visit
   www.juce.com for more information.

  ==============================================================================
*/

MidiKeyboardState::MidiKeyboardState()
{
    zerostruct (noteStates);
}

MidiKeyboardState::~MidiKeyboardState()
{
}

//==============================================================================
void MidiKeyboardState::reset()
{
    const ScopedLock sl (lock);
    zerostruct (noteStates);
    eventsToAdd.clear();
}

bool MidiKeyboardState::isNoteOn (const int midiChannel, const int n) const noexcept
{
    jassert (midiChannel >= 0 && midiChannel <= 16);

    return isPositiveAndBelow (n, (int) 128)
            && (noteStates[n] & (1 << (midiChannel - 1))) != 0;
}

bool MidiKeyboardState::isNoteOnForChannels (const int midiChannelMask, const int n) const noexcept
{
    return isPositiveAndBelow (n, (int) 128)
            && (noteStates[n] & midiChannelMask) != 0;
}

void MidiKeyboardState::noteOn (const int midiChannel, const int midiNoteNumber, const float velocity)
{
    jassert (midiChannel >= 0 && midiChannel <= 16);
    jassert (isPositiveAndBelow (midiNoteNumber, (int) 128));

    const ScopedLock sl (lock);

    if (isPositiveAndBelow (midiNoteNumber, (int) 128))
    {
        const int timeNow = (int) Time::getMillisecondCounter();
        eventsToAdd.addEvent (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity), timeNow);
        eventsToAdd.clear (0, timeNow - 500);

        noteOnInternal (midiChannel, midiNoteNumber, velocity);
    }
}

void MidiKeyboardState::noteOnInternal  (const int midiChannel, const int midiNoteNumber, const float velocity)
{
    if (isPositiveAndBelow (midiNoteNumber, (int) 128))
    {
        noteStates [midiNoteNumber] |= (1 << (midiChannel - 1));

        for (int i = listeners.size(); --i >= 0;)
            listeners.getUnchecked(i)->handleNoteOn (this, midiChannel, midiNoteNumber, velocity);
    }
}

void MidiKeyboardState::noteOff (const int midiChannel, const int midiNoteNumber, const float velocity)
{
    const ScopedLock sl (lock);

    if (isNoteOn (midiChannel, midiNoteNumber))
    {
        const int timeNow = (int) Time::getMillisecondCounter();
        eventsToAdd.addEvent (MidiMessage::noteOff (midiChannel, midiNoteNumber), timeNow);
        eventsToAdd.clear (0, timeNow - 500);

        noteOffInternal (midiChannel, midiNoteNumber, velocity);
    }
}

void MidiKeyboardState::noteOffInternal  (const int midiChannel, const int midiNoteNumber, const float velocity)
{
    if (isNoteOn (midiChannel, midiNoteNumber))
    {
        noteStates [midiNoteNumber] &= ~(1 << (midiChannel - 1));

        for (int i = listeners.size(); --i >= 0;)
            listeners.getUnchecked(i)->handleNoteOff (this, midiChannel, midiNoteNumber, velocity);
    }
}

void MidiKeyboardState::allNotesOff (const int midiChannel)
{
    const ScopedLock sl (lock);

    if (midiChannel <= 0)
    {
        for (int i = 1; i <= 16; ++i)
            allNotesOff (i);
    }
    else
    {
        for (int i = 0; i < 128; ++i)
            noteOff (midiChannel, i, 0.0f);
    }
}

void MidiKeyboardState::processNextMidiEvent (const MidiMessage& message)
{
    if (message.isNoteOn())
    {
        noteOnInternal (message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
    }
    else if (message.isNoteOff())
    {
        noteOffInternal (message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
    }
    else if (message.isAllNotesOff())
    {
        for (int i = 0; i < 128; ++i)
            noteOffInternal (message.getChannel(), i, 0.0f);
    }
}

void MidiKeyboardState::processNextMidiBuffer (MidiBuffer& buffer,
                                               const int startSample,
                                               const int numSamples,
                                               const bool injectIndirectEvents)
{
    MidiBuffer::Iterator i (buffer);
    MidiMessage message;
    int time;

    const ScopedLock sl (lock);

    while (i.getNextEvent (message, time))
        processNextMidiEvent (message);

    if (injectIndirectEvents)
    {
        MidiBuffer::Iterator i2 (eventsToAdd);
        const int firstEventToAdd = eventsToAdd.getFirstEventTime();
        const double scaleFactor = numSamples / (double) (eventsToAdd.getLastEventTime() + 1 - firstEventToAdd);

        while (i2.getNextEvent (message, time))
        {
            const int pos = jlimit (0, numSamples - 1, roundToInt ((time - firstEventToAdd) * scaleFactor));
            buffer.addEvent (message, startSample + pos);
        }
    }

    eventsToAdd.clear();
}

//==============================================================================
void MidiKeyboardState::addListener (MidiKeyboardStateListener* const listener)
{
    const ScopedLock sl (lock);
    listeners.addIfNotAlreadyThere (listener);
}

void MidiKeyboardState::removeListener (MidiKeyboardStateListener* const listener)
{
    const ScopedLock sl (lock);
    listeners.removeFirstMatchingValue (listener);
}
