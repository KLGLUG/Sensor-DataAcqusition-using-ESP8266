# Sensor-DataAcqusition-using-ESP8266

In this project sensor data from dht11 which is connected to Esp8266 is transmitted to server continously using mqtt protocol.

file-1:pooling data to server when payload recieved.ino
  Starts sending  data to server continously only if it receives a payload from server.(publish command from server with random message)
  
  file-2:pooling data to server without need of payload or request from server.ino
     Starts sending data to server continously without need of any initiation command/payload/publish command from server.
     
 Basecode:https://gist.github.com/igrr/7f7e7973366fc01d6393
  
