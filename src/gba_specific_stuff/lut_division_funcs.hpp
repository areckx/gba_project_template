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


#ifndef lut_division_funcs_hpp
#define lut_division_funcs_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "attribute_defines.hpp"

u64 unsafe_lut_udiv( u32 numerator, u16 divisor )
	__attribute__((_iwram_code,_target_arm));
s64 unsafe_lut_sdiv( s32 numerator, s16 divisor )
	__attribute__((_iwram_code,_target_arm));
u64 safe_lut_udiv( u32 numerator, u16 divisor, int& valid ) 
	__attribute__((_iwram_code,_target_arm));
s64 safe_lut_sdiv( s32 numerator, s16 divisor, int& valid ) 
	__attribute__((_iwram_code,_target_arm));


#endif		// lut_division_funcs_hpp
