#include <Servo.h>

Servo servoX;
int posX = 90;  // Начальное положение сервопривода

// Пины для мотора (управление через драйвер, например L298N)
int motorPin1 = 2;  // Пин для направления вперед
int motorPin2 = 3;  // Пин для направления назад
int ENA = 11;       // Пин для управления скоростью мотора (ШИМ)
int driveSpeed = 70;
int servoSpeed = 5;
void setup() {
  servoX.attach(9);  // Пин для сервопривода
  servoX.write(posX);  // Начальное положение сервопривода
  Serial.begin(115200);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();  // Чтение команды с последовательного порта

    // Управление сервоприводом
    if (ch == 'd') {
      posX -= servoSpeed;  // Поворот влево
      if (posX < 0) posX = 0;  // Ограничение угла
      servoX.write(posX);
    }
    else if (ch == 'a') {
      posX += servoSpeed;  // Поворот вправо
      if (posX > 180) posX = 180;  // Ограничение угла
      servoX.write(posX);
    }

    // Управление мотором
    if (ch == 'w') {
      driveForward();  // Едем вперед
    }
    else if (ch == 's') {
      driveBackward();  // Едем назад
    }
    else if (ch == 'x') {  // Стоп мотор
      stopMotor();
    }
  }
}

// Функция для движения вперед
void driveForward() {
  analogWrite(ENA, driveSpeed);  // Полная мощность
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

// Функция для движения назад
void driveBackward() {
  analogWrite(ENA, driveSpeed);  // Полная мощность
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

// Функция для остановки мотора
void stopMotor() {
  analogWrite(ENA, 0);  // Останавливаем мотор
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
