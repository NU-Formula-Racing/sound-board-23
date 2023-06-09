#include <Arduino.h>
#include <soundBoard.h>

/**
 * @brief Construct a new class to read the ETC as
 * drive states.
 */
enum class SoundBoard::ETCState
{
    OFF = 0,
    N = 1,
    DRIVE = 2,
    FDRIVE = 3,
};

/**
 * @brief Construct a new Sound Board:: Sound Board object.
 *
 */
SoundBoard::SoundBoard()
{
    channel = 0;
    resolution = 8;
    notes = {293.66 / 2, 392, 440, 587.33};
    noteDurations = {300, 100, 100, 100};
    // LED Setup
    ledcAttachPin(23, channel);
    ledcSetup(channel, 392, resolution);
    // Set the initial previous state to off.
    previousState = ETCState::OFF;
};

/**
 * @brief Play sound if throttle status changes from neutral to drive.
 *
 * @param state: current throttle status read from CAN
 */
void SoundBoard::PlaySound(ETCState state)
{
    // Play sound if throttle status changes from neutral to drive.
    if (previousState == ETCState::N && state == ETCState::DRIVE)
    {
        ledcWrite(channel, 127);
        for (int i = 0; i < 1000; i++)
        {
            ledcWriteTone(channel, notes[i]);
            delay(noteDurations[i] + 100);
        }
        ledcWrite(channel, 0);
    }
    // Update previous state to current state.
    previousState = state;
}