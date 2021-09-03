
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 


/**
 * Display
 * adress 0x3f or 0x27
 * Display's sizes 16x2
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Laser
#define LASER 6 // name and display port(pin out)

// Analog stick
const int Y_PIN = 1;           // Потенциометр оси Y подключен к analog port 5 
const int X_PIN = 2;           // Потенциометр оси X подключен к analog port 4
сonst int BUTTON_PIN = 2;      // Кнопка подключена к цифровому выводу 2 
float stepSize = 180F / 1024;  // Вычисляем шаг. градусы / на градацию 
// Угол поворота джойстика 180 градусов, АЦП выдает значения от 0 до 1023, всего 1024 градации

// Servo
Servo servo;
const int servoPort = 10; // Digital port

void setup() 
{
    Serial.begin(9600);
    servo.attach(servoPort);
    pinMode(LASER, OUTPUT); 
        lcd.init();
    lcd.backlight();      // light on
    lcd.setCursor(1, 0);  
    lcd.print("Hello, world!");    
}
void loop() 
{
    int yVal = analogRead(Y_PIN);   // Задаем переменную yVal для считывания показаний аналогового значения
    int xVal = analogRead(X_PIN);
    float yAngle = yVal * stepSize; // Переводим выходные данные yVal в угол наклона джойстика (от 0 до 180)
    float xAngle = xVal * stepSize; // Аналогично xVal
    boolean isClicked = !digitalRead(BUTTON_PIN);  // Считываем не было ли нажатия на джойстик

    Serial.print("Horisontal angle = " + xAngle); // Выводим текст и значение угла 
    Serial.print("Vertical angle = " +   yAngle);

    // Если кнопка джойстика нажата, происходить "выстрел лазером"
    if (isClicked)
    {
        digitalWrite(LASER, HIGH);
        delay(500);
        digitalWrite(LASER, LOW);
    }
    delay(1000);
}