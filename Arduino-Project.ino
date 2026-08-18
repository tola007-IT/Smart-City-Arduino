#include <LiquidCrystal_I2C.h>
#define IR_sensor 8
#define LDR_sensor A2
#define LED_R 3
#define LED_Y 4
#define LED_G 5
#define LED_STREET 6
#define BUTTON 7
#define BUZZER 10 
LiquidCrystal_I2C LCD(0x27,16,2);
int state = 1;
long TIME = 0;
bool BT_STATE = HIGH;
void setup(){
  pinMode(IR_sensor, INPUT);
  pinMode(LDR_sensor, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_STREET, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  LCD.init();
  LCD.backlight();
  Serial.begin(9600);
  Serial.println(" SMART CITY START");
}
void loop(){
  bool BT = digitalRead(BUTTON);
  if(BT == LOW && BT_STATE == HIGH){
    state = 4;
    TIME = millis();
  }
  Serial.println(analogRead(LDR_sensor));
  if(analogRead(LDR_sensor) <= 400){
    digitalWrite(LED_STREET, HIGH);
  }else{
    digitalWrite(LED_STREET, LOW);
  }
  if(state == 1 ){
    digitalWrite(LED_G, HIGH);
    LCD.setCursor(0,0);
    LCD.print("    GO GO.....      ");
    LCD.setCursor(0,1);
    LCD.print("                 ");
    if(millis() - TIME >= 3000){
      digitalWrite(LED_G, LOW);
      TIME = millis();
      state = 2;
    }
  }else if(state == 2){
    digitalWrite(LED_Y, HIGH);
    LCD.setCursor(0,0);
    LCD.print("   BE CAREFUL  ");
    LCD.setCursor(0,1);
    LCD.print("                 ");
    if(millis() - TIME >= 500){
      digitalWrite(LED_Y, LOW);
      TIME = millis();
      state = 3;
    }
  }else if(state == 3){
    digitalWrite(LED_R, HIGH);
    if(digitalRead(IR_sensor) == LOW){
      LCD.setCursor(0,0);
      LCD.print("    HAVE CAR   ");
      LCD.setCursor(0,1);
      LCD.print("  PLEASE STOP  ");
      tone(BUZZER,1000,500);
    }else{
      LCD.setCursor(0,0);
      LCD.print("     STOP     ");
      LCD.setCursor(0,1);
      LCD.print("                ");
    }
    if(millis() - TIME >= 3000){
      digitalWrite(LED_R, LOW);
      TIME = millis();
      state = 1;      
    }
  }else if(state == 4){
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_Y, LOW);
    digitalWrite(LED_G, LOW);
    LCD.setCursor(0,0);
    LCD.print(" WAIT! PERSON");
    LCD.setCursor(0,1);
    LCD.print("..............");
    if(millis()- TIME >= 5000){
      digitalWrite(LED_R, LOW);
      TIME = millis();
      state = 1;
    }
    if(digitalRead(IR_sensor) == LOW){
      LCD.setCursor(0,0);
      LCD.print("    HAVE CAR  ");
      LCD.setCursor(0,1);
      LCD.print("  PLEASE STOP  ");
      tone(BUZZER,1000,500);
    }
  }
  BT_STATE = BT;
}
