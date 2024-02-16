/* 

  4 TRAYS SANITARY VENDING MACHINE

  This Vending Machine project was created by Marvin T. Bangcailan, with assistance from Ivan Mamaril.
  The original design used a customized STM32 Board from a Chinese supplier,
  but due to unavailability and lack of support during setup, we decided to replace it with an ARDUINO UNO.
  Through our innovation, we have successfully modified the setup process, ensuring the operational usage of this vending machine.
  If you are interested in following the Arduino code for this sanitary vending machine, you can find it here.
  Please ensure proper attribution if you intend to use or modify the codes for your own projects.
  Proper crediting is appreciated.
  
*/

#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define coinSig 2
#define coinSet 3

// Mosfet switches that triggers the 12VDC motor
#define m1 A0
#define m2 A1
#define m3 A2
#define m4 A3

// Buttons
#define btn1 4
#define btn2 5
#define btn3 6
#define btn4 7
#define setbtn 13

//Limit switches. To maintain the origin of the spiral position after the vending process
#define ls1 8
#define ls2 9
#define ls3 10
#define ls4 11

// Coin acceptor variables
int coinCounter = 0;
int coin = 0;
int total = 0;

// Settings menu variables
bool setupOnce = true;
int setDone;
bool settingsDone = false;
int changeBTNState;

// Item selection variables
int selectedItem;
int itembtn;
int price1 = 0, price2 = 0, price3 = 0, price4 = 0, price5 = 0;
int price[5] = { price1, price2, price3, price4, price5 };

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long timer;
const unsigned long period = 40000;  //the value is a number of milliseconds

void setup() {
  Serial.begin(9600);

  // Initializes the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SPLOOP Sanitary");
  lcd.setCursor(5, 1);
  lcd.print("Vendo");
  delay(300);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Item");
  lcd.setCursor(0, 1);
  lcd.print("Press Button   ");
  //Assig pins for coin acceptor
  pinMode(coinSig, INPUT_PULLUP);
  pinMode(coinSet, OUTPUT);
  digitalWrite(coinSet, LOW);
  //Asign pins to item 1
  pinMode(btn1, INPUT_PULLUP);
  pinMode(ls1, INPUT_PULLUP);
  pinMode(m1, OUTPUT);
  //Asign pins to item 2
  pinMode(btn2, INPUT_PULLUP);
  pinMode(ls2, INPUT_PULLUP);
  pinMode(m2, OUTPUT);
  //Asign pins to item 3
  pinMode(btn3, INPUT_PULLUP);
  pinMode(ls3, INPUT_PULLUP);
  pinMode(m3, OUTPUT);
  //Asign pins to item 4
  pinMode(btn4, INPUT_PULLUP);
  pinMode(ls4, INPUT_PULLUP);
  pinMode(m4, OUTPUT);
  //Asign pins to settings menu
  pinMode(setbtn, INPUT_PULLUP);
  pinMode(coinSet, OUTPUT);
  digitalWrite(coinSet, LOW);

  // Coin identity process
  attachInterrupt(digitalPinToInterrupt(coinSig), coinPulse, FALLING);
  EEPROM.get(0, total);
  total = 0;
  EEPROM.put(0, total);
  for (int i = 1; i <= 4; i++) {
    price[i - 1] = EEPROM.read(i + 1);  // Read from EEPROM
    Serial.println((String) "Item " + i + " - " + price[i - 1]);
  }
  startMillis = millis();
}

void loop() {

  if (settingsDone == false) {
    item1();
    item2();
    item3();
    item4();
    resetghost();
  }

  if (digitalRead(setbtn) == LOW && total == 0 || settingsDone == true) {
    settingsMenu();
  }
}

void item1() {

  //item1
  if (digitalRead(btn1) == LOW && itembtn == 0) {
    digitalWrite(coinSet, HIGH);
    total = 0;
    coinCounter = 0;
    itembtn = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You've Selected");
    lcd.setCursor(0, 1);
    lcd.print("Item No. 1");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((String) "PRICE: P" + price[0] + " NO: 1");
    lcd.setCursor(0, 1);
    lcd.print("COINS: P");
  }

  //vend
  if (itembtn == 1) {
    coindisplay();
    if (total >= price[0]) {
      digitalWrite(coinSet, LOW);
      analogWrite(m1, 255);
      delay(400);
      analogWrite(m1, 0);
    }
  }

  if (digitalRead(ls1) == LOW) {
    analogWrite(m1, 255);
    coinCounter = 0;
    total = 0;
    EEPROM.put(0, total);
    itembtn = 0;
    lcd.setCursor(0, 0);
    lcd.print("Item is Vended");
    lcd.setCursor(0, 1);
    lcd.print("Select New Item ");

  } else {
    analogWrite(m1, 0);
  }
}

void item2() {

  //item1
  if (digitalRead(btn2) == LOW && itembtn == 0) {
    digitalWrite(coinSet, HIGH);
    total = 0;
    coinCounter = 0;
    itembtn = 2;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You've Selected");
    lcd.setCursor(0, 1);
    lcd.print("Item No. 2");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((String) "PRICE: P" + price[1] + " NO: 2");
    lcd.setCursor(0, 1);
    lcd.print("COINS: P");
  }

  //vend
  if (itembtn == 2) {
    coindisplay();
    if (total >= price[1]) {
      digitalWrite(coinSet, LOW);
      analogWrite(m2, 255);
      delay(400);
      analogWrite(m2, 0);
    }
  }

  if (digitalRead(ls2) == LOW) {
    analogWrite(m2, 255);
    coinCounter = 0;
    total = 0;
    EEPROM.put(0, total);
    itembtn = 0;
    lcd.setCursor(0, 0);
    lcd.print("Item is Vended");
    lcd.setCursor(0, 1);
    lcd.print("Select New Item");

  } else {
    analogWrite(m2, 0);
  }
}

void item3() {

  //item1
  if (digitalRead(btn3) == LOW && itembtn == 0) {
    digitalWrite(coinSet, HIGH);
    total = 0;
    coinCounter = 0;
    itembtn = 3;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You've Selected");
    lcd.setCursor(0, 1);
    lcd.print("Item No. 3");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((String) "PRICE: P" + price[2] + " NO: 3");
    lcd.setCursor(0, 1);
    lcd.print("COINS: P");
  }

  //vend
  if (itembtn == 3) {
    coindisplay();
    if (total >= price[2]) {
      digitalWrite(coinSet, LOW);
      analogWrite(m3, 255);
      delay(400);
      analogWrite(m3, 0);
    }
  }

  if (digitalRead(ls3) == LOW) {
    analogWrite(m3, 255);
    coinCounter = 0;
    total = 0;
    EEPROM.put(0, total);
    itembtn = 0;
    lcd.setCursor(0, 0);
    lcd.print("Item is Vended");
    lcd.setCursor(0, 1);
    lcd.print("Select New Item");

  } else {
    analogWrite(m3, 0);
  }
}

void item4() {

  //item1
  if (digitalRead(btn4) == LOW && itembtn == 0) {
    digitalWrite(coinSet, HIGH);
    total = 0;
    coinCounter = 0;
    itembtn = 4;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You've Selected");
    lcd.setCursor(0, 1);
    lcd.print("Item No. 4");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((String) "PRICE: P" + price[3] + " NO: 4");
    lcd.setCursor(0, 1);
    lcd.print("COINS: P");
  }

  //vend
  if (itembtn == 4) {
    coindisplay();
    if (total >= price[3]) {
      digitalWrite(coinSet, LOW);
      analogWrite(m4, 255);
      delay(400);
      analogWrite(m4, 0);
    }
  }

  if (digitalRead(ls4) == LOW) {
    analogWrite(m4, 255);
    coinCounter = 0;
    total = 0;
    EEPROM.put(0, total);
    itembtn = 0;
    lcd.setCursor(0, 0);
    lcd.print("Item is Vended");
    lcd.setCursor(0, 1);
    lcd.print("Select New Item");

  } else {
    analogWrite(m4, 0);
  }
}

void settingsMenu() {
  byte in = Serial.read();
  // Wait to press settingBTN
  if (digitalRead(setbtn) == LOW && settingsDone == false) {
    setDone = 1;
    selectedItem = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" SETTINGS  MENU");
    lcd.setCursor(0, 1);
    lcd.print("CHANGE THE PRICE");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CHANGE THE PRICE");
    lcd.setCursor(0, 1);
    displayItemValue(selectedItem + 1, price[selectedItem]);

    settingsDone = true;
    delay(500);
  }

  // After settingBTN is pressed, wait to press changeBTN
  if (settingsDone == true) {
    changeBTNState = digitalRead(btn1);
    if (changeBTNState == LOW || in == '3' && setDone == 1) {
      if (price[selectedItem] < 99) {
        price[selectedItem] += 1;
      } else {
        price[selectedItem] = 0;  // Reset to 0 if it reaches 99
      }


      displayItemValue(selectedItem + 1, price[selectedItem]);
      delay(150);
    }

    if (digitalRead(btn3) == LOW) {
      price[selectedItem] = 0;

      displayItemValue(selectedItem + 1, price[selectedItem]);
      delay(150);
    }
  }

  // Press acceptBTN to finish setting an item and move to the next one
  if (digitalRead(btn2) == LOW || in == '2' && settingsDone) {
    selectedItem++;
    if (selectedItem >= 4) {
      // All items are done, exit the settings
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  ALL SETTINGS");
      lcd.setCursor(0, 1);
      lcd.print("    ARE DONE");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select Item");
      lcd.setCursor(0, 1);
      lcd.print("Press Button   ");
      settingsDone = false;

      // Save item values to EEPROM
      for (int i = 1; i <= 4; i++) {
        EEPROM.put(i + 1, price[i - 1]);  // Write to EEPROM
        Serial.println((String) "New Item " + i + " - " + price[i - 1]);
      }

    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CHANGE THE PRICE");
      lcd.setCursor(0, 1);
      displayItemValue(selectedItem + 1, price[selectedItem]);
      delay(500);
    }
  }
}

void displayItemValue(int itemNumber, int itemValue) {
  lcd.setCursor(0, 1);
  char lcdBuffer[16];
  sprintf(lcdBuffer, "ITEM %d: P%d.00", itemNumber, itemValue);
  lcd.print(lcdBuffer);
}

void coinPulse() {
  coinCounter++;
  coin = 0;

  if (setupOnce) {
    coinCounter = 0;
    total = 0;
    EEPROM.put(0, total);
    setupOnce = false;
  }
}

void coindisplay() {
  coin++;

  Serial.print("coin=");
  Serial.print(coin);
  Serial.print(" coinCounter:");
  Serial.print(coinCounter);
  Serial.print(" Total:");
  Serial.println(total);

  if (coin >= 30 && coinCounter == 1) {
    total = total + 1;
    coinCounter = 0;
    EEPROM.put(0, total);
  }
  if (coin >= 30 && coinCounter == 2) {
    total = total + 5;
    coinCounter = 0;
    EEPROM.put(0, total);
  }
  if (coin >= 30 && coinCounter == 3) {
    total = total + 10;
    coinCounter = 0;
    EEPROM.put(0, total);
  }

  if (total < 10) {

    lcd.setCursor(8, 1);
    lcd.print((String)total + " ");

  } else {

    lcd.setCursor(8, 1);
    lcd.print(total);
  }
}

void resetghost() {
  if (itembtn != 0) {
     currentMillis = millis(); //get the current "time" (actually the number of milliseconds since the program started)
      if (currentMillis - startMillis >= period)  //test whether the period has elapsed
      {
        digitalWrite(coinSet, LOW);
        itembtn = 0;
        coin = 0;
        coinCounter = 0;
        total = 0;
        EEPROM.put(0, total);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Select Item");
        lcd.setCursor(0, 1);
        lcd.print("Press Button   ");
        startMillis = currentMillis;  //IMPORTANT to save the start time of the current state.
      }

    if (total != price[0] || total != price[1] || total != price[2] || total != price[3]) {
     
      timer = (period - (currentMillis - startMillis)) / 1000;
      if (timer >= 10 && timer <40) {
        lcd.setCursor(14, 1);
        lcd.print(timer);
      } else if (timer < 10 && timer > 0) {
        lcd.setCursor(14, 1);
        lcd.print((String) " " + timer);
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Item Dispensing ");
      lcd.setCursor(0, 1);
      lcd.print(" Please Wait   ");
    }
  }
}