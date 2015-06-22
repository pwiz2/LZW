//  Author: Haroon Arshad

/*
	Implement the LZW algorithm : 12-bit fixed-width format only for now
	http://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch

	I have opted for certain language features that will most likely 
	aid in better performance while keeping the code portable (at least
	from C++11 compatible compilers onwards).

	Some future improvement considerations particularly for much larger files
	and if there is addition to the standard fixed 12-bit LZW implementation
	1. Custom allocators/memory pools - more optimised dictionary storage
	2. Use native OS file I/O for better performance
	3. If the fellow encoder class was to be implemented, the design of the OO
		design would  change. For instance, the common member variables/functions
		are to be inherited froma parent class
	4. Consider using classic C arrays to compare performance
	5. c++14. new functionality: binary literals may aid in better program design

	usage:
	g++ -std=c++11 main.cpp -I./lzw/ ./lzw/file_stream_lzw.cpp ./lzw/decoder.cpp -o main.o -O3 -Wall -Wno-unknown-pragmas

 ./main.o

*/

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"

#include <iostream>
#include "lzw/lzw.h"
#include "timer.h"



int main()
{
	using namespace lzw;

	//dictionary_base<12> dict;	

	//auto d1(decoder<LZW::fixed,12>("compressedfile1.z", "compressedfile1.txt"));	// not okay, makes copy first (class decoder is uncopyable)
	//decoder<LZW::fixed,12> d1{"compressedfile1.z", "compressedfile1.txt"};		// okay!
	//decoder<LZW::fixed, 12> *d1 = new decoder<LZW::fixed, 12>						// okay!
	//			("compressedfile1.z", "compressedfile1.txt");						
	decoder<LZW::fixed, 12> d1("input/compressedfile1.z", "output/compressedfile1.txt"); // okay!
	d1.print_details();
	d1.run();

	decoder<LZW::fixed, 12> d2("input/compressedfile2.z", "output/compressedfile2.txt");
	d2.print_details();
	d2.run();

	
/*
	unsigned TOTAL = 300;
	unsigned DOLOOP = 0;
	if (DOLOOP == 1)
	{
		TIMER_INIT(t_start,t_end);
		TIMER_START(t_start, t_end);
		for (std::size_t i = 0; i < TOTAL; ++i)
		{
			decoder<LZW::fixed, 12> d("input/compressedfile3.z", "output/compressedfile3.txt");
			d.run();
		}
		TIMER_STOP(t_start, t_end,TOTAL);
	}
*/
	return 0;
}