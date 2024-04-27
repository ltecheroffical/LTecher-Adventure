#include <stddef.h>

#include <network/types/packet_types.h>

#ifndef NETWORK_PACKET_UTILS_H
#define NETWORK_PACKET_UTILS_H

/*
 * Get the size of a packet
 *
 * @param type The type of the packet
 *
 * @returns The size of the packet
 */
size_t packet_size(const PacketType type);
/*
 * Get the size of a packet when passed through `packet_to_bytes`
 *
 * @param type The type of the packet
 *
 * @returns The size of the packet
 */
size_t packet_size_bytes(const PacketType type);

/*
 * Converts a packet into bytes
 *
 * @param type The type of the packet
 * @param data The data of the packet
 *
 * @returns The bytes of the packet
 */
char *packet_to_bytes(const PacketType type, const void *data);
/*
 * Converts bytes into a packet
 *
 * @param data The bytes of the packet
 * @param size The size of the packet
 *
 * @param data_out The output data of the packet
 *
 * NOTE: To use the output then cast it to the correct type
 *
 * @returns The packet type or NULL if there was an error
 */
PacketType bytes_to_packet(const char *data, const size_t size, void *data_out);
#endif
