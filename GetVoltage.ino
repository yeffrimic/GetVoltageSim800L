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



int GetBatteryAverage() {

  int average = 0;
  String nivel = "";
  int nivelint = 0;
  for (int i = 0; i < 5; i++) {
    nivel = GetBattery();
 //   Serial.print(F("nivel string = "));
 //   Serial.println(nivel);
    nivelint = nivel.toInt();
 //   Serial.print(F("nivel int = "));
 //   Serial.println(nivelint);
    average += nivelint;
 //   Serial.print(F("average int = "));
 //   Serial.println(average);
 //   Serial.println("vuelta numero" + i);
  }
  average /= 5;
 // Serial.print(F("average int total = "));
 // Serial.println(average);
  return average;
}

String GetBattery () {
  String result;
  result = GPRScommnad ("AT+CBC");
  int firstindex = result.indexOf(',');
  int secondindex = result.indexOf(',', firstindex + 1);
  String command = result.substring(0, firstindex);
  String level = result.substring(firstindex + 1, secondindex);
  return level;
}

void loop() // run over and over
{
  Serial.println(GetBatteryAverage());
  delay(1000);
}
