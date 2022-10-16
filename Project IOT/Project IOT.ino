#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <stdio.h>
#include <string.h>
#define KONTAKTRON 11
#define PIR 3 //ANALOG PIN

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'X'},
  {'4','5','6', '<'},
  {'7','8','9', 'C'},
  {'*','0','#', 'S'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String PIN = "0000";
int position = 0;
String current = "";
int MAX_SIZE = 15;
int MAX_ATTEMPTS = 3;
bool LOGGED = false;
int attempts = 0;

void print_line(String txt, int position = 0){
    lcd.setCursor(0, position);
    lcd.print(txt);
}

void recordPressNumber(char x, int position = 0){
  if(current.length()<MAX_SIZE){
    current += x;
    print_line(current, position);
  }
}

void initialMessage(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PRESS * TO START");
}

void hello(){
  lcd.init();
  lcd.backlight();
  // delay(100);
  lcd.setCursor(0,0);
  lcd.print("IOT PROJECT");
  lcd.setCursor(0,1);
  lcd.print("PROSTY ALARM");
  // delay(1000);
  initialMessage();
}

int LED_RED = 13;
int LED_GREEN = 12;
int BUZZ = 10;

void initDiody(){
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(KONTAKTRON, INPUT_PULLUP);
  pinMode(PIR, INPUT);
  
  delay(100);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(BUZZ, HIGH);
  delay(100);
  digitalWrite(LED_GREEN, HIGH);
  delay(100);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZZ, LOW);
  delay(100);
  digitalWrite(LED_GREEN, LOW);
  delay(100);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(BUZZ, HIGH);
  delay(100);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(BUZZ, LOW);
}

void setup() {
  Serial.begin(9600);
  initDiody();
  hello();
}

void czuwanie() {
  delay(500);
  while(true){
    lcd.clear();
    print_line("CLEAR", 0);
    delay(100);
    while(digitalRead(KONTAKTRON) == HIGH){
      lcd.clear();
      print_line("DOORS OPEN!", 0);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
      digitalWrite(BUZZ, HIGH);
      delay(200);
      digitalWrite(LED_RED, LOW);
      digitalWrite(BUZZ, LOW);
      delay(200);
    }

    int ruch = analogRead(PIR);
    if(ruch > 300){ 
      lcd.clear();
      print_line("MOVE DETECTED!", 0);
      for(int i = 0; i<10;i++){
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(BUZZ, HIGH);
        delay(100);
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(BUZZ, LOW);
        delay(100);
      }
    }else{
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(BUZZ, LOW);
    }

    if (digitalRead(KONTAKTRON) == LOW) { //Jeśli czujnik zwarty
      digitalWrite(LED_RED, LOW); //Stan OK - dioda zielona
      digitalWrite(LED_GREEN, HIGH);
    }
  }
}

void loop() {
  if(!LOGGED){
    login();
  }else{
    // userMenu();
    czuwanie();
  }
}

void login() {
    char key = keypad.getKey();
    bool lock = false;
    if(key=='*'){
      digitalWrite(BUZZ, HIGH);
      delay(100);
      digitalWrite(BUZZ, LOW);
      digitalWrite(LED_GREEN, HIGH);
      lcd.clear();
      print_line("Enter password:", 0);
      print_line("Confirm with #", 1);
      delay(1000);
      lcd.clear();
      print_line("Enter password:", 0);
      while(!lock){ 
        char key = keypad.getKey();
        if(key){
          digitalWrite(BUZZ, HIGH);
          delay(100);
          digitalWrite(BUZZ, LOW);
          switch (key){
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
              recordPressNumber(key, 1);
              break;
            case '<':
              recordBackButton();
              break;
            case 'X':
              recordClearButton();
              break;
            case '#':
              verifyPassword();
              lock = true;
              break;
            default:
              printStatment(key);
          }
        }
      }
  }

}

void verifyPassword(){
    Serial.println(current);
    if(current == PIN){
      lcd.clear();
      print_line("WELCOME ! ! !", 0);
      LOGGED = true;
    }else{
      attempts+=1;
      current = "";
      digitalWrite(LED_RED, HIGH);
      for(int i = 0; i < 3; i++){
        digitalWrite(BUZZ, HIGH);
        delay(100);
        digitalWrite(BUZZ, LOW);
        delay(100);
      }
      lcd.clear();
      print_line("BAD PASSWORD", 0);
      print_line("ATTEMPTS LEFT: "+String(MAX_ATTEMPTS-attempts), 1);
      delay(1000);
      digitalWrite(LED_RED, LOW);
      initialMessage();
    }
}


void userMenu(){
  lcd.clear();
  while(true){
    char key = keypad.getKey();
      if(key){
        switch (key){
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
          case '0':
            recordPressNumber(key, 0);
            break;
          case '<':
            recordBackButton();
            break;
          case 'X':
            recordClearButton();
            break;
          default:
            printStatment(key);
        }
      }
  }
}


void recordBackButton(){
  if(current.length()>0){
    current = current.substring(0, current.length()-1);
    print_line(current, 0);
  }
}

void recordClearButton(){
    current = "";
    print_line(current, 0);
    // Serial.println(x);
}


void printStatment(char x){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(x);
  Serial.println(x);
}






