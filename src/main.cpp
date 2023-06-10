#include <Arduino.h>
#include <driver/ledc.h>
#include "soundBoard.h"
#include "virtualTimer.h"
#include <string>

#define SERIAL_DEBUG

#ifdef ARDUINO_ARCH_ESP32
#include "esp_can.h"
// The tx and rx pins are constructor arguments to ESPCan, which default to TX = 5, RX = 4
ESPCAN can_bus{};
#endif

// Initialize timer to call functions at
// specified frequencies.
VirtualTimerGroup read_timer;

// Initialize board.
SoundBoard sound_board;

// Read throttle status from CAN.
CANSignal<SoundBoard::ETCState, 0, 8, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> throttle_status_rx_signal{};
CANRXMessage<1> rx_message{can_bus, sound_board.kCANID, throttle_status_rx_signal};

/**
 * @brief Function that calls the PlaySound
 * function in the timer group.
 */
void ThrottleStatusCheck()
{

  sound_board.PlaySound(throttle_status_rx_signal);

}

void setup()
{

#ifdef SERIAL_DEBUG
  // Initialize serial output
  Serial.begin(9600);
#endif

  // Initialize CAN bus.
  can_bus.Initialize(ICAN::BaudRate::kBaud1M);
  ledcWrite(0, 0);

  // Initialize our timer(s)
  read_timer.AddTimer(100, ThrottleStatusCheck);
}

void loop()
{
  // Necessary to tick the CAN bus to get the throttle_status_rx_sign.
  can_bus.Tick();
  read_timer.Tick(millis());
}