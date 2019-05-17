#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
 
#include "index_test.h"  //Web page header file

//===============================================================
// Initialize every attribut we need
//===============================================================
WebServer server(80);
 
//Enter your SSID and PASSWORD
const char* ssid = "HUAWEI P20 lite";
const char* password = "**********";
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleADC() {
  int a = random(255);
  String adcValue = String(a);
  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
//===============================================================
// Setup
//===============================================================
 
void setup(void){
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connect to your wifi
  WiFi.begin(ssid, password);
     
  Serial.println("Connecting to ");
  Serial.print(ssid);
 
  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
  server.on("/", handleRoot);      //This is display page
  server.on("/readADC", handleADC);//To get update of ADC Value only

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();
}
