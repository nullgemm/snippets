#ifndef H_FARBFELD
#define H_FARBFELD

#include "swap/swap.h"
#include <stdlib.h> // malloc
#include <string.h> // strncmp
#include <stdint.h> // uint8_t, uint16_t, uint32_t
#include <stdio.h> // FILE, EOF, NULL, fopen, fclose, fwrite

uint8_t farbfeld_write(
	const char* file,
	uint32_t width,
	uint32_t height,
	uint8_t* rgba)
{
	FILE* fp = fopen(file, "w");

	if (fp == NULL)
	{
		return 0;
	}

	uint32_t size = ((uint32_t) 4) * width * height;
	int ok = fwrite("farbfeld", 8, 1, fp);

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

uint8_t farbfeld_read(
	const char* file,
	uint32_t* width,
	uint32_t* height,
	uint8_t** rgba)
{
	FILE* fp = fopen(file, "r");

	if (fp == NULL)
	{
		return 0;
	}

	char header[8] = {'\0'};
	int ok = fread(header, 8, 1, fp);

	if ((ok == 0) || (strncmp(header, "farbfeld", 8) != 0))
	{
		return 0;
	}

	ok = fread(width, 4, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	// remove for big-endian
	*width = swap_u32(*width);

	ok = fread(height, 4, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	// remove for big-endian
	*height = swap_u32(*height);

	uint32_t size = ((uint32_t) 4) * (*width) * (*height);
	*rgba = malloc(size);

	if (*rgba == NULL)
	{
		return 0;
	}

	uint16_t value;

	for (uint32_t i = 0; i < size; ++i)
	{
		ok = fread(&value, 1, 2, fp);

		if (ok != 2)
		{
			return 0;
		}

		(*rgba)[i] = value;
	}

	ok = fclose(fp);

	return ok != EOF;
}

#endif
