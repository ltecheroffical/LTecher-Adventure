#include <stdint.h>
#include <stdbool.h>

#include "network_types.h"

#ifndef NETWORK_PACKET_TYPES_H
#define NETWORK_PACKET_TYPES_H

typedef enum PacketType {
  PACKET_NONE,

  PACKET_C2S_CONNECT,
  PACKET_S2C_WELCOME,
  PACKET_S2C_CONNECT_ERROR,

  PACKET_C2S_POSITION_UPDATE,
  PACKET_S2C_POSITION_UPDATE
} PacketType;


typedef enum S2CConnectError {
  S2C_CONNECT_ERROR_VERSION,
  
  S2C_CONNECT_ERROR_SERVER_FULL,

  S2C_CONNECT_ERROR_BANNED,

  S2C_CONNECT_ERROR_CUSTOM
} S2CConnectError;


typedef struct C2SPacketConnect {
  char name[64];
  uint16_t version; // This is 65,535 possible versions!
} C2SPacketConnect;

typedef struct S2CPacketWelcome {
  uint32_t id;

  bool player_health_public;
} S2CPacketWelcome;

typedef struct S2CPacketConnectError {
  char error_data[128];
  S2CConnectError error_type;
} S2CPacketConnectError;


typedef struct C2SPacketPositionUpdate {
  uint8_t direction_x;
  uint8_t direction_y;
  bool is_running;
} C2SPacketPositionUpdate;

typedef struct S2CPacketPositionUpdate {
  uint32_t id;
  float position_x;
  float position_y;
} S2CPacketPositionUpdate;
#endif
