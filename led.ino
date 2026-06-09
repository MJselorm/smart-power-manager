#define LED_PIN 33

void lamp_setup() {
  pinMode(LED_PIN, OUTPUT);
}



void led_on(){
  digitalWrite(LED_PIN, HIGH);
}

void led_off(){
  digitalWrite(LED_PIN, LOW);

}