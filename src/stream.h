#ifndef _STREAM_H
#define _STREAM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "types.h"

struct stream_t;

/*
* Struct that represents a stream of bytes, that you can read
* from and write to.
* 
* Writing is guaranteed to succeed as long as there is enough
* memory left on the machine.
* Reading, in turn, can happen to only be executed partly,
* which depends on how much reading content there is in the stream.
*/
typedef struct stream_t {
  char* data; // The data in memory
  int64 position; // The current read/write position
  int64 length; // The number of bytes written to the stream
  int64 capacity; // The actual number of bytes allocated
}STREAM;

/*
* Initializes @stream and reserves @capac number of bytes.
*/
void stream_init(STREAM* stream, int64 capac);

/*
* Clears all resources used by a stream.
* Make sure to call this on every stream when you are done with it.
*/
void stream_close(STREAM* stream);

/*
* Extends the capacity of a stream by @size bytes.
* Returns the new size of @stream.
*/
int64 stream_reserve(STREAM* stream, int64 size);

/*
* Writes @count bytes from @buffer to @stream at the current position.
* @offset determines the offset of the input buffer.
* Returns the total number of bytes written to @stream.
*
* The difference to stream_insert is, that this function overwrites the data
* of the stream it collides with from position to end.
*/
int64 stream_write(STREAM* stream, char* buffer, int64 count, int64 offset);

/*
* Writes a byte to @stream.
*/
void stream_write_byte(STREAM* stream, char value);

/*
* Writes a string to @stream.
*/
int64 stream_write_str(STREAM* stream, const char* str);

/*
* Inserts @count bytes from @buffer into the stream at it's current position.
* @offset determines the offset of the input buffer.
* Returns the total number of bytes written to @stream.
*
* The difference to stream_write is, that this function does not overwrite the
* data is collides with, instead it actually inserts it into memory, which
* is obviously more expensive.
*/
int64 stream_insert(STREAM* stream, char* buffer, int64 count, int64 offset);

/*
* Inserts a byte into @stream.
*/
void stream_insert_byte(STREAM* stream, char value);

/*
* Inserts a string into @stream.
*/
int64 stream_insert_str(STREAM* stream, const char* str);

/*
* Reads @count bytes from @stream into @buffer.
* @offset determines the offset of the output buffer.
* Returns the actual number of bytes read or -1 if the end was reached.
*/
int64 stream_read(STREAM* stream, char* buffer, int64 count, int64 offset);

/*
* Reads a byte from @stream.
* Returns the integer value of the byte or -1
* if the end was reached.
*/
int32 stream_read_byte(STREAM* stream);

/*
* Sets all bytes, position and the length to zero.
* The actual memory is kept allocated. Capacity stays the same.
* If your intention is to free the memory, use stream_close.
*/
void stream_clear(STREAM* stream);

/*
* Copies the whole content of one stream to another at the
* destinations position.
* Returns 1 if success or 0 if failure.
*/
int32 stream_copy(STREAM* src, STREAM* dest);

/*
* Sets the position of @stream.
* Returns the new position of the stream or -1 on failure.
*/
int64 stream_set_pos(STREAM* stream, int64 pos);

/*
* Sets the position of @stream.
* Returns the new position of the stream or -1 on failure.
*/
int64 stream_seek(STREAM* stream, int64 pos);

/*
* Sets the position of @stream to 0.
* Returns the new position of the stream or -1 on failure.
*/
int64 stream_rewind(STREAM* stream);

/*
* Short macros for shortness.
*/
#ifdef _STREAM_MACROS
#define _init(stream, capacity) stream_init(stream, capacity)
#define _close(stream) stream_close(stream)
#define _reserve(stream, size) stream_reserve(stream, size)
#define _write(stream, buffer, count, offset) stream_write(stream, buffer, count, offset)
#define _writeb(stream, value) stream_write_byte(stream, value)
#define _writes(stream, string) stream_write_str(stream, string)
#define _insert(stream, buffer, count, offset) stream_insert(stream, buffer, count, offset)
#define _insertb(stream, value) stream_insert_byte(stream, value)
#define _inserts(stream, string) stream_insert_str(stream, string)
#define _read(stream, buffer, count, offset) stream_read(stream, buffer, count, offset)
#define _readb(stream) stream_read_byte(stream)
#define _clear(stream) stream_clear(stream)
#define _copy(src, dest) stream_copy(src, dest)
#define _seek(stream, pos) stream_set_pos(stream, pos)
#define _rewind(stream) stream_rewind(stream)
#endif /* _STREAM_MACROS */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STREAM_H */