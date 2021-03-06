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


#ifndef profiling_stuff_hpp
#define profiling_stuff_hpp


#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "asm_funcs.hpp"
#include "timer_stuff.hpp"
#include "../general_utility_stuff/debug_vars.hpp"


inline void profile_start()
{
	asm_comment("Start of profile_start()");
	
	
	reg_tm2cnt_full = reg_tm3cnt_full = 0;
	
	// Cascade Timer 3 with Timer 2
	reg_tm2cnt = timer_operate;
	reg_tm3cnt = timer_operate | timer_cascade_enable;
	
	
	asm_comment("End of profile_start()");
}

inline u32 profile_stop()
{
	// I guess stopping Timer 2 will stop Timer 3 since Timer 3 is cascaded
	// with Timer 2.
	reg_tm2cnt = 0;
	
	return ( ( static_cast<u32>(reg_tm3data) << 16 ) 
		| static_cast<u32>(reg_tm2data) );
}

inline void show_profile_stop()
{
	asm_comment("Start of show_profile_stop()");
	
	
	debug_arr_group::write_u32_and_inc(profile_stop());
	
	
	asm_comment("End of show_profile_stop()");
}


// Profile new, delete, new[], delete[], malloc, and free.
//void profile_dynamic_allocations( size_t num_elems )
//	__attribute__((_iwram_code));


#endif		// profiling_stuff_hpp
