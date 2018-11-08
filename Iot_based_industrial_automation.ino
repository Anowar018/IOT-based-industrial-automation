
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#include "mainPage.h"

const int Light1=16;
const int Light2=14;
const int Light3=12;
const int Grinder=13;
const int Fan=15;

/* Set these to your desired credentials. */
const char *ssid = "Jontrotantrik";
const char *password = "jtl.roboticsv2";

ESP8266WebServer server(80);
String Light1Status,Light2Status,Light3Status,GrinderStatus,FanStatus,Temperature;
//=======================================================================
//                    handles main page 192.168.4.1
//=======================================================================
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  String s = MAIN_page;    
  s.replace("@@Light1@@", Light1Status);
  s.replace("@@Light2@@", Light2Status);
  s.replace("@@Light3@@", Light3Status);
  s.replace("@@Grinder@@", GrinderStatus);
   s.replace("@@Fan@@", FanStatus);
  s.replace("@@TEMP@@", Temperature);
  server.send(200, "text/html", s);    
}

//=======================================================================
//                    Handle Set Date/Time Settings
//=======================================================================
void handleForm() {
  String t_state = server.arg("submit");
  
  Temperature = String(analogRead(A0)/10);   //Do calibration here
  
//Change Load-1 State as per request
  if(t_state=="ON1")
  {
    Light1Status="ON";    
    digitalWrite(Light1, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF1")
  {
    Light1Status="OFF";    
    digitalWrite(Light1, LOW);      //Load1 Turned off  
  }
//Change Load-2 State as per request
  if(t_state=="ON2")
  {
    Light2Status="ON";    
    digitalWrite(Light2, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF2")
  {
    Light2Status="OFF";    
    digitalWrite(Light2, LOW);      //Load1 Turned off  
  }
//Change Load-3 State as per request
  if(t_state=="ON3")
  {
    Light3Status="ON";    
    digitalWrite(Light3, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF3")
  {
    Light3Status="OFF";    
    digitalWrite(Light3, LOW);      //Load1 Turned off  
  }
//Change Load-4 State as per request
  if(t_state=="ON4")
  {
    GrinderStatus="ON";    
    digitalWrite(Grinder, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF4")
  {
    GrinderStatus="OFF";    
    digitalWrite(Grinder, LOW);      //Load1 Turned off  
  }
  if(t_state=="ON5")
  {
    FanStatus="ON";    
    digitalWrite(Fan, HIGH);       //Load1 Turned on
  }
  
  if(t_state=="OFF5")
  {
    FanStatus="OFF";    
    digitalWrite(Fan, LOW);      //Load1 Turned off  
  }
  if(t_state=="ON6")
  {
    FanStatus="Full Speed";    
    analogWrite(Fan, 255);       //Load1 Turned on
  }
  
  if(t_state=="ON7")
  {
    FanStatus="Medium Speed";    
    analogWrite(Fan, 127);      //Load1 Turned off  
  }
  if(t_state=="ON8")
  {
    FanStatus="Slow Speed";    
    analogWrite(Fan, 63);      //Load1 Turned off  
  }

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");  //This Line Keeps It on Same Page
   
  delay(500);
}
//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/form", handleForm);
 
  server.begin();
  Serial.begin(9600);
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(Light3, OUTPUT);
  pinMode(Grinder, OUTPUT);  
  pinMode(Fan, OUTPUT);  
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  server.handleClient();
}
//=======================================================================
