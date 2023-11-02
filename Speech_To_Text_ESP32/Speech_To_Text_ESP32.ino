#include "Audio.h"
#include "CloudSpeechClient.h"

CloudSpeechClient *cloudSpeechClient;

String record()
{
  Serial.println("\r\nRecord start!\r\n");
  Audio *audio = new Audio(ICS43434);
  audio->Record();
  Serial.println("Recording Completed. Now Processing...");
  String data = cloudSpeechClient->Transcribe(audio);
  Serial.println(data);
  delete audio;

  return data;
}

void setup()
{
  cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
  Serial.begin(115200);
  delay(500);
}

void loop()
{
  record();
  delay(1000);
}
