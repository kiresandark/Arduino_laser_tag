// базовый пример инициализации и вывода текста
#include <LiquidCrystal_I2C.h>  // подключаем библу
#include <Servo.h> //используем библиотеку для работы с сервоприводом


// Дисплей
// адрес дисплея 0x3f или 0x27
// размер дисплея 16x2 (поддерживаются и другие, например 20x4)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // адрес, столбцов, строк

// Лазер
#define LASER 6 // задаем имя для Pin лазера, цифра означает цифровой вход

// Модуль джойстика
const int Y_PIN = 1;           // Потенциометр оси Y подключен к аналоговому входу 5 
const int X_PIN = 2;           // Потенциометр оси X подключен к аналоговому входу 4
сonst int BUTTON_PIN = 2;      // Кнопка подключена к цифровому выводу 2 
float stepSize = 180F / 1024;  // Вычисляем шаг. градусы / на градацию 
// Угол поворота джойстика 180 градусов, АЦП выдает значения от 0 до 1023, всего 1024 градации

// Сервопривод
Servo servo; //объявляем переменную servo типа Servo
const int servoPort = 10; // задаем необхоимый цифровой порт

void setup() {
    Serial.begin(9600);  // Скорость работы с монитором орта 

    // Сервопривод
    servo.attach(servoPort); //привязываем привод к порту 
    // Лазер
    pinMode(LASER, OUTPUT); // инициализируем Pin выход 

    // Дисплей
    lcd.init();           // инициализация
    lcd.backlight();      // включить подсветку  
    lcd.setCursor(1, 0);  // столбец 1 строка 0
    lcd.print("Hello, world!");
    lcd.setCursor(4, 1);  // столбец 4 строка 1
    lcd.print("GyverKIT");
}
void loop() {
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