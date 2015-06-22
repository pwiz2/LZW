// created by Haroon Arshad
//#pragma once
#ifndef _LZW_FILE_STREAM_H__
#define _LZW_FILE_STREAM_H__

//#include "lzw_properties.h"
#include <fstream>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>

namespace lzw {

	using std::ifstream;
	using std::ofstream;
	using std::ios;
	using std::string;

	/** Seperate class to deal with file operations for both reading (std:ifstream)
	*	and writing (std::ofstream)
	*	The LZW class will contain this object
	*/
	class file_stream_lzw
	{
		/** read file object */
		ifstream infile;

		/** write file object */
		ofstream outfile;

		/** size of input file in bytes */
		std::size_t infile_size_bytes;

		/** size of memory buffer for file I/O operations */
		const std::size_t file_buffer_size{ 512 * 512 };

		/** buffer for both file types (read/write) - performance */
		std::unique_ptr<char[]> input_buffer{ new char[file_buffer_size] };
		std::unique_ptr<char[]> output_buffer{ new char[file_buffer_size] };

	public:

		/** creates a file_stream_lzw object from string input parameters
		 *  which may be the abolsute path or relative path to the file
		 *  location
		 *
		 *	ifile_name - input file name containing decoding/encoding text
		 *	ofile_name - output file name for the results output
		*/
		file_stream_lzw(const string& ifile_name, const string& ofile_name);

		//file_stream_lzw() = delete;

		/** Write string to output file */
		void write(const std::string& s);

		/** Read characters to a string array r for a particular size k
		  *	also returns the istream object for conditional use 
		  */
		std::istream& read(char* r, std::streamsize k = 0);

		/** Read specific bytes to a string array r for the start and end position
		  * also returns the istream object for conditional use. For use when a
		  * file leaves odd ammount of characters from a set of conditions
		  * (for example, see decoder::run() method  to see the 3-byte read
		  * protocol
		  */
		std::istream& read_specific(char* r, std::streamsize pstart, std::streamsize pend);

		/** same as read function, but does not return the object */
		void get(char* c, std::streamsize k);

		//std::string& get_file_contents(){return buffer;};

		/** return the size of the input file in bytes */
		std::size_t get_bytes() const;

		/** destructor - close files */
		~file_stream_lzw();

	}; // end lzw_file_stream class


	inline
	void file_stream_lzw::write(const string& s)
	{
		outfile << s;
	}

	inline
	void file_stream_lzw::get(char* c, std::streamsize k)
	{
		infile.get(c, k);
	}

	inline
	std::size_t file_stream_lzw::get_bytes() const
	{
		return infile_size_bytes;
	}




} // end of starleaf namespace
#endif
