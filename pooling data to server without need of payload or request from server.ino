#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 2

const char *ssid = "NETGEAR";
const char *password = "bravehill576";
const char* mqtt_server = "192.168.1.14";
const char* clientID = "esp8266";//name of the device
const char* outTopic = "output";////outtopic to be used by mqtt broker


DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp_c; 
 WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);//function to connect to the network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());//ip address of the esp8266 device
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);//server,portno
   dht.begin(); //initialization of sensor
         
}

 void reconnect() {
// Loop until we're reconnected
  while (!client.connected())
 {
    Serial.print("Attempting MQTT connection...");
  // Attempt to connect
     if (client.connect(clientID)) {
      Serial.println("connected");
// Once connected, publish an announcement...
       client.publish(outTopic, clientID);
      // ... and resubscribe
    }
 else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
 // Wait 5 seconds before retrying
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
} 
void loop() {

  if (!client.connected()) {
    reconnect();
  }  
publishtemp();//function to publish temerature
publishhum();//function to publish humidity
} 



void publishtemp()
{
    dht.begin();//initialize the sensor
  String t="";
char te[20];
  temp_c = dht.readTemperature(); //reading temperature
t=t+"temperature is"+String(temp_c);
int l=t.length()+1;
t.toCharArray(te,l);//converting to character array
client.publish(outTopic,te);  //publishing the data to server
delay(2000);
  }

void publishhum()
{
    dht.begin();//initialize the sensor
 String h="";

char hu[20];
 
humidity = dht.readHumidity();//reading temperature
h=h+"humidity is"+humidity;
int j=h.length()+1;
h.toCharArray(hu,j);//converting to character array
client.publish(outTopic,hu);//publishing the data to server
delay(2000);

  }

