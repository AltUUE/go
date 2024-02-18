#include <Server.h>

extern "C" {
    #include <CSML_Server.h>
}

#define HOST "localhost"
#define PORT "9034"


void on_connect(CSML_Server* server, int fd){
    add_client_to_lobby(server, fd, 0);
}

int main(){
    CSML_Server* server = initialize_server(HOST, PORT, 5, 256, 5, on_connect);
    char* secret_state = "Hello World!";
    int lobby_id = add_lobby_to_server(server, secret_state, 10, 10);
    while(1){
        poll_server(server);
    }
}
