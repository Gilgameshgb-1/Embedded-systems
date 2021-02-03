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
 
Ticker t;
AnalogIn pot1(p15); 
AnalogIn pot2(p16);
 
void dump_response(HttpResponse* res) {
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());
 
    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

void write_db(void) {
    
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

    // POST requests
     
    HttpRequest* post_req1 = new HttpRequest(socket, HTTP_POST, "http://195.130.59.222:8086/write?db=ugradbeni");
    char *body1;
    sprintf(body1,"potenciometar1,user=%s value=%f",USER_NAME,pot1.read()); 
    HttpResponse* post_res1 = post_req1->send(body1, strlen(body1));
    if (!post_res1) {
        printf("HttpRequest failed (error code %d)\n", post_req1->get_error());
        return;
    }
 
    printf("\n----- HTTP POST response -----\n");
    dump_response(post_res1);
    delete post_req1;
    
    HttpRequest* post_req2 = new HttpRequest(socket, HTTP_POST, "http://195.130.59.222:8086/write?db=ugradbeni");
    char *body2;
    sprintf(body2,"potenciometar2,user=%s value=%f",USER_NAME,pot2.read()); 
    HttpResponse* post_res2 = post_req2->send(body2, strlen(body2));
    if (!post_res2) {
        printf("HttpRequest failed (error code %d)\n", post_req2->get_error());
        return;
    }

    printf("\n----- HTTP POST response -----\n");
    dump_response(post_res2);
    delete post_req2;
    socket->close();
    delete socket;
}
 
int main() {
    t.attach(write_db,2);
    while(1) {
        wait(0.5);
    }
}
