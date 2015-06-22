#ifdef _MSC_VER
#pragma once
#endif
//#ifndef _FILE_STREAM_LZW_CPP__
//#define _FILE_STREAM_LZW_CPP__

#include "stdafx.h"
#include "file_stream_lzw.h"

namespace lzw {

	file_stream_lzw::file_stream_lzw(const string& ifile_name, const string& ofile_name) :
		infile{ifile_name, ios::binary | ios::in | ios::ate},
		outfile{ofile_name, ios::binary | ios::out},
		infile_size_bytes{static_cast<size_t>(infile.tellg())}
	{
		if (!infile.is_open())
			std::cerr << "Could not open the file " << ifile_name << " to read. Decompress halted!\n";
		//throw std::logic_error("Could not open file to read");
		// [exception handling incomplete]
		if (!outfile.is_open())
			std::cerr << "Could not open the file " << ofile_name << " to write to. Decompress halted!\n";
		//throw std::logic_error("Could not open file to write");

		// read buffer into stringstream (appears to be the most platform-independent, efficient solutions)
		infile.seekg(0, std::ios::beg);
		infile.rdbuf()->pubsetbuf(input_buffer.get(), file_buffer_size);

		// set buffer for output file
		outfile.rdbuf()->pubsetbuf(output_buffer.get(), file_buffer_size);
	}


	std::istream& file_stream_lzw::read(char* r, std::streamsize k)
	{
		return infile.read(r, k);
	}

	std::istream& file_stream_lzw::read_specific(char* r, std::streamsize pstart, std::streamsize pend)
	{
		infile.seekg(-pstart, std::ios_base::end);
		return infile.read(r, pend-pstart);
	}

	file_stream_lzw::~file_stream_lzw()
	{
		infile.close();
		outfile.close();
	}

}

//#endif