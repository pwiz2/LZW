//#pragma once
#ifndef LZW_PROPERTIES_H__
#define LZW_PROPERTIES_H__

// ::common shared variables
// would be better implemented with inheritence if encoder class
// were also included etc
namespace lzw
{
	/** The type of LZW algorithm (only fixed-width available)  */
	enum class LZW {
		fixed
		// other types of LZW...
		//variable
	};
}

#endif
