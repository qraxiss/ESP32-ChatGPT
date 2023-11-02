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
  Serial.println("\r\nRecord start!\r\n");
  Audio *audio = new Audio(ICS43434);
  audio->Record();
  Serial.println("Recording Completed. Now Processing...");
  String data = cloudSpeechClient->Transcribe(audio);
  delete audio;

  return data;
}

void setup()
{

  Serial.begin(115200, SERIAL_8N1, RXp2, TXp2);
  Serial2.begin(9600)

      cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);

  delay(500);
}

void loop()
{

  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    if (data.length() > 0)
    {
      float floatData = data.toFloat();
      Serial.print("floatData: ");
      Serial.print(floatData, 2);

      if (floatData > 0.5)
      {
        String transcript = record();
        Serial.println(transcript);
      }
    }
  }
}
