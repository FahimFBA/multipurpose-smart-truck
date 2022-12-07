#include <NewPing.h>
NewPing sonar(10, 11, 200);

void setup() {
  Serial.begin(9600);
  delay(50);  
}

void loop() {
  Serial.print("The current distance is:  ");
  Serial.println(sonar.ping_cm());
  delay(1000);
}