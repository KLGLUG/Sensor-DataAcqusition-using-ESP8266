 #include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 2

const char *ssid = "your network name";
const char *password = "your password";
const char* mqtt_server = "ip address of server";


const char* clientID = "esp8266";//name of the device
const char* outTopic = "output";//outtopic to be used by mqtt broker
const char* inTopic = "input";//intopic to be used by mqtt broker


DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp_c;
char se[20];
char he[20];
WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];


void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);//function used to connect to your network

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
 // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientID)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic, clientID);
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}   
   
    
void callback(char* topic, byte* payload, unsigned int length) {

  payload[length] = '\0'; 
 String message = (char*)payload;//message recieved from server
while(1)//infinite loop
 {
 String k=""; 
k=k+"temp :"+dht.readTemperature(); //temp data
k.toCharArray(se,k.length()+1);

String h=""; 
h=h+"hum :"+dht.readHumidity(); //temp data
h.toCharArray(he,h.length()+1);

    client.publish(outTopic,se);//publishing data
    delay(1000);
    client.publish(outTopic,he);//publishing data
    delay(1000);

 } 
 

}
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);//server,portno
  
 client.setCallback(callback);

}

void loop() {

  if (!client.connected()) {
    reconnect();
    
  }
  
   client.loop();
  
      
}


