int enA = 9;   
int in1 = 8;   
int in2 = 11;   
int in3 = 12;
int in4 = 13;
int enB = 10;
int in5 = 4;
int in6 = 3;
int in7 = 2;
int in8 = 7;
int enA2 = 5;
int enB2 = 6;

String command = "";  

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(enA2, OUTPUT);
  pinMode(in7, OUTPUT);  
  pinMode(in8, OUTPUT);
  pinMode(enB2, OUTPUT);

  Serial.begin(9600);  
  Serial.println("Bluetooth Motor Control Ready");
}

void loop() {
 
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (command.length() > 0) {
        handleCommand(command);
        command = "";  
      }
    } else {
      command += c;
    }
  }
}

void handleCommand(String cmd) {
  cmd.trim();  

  const int maxSafePWM = 170;  

  if (cmd.startsWith("F")) {  
    int speed = cmd.substring(1).toInt();
    speed = constrain(speed, 0, 100);
    int pwm = map(speed, 0, 100, 0, maxSafePWM);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    analogWrite(enA, pwm);
    analogWrite(enB, pwm);
    analogWrite(enA2, pwm);
    analogWrite(enB2, pwm);
    Serial.println("Moving Forward at " + String(speed) + "% (" + String(pwm) + " PWM)");
  } 
  else if (cmd.startsWith("B")) {  
    int speed = cmd.substring(1).toInt();
    speed = constrain(speed, 0, 100);
    int pwm = map(speed, 0, 100, 0, maxSafePWM);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
    analogWrite(enA, pwm);
    analogWrite(enB, pwm);
    analogWrite(enA2, pwm);
    analogWrite(enB2, pwm);
    Serial.println("Moving Backward at " + String(speed) + "% (" + String(pwm) + " PWM)");
  } 
  else if (cmd.startsWith("L")) {  
  int speed = cmd.substring(1).toInt();
  speed = constrain(speed, 0, 100);
  int pwm = map(speed, 0, 100, 0, maxSafePWM);


  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  digitalWrite(in5, LOW);   
  digitalWrite(in6, HIGH);

  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);

  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  analogWrite(enA2, pwm);
  analogWrite(enB2, pwm);

  Serial.println("Turning Left at " + String(speed) + "% (" + String(pwm) + " PWM)");
} 
else if (cmd.startsWith("R")) {  
  int speed = cmd.substring(1).toInt();
  speed = constrain(speed, 0, 100);
  int pwm = map(speed, 0, 100, 0, maxSafePWM);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);

  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);

  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);

  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  analogWrite(enA2, pwm);
  analogWrite(enB2, pwm);

  Serial.println("Turning Right at " + String(speed) + "% (" + String(pwm) + " PWM)");
}
  else if (cmd.equalsIgnoreCase("STOP")) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    analogWrite(enA2, 0);
    analogWrite(enB2, 0);
    Serial.println("Motor Stopped");
  } 
  else {
    Serial.println("Unknown Command: " + cmd);
  }
}
