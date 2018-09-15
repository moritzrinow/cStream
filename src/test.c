#include "cStream.h"

#define PERSON_NAME_LEN 1024

typedef struct {
	char name[PERSON_NAME_LEN];
	int32 age;
	float height;
	float weight;
}PERSON;

void serialize_person(STREAM* stream, const PERSON* p)
{
	serialize_string(&stream, p->name);
	serialize_int32(&stream, p->age);
	serialize_float(&stream, p->height);
	serialize_float(&stream, p->weight);
}

void deserialize_person(STREAM* stream, PERSON* p)
{
	deserialize_string(&stream, p->name, PERSON_NAME_LEN);
	deserialize_int32(&stream, &p->age);
	deserialize_float(&stream, &p->height);
	deserialize_float(&stream, &p->weight);
}

int32 main(int32 argc, char** argv)
{
	// Init stream

	STREAM stream;
	stream_init(&stream, sizeof(PERSON));

	// Serialize

	PERSON pIn;
	strcpy(pIn.name, "SampleName");
	pIn.age = 20;
	pIn.height = 1.90;
	pIn.weight = 85.5;
	serialize_person(&stream, &pIn);

	// Deserialize

	PERSON pOut;
	stream_seek(&stream, 0); // Reset the streams position
	deserialize_person(&stream, &pOut);

	// Close stream

	stream_close(&stream);
	return 0;
}