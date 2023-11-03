#include "Audio.h"
#include "CloudSpeechClient.h"

#define uart_ens 14
#define RXp0 3
#define TXp0 1
#define RXp2 16
#define TXp2 17

CloudSpeechClient *cloudSpeechClient;

String record()
{
  Audio *audio = new Audio(ICS43434);
  audio->Record();
  String data = cloudSpeechClient->Transcribe(audio);
  delete audio;

  return data;
}

void setup()
{
  Serial.begin(115200);
  cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
}

void loop()
{
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    if (data.length() > 0)
    {
      float floatData = data.toFloat();
      if (floatData > 0.5)
      {
        String transcript = record();
        Serial.print(transcript);
      }
    }
  }
}