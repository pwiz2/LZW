#ifndef _DICTIONARY_BASE_LZW_H__
#define _DICTIONARY_BASE_LZW_H__

//#include "lzw_properties.h"
#include <vector>
#include <map>
#include <string>
#include "math.h"

namespace lzw{

	/** A dictionary object for some code lengths of
	 * nbits. For this implementation, only the 12 bit is used
	 * example: dictionary_base<12> dictionary;
	 */
	using Code_size = unsigned;
	using Pattern = std::string;

	template <Code_size n_bits>
	struct dictionary_base {

		/** The pattern stored in the dictionary */
		using Pattern = std::string;

		/** The associated key to the pattern in the dictionary */
		using Key = unsigned;

		/** Dictionary container stored in vector of maps 
		 *	There will be 256 elements to 
		 */
		using Storage = std::vector<std::map<Key, Pattern>>;

	private:
		/** Member variable for dictionary container 
		  *	The dictionary container is stored in a vector of maps
		  * where each vector element identifies the first character
		  * in this way, we are able to search only one map
		  * depending on the initial character. This is set to 256
		  * (ascii character codes)
		  */
		Storage dict{ 256 };
		
		/**  */
		Key Kiter{ 256 };

		/** The maxximum ammount of string patterns dictionary can hold
		 *  this is bound by the maxuimum number that can be acheived 
		 *  from the bit length
		 */
		const Key max_patterns{ pow(2,n_bits) };

		/** An initial character identifier to aid in the dictionary search  
		  *	Each key is signified by the element number where the stored value
		  *	of each respective element defines the character.
		  * 
		  * all elements denoted -1 implies value has no associated key-value
		  * otherwise the element will present the initial character of each 
		  * pattern
		  */
		std::vector<signed> initial_chars;

		/** current string pattern member variable  */
		Pattern p_str;

	public:

		/**	instantiates a dictionary
		 *
		 */
		dictionary_base<n_bits>() :
			initial_chars(max_patterns, -1)
		{}

		/** checks if the current word exists in the dictionary
		 *	and stores the result in temp string
		 */
		signed does_word_exist(Key k);


		/** Retreive a string pattern from the dictionary
		 *  which was stored from the does_word_exist() check.
		 *		k - specified key value
		 */
		Pattern getword();

		/** Function to add a string pattern (str) to the dictionary. 
		 *  Also implicitly checks if the maximum allowable string 
		 *  patterns has reached 
		 */
		void add(Pattern str);

		/** function to reset the dictionary when the
		 * maximum decimal value of bitlength is met
		 * max value storead as max_patterns
		 */
		void reset();

		/** destructor */
		~dictionary_base<n_bits>(){};

	};

	template <Code_size n_bits>
	inline
	signed dictionary_base<n_bits>::does_word_exist(Key k)
	{
		if (k < 256)
		{
			p_str = std::string{ static_cast<char>(k) };
			return static_cast<char>(k);
		}
		auto& a = initial_chars[k];
		if(a > -1)
		{
			p_str = std::string{ dict[initial_chars[k]].find(k)->second };
			return initial_chars[k];
		}
		else
		{
			return -1;
		}
	};
	
	template <Code_size n_bits>
	inline
	Pattern dictionary_base<n_bits>::getword()
	{
		return p_str;
	};
	

	template <Code_size n_bits>
	void dictionary_base<n_bits>::add(Pattern str)
	{
		if (str.length() > 1) {
			auto g = static_cast<unsigned char>(str[0]);
			initial_chars[Kiter] = g;
			dict[g].emplace(Kiter++, str);
			if (Kiter == max_patterns)
				reset();
		}
	}

	template <Code_size n_bits>
	void dictionary_base<n_bits>::reset()
	{
		Storage temp{ 256 };
		dict.swap(temp);

		Kiter = 256;

		std::fill(begin(initial_chars), end(initial_chars), -1);
	}

	/** instantiate a dictionary for 12-bits */
	//dictionary_base<12> dictionary;

} // end of lzw namespace

#endif