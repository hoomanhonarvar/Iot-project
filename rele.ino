#include <ESP8266WiFi.h>
const char* ssid = "HH";
const char* password = "12345678";
int ledPin = D1;
WiFiServer server(80);
void setup() {
Serial.begin(115200);
delay(10);
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, HIGH);
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
int value = HIGH;
if (request.indexOf("/LED=ON") != -1) {
digitalWrite(ledPin, HIGH);
value = HIGH; }
if (request.indexOf("/LED=OFF") != -1){
digitalWrite(ledPin, LOW);
value = LOW;
}
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("Led pin is now: ");
if(value == LOW) {
client.print("Off");
digitalWrite(ledPin, HIGH);
} else {
client.print("On");
digitalWrite(ledPin, LOW);
}
client.println("<head>");
client.println("");
client.println("<style>");
client.println("body{");
client.println("background-color:rgb(160, 153, 250,0.5);");
client.println("font-size: 32px;");
client.println("font-family: Arial, Helvetica, sans-serif;");
client.println("text-align: center;");
client.println("align-items: center;");
client.println("color: #ffffff;");
client.println("}");
client.println(".container{");
 client.println("background-color:rgb(160, 153, 250,0.8) ;");
client.println(" border-radius: 20px;");
client.println("margin: 10%;");
client.println("padding: 10%;");
client.println("}");
client.println(".btn {background-color:  rgb(130, 131, 130); blue);");
client.println("margin: 20px;");
client.println("padding: 20px;");
client.println("border-radius: 20px;}");
client.println("a{ color: #ffffff;");
client.println("font-style: normal;");
client.println("text-decoration: none;}");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<br><br>");
client.println("<div class=""container"">");
client.println("<p>Click to turn ON/OFF the Reley</p>");
client.println("<div class=""btn""><a href=\"/LED=ON\">ON</a></div>");
client.println("<div class=""btn""><a href=\"/LED=OFF\">OFF</a></div>");
client.println("</div>");
client.println("</body>");
client.println("</html>");
delay(1);
Serial.println("Client disconnected");
Serial.println("");}