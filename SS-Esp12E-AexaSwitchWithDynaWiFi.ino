/*
 * This one is tested by Shajahan and working one
 */ 
#include <WiFiManager.h>
#include <Espalexa.h>
#include <ArduinoOTA.h>

const int RELAY_1 = 16;  // D0 Living Room Light
const int RELAY_2 = 5;   //  D1 Living Room Fan
const int RELAY_3 = 4;   //  D2 Bed Room Light
const int RELAY_4 = 0;   //  D3 Bed Room Fan
const int RELAY_5 = 3;  //  D4 Guest Room Light
const int RELAY_6 = 14;  // D5 Guest Room Fan
const int RELAY_7 = 12;  // D6 TV
const int RELAY_8 = 13;  // D7 Kitchen Light
#define LED 2
int MillisCount = 0;

String Device_1_Name = "Living Light";
String Device_2_Name = "Living Fan";
String Device_3_Name = "Bed Light";
String Device_4_Name = "Bed Fan";
String Device_5_Name = "Guest Light";
String Device_6_Name = "Guest Fan";
String Device_7_Name = "Living TV";
String Device_8_Name = "Kitchen Light";

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
void fifthLightChanged(uint8_t brightness);
void sixthLightChanged(uint8_t brightness);
void senventhLightChanged(uint8_t brightness);
void eighthLightChanged(uint8_t brightness);

Espalexa espalexa;

EspalexaDevice* device3; //this is optional

void setup()
{
  Serial.begin(115200);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);
  pinMode(RELAY_7, OUTPUT);
  pinMode(RELAY_8, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);
  digitalWrite(RELAY_5, HIGH);
  digitalWrite(RELAY_6, HIGH);
  digitalWrite(RELAY_7, HIGH);
  digitalWrite(RELAY_8, HIGH);
  // Initialise wifi connection
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool wifiConnected;
  wifiConnected = wm.autoConnect("SsAlexaSwitch");

  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged); //third parameter is beginning state (here fully on)
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(Device_4_Name, fourthLightChanged);
    espalexa.addDevice(Device_5_Name, fifthLightChanged);
    espalexa.addDevice(Device_6_Name, sixthLightChanged);
    espalexa.addDevice(Device_7_Name, seventhLightChanged);
    espalexa.addDevice(Device_8_Name, eighthLightChanged);
    //device3 = new EspalexaDevice("Light 3", thirdLightChanged); //you can also create the Device objects yourself like here
    //espalexa.addDevice(device3); //and then add them
    //device3->setValue(128); //this allows you to e.g. update their state value at any time!
    espalexa.begin();

    ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   ArduinoOTA.handle();
   if (MillisCount == 1000)
    digitalWrite(LED, LOW);

  if (MillisCount == 2000) {
    digitalWrite(LED, HIGH);
    MillisCount = 0;
  }

  MillisCount += 1;
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
    Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_1, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_1, HIGH);
    }
}

void secondLightChanged(uint8_t brightness) {
  //do what you need to do here
    Serial.print("Device 2 changed to ");
    //do what you need to do here
    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_2, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_2, HIGH);
    }
}

void thirdLightChanged(uint8_t brightness) {
    Serial.print("Device 3 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_3, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_3, HIGH);
    }
  //do what you need to do here
}

void fourthLightChanged(uint8_t brightness) {
    Serial.print("Device 4 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_4, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_4, HIGH);
    }
  //do what you need to do here
}

void fifthLightChanged(uint8_t brightness) {
    Serial.print("Device 5 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_5, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_5, HIGH);
    }
  //do what you need to do here
}

void sixthLightChanged(uint8_t brightness) {
    Serial.print("Device 6 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_6, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_6, HIGH);
    }
  //do what you need to do here
}

void seventhLightChanged(uint8_t brightness) {
    Serial.print("Device 7 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_7, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_7, HIGH);
    }
  //do what you need to do here
}

void eighthLightChanged(uint8_t brightness) {
    Serial.print("Device 8 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
      digitalWrite(RELAY_8, LOW);
    }
    else  {
      Serial.println("OFF");
      digitalWrite(RELAY_8, HIGH);
    }
  //do what you need to do here
}
