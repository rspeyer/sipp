/* 
 * FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 * Copyright (C) 2005-2012, Anthony Minessale II <anthm@freeswitch.org>
 *
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 *
 * The Initial Developer of the Original Code is
 * Anthony Minessale II <anthm@freeswitch.org>
 * Portions created by the Initial Developer are Copyright (C)
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * 
 * Anthony Minessale II <anthm@freeswitch.org>
 *
 *
 * switch_stun.h STUN (Simple Traversal of UDP over NAT)
 *
 */
/*!
  \defgroup stun1 STUN code
  \ingroup core1
  \{
*/
#ifndef FREESWITCH_STUN_PARSER_H
#define FREESWITCH_STUN_PARSER_H


#ifdef __cplusplus
extern "C" {
#endif

#define SWITCH_DECLARE(x) x
typedef size_t switch_size_t;
typedef uint16_t switch_port_t;

typedef enum {
	SWITCH_STATUS_SUCCESS,
	SWITCH_STATUS_FALSE,
	SWITCH_STATUS_TIMEOUT,
	SWITCH_STATUS_RESTART,
	SWITCH_STATUS_INTR,
	SWITCH_STATUS_NOTIMPL,
	SWITCH_STATUS_MEMERR,
	SWITCH_STATUS_NOOP,
	SWITCH_STATUS_RESAMPLE,
	SWITCH_STATUS_GENERR,
	SWITCH_STATUS_INUSE,
	SWITCH_STATUS_BREAK,
	SWITCH_STATUS_SOCKERR,
	SWITCH_STATUS_MORE_DATA,
	SWITCH_STATUS_NOTFOUND,
	SWITCH_STATUS_UNLOAD,
	SWITCH_STATUS_NOUNLOAD,
	SWITCH_STATUS_IGNORE,
	SWITCH_STATUS_TOO_SMALL,
	SWITCH_STATUS_FOUND,
	SWITCH_STATUS_CONTINUE,
	SWITCH_STATUS_TERM,
	SWITCH_STATUS_NOT_INITALIZED,
	SWITCH_STATUS_INVALID_PACKET,
	SWITCH_STATUS_BAD_ARG
} switch_status_t;

#define SWITCH_STUN_DEFAULT_PORT 3478
#define SWITCH_STUN_PACKET_MIN_LEN 20
#define SWITCH_STUN_ATTRIBUTE_MIN_LEN 8
#define SWITCH_STUN_MAX_BUFFER_SIZE 512

// USERNAME and PASSWORD must be multiple of 4 as per RFC 5245
#define SWITCH_STUN_UFRAG_LENGTH 16 // Defined to match WebRTC
#define SWITCH_STUN_PASSWORD_LENGTH 22 // Defined to match WebRTC
#define SWITCH_STUN_USERNAME_LENGTH 33 // (RFRAG:LFRAG) == (2 * UFRAG_LENGTH) + 1
#define SWITCH_STUN_USERNAME_PADDED_LENGTH 36 // 4-byte padded length of SWITCH_STUN_USERNAME_LENGTH

#define SWITCH_ICE_HOST_LENGTH 50

typedef enum {
	SWITCH_STUN_BINDING_REQUEST = 0x0001,
	SWITCH_STUN_BINDING_RESPONSE = 0x0101,
	SWITCH_STUN_BINDING_ERROR_RESPONSE = 0x0111,
	SWITCH_STUN_SHARED_SECRET_REQUEST = 0x0002,
	SWITCH_STUN_SHARED_SECRET_RESPONSE = 0x0102,
	SWITCH_STUN_SHARED_SECRET_ERROR_RESPONSE = 0x0112,
	SWITCH_STUN_ALLOCATE_REQUEST = 0x0003,
	SWITCH_STUN_ALLOCATE_RESPONSE = 0x0103,
	SWITCH_STUN_ALLOCATE_ERROR_RESPONSE = 0x0113,
	SWITCH_STUN_SEND_REQUEST = 0x0004,
	SWITCH_STUN_SEND_RESPONSE = 0x0104,
	SWITCH_STUN_SEND_ERROR_RESPONSE = 0x0114,
	SWITCH_STUN_DATA_INDICATION = 0x0115
} switch_stun_message_t;

#define STUN_MAGIC_COOKIE 0x2112A442

typedef enum {
	SWITCH_STUN_ATTR_MAPPED_ADDRESS = 0x0001,	/* Address */
	SWITCH_STUN_ATTR_RESPONSE_ADDRESS = 0x0002,	/* Address */
	SWITCH_STUN_ATTR_CHANGE_REQUEST = 0x0003,	/* UInt32 */
	SWITCH_STUN_ATTR_SOURCE_ADDRESS = 0x0004,	/* Address */
	SWITCH_STUN_ATTR_CHANGED_ADDRESS = 0x0005,	/* Address */
	SWITCH_STUN_ATTR_USERNAME = 0x0006,	/* ByteString, multiple of 4 bytes */
	SWITCH_STUN_ATTR_PASSWORD = 0x0007,	/* ByteString, multiple of 4 bytes */
	SWITCH_STUN_ATTR_MESSAGE_INTEGRITY = 0x0008,	/* ByteString, 20 bytes */
	SWITCH_STUN_ATTR_ERROR_CODE = 0x0009,	/* ErrorCode */
	SWITCH_STUN_ATTR_UNKNOWN_ATTRIBUTES = 0x000a,	/* UInt16List */
	SWITCH_STUN_ATTR_REFLECTED_FROM = 0x000b,	/* Address */
	SWITCH_STUN_ATTR_TRANSPORT_PREFERENCES = 0x000c,	/* TransportPrefs */
	SWITCH_STUN_ATTR_LIFETIME = 0x000d,	/* UInt32 */
	SWITCH_STUN_ATTR_ALTERNATE_SERVER = 0x000e,	/* Address */
	SWITCH_STUN_ATTR_MAGIC_COOKIE = 0x000f,	/* ByteString, 4 bytes */
	SWITCH_STUN_ATTR_BANDWIDTH = 0x0010,	/* UInt32 */
	SWITCH_STUN_ATTR_DESTINATION_ADDRESS = 0x0011,	/* Address */
	SWITCH_STUN_ATTR_SOURCE_ADDRESS2 = 0x0012,	/* Address */
	SWITCH_STUN_ATTR_DATA = 0x0013,	/* ByteString */
	SWITCH_STUN_ATTR_REALM = 0x0014, /* ByteString */
	SWITCH_STUN_ATTR_NONCE = 0x0015, /* ByteString */
	SWITCH_STUN_ATTR_XOR_MAPPED_ADDRESS = 0x0020,   /* Address */
	SWITCH_STUN_ATTR_PRIORITY = 0x0024,  /* UInt32 */
	SWITCH_STUN_ATTR_USE_CANDIDATE = 0x0025,  /* No content, Length = 0 */
	SWITCH_STUN_ATTR_OPTIONS = 0x8001,	/* UInt32 */
	SWITCH_STUN_ATTR_SOFTWARE = 0x8022, /* ByteString */
	SWITCH_STUN_ATTR_ALTERNATE_SERVER2 = 0x8023, /* ByteString */
	SWITCH_STUN_ATTR_FINGERPRINT = 0x8028, /* UInt32 */
	SWITCH_STUN_ATTR_ICE_CONTROLLED = 0x8029,  /* UInt64 */
	SWITCH_STUN_ATTR_ICE_CONTROLLING = 0x802A,   /* UInt64 */
	SWITCH_STUN_ATTR_RETRANSMIT_COUNT = 0xFF00 /* UInt32 */
} switch_stun_attribute_t;

typedef enum {
	SWITCH_STUN_ERROR_BAD_REQUEST = 400,
	SWITCH_STUN_ERROR_UNAUTHORIZED = 401,
	SWITCH_STUN_ERROR_UNKNOWN_ATTRIBUTE = 420,
	SWITCH_STUN_ERROR_STALE_CREDENTIALS = 430,
	SWITCH_STUN_ERROR_INTEGRITY_CHECK_FAILURE = 431,
	SWITCH_STUN_ERROR_MISSING_USERNAME = 432,
	SWITCH_STUN_ERROR_USE_TLS = 433,
	SWITCH_STUN_ERROR_SERVER_ERROR = 500,
	SWITCH_STUN_ERROR_GLOBAL_FAILURE = 600
} switch_stun_error_t;

typedef enum {
	SWITCH_STUN_TYPE_PACKET_TYPE,
	SWITCH_STUN_TYPE_ATTRIBUTE,
	SWITCH_STUN_TYPE_ERROR
} switch_stun_type_t;

typedef struct {
	uint16_t type;
	uint16_t length;
	uint32_t cookie;
	char id[12];
} switch_stun_packet_header_t;

typedef struct {
	uint16_t type;
	uint16_t length;
	char value[];
} switch_stun_packet_attribute_t;

typedef struct {
	switch_stun_packet_header_t header;
	uint8_t first_attribute[];
} switch_stun_packet_t;

typedef struct {
	char *username;
	uint8_t controlling;
	uint32_t priority;
	uint8_t use_candidate;
	char host[SWITCH_ICE_HOST_LENGTH + 1];
	switch_port_t port;
} switch_stun_packet_data_t;

typedef struct {
	uint8_t wasted;
	uint8_t family;
	uint16_t port;
	uint32_t address;
} switch_stun_ip_t;

/*!
  \brief Generates the CRC32 checksum for a buffser
  \param start start value
  \param buffer the buffer to compute the checksum on
  \param len the length of the data
*/
SWITCH_DECLARE(uint32_t) switch_stun_compute_crc32(const void* buf, switch_size_t len);

/*!
  \brief Writes random characters into a buffer
  \param buf the buffer
  \param len the length of the data
  \param set the set of chars to use (NULL for auto)
*/
SWITCH_DECLARE(void) switch_stun_random_string(char *buf, uint16_t len, char *set);

/*!
  \brief Prepare a raw packet for parsing
  \param buf the raw data
  \param len the length of the data
  \return a stun packet pointer to buf to use as an access point
*/
SWITCH_DECLARE(switch_stun_packet_t *) switch_stun_packet_parse(uint8_t *buf, uint32_t len, switch_stun_packet_data_t *data/*, switch_memory_pool_t *pool*/);

/*!
  \brief Obtain a printable string form of a given value
  \param type the type of message
  \param value the value to look up
  \return a sring version of value
*/
SWITCH_DECLARE(const char *) switch_stun_value_to_name(int32_t type, uint32_t value);

SWITCH_DECLARE(char *) switch_stun_host_lookup(const char *host/*, switch_memory_pool_t *pool*/);

/*!
  \brief Extract a mapped address (IP:PORT) from a packet attribute
  \param attribute the attribute from which to extract
  \param ipstr a buffer to write the string representation of the ip
  \param port the port
  \return true or false
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_get_mapped_address(switch_stun_packet_attribute_t *attribute, char *ipstr, uint16_t *port);

/*!
  \brief Prepare a new outbound packet of a certian type and id
  \param id id to use (NULL for an auto generated id)
  \param type the stun packet type
  \param buf a pointer to data to use for the packet
  \return a pointer to a ready-to-use stun packet
*/
SWITCH_DECLARE(switch_stun_packet_t *) switch_stun_packet_build_header(switch_stun_message_t type, char *id, uint8_t *buf);

/*!
  \brief Add a username packet attribute
  \param packet the packet to add the attribute to
  \param username the string representation of the username
  \param ulen the length of the username
  \return true or false
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_username(switch_stun_packet_t *packet, char *username, uint16_t ulen);
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_password(switch_stun_packet_t *packet, char *password, uint16_t ulen);

SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_integrity(switch_stun_packet_t *packet, const char *pass);
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_fingerprint(switch_stun_packet_t *packet);

/*!
  \brief Add a mapped address packet attribute
  \param packet the packet to add the attribute to
  \param ipstr the string representation of the ip
  \param port the port of the mapped address
  \return true or false
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_mapped_address(switch_stun_packet_t *packet, char *ipstr, uint16_t port);
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_xor_mapped_address(switch_stun_packet_t *packet, char *ipstr, uint16_t port);

/*!
  \brief Set ICE controlled parameter
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_ice_controlled(switch_stun_packet_t *packet);

/*!
  \brief Set ICE controlling parameter
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_ice_controlling(switch_stun_packet_t *packet);

/*!
  \brief Set ICE controlling parameter
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_use_candidate(switch_stun_packet_t *packet);

/*!
  \brief Set ICE priority parameter
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_priority(switch_stun_packet_t *packet, uint32_t priority);

/*!
  \brief Set STUN error parameter
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_attribute_add_error(switch_stun_packet_t *packet, int error);

/*!
  \brief Perform a stun lookup
  \param ip the local ip to use (replaced with stun results)
  \param port the local port to use (replaced with stun results)
  \param stunip the ip of the stun server
  \param stunport the port of the stun server
  \param err a pointer to describe errors
  \param pool the memory pool to use
  \return SUCCESS or FAIL
*/
#ifdef SIPP_NOT_NEEDED
SWITCH_DECLARE(switch_status_t) switch_stun_lookup(char **ip,
												   switch_port_t *port, char *stunip, switch_port_t stunport, char **err, switch_memory_pool_t *pool);
#endif


/*!
  \brief Obtain the padded length of an attribute's value
  \param attribute the attribute
  \return the padded size in bytes
*/
SWITCH_DECLARE(uint16_t) switch_stun_attribute_padded_length(switch_stun_packet_attribute_t *attribute);

/*!
  \brief set a switch_stun_packet_attribute_t pointer to point at the first attribute in a packet
  \param packet the packet in question
  \param attribute the pointer to set up
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_first_attribute(switch_stun_packet_t *packet, switch_stun_packet_attribute_t **attribute);

/*!
  \brief Increment an attribute pointer to the next attribute in it's packet
  \param attribute the pointer to increment
  \param end pointer to the end of the buffer
  \return true or false depending on if there are any more attributes
*/
SWITCH_DECLARE(uint8_t) switch_stun_packet_next_attribute(switch_stun_packet_attribute_t **attribute);


/*!
  \brief Validate a STUN attribute
  \param attribute the pointer to increment
  \param end pointer to the end of the buffer
  \return true or false depending on if there are any more attributes
*/
SWITCH_DECLARE(uint8_t) switch_stun_validate_packet_attribute(switch_stun_packet_attribute_t *attribute, void* end);

/*!
  \brief Obtain the correct length in bytes of a stun packet
  \param packet the packet in question
  \return the size in bytes (host order) of the entire packet
*/
#define switch_stun_packet_length(packet) ntohs(packet->header.length) + (sizeof(switch_stun_packet_header_t))
///\}

#ifdef __cplusplus
}
#endif

#endif
/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4:
 */
