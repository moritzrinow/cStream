#include "serialize.h"

#ifdef _SERIALIZE_FUNCTION_CALLS

void serialize_int8(STREAM * stream, int8 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_int16(STREAM * stream, int16 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_int32(STREAM * stream, int32 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_int64(STREAM * stream, int64 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

int32 deserialize_int8(STREAM * stream, int8 * out)
{
  return (stream_read(stream, (char*)out, sizeof(int8), 0)) == sizeof(int8);
}

int32 deserialize_int16(STREAM * stream, int16 * out)
{
  return (stream_read(stream, (char*)out, sizeof(int16), 0)) == sizeof(int16);
}

int32 deserialize_int32(STREAM * stream, int32 * out)
{
  return (stream_read(stream, (char*)out, sizeof(int32), 0)) == sizeof(int32);
}

int32 deserialize_int64(STREAM * stream, int64 * out)
{
  return (stream_read(stream, (char*)out, sizeof(int64), 0)) == sizeof(int64);
}

void serialize_uint8(STREAM * stream, uint8 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_uint16(STREAM * stream, uint16 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_uint32(STREAM * stream, uint32 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_uint64(STREAM * stream, uint64 value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

int32 deserialize_uint8(STREAM * stream, uint8 * out)
{
  return (stream_read(stream, (char*)out, sizeof(uint8), 0)) == sizeof(uint8);
}

int32 deserialize_uint16(STREAM * stream, uint16 * out)
{
  return (stream_read(stream, (char*)out, sizeof(uint16), 0)) == sizeof(uint16);
}

int32 deserialize_uint32(STREAM * stream, uint32 * out)
{
  return (stream_read(stream, (char*)out, sizeof(uint32), 0)) == sizeof(uint32);
}

int32 deserialize_uint64(STREAM * stream, uint64 * out)
{
  return (stream_read(stream, (char*)out, sizeof(uint64), 0)) == sizeof(uint64);
}

void serialize_float(STREAM * stream, float value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

void serialize_double(STREAM * stream, double value)
{
  stream_write(stream, (char*)&value, sizeof(value), 0);
}

int32 deserialize_float(STREAM * stream, float * out)
{
  return (stream_read(stream, (char*)out, sizeof(float), 0)) == sizeof(float);
}

int32 deserialize_double(STREAM * stream, double * out)
{
  return (stream_read(stream, (char*)out, sizeof(double), 0)) == sizeof(double);
}

void serialize_cstring(STREAM * stream, const char * value)
{
  int32 length = strlen(value) + 1;
  stream_write(stream, value, length, 0);
}

void serialize_string(STREAM * stream, char * value)
{
  int32 length = strlen(value) + 1;
  stream_write(stream, value, length, 0);
}

int32 deserialize_string(STREAM * stream, char * out, int32 size)
{
  if (size == 0) {
    return -1;
  }

  *out = '\0';

  for (int32 i = 0; i < size; i++) {
    int32 current = stream_read_byte(stream);
    if (current < 0) {
      break;
    }

    char value = (char)current;
    out[i] = value;
    if (value == '\0') {
      return 1;
    }
  }

  return 0;
}

#endif /* _SERIALIZE_FUNCTION_CALLS */