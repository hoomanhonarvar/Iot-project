#include <ESP8266WiFi.h>
const char* ssid = "HH";
const char* password = "12345678";
int ledPin = D4;
int timeOn=0;
int timeOff=1000;
WiFiServer server(80);
void setup() {
Serial.begin(115200);
delay(10);
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, LOW);
// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
digitalWrite(ledPin, !digitalRead(ledPin));
}
Serial.println("");
Serial.println("WiFi connected");
// Start the server
server.begin();
Serial.println("Server started");
// Print the IP address
Serial.print("Use this URL : ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}
void loop() {
// Check if a client has connected
if(timeOn)
digitalWrite(ledPin,LOW);
delay(timeOn);
digitalWrite(ledPin,HIGH);
delay(timeOff);
WiFiClient client = server.available();
if (!client) {
return;
}
// Wait until the client sends some data
Serial.println("new client");
while(!client.available()){
delay(1);
}
// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);

client.flush();
// Match the request
int value = LOW;
int x=request.indexOf("On=");
int y=request.indexOf("&");
x+=3;
int x1=x;
x=y-x;

if (request.indexOf("On=") != -1) {
int numOn=0;
for (int i=x;i>=1;i--)
{
  numOn+=(request[x1]-48)*pow(10,i-1);
  x1++;
}
Serial.print("\ntime On is :");
Serial.println(numOn);
timeOn=numOn;
 }
if(request.indexOf("H")!=-1)
 y=request.indexOf("H");
x=request.indexOf("off=");
x+=4;
x1=x;
x=y-x-1;
int numOff=0;
if (request.indexOf("off=") != -1){
for (int i=x;i>=1;i--)
{
  numOff+=(request[x1]-48)*pow(10,i-1);
  x1++;
}
Serial.print("\ntime of is :");
Serial.println(numOff);
timeOff=numOff;
}
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<style>");
client.println("body {background-color: rgba(0, 50, 255, 0.30);");
client.println("color: rgb(255, 255, 255);");
client.println("font-family: Arial, Helvetica, sans-serif;\n}");
client.println("form{");
client.println("text-align: center;");
client.println("background-color: rgba(0, 10, 255, 0.50);");
client.println("border: 1px solid #fff;");
client.println(" border-radius: 20px;");
 client.println(" padding: 5%;");
client.println("margin: 20%;}");
client.println("input {");
client.println("margin: 1%");
client.println(" }");
client.print("#");
client.println("botton{padding: 10px;");
client.println("background-color: #fff;");
client.println("color:rgba(0, 50, 255, 0.30);");
client.println(" text-align: center;");
client.println("border: 0;");
client.println("border-radius: 10px;");
client.println("}");
client.println("#");
client.println("fild{");
client.println("background-color: #fff;");
client.println("color:rgba(0, 50, 255, 0.30);");
client.println("text-align: center;");
client.println("border: 0;");
client.println("padding: 5px;");
client.println("border-radius: 10px;");
client.println("}");
client.println("</style>");
client.println(" </head>");                
client.println("<form action="" method=""get"" class=""form-example"">");
client.println("<label for=""ON"">Time(ms) on: </label>");
client.println("<input type=""text"" name=""On"" id=""On"" required><br><br>");
client.println("<label for=""OFF:"">Time(ms) off: </label>");
client.println("<input type=""text"" ""name=""off"" id=""off"" required><br><br>");
client.println("<input type=""submit"" value=""Send");
client.println("Click <a href=\"/time\"><br>");
client.println("</form>");
client.println("</html>");
delay(1);
Serial.println("Client disconnected");
Serial.println("");}