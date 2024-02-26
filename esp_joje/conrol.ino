

void control() {
  adc_k = analogRead(A0);


  if (adc_k >= 100) hach = 1;
  if (adc_k < 50) hach = 0;

  if (hach == 0) {
    if (temp <= 37.2) digitalWrite(rele_dama, HIGH);
    if (temp >= 37.5) digitalWrite(rele_dama, LOW);
  }

  if (hach == 1) {
    if (temp <= 36.2) digitalWrite(rele_dama, HIGH);
    if (temp >= 36.5) digitalWrite(rele_dama, LOW);
  }

  reset_check = 0;
  if (temp < 39) digitalWrite(bazzer, LOW);
  ESP.wdtFeed();
  ESP.wdtFeed();
  ESP.wdtDisable();
}