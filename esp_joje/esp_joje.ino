#include "DFRobot_SHT20.h"
DFRobot_SHT20 sht20(&Wire, SHT20_I2C_ADDR);
//***************timer*************
#if !defined(ESP8266)
#error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif
#define TIMER_INTERRUPT_DEBUG 1
#define _TIMERINTERRUPT_LOGLEVEL_ 1
#define USING_TIM_DIV1 false   // for shortest and most accurate timer
#define USING_TIM_DIV16 false  // for medium time and medium accurate timer
#define USING_TIM_DIV256 true  // for longest timer but least accurate. Default
#include "ESP8266TimerInterrupt.h"
volatile uint32_t lastMillis = 0;
#define TIMER_INTERVAL_MS 1000
ESP8266Timer ITimer;
#include "Arduino.h"
//***************************timer********************************
//***************************timer********************************
void IRAM_ATTR TimerHandler() {
  timer_();
}

//********7seg*****************
//********7seg*****************
#include <HCMAX7219.h>
#include "SPI.h"
#define LOAD D8
HCMAX7219 HCMAX7219(LOAD);


int motor_time;

int rele_dama = D0;
int rele_motor = D4;
int bazzer = D6;
int led = D3;
int k1 = A0;
float humd;
float temp;
int adc_k;
int hach;
int time_motor_on;
int reset_check;
void setup() {
  Serial.begin(115200);
  Serial.print("Start...");
  pinMode(rele_dama, OUTPUT);
  pinMode(rele_motor, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(bazzer, OUTPUT);



  digitalWrite(bazzer, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                  // wait for a second
  digitalWrite(bazzer, LOW);   // turn the LED off by making the voltage LOW
  delay(100);
  digitalWrite(bazzer, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                  // wait for a second
  digitalWrite(bazzer, LOW);   // turn the LED off by making the voltage LOW
  delay(200);

  HCMAX7219.Intensity(3, 2);
  HCMAX7219.Intensity(3, 1);
  HCMAX7219.Intensity(3, 0);

  sht20.initSHT20();
  delay(100);
  Serial.println("Sensor init finish!");
  sht20.checkSHT20();

  //***************timer**************
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler)) {
    lastMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(lastMillis);
  } else
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));
}

void loop() {
  sht();
  control();
  time_motor();
  lcd();
  delay(500);
  ESP.wdtFeed();
  ESP.wdtDisable();
}
