#include <iostream>
#include <map>

#include <enet.h>

#include <network/network_constants.h>

#include "server.h"

static bool sigint_received = false;

void sigint_handler([[maybe_unused]] int sig) {
  sigint_received = true;
}

int run_server(const unsigned short port) {
  std::cout << "[Server] Starting on port " << port << std::endl;
  
  if (enet_initialize() != 0) {
    std::cout << "[Server] Failed to initialize ENet" << std::endl;
  }

  ENetAddress address;

  address.host = ENET_HOST_ANY;
  address.port = port;

  ENetHost *server = nullptr;

    server = enet_host_create(
      &address,     /* address to bind to */ 
      MAX_CHANNELS, /* number of channels to allow */
      MAX_CLIENTS,  /* maximum number of clients */
      0,            /* maximum packet size */
      0             /* peer limit */
    );

  if (server == nullptr) {
    std::cout << "[Server] Failed to create server" << std::endl;
    return 1;
  }

  signal(SIGINT, sigint_handler);

  std::map<uint32_t, Client> clients;

  while (true) {
    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
          uint32_t client_id = event.peer->connectID;

          clients.emplace(client_id, Client{});

          std::cout << "[Server] Client connected!" << std::endl;
          break;
        }
        case ENET_EVENT_TYPE_RECEIVE: {
          
          enet_packet_destroy(event.packet);
          break;
        }
        case ENET_EVENT_TYPE_DISCONNECT: {
          break;
        }
        default: {
          break;
        }
      }
    }

    // Break if SIGINT is received
    if (sigint_received) {
      break;
    }
  }

  std::cout << "[Server] Shutting down now" << std::endl;

  enet_host_flush(server);

  enet_host_destroy(server);
  enet_deinitialize();
  return 0;
}
