#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;
int httpCode;

// ===========================================
// == CUSTOMIZE HERE YOUR WIFI NETWORK ACCESS
// ===========================================

const char* ssid     = "YOUR_NETWORK_SSID";
const char* password = "YOUR_NETWORK_KEY";

// ===========================================
// == PUT HERE YOUR STRING TO ENCODE
// ===========================================

String stringToTransmit = "YOUR_STRING_TO_ENCODE";

// ===========================================
// == SOFTWARE CONFIGURATION
// ===========================================

bool enable_web_request = true;
bool enable_led_blinking = true;
bool enable_start_signal = true;
bool enable_differenciate_odd_even_charactere = true;
int pause_before_start_signal = 10000;
int pause_after_start_signal = 5000;

// ===========================================
// == CUSTOMIZE HERE HOW YOU WANT TO BLINK THINGS
// ===========================================

int ledPinEven = 32; // Pin for the LED 1 (even character)
int ledPinOdd = 25; // Pin for the LED 2 (odd character)
int ledPinStartSignal = 26; // Pin for the LED 3 (star signal)

// ===========================================
// == CUSTOMIZE HERE WHERE YOU WANT TO SEND WEB-REQUEST
// ===========================================

String url_request_ON_odd = "";
String url_request_ON_even = "";
String url_request_OFF_odd = "";
String url_request_OFF_even = "";

// ===========================================
// == MORSE TIMING CONFIGURATION
// ===========================================

int durationPOINT = 300;
int durationTRAIT = durationPOINT * 5;
int durationPauseSigne = durationPOINT * 3;
int durationPauseCharacter = durationPOINT;

// ========================================
// == MORSE DICTIONNARY
// ========================================

String MorseDictionnary[36][2] ={
  {"A",".-"},
  {"B","-..."},
  {"C","-.-."}, 
  {"D","-.."}, 
  {"E","."}, 
  {"F","..-."}, 
  {"G","--."}, 
  {"H","...."}, 
  {"I",".."}, 
  {"J",".---"}, 
  {"K","-.-"}, 
  {"L",".-.."}, 
  {"M","--"}, 
  {"N","-."}, 
  {"O","---"}, 
  {"P",".--."}, 
  {"Q","--.-"}, 
  {"R",".-."}, 
  {"S","..."}, 
  {"T","-"}, 
  {"U","..-"}, 
  {"V","...-"}, 
  {"W",".--"}, 
  {"X","-..-"}, 
  {"Y","-.--"}, 
  {"Z","--.."}, 
  {"0","-----"},
  {"1",".----"},
  {"2","..---"},
  {"3","...--"},
  {"4","....-"},
  {"5","....."},
  {"6","-...."},
  {"7","--..."},
  {"8","---.."},
  {"9","----."}
};

void setup() {

  // Starting the Serial Port
  Serial.begin(115200);
  delay(10);

  // If needed starts WiFi network
  if(enable_web_request){
      Serial.print("Connecting to ");
      Serial.println(ssid);
      WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }

  // Turn string to transmit to uppercase
  stringToTransmit.toUpperCase();
  
  if(enable_led_blinking){
    // Setting LED pin as output
    pinMode(ledPinEven,OUTPUT);
    pinMode(ledPinOdd,OUTPUT);
    pinMode(ledPinStartSignal,OUTPUT);

      if(enable_start_signal){
        // Wait to give the start signal
        delay(pause_before_start_signal);
        digitalWrite(ledPinStartSignal, HIGH);
        delay(1000);
        digitalWrite(ledPinStartSignal, LOW);
        delay(pause_after_start_signal);
      }
  }

  for(int i = 0 ; i < stringToTransmit.length() ; i++){
    Serial.println(stringToTransmit[i]);
    BlinktoMorse(stringToTransmit[i],i%2);
  }
  Serial.println("----");
  delay(durationPauseCharacter);
}

void BlinktoMorse(char charToTranslate, int parity){
  String morseStringToBlink;
  for(int i = 0 ; i < 36 ; i++)
  {
    if(charToTranslate == MorseDictionnary[i][0][0]){
      morseStringToBlink = MorseDictionnary[i][1];
      Serial.println(morseStringToBlink);
    }
  }
  for(int i = 0 ; i < morseStringToBlink.length() ; i++){
    Serial.println(morseStringToBlink[i]);
    if(morseStringToBlink[i] == '.'){
      DASH_DOT("DOT",parity);
    } else if(morseStringToBlink[i] == '-') {
      DASH_DOT("DASH",parity);
    }
  }
}

void DASH_DOT(String type, int parity){
    if(enable_differenciate_odd_even_charactere){
      if(parity==0){
        if(enable_web_request){
          http.begin(url_request_ON_even);
          httpCode = http.GET();
          http.end();
        }
        if(enable_led_blinking){
          digitalWrite(ledPinEven, HIGH);
        }
      } else{
        if(enable_web_request){
          http.begin(url_request_ON_odd);
          httpCode = http.GET();
          http.end();
        }
        if(enable_led_blinking){
          digitalWrite(ledPinOdd, HIGH);
        }
      }
    } else {
        if(enable_web_request){
          http.begin(url_request_ON_even);
          httpCode = http.GET();
          http.end();
        }
        if(enable_led_blinking){
          digitalWrite(ledPinEven, HIGH);
        }
    }

    if(type=="DASH"){
      delay(durationTRAIT);
    } else {
      delay(durationPOINT);
    }

    if(enable_differenciate_odd_even_charactere){
      if(parity==0){
        if(enable_web_request){
          http.begin(url_request_OFF_even);
          httpCode = http.GET();
          http.end();
        }
        if(enable_led_blinking){
          digitalWrite(ledPinEven, LOW);
        }
      } else{
        if(enable_web_request){
          http.begin(url_request_OFF_odd);
          httpCode = http.GET();
          http.end();
        }
        if(enable_led_blinking){
          digitalWrite(ledPinOdd, LOW);
        }
      }
    } else {
        if(enable_web_request){
          http.begin(url_request_OFF_even);
          httpCode = http.GET();
          http.end();
        }
        if(enable_led_blinking){
          digitalWrite(ledPinEven, LOW);
        }
    }
    delay(durationPauseSigne);
}

void loop() {

}
