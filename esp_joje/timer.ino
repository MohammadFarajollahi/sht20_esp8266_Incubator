void timer_() {
  if (hach == 0) {
    ++motor_time;
    digitalWrite(led, !digitalRead(led));
  }

  if (temp >=39)digitalWrite(bazzer, !digitalRead(bazzer));


  //*****reset******
   ++reset_check;
  if (reset_check >= 30) ESP.reset();
}

void time_motor() {

  if (hach == 0) {
    // Serial.print("time:");
    // Serial.println(motor_time);

    if (motor_time >= 5400 && time_motor_on == 0) {
      time_motor_on = 1;
      motor_time = 0;
      digitalWrite(rele_motor, HIGH);
      digitalWrite(bazzer, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(200);                  // wait for a second
      digitalWrite(bazzer, LOW);   // turn the LED off by making the voltage LOW
    }



    if (motor_time >= 15 && time_motor_on == 1) {
      time_motor_on = 0;
      motor_time = 0;
      digitalWrite(rele_motor, LOW);
    }
  }

  if (hach == 1) {
    motor_time = 0;
    digitalWrite(led, LOW);
    time_motor_on = 0;
  }
}