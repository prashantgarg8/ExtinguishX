
#define IR_SENSOR_LEFT 2
#define IR_SENSOR_CENTER 3
#define IR_SENSOR_RIGHT 4
#define SERVO_PIN 5
#define WATER_PUMP_PIN 13
#define ENA 11
#define ENB 12
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

#include <Servo.h>
Servo servo;

void setup() {
  Serial.begin(9600);

  pinMode(IR_SENSOR_LEFT, INPUT);
  pinMode(IR_SENSOR_CENTER, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(WATER_PUMP_PIN, OUTPUT);

  servo.attach(SERVO_PIN);

  servo.write(90);
}

void loop() {
  int irLeft = digitalRead(IR_SENSOR_LEFT);
  int irCenter = digitalRead(IR_SENSOR_CENTER);
  int irRight = digitalRead(IR_SENSOR_RIGHT);

  Serial.print("IR Left: ");
  Serial.print(irLeft);
  Serial.print(" IR Center: ");
  Serial.print(irCenter);
  Serial.print(" IR Right: ");
  Serial.println(irRight);

  if (irLeft == LOW && irCenter == LOW && irRight == LOW) {
    moveForward();
  } else if (irLeft == LOW && irCenter == HIGH && irRight == HIGH) {
    turnLeft();
  } else if (irLeft == HIGH && irCenter == HIGH && irRight == LOW) {
    turnRight();
  } else if (irLeft == HIGH&& irCenter == HIGH && irRight == HIGH) {
    stopRobot();
    activateWaterPump();
  } else {
    // Default to stop
    stopRobot();
  }

  delay(100);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 160);
  analogWrite(ENB, 160);
  servo.write(90); 
  
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 160);
  analogWrite(ENB, 160);
  servo.write(45); 
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 160);
  analogWrite(ENB, 160);
  servo.write(45); 
  
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void activateWaterPump() {
  digitalWrite(WATER_PUMP_PIN, HIGH);
  delay(5000); 
  digitalWrite(WATER_PUMP_PIN, LOW);
}
