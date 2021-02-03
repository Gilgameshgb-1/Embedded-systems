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
 
 
#define TEMAPUBPOT1 "ugradbeni/fbazdar/potenciometar1"
#define TEMAPUBPOT2 "ugradbeni/fbazdar/potenciometar2"

#include "mbed.h"
#include "C12832.h"

#define MQTTCLIENT_QOS2 0

#include "easy-connect.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include <string.h>

double pot_value1=-1;
double pot_value2=-1;
 
Ticker t;
AnalogIn pot1(p15); 
AnalogIn pot2(p16);
 

void write_db(void) {
   
    NetworkInterface* network;
    network=NetworkInterface::get_default_instance();
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return;
    }
    MQTTNetwork mqttNetwork(network);

    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);

    const char* hostname = "broker.hivemq.com";
    int port = 1883;
    printf("Connecting to %s:%d\r\n", hostname, port);
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "ugradbeni";
    data.username.cstring = "";
    data.password.cstring = "";
    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\r\n", rc);

    MQTT::Message message;

    // QoS 0
    char buf[100];

        if (pot_value2!=pot2) {
            pot_value2=pot2;
            sprintf(buf, "%f", pot_value2);
            message.qos = MQTT::QOS0;
            message.retained = false;
            message.dup = false;
            message.payload = (void*)buf;
            message.payloadlen = strlen(buf);
            rc = client.publish(TEMAPUBPOT1, message);
        }
        if (pot_value1!=pot1) {
            pot_value1=pot1;
            sprintf(buf, "%f", pot_value1);
            message.qos = MQTT::QOS0;
            message.retained = false;
            message.dup = false;
            message.payload = (void*)buf;
            message.payloadlen = strlen(buf);
            rc = client.publish(TEMAPUBPOT2, message);
        }
}
 
int main() {
    t.attach(write_db,2);
    while(1) {
        wait(0.5);
    }
}
