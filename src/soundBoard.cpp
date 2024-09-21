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
};

/**
 * @brief Construct a new Sound Board:: Sound Board object.
 *
 */
SoundBoard::SoundBoard()
{
    Serial.println("Sound board created");
    // channel = 0;
    // resolution = 8;
    // notes = {200};         //{293.66 / 2, 392, 440, 587.33};
    // noteDurations = {100}; //{300, 100, 100, 100};
    // // LED Setup

    // ledcSetup(channel, 392, resolution);
    // ledcAttachPin(17, channel);
    // // Set the initial previous state to off.
    // Configure the LEDC timer
    // ledcSetup(ledcChannel, ledcBaseFreq, ledcResolution);

    // // Attach the LEDC channel to the specified pin
    // ledcAttachPin(ledcPin, ledcChannel);
    // previousState = ETCState::OFF;
};

/**
 * @brief Initialize the sound board.
 *
 */
void SoundBoard::Initialize()
{
    // Configure the LEDC timer
    ledcSetup(ledcChannel, ledcBaseFreq, ledcResolution);

    // Attach the LEDC channel to the specified pin
    ledcAttachPin(ledcPin, ledcChannel);
    previousState = ETCState::OFF;
}

/**
 * @brief Play sound if throttle status changes from neutral to drive.
 *
 * @param state: current throttle status read from CAN
 */
void SoundBoard::PlaySound(ETCState state)
{
    // Serial.println("playing sound");
    // // Play sound if throttle status changes from neutral to drive.
    // if (true)
    // {
    //     ledcWrite(channel, 127);
    //     for (int i = 0; i < 1000; i++)
    //     {
    //         ledcWriteTone(channel, notes[i]);
    //         delay(noteDurations[i] + 100);
    //         int dutyCycle = 128; // 50% duty cycle for square wave
    //         // Set the duty cycle for the LEDC channel
    //         ledcWrite(channel, dutyCycle);
    //     }
    //     ledcWrite(channel, 0);
    // }
    // // Update previous state to current state.
    // previousState = state;

    if (previousState == ETCState::N && state == ETCState::DRIVE)
    {
        // Play sound if throttle status changes from neutral to drive.
        // Generate a tone with a frequency of 1000 Hz
        Serial.println("Playing 1000 Hz for 500 ms");
        PlayTone(1000, 500);

        delay(1000); // Wait for a second

        // Generate a tone with a frequency of 2000 Hz
        Serial.println("Playing 2000 Hz for 500 ms");
        PlayTone(2000, 500);

        delay(1000); // Wait for a second

        // Generate a tone with a frequency of 500 Hz
        Serial.println("Playing 500 Hz for 500 ms");
        PlayTone(500, 500);

        delay(1000); // Wait for a second
    }
    previousState = state;
}

void SoundBoard::PlayTone(int freq, int duration)
{
    // Calculate the duty cycle for the given frequency
    int dutyCycle = 128; // 50% duty cycle for square wave

    // Set the frequency for the LEDC channel
    Serial.print("Setting frequency: ");
    Serial.println(freq);
    ledcWriteTone(ledcChannel, freq);

    // Set the duty cycle for the LEDC channel
    Serial.print("Setting duty cycle: ");
    Serial.println(dutyCycle);
    ledcWrite(ledcChannel, dutyCycle);

    // Wait for the specified duration
    delay(duration);

    // Stop the tone
    Serial.println("Stopping tone");
    ledcWriteTone(ledcChannel, 0);
}