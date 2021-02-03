//
// Ugradbeni sistemi
// Demonstracija korištenja HTTP POST za upis u InfluxDB Time Series bazu
//
// Napomena: Svaki student treba koristiti jedinstvenu riječ/ime
//           za identficiranje umjesto "korisnik1" 
//

#include "mbed.h"
#include "http_request.h"

#define USER_NAME "fbazdar"
 
#define TEMAPUBSIN  "ugradbeni/fbazdar/sinusoida"

#include "mbed.h"
#include "C12832.h"

#define MQTTCLIENT_QOS2 0

#include "easy-connect.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include <string.h>
#include <cmath>

Ticker sine;


float i = 0;
void draw_sine(void){
    NetworkInterface* network;
    network=NetworkInterface::get_default_instance();
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return;
    }
    // Create a TCP socket
    printf("\n----- Setting up TCP connection -----\n");
    TCPSocket* socket = new TCPSocket();
    nsapi_error_t open_result = socket->open(network);
    if (open_result != 0) {
        printf("Opening TCPSocket failed... %d\n", open_result);
        return;
    }
 
    nsapi_error_t connect_result = socket->connect("195.130.59.222", 8086);
    if (connect_result != 0) {
        printf("Connecting over TCPSocket failed... %d\n", connect_result);
        return;
    }
 
    printf("Connected over TCP\n");
    
    MQTTNetwork mqttNetwork(network);

    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);

    const char* hostname = "broker.hivemq.com";
    int port = 1883;
    printf("Connecting to %s:%d\r\n", hostname, port);
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;https://195.130.59.222:3000/dashboard/script/ugradbeni_zad3.js?panelId=2&fullscreen&orgId=1&rows=1&from=now-5m&to=now&name=fbazdar&refresh=1s
    data.MQTTVersion = 3;
    data.clientID.cstring = "ugradbeni";
    data.username.cstring = "";
    data.password.cstring = "";
    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\r\n", rc);
        
    MQTT::Message message;

    char buf[100];
    sprintf(buf, "%f", sin(i)*5);
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buf;
    message.payloadlen = strlen(buf);
    rc = client.publish(TEMAPUBSIN, message);
    if(i<=6.28){
        i+=((6.28)/(12));
    }else i = 0;
}
 
int main() {
    sine.attach(draw_sine,5);
    while(1) {
        wait(0.5);
    }
}
