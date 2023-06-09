#include <array>
/**
 * @brief  Sound board class.
 */
class SoundBoard
{
public:
    // Constructor
    SoundBoard();

    const uint16_t kCANID{0x301};

    enum class ETCState;

    void PlaySound(ETCState state);

private:
    int channel;
    int resolution;
    std::array<double, 4> notes;
    std::array<double, 4> noteDurations;
    ETCState previousState;
};