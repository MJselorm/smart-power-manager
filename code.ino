int potpin = 32;
int potval;
int batteryPercent;

int delayt = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(potpin, INPUT); //for potentiometer
  site_setup();
  lamp_setup();
  fan_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  potval = analogRead(potpin);
   // Convert 0-4095 to 0-100%
  batteryPercent = map(potval, 0, 4095, 0, 100);
  handleWebsite();

if (batteryPercent >= 70) {
    movefan();
    led_on();
    play_sound();
  }
  else if (batteryPercent >= 40) {
    
      play_sound();
        led_on();
  }

  else if (batteryPercent > 10){
    
    led_on();
  }
  else{

  
    led_off();
  }

 
  delay(delayt);
}


