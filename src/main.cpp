#include <Arduino.h>
#include <driver/ledc.h>

int channel = 0;
int resolution = 8;
double notes[] = {293.66/2, 392, 440, 587.33};
double noteDurations[] = {300, 100, 100, 100};
bool soundPlayed = false;

void setup() {
  ledcAttachPin(23, channel);
  ledcSetup(channel, 392, resolution);
}

void loop() {
  if (!soundPlayed) {
    ledcWrite(channel, 127);
    for (int i = 0; i < 1000; i++) {
      ledcWriteTone(channel, notes[i]);
      delay(noteDurations[i] + 100);
    }
    ledcWrite(channel, 0);
    soundPlayed = true;
  }

}