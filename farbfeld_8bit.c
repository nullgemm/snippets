#include <stdint.h> // uint8_t, uint16_t, uint32_t
#include <stdio.h> // FILE, EOF, NULL, fopen, fclose, fwrite

static inline uint32_t swap_u32(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    return (val << 16) | (val >> 16);
}

uint8_t farbfeld(const char* file, uint32_t width, uint32_t height, uint8_t* rgba)
{
	FILE* fp = fopen(file, "w");

	if (fp == NULL)
	{
		return 0;
	}

	uint32_t size = ((uint32_t) 4) * width * height;
	uint8_t ok = fwrite("farbfeld", 8, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	// remove for big-endian
	width = swap_u32(width);
	ok = fwrite(&width, 4, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	// remove for big-endian
	height = swap_u32(height);
	ok = fwrite(&height, 4, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	uint16_t value;

	for (uint32_t i = 0; i < size; ++i)
	{
		// leverages endianness mismatch to avoid byte swapping
		// replace by the following line for big-endian
		// value = ((uint16_t) rgba[i]) << 8;
		value = rgba[i];
		ok = fwrite(&value, 2, 1, fp);

		if (ok == 0)
		{
			return 0;
		}
	}

	ok = fclose(fp);

	return ok != EOF;
}

/////////////
// example //
/////////////

int main()
{
	// avoids removing a #define when using the code
	const uint32_t size = 200*400*4;
	uint8_t rgba[size];

	// sets all the channels to 0xA0, including alpha
	for (uint32_t i = 0; i < size; ++i)
	{
		rgba[i] = 0xA0;
	}

	uint8_t ok = farbfeld("test.ff", 200, 400, rgba);

	return ok == 1;
}
