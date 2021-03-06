// This file is part of GBA Project Template.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#ifndef array_helper_class_hpp
#define array_helper_class_hpp



#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"


// This is a VERY thin wrapper class for working with 1D arrays
template< typename type >
class array_helper
{
public:			// variables
	type* the_array = NULL;
	
protected:		// variables
	u32 size = 0;
	
public:			// functions
	array_helper()
	{
	}
	
	array_helper( type* s_the_array, u32 s_size )
		: the_array(s_the_array), size(s_size)
	{
	}
	
	array_helper( const array_helper<type>& to_copy )
		: the_array(to_copy.the_array), size(to_copy.size)
	{
	}
	
	void init( type* s_the_array, u32 s_size )
	{
		the_array = s_the_array;
		size = s_size;
	}
	
	
	array_helper<type>& operator = ( const array_helper<type>& to_copy )
	{
		the_array = to_copy.the_array;
		size = to_copy.size;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	u32 get_size() const
	{
		return size;
	}
	
	type& at( u32 offset )
	{
		return the_array[offset];
	}
	const type& at( u32 offset ) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_align4));


#endif		// array_helper_class_hpp
