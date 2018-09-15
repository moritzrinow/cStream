# cStream

C byte-stream and serialization utils

## Content

* Build
* Usage

## Build

### Linux
Open the terminal and type:

"make" to install cStream

"make clean" to uninstall cStream

### Windows
Have not added a way to build binaries for Windows yet...
Just add the source files to your VS Solution/Project.


## Using streams

#### The structure
STREAM stream;

#### Initialize
stream_init(&stream , 0)                            // (stream, capacity)

_init(&stream, 0)                                   // Macro

#### Reserve memory
stream_reserve(&stream, 1024)                       // (stream, size)

_reserve(&stream, 1024)                             // Macro

#### Write (overwrite)
stream_write(&stream, some_byte_buffer, length, 0)  // (stream, buffer, length, offset)

_write(&stream, some_byte_buffer, length, 0)        // Macro

#### Write (insert)
stream_insert(&stream, some_byte_buffer, length, 0) // (stream, buffer, length, offset)

_insert(&stream, some_byte_buffer, length, 0)       // Macro

#### Read
stream_read(&stream, some_byte_buffer, length, 0)   // (stream, buffer, length, offset)

_read(&stream, some_byte_buffer, length, 0)         // Macro

#### Seek (change position)
stream_seek(&stream, 0)                             // (stream, position)

_seek(&stream, 0)                                   // Macro

#### Clear (reset)
stream_clear(&stream)                               // (stream)

_clear(&stream)                                     // Macro

#### Copy
stream_copy(&stream, &some_other_stream)            // (source_stream, dest_stream)

_copy(&stream, &some_other_stream)                  // Macro

#### Close (cleanup resources)
stream_close(&stream)                               // (stream)

_close                                              // Macro

##### The macros are available if you define _STREAM_MACROS before including stream.h
