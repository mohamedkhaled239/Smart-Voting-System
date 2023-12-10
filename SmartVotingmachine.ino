#include <Adafruit_Fingerprint.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
MCUFRIEND_kbv tft;
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
 TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//param calibration from kbv
#define TS_MINX 906
#define TS_MAXX 116

#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define TS_MINY 92 
#define TS_MAXY 952
#define  BLACK   0x0000
#define BLUE    0x001F
#define CYAN    0x07FF
#define WHITE   0xFFFF
int candidate1_votes = 0;
int candidate2_votes = 0;
int candidate3_votes = 0;
int candidate4_votes= 0;
int candidate5_votes= 0;
int candidate6_votes= 0;
bool hasVoted[6];

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(18, 19);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void Result_elections(){
  
 int max_votes = max(candidate1_votes, max(candidate2_votes, max(candidate3_votes,max(candidate4_votes, max(candidate5_votes, candidate5_votes)))));
        tft.reset();
      tft.begin(tft.readID());
        tft.setRotation(1);
        tft.fillScreen(CYAN);
      tft.setTextColor(BLACK);
      tft.setTextSize(3);
      tft.setCursor(100, 100);
      if (max_votes == candidate1_votes) {
        result_number();
        tft.print("\n candidate1 wins!");
      }
      else if (max_votes == candidate2_votes) {
        result_number();
        tft.print("candidate 2 wins!");
      }
      else if (max_votes == candidate4_votes) {
        result_number();
        tft.print("candidate 4 wins!");
      }
      else if (max_votes == candidate5_votes) {
        result_number();
        tft.print("candidate 5 wins!");
      }
      else if (max_votes == candidate6_votes) {
        result_number();
        tft.print("candidate 6 wins!");
      }
      else if (max_votes == candidate3_votes) {
        result_number();
        tft.print("candidate 3 Wins!");
      }
      delay(40000);
}

void Thank_For_Voting(){
  tft.reset();
  tft.begin(tft.readID());
  tft.setRotation(1);
  tft.fillScreen(WHITE);
  tft.setCursor(20, 140);
  tft.print("Thank you for voting!");
  delay(3000);
  setup();    
}

void Text(String text){
   tft.reset();
  tft.begin(tft.readID());
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(70, 140);
  tft.print(text);
  tft.setCursor(20, 100);
}


void You_voted_before(){
   tft.reset();
  tft.begin(tft.readID());

  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(70, 140);
  tft.print(" Unavailable\nYou voted before");
  tft.setCursor(20, 100);
  delay(4000);
  setup();
}

void result_number(){
    tft.print("candidate1 votes= ");tft.println(candidate1_votes);

    tft.print("candidate2 votes= ");tft.println(candidate2_votes);
        
    tft.print("candidate3 votes= ");tft.println(candidate3_votes);
        
    tft.print("candidate4 votes=");  tft.println(candidate4_votes);

    tft.print("candidate5 votes=");   tft.println(candidate5_votes);

    tft.print("candidate6 votes=");  tft.println(candidate6_votes); 
    tft.setTextColor(WHITE);
}
void  Nameofcandidate(int x,int y , String name){
   tft.setCursor(x, y);
  tft.print(name);
}

void MAIN_GUI() {
  tft.reset();
  tft.begin(tft.readID());
  tft.setRotation(1);
  tft.fillScreen(BLUE);
  tft.fillRect(0, 0, 237, 75, WHITE);
  tft.fillRect(0, 80, 237, 75, WHITE);
  tft.fillRect(0, 160, 237, 75, WHITE);
  tft.fillRect(0, 240, 480, 75, WHITE);
  tft.fillRect(240, 0, 480, 75, WHITE);
  tft.fillRect(240, 80, 480, 75, WHITE);
  tft.fillRect(240, 160, 480, 75, WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  Nameofcandidate(20,20,"candidate1");
  Nameofcandidate(20,100,"candidate2");
  Nameofcandidate(20,180,"candidate3");
  Nameofcandidate(190,260,"result");
  Nameofcandidate(275,20,"candidate6");
  Nameofcandidate(275,100,"candidate5");
  Nameofcandidate(275,180,"candidate4");
}
void setup(){

  Text("Put your Finger");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

void loop() {
   getFingerprintID();
  TSPoint p = ts.getPoint();
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
     p.x = 320-map(p.x  , TS_MINX, TS_MAXX, 320, 0);
     p.y = 480-map(p.y, TS_MINY, TS_MAXY, 480, 0);

   
    if (p.x >= 0 && p.x <= 80 && p.y >= 0 && p.y >= 240) {
      candidate1_votes++;
      Thank_For_Voting();
    }
    if (p.x >= 0 && p.x <= 80 && p.y >= 0 && p.y <= 240) {
      candidate6_votes++;
     Thank_For_Voting();
    }

    if (p.x >= 80 && p.x <= 160 && p.y >= 0 && p.y >= 240) {
        candidate2_votes++;
        Thank_For_Voting();
    }
    if (p.x >= 80 && p.x <= 160 && p.y >= 0 && p.y <= 240) {
        candidate5_votes++;
        Thank_For_Voting();
    }

    if (p.x >= 160 && p.x <= 240 && p.y >= 0 && p.y >= 240) {
        candidate3_votes++;
        Thank_For_Voting();
    }
    if (p.x >= 160 && p.x <= 240 && p.y >= 0 && p.y <= 240) {
        candidate4_votes++;
        Thank_For_Voting();
    }
      
    if (p.x >= 240 && p.x < 320 && p.y >= 0 ) {
     Text("Not available\n          to you");
     MAIN_GUI();
    }
  }

  
  delay(10);
      }

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  // OK success!

  p = finger.image2Tz();


  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  for(int i=0;i<6;i++){
  if(finger.fingerID==i&&finger.fingerID!=5){
      if(hasVoted[i]==false){
        hasVoted[i]=true;
        MAIN_GUI();
      }
      else{
        Text("Not available    \n you already voted");
      }
  }
    else if(finger.fingerID==5){ 
        Result_elections();
      }
  }
 
}
 
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}