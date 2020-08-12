#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
char* ssid = "name";
char* password = "name12345”";
int sensorValue;
int sendmessage(String d)
{
  int sres,net;
  if (WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;
    String url="http://aaa987.000webhostapp.com/writefile.php?data="+d;
    Serial.println("URL: "+url);
    http.begin(url);
    http.addHeader("Content-Type","text/plain");
    int httpCode=http.GET();
    String payload=http.getString();
    Serial.println("While sending I received this from server : "+payload);
    if (payload=="SUCCESS. Data written in file.")
    {
      sres=1;
      net=1;
    }
    else
    {
      sres=0;
      net=0;
    }
    http.end();
  }
  else
  {
    Serial.println("Internet Problem!");
    net=0;
  }
  return(sres && net);
}
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status() !=WL_CONNECTED)
  {
    delay(500);
    Serial.println("Waiting for connection");
  }
  Serial.println("Connected...");
  delay(1000);
  if (WiFi.status() ==WL_CONNECTED)
  {
    Serial.println("Wi-Fi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
  delay(2000);
  Serial.println("Sending message to server espcomm");
  delay(5000);
  int res=sendmessage("Message_from_ESP8266");
  delay(1000);
  if (res==1)
  {
    Serial.println("Send Successfully");
  }
  else
  {
    Serial.println("Error on Server side or client side.");
  }
  int res1=sendmessage("Bikenum:7932");
  delay(1000);
  if (res1==1)
  {
    Serial.println("Send Successfully");
  }
  else
  {
    Serial.println("Error on Server side or client side.");
  }
}
void loop()
{
  sensorValue = analogRead(A0);
  Serial.print("Sensor value : ");
  Serial.println(sensorValue,DEC);
  int res=sendmessage((String)sensorValue);
  delay(1000);
  if (res==1 )
  {
    Serial.println("Send Successfully");
  }
  else
  {
    Serial.println("Error on Server side or client side.");
  }
  delay(2000);
}
