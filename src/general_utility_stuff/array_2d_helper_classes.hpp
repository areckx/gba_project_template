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


#ifndef array_2d_helper_classes_hpp
#define array_2d_helper_classes_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "vec2_class.hpp"



// This utility class is intended to be used when inherently 2D data, with
// CONSTANT dimensions (as is usually the case in my GBA code), is stored
// within a 1D array.
template< typename type, u32 _width, u32 _height >
class array_csz_2d_helper
{
protected:		// variables
	static constexpr vec2_u32 size_2d = { _width, _height };
	static constexpr u32 size = size_2d.x * size_2d.y;
	
public:			// variables
	type* the_array = NULL;
	
public:			// functions
	inline array_csz_2d_helper()
	{
	}
	inline array_csz_2d_helper( type* s_the_array )
		: the_array(s_the_array)
	{
	}
	
	void init( type* s_the_array )
	{
		the_array = s_the_array;
	}
	
	array_csz_2d_helper< type, _width, _height >& operator = 
		( const array_csz_2d_helper< type, _width, _height >& to_copy )
	{
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	u32 width() const
	{
		return size_2d.x;
	}
	u32 height() const
	{
		return size_2d.y;
	}
	
	const vec2_u32& get_size_2d() const
	{
		return size_2d;
	}
	u32 get_size() const
	{
		return size;
	}
	
	type& at( u32 x, u32 y )
	{
		return the_array[ y * size_2d.x + x ];
	}
	type& at( const vec2_u32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	type& at( const vec2_s32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	const type& at( u32 x, u32 y ) const
	{
		return the_array[ y * size_2d.x + x ];
	}
	const type& at( const vec2_u32& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	const type& at( const vec2_s32& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	
} __attribute__((_align4));

// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template< typename type >
class array_2d_helper
{
protected:		// variables
	vec2_u32 size_2d;
	u32 size = 0;
	
public:			// variables
	type* the_array = NULL;
	
public:			// functions
	//array_2d_helper() : size_2d({ 0, 0 }), size(0), the_array(0)
	//{
	//}
	inline array_2d_helper()
	{
	}
	inline array_2d_helper( type* s_the_array, 
		const vec2_u32& s_size_2d )
		: size_2d(s_size_2d), size( s_size_2d.x * s_size_2d.y ),
		the_array(s_the_array)
	{
	}
	
	void init( type* s_the_array, const vec2_u32& s_size_2d )
	{
		size_2d = s_size_2d;
		size = size_2d.x * size_2d.y;
		the_array = s_the_array;
	}
	
	array_2d_helper<type>& operator = 
		( const array_2d_helper<type>& to_copy )
	{
		size_2d = to_copy.size_2d;
		size = to_copy.size;
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	u32 width() const
	{
		return size_2d.x;
	}
	u32 height() const
	{
		return size_2d.y;
	}
	
	const vec2_u32& get_size_2d() const
	{
		return size_2d;
	}
	u32 get_size() const
	{
		return size;
	}
	
	type& at( u32 x, u32 y )
	{
		return the_array[ y * size_2d.x + x ];
	}
	type& at( const vec2_u32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	type& at( const vec2_s32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	const type& at( u32 x, u32 y ) const
	{
		return the_array[ y * size_2d.x + x ];
	}
	const type& at( const vec2_u32& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	const type& at( const vec2_s32& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	
} __attribute__((_align4));



#endif		// array_2d_helper_classes_hpp
