#pragma once

#include "message.hpp"
#include <vector>
#include <cstring>

/**
 * decodeMessage:
 *   - input: raw buffer + length
 *   - output: a Message (type + payload)
 *
 * Returns false if the buffer is invalid or too short.
 */
bool decodeMessage(const char* data, size_t length, Message& out_msg);

/**
 * encodeMessage:
 *   - input: a Message
 *   - output: a std::vector<uint8_t> with 4-byte header + payload
 */
std::vector<uint8_t> encodeMessage(const Message& msg);
