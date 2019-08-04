#include "farbfeld.h"
#include <stdio.h> // printf

int main()
{
	// write
	const uint32_t size = 200*400*4;
	uint8_t rgba[size];

	// sets all the channels to 0xA0, including alpha
	for (uint32_t i = 0; i < size; ++i)
	{
		rgba[i] = 0xA0;
	}

	uint8_t ok = farbfeld_write("test.ff", 200, 400, rgba);

	// read
	uint32_t width;
	uint32_t height;
	uint8_t* ptr;
	
	farbfeld_read("test.ff", &width, &height, &ptr);
	printf("%d %d\n", width, height);

	return 0;
}
