#ifndef _SERIALIZE_H
#define _SERIALIZE_H

#include "stream.h"

#ifndef _SERIALIZE_FUNCTION_CALLS // We make full function calls for one-liner
#define _SERIALIZE_MACROS // We use inline code with macros
#endif /* _SERIALIZE_FUNCTION_CALLS */

/*
* The following functions allow you to serialize/deserialize primitive data types like
* integers, floats to/from byte streams. Strings can also be writting or read, but it
* takes a little more effort.
* Note:
* If you use the standart macros, some of them might not represent a result value.
* Examples of that would be the string serialize functions.
*/

/*******************/
/* Signed integers */
/*******************/

/*
* Writes signed integer values to a stream.
*/

#ifdef _SERIALIZE_MACROS
#define serialize_int8(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_int16(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_int32(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_int64(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)
#else
  void serialize_int8(STREAM* stream, int8 value);
  void serialize_int16(STREAM* stream, int16 value);
  void serialize_int32(STREAM* stream, int32 value);
  void serialize_int64(STREAM* stream, int64 value);
#endif /* _SERIALIZE_MACROS */

/*
* Reads signed integer values from a stream.
* Returns 1 on success, 0 on failure.
*/

#ifdef _SERIALIZE_MACROS
#define deserialize_int8(stream, out) \
  ((stream_read(stream, (char*)out, sizeof(int8), 0)) == sizeof(int8))

#define deserialize_int16(stream, out) \
  ((stream_read(stream, (char*)out, sizeof(int16), 0)) == sizeof(int16))

#define deserialize_int32(stream, out) \
  ((stream_read(stream, (char*)out, sizeof(int32), 0)) == sizeof(int32))

#define deserialize_int64(stream, out) \
  ((stream_read(stream, (char*)out, sizeof(int64), 0)) == sizeof(int64))
#else
  int32 deserialize_int8(STREAM* stream, int8* out);
  int32 deserialize_int16(STREAM* stream, int16* out);
  int32 deserialize_int32(STREAM* stream, int32* out);
  int32 deserialize_int64(STREAM* stream, int64* out);
#endif /* _SERIALIZE_MACROS */

/********************/
/* /Signed integers */
/********************/

/*********************/
/* Unsigned integers */
/*********************/

/*
* Writes unsigned integer values to a stream.
*/

#ifdef _SERIALIZE_MACROS
#define serialize_uint8(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_uint16(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_uint32(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_uint64(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)
#else
  void serialize_uint8(STREAM* stream, uint8 value);
  void serialize_uint16(STREAM* stream, uint16 value);
  void serialize_uint32(STREAM* stream, uint32 value);
  void serialize_uint64(STREAM* stream, uint64 value);
#endif /* _SERIALIZE_MACROS */

/*
* Reads unsigned integer values from a stream.
* Returns 1 on success, 0 on failure.
*/

#ifdef _SERIALIZE_MACROS
#define deserialize_uint8(stream, out) \
  (stream_read(stream, (char*)out, sizeof(uint8), 0)) == sizeof(uint8))

#define deserialize_uint16(stream, out) \
  (stream_read(stream, (char*)out, sizeof(uint16), 0)) == sizeof(uint16))

#define deserialize_uint32(stream, out) \
  (stream_read(stream, (char*)out, sizeof(uint32), 0)) == sizeof(uint32))

#define deserialize_uint64(stream, out) \
  (stream_read(stream, (char*)out, sizeof(uint64), 0)) == sizeof(uint64))
#else
  int32 deserialize_uint8(STREAM* stream, uint8* out);
  int32 deserialize_uint16(STREAM* stream, uint16* out);
  int32 deserialize_uint32(STREAM* stream, uint32* out);
  int32 deserialize_uint64(STREAM* stream, uint64* out);
#endif /* _SERIALIZE_MACROS */

/**********************/
/* /Unsigned integers */
/**********************/

/******************/
/* Floating point */
/******************/

/*
* Writes floating point numbers to a stream.
*/

#ifdef _SERIALIZE_MACROS
#define serialize_float(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)

#define serialize_double(stream, value) \
  stream_write(stream, (char*)&value, sizeof(value), 0)
#else
  void serialize_float(STREAM* stream, float value);
  void serialize_double(STREAM* stream, double value);
#endif /* _SERIALIZE_MACROS */

/*
* Reads floating point numbers from a stream.
* Returns 1 on success, 0 on failure.
*/

#ifdef _SERIALIZE_MACROS
#define deserialize_float(stream, out) \
  ((stream_read(stream, (char*)out, sizeof(float), 0)) == sizeof(float))

#define deserialize_double(stream, out) \
  ((stream_read(stream, (char*)out, sizeof(double), 0)) == sizeof(double))
#else
  int32 deserialize_float(STREAM* stream, float* out);
  int32 deserialize_double(STREAM* stream, double* out);
#endif /* _SERIALIZE_MACROS */

/*******************/
/* /Floating point */
/*******************/

/**********/
/* String */
/**********/

/*
* Writes character sequences to a stream.
* The null-terminator is also written to the stream.
*/

#ifdef _SERIALIZE_MACROS
#define serialize_cstring(stream, value) \
do { \
  int32 length = _mbstrlen(value) + 1; \
  stream_write(stream, value, length, 0); \
} while(0)

#define serialize_string(stream, value) \
do { \
  int32 length = _mbstrlen(value) + 1; \
  stream_write(stream, value, length, 0); \
} while(0)
#else
  void serialize_cstring(STREAM* stream, const char* value); // Including null-terminator
  void serialize_string(STREAM* stream, char* value); // Including null-terminator
#endif /* _SERIALIZE_MACROS */

/*
* Reads character sequences from a stream until a null-terminator
* is reached. The null-terminator is also read from the stream.
*/

#ifdef _SERIALIZE_MACROS
#define deserialize_string(stream, out, size) \
do { \
  if (size == 0) { \
    break; \
  } \
\
  *out = '\0'; \
\
  for (int32 i = 0; i < size; i++) { \
    int32 current = stream_read_byte(stream); \
    if (current < 0) { \
      break; \
    } \
\
    char value = (char)current; \
    out[i] = value; \
    if (value == '\0') { \
      break; \
    } \
  } \
} while(0)
#else
  int32 deserialize_string(STREAM* stream, char* out, int32 size); // Including null-terminator
#endif /* _SERIALIZE_MACROS */

/***********/
/* /String */
/***********/

#endif /* _SERIALIZE_H */
