//
// Ugradbeni sistemi
// Demonstracija korištenja MQTT protokola
//
// Napomena: Svaki student treba koristiti jedinstvenu riječ 
//           umjesto "ugradbeni" u okviru tema
//

#define TEMASUBLEDS "fbazdar/ledice"
#define TEMAPUBPOT "fbazdar/potenciometar"
#define TEMAPUBTAST "fbazdar/taster"
#define TEMASUBDISP "fbazdar/display"

#include "mbed.h"
#include "C12832.h"

#define MQTTCLIENT_QOS2 0

#include "easy-connect.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include <string.h>

int arrivedcount = 0;

DigitalIn taster(p7);
DigitalOut led1(p5);
DigitalOut led2(p6);
AnalogIn pot(p15);
PwmOut led3(p21);

C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);

char* str;
double pot_value=-1;
bool taster_state=1;

void messageArrived(MQTT::MessageData& md)
{
    MQTT::Message &message = md.message;
    printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\r\n", message.payloadlen, (char*)message.payload);
    ++arrivedcount;
    
    str=(char*)message.payload;
    
    if (!strncmp(str,"led1",sizeof(str))) led1=!led1;
    else if (!strncmp(str,"led2",sizeof(str))) led2=!led2;
    else led3=atof(str);
}

void messageArrivedForDisplay(MQTT::MessageData& md) // funkcija za display
{
    MQTT::Message &message = md.message;
    printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\r\n", message.payloadlen, (char*)message.payload);
    ++arrivedcount;
    lcd.cls();
    lcd.locate(0,3);
    lcd.printf("%.*s\r\n",message.payloadlen, (char*)message.payload);
}

int main(int argc, char* argv[])
{
    printf("Ugradbeni sistemi\r\n");
    printf("Demonstracija korištenja MQTT protokola\r\n\r\n");

    NetworkInterface *network;
    network = NetworkInterface::get_default_instance();
    
    if (!network) {
        return -1;
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

    if ((rc = client.subscribe(TEMASUBLEDS, MQTT::QOS2, messageArrived)) != 0)
        printf("rc from MQTT subscribe is %d\r\n", rc);

    MQTT::Message message;

    // QoS 0
    char buf[100];
    while(1) {
        if (taster_state!=taster) {
            taster_state=taster;
            sprintf(buf, "{\"Taster\": %d}", taster.read());
            message.qos = MQTT::QOS0;
            message.retained = false;
            message.dup = false;
            message.payload = (void*)buf;
            message.payloadlen = strlen(buf);
            rc = client.publish(TEMAPUBTAST, message);
        }
        if (pot_value!=pot) {
            pot_value=pot;
            sprintf(buf, "{\"Potenciometar\": %f}", pot_value);
            message.qos = MQTT::QOS0;
            message.retained = false;
            message.dup = false;
            message.payload = (void*)buf;
            message.payloadlen = strlen(buf);
            rc = client.publish(TEMAPUBPOT, message);
        }
        rc = client.subscribe(TEMASUBDISP,MQTT::QOS2,messageArrivedForDisplay);//dodano
        rc = client.subscribe(TEMASUBLEDS, MQTT::QOS0, messageArrived);
        wait(1);
    }

}
