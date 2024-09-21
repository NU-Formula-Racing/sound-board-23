#include <array>
/**
 * @brief  Sound board class.
 */
class SoundBoard
{
public:
    // Constructor
    SoundBoard();

    const uint16_t kCANID{0x000};
    const int ledcChannel = 0;
    const int ledcPin = 17; // Change to the pin you are using for the speaker

    // Define the LEDC timer parameters
    const int ledcTimer = 0;
    const int ledcResolution = 8;  // 8-bit resolution
    const int ledcBaseFreq = 5000; // Base frequency (Hz)

    enum class ETCState;

    void PlaySound(ETCState state);
    void Initialize();
    void PlayTone(int freq, int duration);

private:
    int channel;
    int resolution;
    std::array<double, 4> notes;
    std::array<double, 4> noteDurations;
    ETCState previousState;
};