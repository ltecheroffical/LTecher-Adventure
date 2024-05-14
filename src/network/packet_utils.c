#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <network/types/packet_types.h>

#include "packet_utils.h"

size_t packet_size(const PacketType type) {
  switch (type) {
    case PACKET_C2S_CONNECT:
    case PACKET_S2C_WELCOME:
    case PACKET_C2S_POSITION_UPDATE:
    case PACKET_S2C_POSITION_UPDATE:
    default:
      return 0;
  }
}

size_t packet_size_bytes(const PacketType type) {
  return packet_size(type) + sizeof(PacketType);
}

char *packet_to_bytes(const PacketType type, const void *data) {
  char *packet = malloc(packet_size_bytes(type));
  short offset = 0;

 
  memcpy(packet + offset, &type, sizeof(PacketType));
  offset += sizeof(PacketType);
  memcpy(packet + offset, data, packet_size(type));

  // We serialized the packet
  return packet;
}

PacketType bytes_to_packet(const char *data, const size_t size, void *data_out) {
  if (size < sizeof(PacketType)) {
    errno = ENOMEM;
    return PACKET_NONE;
  }

  short offset = 0;

  PacketType type;
  memcpy(&type, data + offset, sizeof(PacketType));
  offset += sizeof(PacketType);

  if (offset + packet_size(type) > size) {
    errno = ENOMEM;
    return PACKET_NONE;
  }

  // For the output just allocate the size of the serialized packet
  memcpy(data_out, data + offset, packet_size(type));

  return type;
}
