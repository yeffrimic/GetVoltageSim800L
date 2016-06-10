// this sketch is used for testing sim800L with Arduino

// Connect VIO to +3.7 battery
// Connect GND to Ground
// Connect RX (data into SIM800l) to Digital 3
// Connect TX (data out from SIM800l) to Digital 2
#include <SoftwareSerial.h>

SoftwareSerial GSMSrl(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  GSMSrl.begin(9600);
}

String GPRScommnad (String comm) {
  GSMSrl.listen();
  String ATComRsp, response;
  Serial.println("command:" + comm);
  GSMSrl.println(comm);
  delay(500);
  while (GSMSrl.available() > 0) {
    char c = GSMSrl.read();
    if (c == '\n') {
      response += ATComRsp + "|";
      ATComRsp = "";
    } else {
      ATComRsp += c;
    }
  }
  ATComRsp = "";
  GSMSrl.flush();
  Serial.flush();
  return response;
}



int GetBatteryAverage(int samples) {

  int average = 0;
  int nivelint = 0;
  for (int i = 0; i < samples; i++) {
    nivelint = GetBattery();
    //   Serial.print(F("nivel int = "));
    //   Serial.println(nivelint);
    average += nivelint;
    //   Serial.print(F("average int = "));
    //   Serial.println(average);
  }
  average /= samples;
  // Serial.print(F("average int total = "));
  // Serial.println(average);
  return average;
}

int GetBattery () {
  String result;
  result = GPRScommnad ("AT+CBC");
  int firstindex = result.indexOf(',');
  int secondindex = result.indexOf(',', firstindex + 1);
  String command = result.substring(0, firstindex);
  String level = result.substring(firstindex + 1, secondindex);
  int nivelint = 0;
  nivelint = level.toInt();
  return nivelint;
}

void loop() // run over and over
{
  Serial.println(GetBatteryAverage(5));
  delay(1000);
}
