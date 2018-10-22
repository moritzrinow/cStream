#include "stream.h"

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>

#define write_space_left(stream) \
  (stream->capacity - stream->position)

#define read_space_left(stream) \
  (stream->length - stream->position)

#define capacity_left(stream) \
  (stream->capacity - stream->length)

static void stream_resize(STREAM* stream, int64 size);

void stream_init(STREAM * stream, int64 capac)
{
  if (capac > 0) { // Reserve
    stream->data = (char*)malloc(capac);
    stream->capacity = capac;
  }
  else { // Dont reserve
    stream->capacity = 0;
    stream->data = NULL;
  }

  stream->length = 0;
  stream->position = 0;
}

void stream_close(STREAM * stream)
{
  if (stream->capacity > 0) {
    free(stream->data);
  }
  stream->data = NULL;
  stream->capacity = 0;
  stream->length = 0;
  stream->position = 0;
}

int64 stream_reserve(STREAM * stream, int64 size)
{
  if (size <= 0) {
    return -1;
  }

  int64 newsize = stream->capacity + size;
  stream_resize(stream, newsize);
  return newsize;
}

int64 stream_write(STREAM * stream, char * buffer, int64 count, int64 offset)
{
  int64 result = 0;

  int64 space_left = write_space_left(stream);
  if (space_left < count) {
    stream_resize(stream, (stream->capacity + (count - space_left)));
  }

  char* dest = &(stream->data[stream->position]);
  char* source = &buffer[offset];
  memcpy(dest, source, count);
  stream->position += count;
  stream->length += count;
  result = count;

  return result;
}

void stream_write_byte(STREAM * stream, char value)
{
  stream_write(stream, &value, 1, 0);
}

int64 stream_write_str(STREAM * stream, const char * str)
{
  int32 len = strlen(str) + 1;
  return stream_write(stream, str, len, 0);
}

int64 stream_insert(STREAM * stream, char* buffer, int64 count, int64 offset)
{
  int64 result = 0;

  int64 space_left = capacity_left(stream);
  if (space_left < count) {
    stream_resize(stream, (stream->capacity + (count - space_left)));
  }

  char* src = &(stream->data[stream->position]);
  char* move_dest = &(stream->data[stream->position + count]);
  int64 read_spc = read_space_left(stream);

  // Move data
  memmove(move_dest, src, read_spc);

  // Insert input buffer at pos
  memcpy(src, &buffer[offset], count);

  // Update position and length
  stream->position += count;
  stream->length += count;
  result = count;

  return result;
}

void stream_insert_byte(STREAM * stream, char value)
{
  stream_insert(stream, &value, 1, 0);
}

int64 stream_insert_str(STREAM * stream, const char * str)
{
  int32 len = strlen(str) + 1;
  return stream_insert(stream, str, len, 0);
}

int64 stream_read(STREAM * stream, char * buffer, int64 count, int64 offset)
{
  int64 result = 0;

  int64 space_left = read_space_left(stream);
  if (space_left == 0) {
    return -1;
  }
  if (space_left > count) {
    space_left = count;
  }

  char* dest = &buffer[offset];
  char* source = &(stream->data[stream->position]);

  memcpy(dest, source, space_left);
  stream->position += space_left;
  result = space_left;

  return result;
}

int32 stream_read_byte(STREAM * stream)
{
  int32 result = 0;

  int64 space_left = read_space_left(stream);
  if (space_left == 0) {
    return -1;
  }
  
  return (int32)stream->data[stream->position++];
}

void stream_clear(STREAM * stream)
{
  memset(stream->data, 0, stream->capacity);
  stream->length = 0;
  stream->position = 0;
}

int32 stream_copy(STREAM* src, STREAM* dest)
{
  return stream_write(dest, src->data, src->length, 0) > 0;
}

int64 stream_set_pos(STREAM* stream, int64 pos)
{
  if (pos < 0 || pos > stream->length) {
    return -1;
  }

  stream->position = pos;
  return stream->position;
}

int64 stream_seek(STREAM* stream, int64 pos)
{
  return stream_set_pos(stream, pos);
}

int64 stream_rewind(STREAM * stream)
{
  return stream_set_pos(stream, 0);
}

static void stream_resize(STREAM * stream, int64 size)
{
  if (size < stream->capacity) {
    return;
  }

  if (stream->capacity > 0) {
    stream->data = (char*)realloc(stream->data, size);
  }
  else {
    stream->data = (char*)malloc(size);
  }

  stream->capacity = size;
}
