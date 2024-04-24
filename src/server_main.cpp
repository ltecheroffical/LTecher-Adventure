#ifdef SERVER_BUILD

#include <iostream>
#include <map>

#include <enet.h>

#include "marcos/exit_codes.h"

#define PORT 8080

typedef struct Client {
  bool is_authenticated;
} Client;

int main(int argc, char** argv) {
  if (enet_initialize() != 0) {
    std::cerr << "Failed to initialize ENet" << std::endl;
    return EXIT_MAJOR_ERROR;
  }

  ENetAddress address;
  ENetHost *server;

  atexit(enet_deinitialize);

  address.host = ENET_HOST_ANY;
  address.port = PORT;

  server = enet_host_create(&address, 32, 2, 0, 0);

  if (server == NULL) {
    std::cerr << "Failed to create server" << std::endl;
    return EXIT_MAJOR_ERROR;
  }

  std::cout << "Server started! [PORT " << PORT << "]" << std::endl;
  
  int event_status = 1;
  enet_uint32 wait = 60'000;

  unsigned int client_id = 0;

  std::map<unsigned int, Client> clients;

  ENetEvent event;
  while (true) {
    event_status = enet_host_service(server, &event, wait);
    
    if (event_status > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
          event.peer->data = malloc(sizeof(unsigned int));
          *(unsigned int *)event.peer->data = client_id;
          clients.emplace(client_id, Client{});

          std::cout << "Client connected [ID #" << client_id << "]" << std::endl;
          client_id++;
          break;
        }
        case ENET_EVENT_TYPE_DISCONNECT: {
          unsigned int peer_id = *(unsigned int *)event.peer->data;
          clients.erase(peer_id);

          std::cout << "Client disconnected [ID #" << peer_id  << "]" << std::endl;

          free(event.peer->data);
          break;
        }
        case ENET_EVENT_TYPE_RECEIVE: {
          std::cout << "Received: " << event.packet->data << std::endl;
          enet_packet_destroy(event.packet);
          break;
        }
        default: {
          break;
        }
      }
    }
  }
  
  enet_host_destroy(server);
  return 0;
}
#endif
