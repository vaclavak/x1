#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ESP8266WiFi.h>

/* Declare LCD object for SPI
 Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);*/
Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 5, 15, 4); /*D5, D7, D1, D8, D2 */
int contrastValue = 60;                                        /* Default Contrast Value */

String ssid = "[134-UC]";
String password = "SaharkaJeMujPejsek*";
String hostname = "X1-V++";
int count;
const String ver = "0.1";

void setup() {
  Serial.begin(115200);
  connectToWifi();
  /* Initialize the Display*/
  display.begin();
  pinMode(D6, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D0, INPUT);
  count = 0;

  /* Change the contrast using the following API*/
  display.setContrast(contrastValue);

  /* Clear the buffer */
  display.clearDisplay();
  display.display();
  delay(100);

  /* Now let us display some text */
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(15, 1);
  display.println("X1 by V++");
  display.setTextColor(BLACK);
  display.setCursor(1, 15);
  display.println("Press (1) to continue");
  display.display();
}

void loop() {
  int btn1 = digitalRead(D6);
  int btn2 = !digitalRead(D3);
  int btn3 = !digitalRead(D4);
  int btn4 = digitalRead(D0);
  Serial.printf("BTN1: %i, BTN2: %i, BTN3: %i, BTN4: %i, COUNT: %i \n", btn1, btn2, btn3, btn4, count);


  if (btn1 == 1) {
    /*    if(count == 0){
      Serial.println("inside 0");      
      drawOptionsMenu();
    }

    if(count == 1){
      Serial.println("inside 1");
     
      drawInfo();
    }

    if(count == 2){
      drawOptionsMenu();
    }*/

    switch (count) {
      case 0:
        Serial.println("inside 0");
        drawOptionsMenu();
        break;
      case 1:
        Serial.println("inside 1");
        drawInfo();
        break;
      case 3:
        drawWiFiInfo();
        break;
      case 5:
        while(true){
          int btn4_2 = digitalRead(D0);
          drawBeeperMenu();


          if(btn4_2 == 1){
            break;
          }
        }
        drawMiscMenu();
        break;

        //break;
      default:
        drawOptionsMenu();
    }
  }

  if(btn2 == 1){
    switch (count){
      case 1:
        drawWifiMenu();
        break;
    }
  }

  if(btn3 == 1){
    switch (count){
      case 1:
        drawMiscMenu();
        break;
    }
  }

  if(btn4 == 1){
    switch (count){
      case 1:
        drawHomeScreen();
        break;
      case 2:
        drawOptionsMenu();
        break;
      case 4:
        drawWifiMenu();
        break;
      case 3:
        drawOptionsMenu();
      case 5:
        drawOptionsMenu();
    }
  }

  delay(500);
}

void connectToWifi() {
  Serial.println("Connecting to:");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Wifi connected");
  Serial.println("IP:");
  Serial.println(WiFi.localIP());
}

void drawOptionsMenu() {
  count = 1;

  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(1, 4);
  display.println("1) Info");
  display.setCursor(1, 16);
  display.println("2) WiFi Menu");
  display.setCursor(1, 28);
  display.println("3) Misc");
  display.setCursor(1, 40);
  display.println("4) Back");
  display.display();
}

void drawInfo() {
  count = 2;
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(15, 1);
  display.println("X1 by V++");
  display.setTextColor(BLACK);
  display.setCursor(1, 15);
  display.println("Ver:");
  display.setCursor(1, 25);
  display.println(ver);
  display.display();
}

void drawHomeScreen(){
  count = 0;
  display.clearDisplay();
  display.display();
  delay(100);

  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(15, 1);
  display.println("X1 by V++");
  display.setTextColor(BLACK);
  display.setCursor(1, 15);
  display.println("Press (1) to continue");
  display.display();
}

void drawWifiMenu(){
  count = 3;
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(1, 4);
  display.println("1) Full WiFi Info");
  display.setCursor(1, 16);
  display.println("4) Back");
  display.display();
}

void drawWiFiInfo(){
  count = 4;
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(1, 4);
  display.println("IP Adress:");
  display.setCursor(1, 16);
  display.println(WiFi.localIP());
  display.setCursor(1, 28);
  display.println("Connected to:");
  display.setCursor(1, 40);
  display.println(ssid);
  display.display();
}

void drawMiscMenu(){
  count = 5;
  display.clearDisplay();
  display.setCursor(1, 4);
  display.println("1) Beeper");
  display.setCursor(1, 16);
  display.println("4) Back");
  display.display();
}

void drawBeeperMenu(){
  count = 6;
  display.clearDisplay();
  display.setCursor(1, 5);
  display.println("BEEPER ACTIVE");
  display.setCursor(1, 20);
  display.println("Press (4) To stop");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  delay(1000);
}
