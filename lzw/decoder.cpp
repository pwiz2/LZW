#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "decoder.h"

//#include "dictionary_base.h"
//#include "file_stream_lzw.h"
#include <iostream>
#include <sstream>

namespace lzw
{

	// template specializations go here
	// see description of run function
	// in the header file

	/*
	 * RUN  : <fixed version, 12-bit>
	 */
	template <>
	void decoder<LZW::fixed, 12>::run()
	{
		// helper variables
		unsigned dict_key{ 0 };
		string current_str{ "" };
		string translated_str;
		translated_str.reserve(100);
		char data[3];
		const std::streamsize csize = 3;

		// lambda object to process each key
		// with the dictionary
		auto process_key = [&] {
			// get translated word from dictionary with key..
			translated_str = dictionary.getword(dict_key);
			// ..write to file..
			fileio.write(translated_str);
			// ..add new word to dictionary (current dictionary word with first char of new word..
			dictionary.add(current_str + translated_str[0]);
			// ..update current word
			current_str = translated_str;
		};

		// Process input file from fileio (file_stream_lzw class object handles this).
		// reads in 3 chars at a time from file using read function (from class).
		// (note: 'X' marks the extracted bit sequence in the programatic diagrams)
		while (fileio.read(&data[0], csize))
		{
			// first case:
			// <---- 8-bit ----> <---- 8-bit ----> <---- 8-bit ---->
			// [X X X X X X X X] [X X X X - - - -] [- - - - - - - -]
			dict_key = (((unsigned char)data[0] << 4) + (((unsigned char)data[1] & 0xF0) >> 4));
			process_key();

			// second case:
			// <---- 8-bit ----> <---- 8-bit ----> <---- 8-bit ---->
			// [- - - - - - - -] [- - - - X X X X] [X X X X X X X X]
			dict_key = ((((unsigned char)data[1] & 0x0F) << 8) + (unsigned char)data[2]);
			process_key();
		}; 

		
		if (file_words % 2 == 1)
		{
			// last (odd) case:
			// <---- 8-bit ----> <---- 8-bit ----> <---- 8-bit ---->
			// [- - - - - - - -] [X X X X X X X X] [X X X X - - - -]   <-- 4 bits padded to the end
			fileio.read_specific(&data[0], file_bytes-3, file_bytes); // for simplicity, get the last three bytes
			dict_key = ((((unsigned char)data[0] & 0x0F) << 8) + (unsigned char)data[1]);
			process_key();
		}
		
	};
}
