// this sketch is used for testing LoNet with Arduino

// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM808) to Digital 11
// Connect TX (data out from SIM808) to Digital 10

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
  int average;
for(int i =0;i<5;i++){
  String a=GetBattery();
  int d= a.toInt();
  average+=d-3;
  Serial.println(average);
}
average/=5;

  Serial.println(String(average));
  delay(10000);
}
