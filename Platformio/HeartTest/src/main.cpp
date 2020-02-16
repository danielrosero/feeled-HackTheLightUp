#include <Arduino.h>


/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 * 
 * This example is for FirebaseESP8266 Arduino library v 2.7.7 or later
 *
*/


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


#define FIREBASE_HOST "lanave-121c6.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "aJkgZO7jvFY8X0cptgdiwyEjtQX4P1N3MxTf6Xav"
#define WIFI_SSID "VeartDesigns"
#define WIFI_PASSWORD "CatorzeDos-87!"

//Digital Capacitive Touch Sensor Arduino Interfacing
 
#define sensorPin 16 // capactitive touch sensor - Arduino Digital pin D1
 
int ledPin = 2; // Output display LED (on board LED) - Arduino Digital pin D13

int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read


//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

void printResult(FirebaseData &data);



void setup()
{

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);  
  pinMode(sensorPin, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  String path = "/Test";
 
  Firebase.setInt(firebaseData, path + "/testUser/touch",0);
}

void loop()
{
  String path = "/Test";

  val = analogRead(analogPin);  // read the input pin
  Serial.println(val);          // debug value

if(val>800){
  Firebase.setInt(firebaseData, path + "/testUser/touch",1);
}else{
  Firebase.setInt(firebaseData, path + "/testUser/touch",0);
}

  delay(50);
}
