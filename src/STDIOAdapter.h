#pragma once

#include <stdio.h>
#include <cassert>

template<class STREAM>
struct STDIOAdapter
{
	static FILE* yield(STREAM* stream)
	{
		assert(stream != NULL);

		static cookie_io_functions_t Cookies =
		{
			.read = NULL,
			.write = cookieWrite,
			.seek = NULL,
			.close = cookieClose
		};

		return fopencookie(stream, "w", Cookies);
	}

	ssize_t static cookieWrite(void* cookie,
		const char* buf,
		size_t size)
	{
		if (cookie == NULL)
			return -1;

		STREAM* writer = static_cast <STREAM*>(cookie);

		writer->write(buf, size);

		return size;
	}

	int static cookieClose(void* cookie)
	{
		return EOF;
	}
}; // STDIOAdapter