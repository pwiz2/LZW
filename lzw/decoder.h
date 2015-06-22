#pragma once
#ifndef _DECODER_LZW_H__
#define _DECODER_LZW_H__

#include "lzw_properties.h"
#include "dictionary_base.h"
#include "file_stream_lzw.h"

namespace lzw {

	//using std::string;
	constexpr const unsigned charbits = CHAR_BIT; // note: POSIX mandates CHAR_BIT == 8

	/** Assumptions of decoder class:
	 *- number of bits is conserved (i.e. char is 8 bits)
	 */
	template <LZW lzw_type, Code_size n_bits>
	class decoder {
		friend class file_stream_lzw;
	public:

		/**
		 * initialise an instance of decoder with the input and output file names
		 * the input file name is the file to be decompressed, and the output file
		 * is where to write too
		 */
		decoder<lzw_type, n_bits>(const string& infile_name, const string& outfile_name);

		/**
		*
		*/
		//decoder<lzw_type, n_bits>(const string& infile_name, const string& outfile_name, dictionary_base<n_bits>& d);

		/** note: cannot instantiate a decoder object without any arguments */
		//decoder<lzw_type, n_bits>() = delete;
		//decoder<lzw_type, n_bits>() = default;

		/** copy constructor for completeness */
		decoder<lzw_type, n_bits>(const decoder& d_);

		/**	Print details of the current file to process.
		  * This includes total bytes, total bits, the number of n_bit patterns
		  * and if there is a remainder. It also serves to check if the files
		  * contain valid ammount for all these to perform the LZW decoder
		  */
		void print_details();

		/**	Validates if file is decompressable. checks the bounds of the bytes and bits
		 *	of file. (assume a byte is 8bits)
		 */
		bool validate_file() const;

		/**	Performes the decoding procedure
		 */
		void run();

		~decoder<lzw_type, n_bits>(){};

	private:
		// file_stream object to organise the I/O operations to file
		file_stream_lzw fileio;

		// total number of bytes in file
		std::size_t file_bytes{ fileio.get_bytes() };

		// total bits of compressed file
		std::size_t file_total_bits{ file_bytes * charbits };

		// remainder of bits that was originally used as padding
		std::size_t file_remainder_bits{ file_total_bits % n_bits };

		// total possible words in file
		std::size_t file_words{ (file_total_bits - file_remainder_bits) / n_bits };

		// a reference to a dictionary
		//dictionary_base<n_bits>& dictionary;
		// a local dictioary object if one is not suplied
		//dictionary_base<n_bits> dict;
		dictionary_base<n_bits> dictionary{};
	};


	template <LZW lzw_type, Code_size n_bits>
	decoder<lzw_type, n_bits>::decoder(const string& infile_name, const string& outfile_name) :
		fileio{ infile_name, outfile_name }
	{
		if (!validate_file())
			std::cerr << "File does not have the correct ammount of bits!";
		// [incomplete exceptions]
	};

	/*
	template <LZW lzw_type, Code_size n_bits>
	decoder<lzw_type, n_bits>::decoder(const string& infile_name, const string& outfile_name, dictionary_base<n_bits>& d) :
		fileio{ infile_name, outfile_name },
		dictionary{ d }
	{
		if (!validate_file())
			std::cerr << "File does not have the correct ammount of bits!";
		// [incomplete exceptions]
	};
	*/
	

	/*template <LZW lzw_type, Code_size n_bits>
	decoder<lzw_type, n_bits>::decoder(const string& infile_name, const string& outfile_name, const dictionary_base<n_bits>& d) :
		fileio{ infile_name, outfile_name },
	{
		if (!validate_file())
			std::cerr << "File does not have the correct ammount of bits!";
		// [incomplete exceptions]
	};*/

	template <LZW lzw_type, Code_size n_bits>
	inline
	bool decoder<lzw_type, n_bits>::validate_file()  const
	{
		return (file_total_bits % charbits) == 0;
	};

	template <LZW lzw_type, Code_size n_bits>
	void decoder<lzw_type, n_bits>::print_details()
	{
		std::cout << "\n*** details of compressed file ***\n"
			<< file_bytes << " total bytes\n"
			<< file_total_bits << " total bits\n"
			<< file_words << " total " << n_bits << "-bit word(s) to retrieve\n"
			<< "with " << file_remainder_bits << " padded remainder\n\n";
	};

	template <LZW lzw_type, Code_size n_bits>
	decoder<lzw_type, n_bits>::decoder(const decoder& d_) : fileio(d_.fileio)
	{
	};

}; // end of namespace lzw

#endif