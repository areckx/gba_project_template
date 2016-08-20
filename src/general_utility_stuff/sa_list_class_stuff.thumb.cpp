// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#include "sa_list_class_stuff.hpp"

#include "debug_vars.hpp"



namespace sa_list_stuff
{

void list_backend::init( void* n_node_array, 
	sa_free_list_backend* n_the_free_list_backend_ptr,
	u32 n_total_num_nodes, u32 n_specific_type_size,
	u32 n_whole_node_size, 
	
	generic_void_2arg_fp n_specific_type_copy_fp, 
	generic_void_2arg_fp n_specific_type_move_fp,
	generic_void_1arg_fp n_specific_type_reset_fp, 
	generic_u32_2arg_fp n_specific_type_less_fp, 
	
	generic_void_ptr_1arg_fp n_get_node_data_fp, 
	generic_vec2_s16_ptr_1arg_fp n_get_index_pair_fp,
	generic_void_2arg_fp n_conv_node_to_contents_fp,
	generic_void_2arg_fp n_insertion_sort_inner_loop_fp )
{
	node_array = n_node_array;
	the_free_list_backend_ptr = n_the_free_list_backend_ptr;
	total_num_nodes = n_total_num_nodes;
	
	specific_type_size = n_specific_type_size;
	whole_node_size = n_whole_node_size;
	
	specific_type_copy_fp = n_specific_type_copy_fp;
	specific_type_move_fp = n_specific_type_move_fp;
	specific_type_reset_fp = n_specific_type_reset_fp;
	specific_type_less_fp = n_specific_type_less_fp;
	
	get_node_data_fp = n_get_node_data_fp;
	get_index_pair_fp = n_get_index_pair_fp;
	
	conv_node_to_contents_fp = n_conv_node_to_contents_fp;
	insertion_sort_inner_loop_fp = n_insertion_sort_inner_loop_fp;
}

void list_backend::fully_deallocate()
{
	s32& the_front_index = get_front_index();
	//while ( get_front_index() != -1 )
	while ( the_front_index >= 0 )
	{
		//erase_at(get_front_index());
		erase_at(the_front_index);
	}
	
	//back_index = -1;
}

void list_backend::fully_deallocate_via_unlink()
{
	s32& the_front_index = get_front_index();
	//while ( get_front_index() != -1 )
	
	
	while ( the_front_index >= 0 )
	{
		//unlink_at_with_dealloc(get_front_index());
		unlink_at_with_dealloc(the_front_index);
		
		//if ( the_front_index == 105 )
		//{
		//	debug_arr_group::gdb_breakpoint_helper = 0;
		//}
	}
	
	//if ( get_back_index() >= 0 )
	//{
	//	debug_arr_group::
	//}
	
	//back_index = -1;
}

void list_backend::internal_func_allocate_and_assign_to_node
	( s32& index, node_contents& node,
	const void* n_data, u32 can_move_value )
{
	index = get_the_free_list_backend().peek_top_and_pop();
	
	//index = get_the_free_list_backend().peek_top();
	//get_the_free_list_backend().pop();
	node = get_node_contents_at(index);
	
	assign_to_node_data( node, n_data, can_move_value );
}


//// push_front() CAN affect back_index
//s32 list_backend::push_front( const void* to_push,
//	u32 can_move_value )
//{
//	s32& the_front_index = get_front_index();
//	s32 old_front_index = the_front_index;
//	
//	//sa_free_list_backend& the_free_list_backend 
//	//	= get_the_free_list_backend();
//	
//	//the_front_index = the_free_list_backend.peek_top();
//	//the_free_list_backend.pop();
//	the_front_index = get_the_free_list_backend().peek_top_and_pop();
//	
//	
//	//node<type>& the_front_node 
//	//	= get_node_at(the_front_index);
//	
//	node_contents the_front_node = get_node_contents_at(the_front_index);
//	
//	s32 new_next_index = -1;
//	
//	// If there was nothing in the list before the push
//	if ( old_front_index < 0 )
//	{
//		get_back_index() = the_front_index;
//	}
//	// If there's at least one element in the list
//	else //if ( old_front_index >= 0 )
//	{
//		new_next_index = old_front_index;
//		
//		//get_node_at(old_front_index).prev_index()
//		//	= the_front_index;
//		get_prev_index_at_index(old_front_index) = the_front_index;
//	}
//	
//	
//	//the_front_node.data = to_push;
//	//the_front_node.next_index() = new_next_index;
//	//the_front_node.prev_index() = -1;
//	assign_to_whole_node( the_front_node, to_push, 
//		vec2_s16( new_next_index, -1 ), can_move_value );
//	
//	return the_front_index;
//}


s32 list_backend::internal_func_move_unlinked_node_to_front
	( s32 to_move_index, node_contents& node_to_move )
{
	s32& the_front_index = get_front_index();
	const s32 old_front_index = the_front_index;
	
	
	the_front_index = to_move_index;
	
	s32 new_next_index = -1;
	
	
	// If there's at least one element in the list
	if ( old_front_index >= 0 )
	{
		new_next_index = old_front_index;
		
		get_prev_index_at_index(old_front_index) = the_front_index;
	}
	
	*node_to_move.index_pair_ptr = vec2_s16( new_next_index, -1 );
	
	if ( old_front_index < 0 )
	{
		get_back_index() = the_front_index;
	}
	
	return the_front_index;
}




//// insert_before() won't affect back_index
//s32 list_backend::insert_before( s32 index, const void* to_insert,
//	u32 can_move_value )
//{
//	//s32 old_prev_index = get_node_at(index)
//	//	.prev_index();
//	////s32 old_next_index = get_node_at(index)
//	////	.next_index()
//	
//	// If index == front_index
//	//if ( old_prev_index == -1 )
//	if ( index == get_front_index() )
//	{
//		return push_front( to_insert, can_move_value );
//	}
//	else
//	{
//		//node<type>& node_at_index 
//		//	= get_node_at(index);
//		node_contents node_at_index = get_node_contents_at(index);
//		
//		const s32 old_prev_index = node_at_index.prev_index();
//		
//		//const s32 new_index = get_the_free_list_backend()
//		//	.peek_top();
//		//get_the_free_list_backend().pop();
//		const s32 new_index = get_the_free_list_backend()
//			.peek_top_and_pop();
//		
//		
//		//node<type>& node_at_new_index
//		//	= get_node_at(new_index);
//		node_contents node_at_new_index = get_node_contents_at(new_index);
//		
//		
//		//get_node_at(old_prev_index).next_index()
//		//	= new_index;
//		
//		get_next_index_at_index(old_prev_index) = new_index;
//		
//		//node_at_new_index.data = to_insert;
//		//node_at_new_index.next_index() = index;
//		//node_at_new_index.prev_index() = old_prev_index;
//		
//		assign_to_whole_node( node_at_new_index, to_insert, 
//			vec2_s16( index, old_prev_index ), can_move_value );
//		
//		
//		node_at_index.prev_index() = new_index;
//		
//		return new_index;
//	}
//	
//	//return index;
//	//return new_index;
//}


s32 list_backend::internal_func_move_unlinked_node_before
	( s32 to_move_before_index, s32 to_move_index, 
	node_contents& node_to_move )
{
	// If to_move_before_index == front_index
	if ( to_move_before_index == get_front_index() )
	{
		//return push_front( to_insert, can_move_value );
		return internal_func_move_unlinked_node_to_front( to_move_index,
			node_to_move );
	}
	
	
	node_contents node_to_move_before = get_node_contents_at
		(to_move_before_index);
	const s32 old_prev_index = node_to_move_before.prev_index();
	
	
	get_next_index_at_index(old_prev_index) = to_move_index;
	
	*node_to_move.index_pair_ptr = vec2_s16( to_move_before_index, 
		old_prev_index );
	
	node_to_move_before.prev_index() = to_move_index;
	
	return to_move_index;
}

//s32 list_backend::internal_func_move_unlinked_node_before
//	( s32 to_move_before_index, s32 to_move_index, 
//	node_contents& node_to_move )
//{
//}


//// insert_after() CAN affect back_index
//s32 list_backend::insert_after( s32 index, const void* to_insert,
//	u32 can_move_value )
//{
//	////s32 old_prev_index = get_node_at(index)
//	////	.prev_index();
//	//s32 old_next_index = get_node_at(index)
//	//	.next_index();
//	
//	//node<type>& node_at_index = get_node_at(index);
//	//const s32 old_next_index = node_at_index
//	//	.next_index();
//	
//	node_contents node_at_index = get_node_contents_at(index);
//	const s32 old_next_index = node_at_index.next_index();
//	
//	
//	////s32 new_index = get_the_free_list_backend().pop();
//	//const s32 new_index = get_the_free_list_backend().peek_top();
//	//get_the_free_list_backend().pop();
//	const s32 new_index = get_the_free_list_backend().peek_top_and_pop();
//	
//	
//	node_at_index.next_index() = new_index;
//	
//	//node<type>& node_at_new_index 
//	//	= get_node_at(new_index);
//	node_contents node_at_new_index = get_node_contents_at(new_index);
//	
//	s32 new_next_index = -1;
//	
//	// Special code is used for inserting an element at the end of the
//	// list.
//	if ( old_next_index < 0 )
//	{
//		get_back_index() = new_index;
//	}
//	else if ( old_next_index >= 0 )
//	{
//		//get_node_at(old_next_index).prev_index() 
//		//	= new_index;
//		get_prev_index_at_index(old_next_index) = new_index;
//		new_next_index = old_next_index;
//	}
//	
//	//node_at_new_index.data = to_insert;
//	//node_at_new_index.next_index() = new_next_index;
//	//node_at_new_index.prev_index() = index;
//	
//	assign_to_whole_node( node_at_new_index, to_insert,
//		vec2_s16( new_next_index, index ), can_move_value );
//	
//	
//	//return index;
//	return new_index;
//}

s32 list_backend::internal_func_move_unlinked_node_after
	( s32 to_move_after_index, s32 to_move_index, 
	node_contents& node_to_move )
{
	//node_contents node_at_index = get_node_contents_at(index);
	//const s32 old_next_index = node_at_index.next_index();
	node_contents node_to_move_after = get_node_contents_at
		(to_move_after_index);
	s16& node_to_move_after_next_index = node_to_move_after.next_index();
	const s32 old_next_index = node_to_move_after_next_index;
	
	//const s32 new_index = get_the_free_list_backend().peek_top_and_pop();
	//node_at_index.next_index() = new_index;
	node_to_move_after_next_index = to_move_index;
	
	//node_contents node_at_new_index = get_node_contents_at(new_index);
	
	s32 new_next_index = -1;
	
	// Special code is used for inserting an element at the end of the
	// list.
	if ( old_next_index < 0 )
	{
		//get_back_index() = new_index;
		get_back_index() = to_move_index;
	}
	else if ( old_next_index >= 0 )
	{
		//get_prev_index_at_index(old_next_index) = new_index;
		get_prev_index_at_index(old_next_index) = to_move_index;
		new_next_index = old_next_index;
	}
	
	//assign_to_whole_node( node_at_new_index, to_insert,
	//	vec2_s16( new_next_index, index ), can_move_value );
	*node_to_move.index_pair_ptr = vec2_s16( new_next_index,
		to_move_after_index );
	
	//return index;
	//return new_index;
	return to_move_index;
}

//s32 list_backend::internal_func_move_unlinked_node_after
//	( s32 to_move_after_index, s32 to_move_index, 
//	node_contents& node_to_move )
//{
//}





// This function is ever so slightly slower than it used to be, but it
// allows more flexiblity since some functions will call unlink_at (or
// erase_at) instead of calling this function directly.  
// 
// Functions that call this one directly are still able to pass in a
// pointer to the node_at_index.
//void* list_backend::internal_func_unlink_at_without_dealloc( s32 index,
//	node_contents* node_at_index_ptr )
//{
//}


//// unlink_at_with_dealloc() CAN affect back_index
//void* list_backend::unlink_at_with_dealloc( s32 index )
//{
//	//s32 old_prev_index = get_node_at(index)
//	//	.prev_index(),
//	//	old_next_index = get_node_at(index)
//	//	.next_index();
//	
//	//node<type>& node_at_index = get_node_at(index);
//	//
//	//const s32 old_prev_index = node_at_index
//	//	.prev_index(),
//	//	old_next_index = node_at_index.next_index();
//	
//	
//	
//	s32& the_front_index = get_front_index();
//	s32& the_back_index = get_back_index();
//	
//	const s32 old_front_index = the_front_index,
//		old_back_index = the_back_index;
//	
//	//vec2_s16& index_pair_at_index = *get_index_pair_at_index(index);
//	
//	node_contents node_at_index = get_node_contents_at(index);
//	vec2_s16& index_pair_at_index = *node_at_index.index_pair_ptr;
//	
//	const s32 old_next_index = index_pair_at_index
//		[node_contents::vec2_index_for_next_index],
//	old_prev_index = index_pair_at_index
//		[node_contents::vec2_index_for_prev_index];
//	
//	index_pair_at_index = { -1, -1 };
//	
//	
//	
//	////node_at_index.data = type();
//	////node_at_index.next_index() = -1;
//	////node_at_index.prev_index() = -1;
//	//node_at_index = node<type>();
//	
//	
//	get_the_free_list_backend().push(index);
//	
//	if ( index == old_front_index && index != old_back_index )
//	{
//		the_front_index = old_next_index;
//		
//		if ( old_next_index >= 0 )
//		{
//			////front().prev_index() = -1;
//			//get_node_at(the_front_index).prev_index() = -1;
//			get_prev_index_at_index(the_front_index) = -1;
//		}
//	}
//	else if ( index != old_front_index && index == old_back_index )
//	{
//		the_back_index = old_prev_index;
//		
//		if ( old_prev_index >= 0 )
//		{
//			get_next_index_at_index(the_back_index) = -1;
//		}
//	}
//	else if ( index == old_front_index && index == old_back_index )
//	{
//		the_front_index = the_back_index = -1;
//	}
//	else //if ( index != old_front_index && index != old_back_index )
//	{
//		//node<type>& old_prev_node 
//		//	= get_node_at(old_prev_index);
//		s16& the_next_index = get_next_index_at_index(old_prev_index);
//		
//		if ( old_next_index >= 0 )
//		{
//			//old_prev_node.next_index() = old_next_index;
//			//get_node_at(old_next_index).prev_index()
//			//	= old_prev_index;
//			
//			the_next_index = old_next_index;
//			get_prev_index_at_index(old_next_index) = old_prev_index;
//		}
//		else
//		{
//			//old_prev_node.next_index() = -1;
//			the_next_index = -1;
//		}
//	}
//	
//	return node_at_index.data_ptr;
//}



void* list_backend::internal_func_unlink_at( s32 index, 
	node_contents* node_at_index_ptr )
{
	s32& the_front_index = get_front_index();
	s32& the_back_index = get_back_index();
	
	const s32 old_front_index = the_front_index,
		old_back_index = the_back_index;
	
	
	//node_contents node_at_index = get_node_contents_at(index);
	node_contents local_node_at_index_raw;
	node_contents* local_node_at_index_ptr;
	
	if ( node_at_index_ptr )
	{
		local_node_at_index_ptr = node_at_index_ptr;
	}
	else
	{
		local_node_at_index_raw = get_node_contents_at(index);
		local_node_at_index_ptr = &local_node_at_index_raw;
	}
	
	
	vec2_s16& index_pair_at_index = *local_node_at_index_ptr
		->index_pair_ptr;
	
	const s32 old_next_index = index_pair_at_index
		[node_contents::vec2_index_for_next_index],
	old_prev_index = index_pair_at_index
		[node_contents::vec2_index_for_prev_index];
	
	index_pair_at_index = { -1, -1 };
	
	
	
	//get_the_free_list_backend().push(index);
	
	if ( index == old_front_index && index != old_back_index )
	{
		the_front_index = old_next_index;
		
		if ( old_next_index >= 0 )
		{
			get_prev_index_at_index(the_front_index) = -1;
		}
	}
	else if ( index != old_front_index && index == old_back_index )
	{
		the_back_index = old_prev_index;
		
		if ( old_prev_index >= 0 )
		{
			get_next_index_at_index(the_back_index) = -1;
		}
	}
	else if ( index == old_front_index && index == old_back_index )
	{
		the_front_index = the_back_index = -1;
	}
	else //if ( index != old_front_index && index != old_back_index )
	{
		s16& the_next_index = get_next_index_at_index(old_prev_index);
		
		if ( old_next_index >= 0 )
		{
			the_next_index = old_next_index;
			get_prev_index_at_index(old_next_index) = old_prev_index;
		}
		else
		{
			the_next_index = -1;
		}
	}
	
	
	if ( the_back_index != old_back_index )
	{
		debug_arr_group::gdb_breakpoint_helper = 0;
	}
	
	
	return local_node_at_index_ptr->data_ptr;
}


void list_backend::internal_func_unlink_from_connected_index_at
	( s32 index, u32 index_to_vec2 )
{
	vec2_s16& index_pair_at_index = *get_index_pair_at_index(index);
	
	const s32 old_other_index = index_pair_at_index[index_to_vec2];
	
	
	// Check whether index is at the front or back of the list.
	if ( old_other_index < 0 )
	{
		return;
	}
	
	index_pair_at_index[index_to_vec2] = -1;
	
	vec2_s16& index_pair_at_other_index = *get_index_pair_at_index
		(old_other_index);
	
	// Generic code
	index_pair_at_other_index[!index_to_vec2] = -1;
	
}



// This is not quite the same algorithm as insertion sort.  In fact, it is
// possible to optimize it, using extra space, by exploiting the fact that
// this algorithm SEARCHES FORWARD to find ONLY ONE node to move.
s32 list_backend::insertion_sort()
{
	s32& the_front_index = get_front_index();
	s32& the_back_index = get_back_index();
	
	// Don't do anything if this list has zero or one nodes.
	if ( the_front_index < 0 )
	{
		return the_front_index;
	}
	
	
	//if ( get_node_at(the_front_index).next_index() < 0 )
	node_contents the_front_node = get_node_contents_at(the_front_index);
	
	s32 front_node_next_index = the_front_node.next_index();
	
	if ( front_node_next_index < 0 )
	{
		return the_front_index;
	}
	
	
	list_backend sorted_list(*this);
	
	s32& temp_front_index = sorted_list.get_front_index();
	
	
	
	//s32 curr_index = temp_front_index;
	
	for ( s32 i=the_front_index;
		i!=-1; )
		//i=get_next_index_at_index(i) )
	{
		s32 index_low = i;
		
		call_insertion_sort_inner_loop_fp(index_low);
		
		node_contents node_at_index_low = get_node_contents_at(index_low);
		
		if ( i == index_low )
		{
			i = node_at_index_low.next_index();
		}
		
		//sorted_list.push_back( unlink_at_with_dealloc(index_low), true );
		
		internal_func_unlink_at( index_low, &node_at_index_low );
		sorted_list.internal_func_move_unlinked_node_to_back( index_low,
			node_at_index_low );
	}
	
	
	the_front_index = temp_front_index;
	the_back_index = sorted_list.get_back_index();
	
	// Prevent any nodes from being erased when sorted_list's destructor is
	// called.
	temp_front_index = -1;
	
	
	return the_front_index;
}

//s32 list_backend::insertion_sort()
//{
//	return get_front_index();
//}






//// These two functions are slowwwwwww because there is too much list
//// traversal.  Thus, I have replaced them with an array of pointers based
//// method.
//s32 list_backend::internal_func_merge( merge_args& args )
//{
//	list_backend out_list(*this);
//	
//	s32& the_front_index = get_front_index();
//	s32& the_back_index = get_back_index();
//	
//	
//	bool done_with_left = false, done_with_right = false;
//	
//	const bool right_list_blank = ( args.get_right_head() < 0 );
//	
//	if (right_list_blank)
//	{
//		done_with_right = true;
//	}
//	
//	node_contents left_node = args.get_left_node(this),
//		right_node;
//	
//	node_contents left_tail_node = args.get_left_tail_node(this), 
//		right_tail_node;
//	
//	
//	s32 actual_tail_index;
//	node_contents* actual_tail_node_ptr = NULL;
//	
//	
//	if (!right_list_blank)
//	{
//		right_node = args.get_right_node(this);
//		right_tail_node = args.get_right_tail_node(this);
//		
//		actual_tail_index = args.get_right_tail();
//		actual_tail_node_ptr = &right_tail_node;
//	}
//	else // if (right_list_blank)
//	{
//		actual_tail_index = args.get_left_tail();
//		actual_tail_node_ptr = &left_tail_node;
//	}
//	
//	
//	
//	// These are for re-linking nodes after a merge.
//	node_contents node_before_start, node_after_end;
//	node_contents * node_before_start_ptr = NULL,
//		* node_after_end_ptr = NULL;
//	
//	
//	
//	
//	// start and end refer to args' parameters, and front and back refer to
//	// this's front_index and back_index.
//	const bool old_start_index_is_front_index = ( args.get_left_head() 
//		== the_front_index ),
//	old_end_index_is_back_index = ( actual_tail_index == the_back_index );
//	
//	const s32 temp_index_before_start = left_node.prev_index(),
//		temp_index_after_end = actual_tail_node_ptr->next_index();
//	
//	// If temp_index_before_start refers to nothing, don't point
//	// node_before_start_ptr to node_before_start.
//	if ( temp_index_before_start >= 0 )
//	{
//		node_before_start = get_node_contents_at(temp_index_before_start);
//		node_before_start_ptr = &node_before_start;
//	}
//	
//	if ( temp_index_after_end >= 0 )
//	{
//		node_after_end = get_node_contents_at(temp_index_after_end);
//		node_after_end_ptr = &node_after_end;
//	}
//	
//	
//	auto merge_left_node = [&]() -> void
//	{
//		if ( args.get_left_index() == args.get_left_tail() )
//		{
//			done_with_left = true;
//		}
//		
//		const s32 old_left_index = args.get_left_index();
//		
//		if (!done_with_left)
//		{
//			args.left_index = left_node.next_index();
//			
//			if ( args.get_left_index() >= 0 )
//			{
//				left_node = args.get_left_node(this);
//			}
//		}
//		
//		void* data_to_move = unlink_at_with_dealloc(old_left_index);
//		out_list.push_back( data_to_move, true );
//	};
//	
//	auto merge_right_node = [&]() -> void
//	{
//		if ( args.get_right_index() == args.get_right_tail() )
//		{
//			done_with_right = true;
//		}
//		
//		const s32 old_right_index = args.get_right_index();
//		
//		if (!done_with_right)
//		{
//			args.right_index = right_node.next_index();
//			
//			if ( args.get_right_index() >= 0 )
//			{
//				right_node = args.get_right_node(this);
//			}
//		}
//		
//		void* data_to_move = unlink_at_with_dealloc(old_right_index);
//		out_list.push_back( data_to_move, true );
//	};
//	
//	//for ( size_t k = 0; k<args.get_out_size(); ++k )
//	while ( !( done_with_left && done_with_right ) )
//	{
//		if (done_with_left)
//		{
//			merge_right_node();
//		}
//		else if (done_with_right)
//		{
//			merge_left_node();
//		}
//		else // if ( !done_with_left && !done_with_right )
//		{
//			if ( call_specific_type_less_func( left_node.data_ptr,
//				right_node.data_ptr ) )
//			{
//				merge_left_node();
//			}
//			else
//			{
//				merge_right_node();
//			}
//		}
//	}
//	
//	
//	// If there is a node before the left sublist's start node
//	if (node_before_start_ptr)
//	{
//		node_before_start.next_index() = out_list.get_front_index();
//		get_prev_index_at_index(out_list.get_front_index())
//			= temp_index_before_start;
//	}
//	// If the left sublist's original head index is the front_index
//	else if (old_start_index_is_front_index)
//	{
//		the_front_index = out_list.get_front_index();
//	}
//	
//	
//	// If there is a node after the right sublist's end node
//	if (node_after_end_ptr)
//	{
//		node_after_end.prev_index() = out_list.get_back_index();
//		get_next_index_at_index(out_list.get_back_index())
//			= temp_index_after_end;
//	}
//	// If the right sublist's original head index is the back_index
//	else if (old_end_index_is_back_index)
//	{
//		the_back_index = out_list.get_back_index();
//	}
//	
//	out_list.get_front_index() = -1;
//	
//	return out_list.get_back_index();
//}
//
//
//s32 list_backend::merge_sort()
//{
//	s32& the_front_index = get_front_index();
//	
//	
//	// Don't do anything if this list has zero or one nodes.
//	if ( the_front_index < 0 )
//	{
//		return the_front_index;
//	}
//	if ( get_next_index_at_index(the_front_index) < 0 )
//	{
//		return the_front_index;
//	}
//	
//	
//	merge_args args;
//	
//	size_t max_sublist_size_raw = 0;
//	
//	for ( s32 i=get_front_index(); i!=-1; i=get_next_index_at_index(i) )
//	{
//		++max_sublist_size_raw;
//	}
//	
//	const size_t& max_sublist_size = max_sublist_size_raw;
//	
//	
//	
//	s32 n_left_head, n_left_tail, n_right_head, n_right_tail;
//	
//	for ( size_t sublist_size=1; 
//		sublist_size<max_sublist_size; 
//		sublist_size*=2 )
//	{
//		n_left_head = n_left_tail = n_right_head = n_right_tail = -1;
//		
//		auto get_n_args = [&]( s32 n_left_head_value ) -> void
//		{
//			//n_left_head = the_front_index;
//			n_left_head = n_left_head_value;
//			n_left_tail = n_left_head;
//			
//			s32 temp = 0;
//			
//			for ( size_t k=0; k<sublist_size-1; ++k )
//			{
//				temp = get_next_index_at_index(n_left_tail);
//				
//				if ( temp < 0 )
//				{
//					break;
//				}
//				
//				n_left_tail = temp;
//			}
//			
//			if ( temp < 0 )
//			{
//				return;
//			}
//			
//			n_right_head = get_next_index_at_index(n_left_tail);
//			n_right_tail = n_right_head;
//			
//			for ( size_t k=0; k<sublist_size-1; ++k )
//			{
//				temp = get_next_index_at_index(n_right_tail);
//				
//				if ( temp < 0 )
//				{
//					break;
//				}
//				
//				n_right_tail = temp;
//			}
//		};
//		
//		get_n_args(the_front_index);
//		
//		for ( size_t i=0; i<max_sublist_size; i+=sublist_size*2 )
//		{
//			args.init( n_left_head, n_left_tail, n_right_head, 
//				n_right_tail );
//			
//			s32 n_left_head_value = internal_func_merge(args);
//			
//			if ( i + ( sublist_size * 2 ) < max_sublist_size )
//			{
//				get_n_args( get_next_index_at_index(n_left_head_value) );
//			}
//		}
//	}
//	
//	
//	return the_front_index;
//}



void list_backend::internal_func_subarr_merge
	( node_data_and_index* left_subarr, const size_t left_subarr_size, 
	node_data_and_index* right_subarr, const size_t right_subarr_size, 
	node_data_and_index* out_subarr )
{
	const size_t out_subarr_size = left_subarr_size + right_subarr_size;
	
	size_t i = 0, j = 0;
	
	for ( size_t k=0; k<out_subarr_size; ++k )
	{
		if ( i >= left_subarr_size )
		{
			out_subarr[k] = right_subarr[j];
			++j;
		}
		else if ( j >= left_subarr_size )
		{
			out_subarr[k] = left_subarr[i];
			++i;
		}
		else // if ( i < left_subarr_size && j < right_subarr_size )
		{
			if ( call_specific_type_less_func( left_subarr[i].data_ptr,
				right_subarr[j].data_ptr ) )
			{
				out_subarr[k] = left_subarr[i];
				++i;
			}
			else
			{
				out_subarr[k] = right_subarr[j];
				++j;
			}
		}
	}
	
}

class ndai_dyn_arr
{
public:		// variables
	node_data_and_index* arr = NULL;
	
public:		// functions
	ndai_dyn_arr( u32 s_size )
	{
		arr = new node_data_and_index[s_size];
	}
	~ndai_dyn_arr()
	{
		delete [] arr;
	}
	
	inline node_data_and_index* get_arr()
	{
		return arr;
	}
	
	inline node_data_and_index& operator [] ( size_t index )
	{
		return get_arr()[index];
	}
	
} __attribute__((_align4));



// Top-down merge sort using an array of node_data_and_index_and_index's.
s32 list_backend::merge_sort_via_array()
{
	s32& the_front_index = get_front_index();
	s32& the_back_index = get_back_index();
	
	const s32 old_front_index = the_front_index, old_back_index 
		= the_back_index;
	
	
	
	
	//std::unique_ptr<node_data_and_index[]> arr_a, work_arr;
	
	
	//arr_a.reset(new node_data_and_index[get_total_num_nodes()]);
	//work_arr.reset(new node_data_and_index[get_total_num_nodes()]);
	
	
	
	// The number of used nodes
	size_t real_num_nodes_raw = 0;
	
	for ( s32 i=old_front_index; 
		i!=-1;
		i=get_next_index_at_index(i) )
	{
		//arr_a[real_num_nodes_raw] = get_node_data_and_index_at(i);
		
		++real_num_nodes_raw;
	}
	
	const size_t& real_num_nodes = real_num_nodes_raw;
	
	
	
	// This is slower than filling arr_a in the previous for loop, but it
	// can use SIGNIFICANTLY less memory in the general case if the sa_list
	// is not full.  This might be a good use case for an std::vector.
	//arr_a.reset(new node_data_and_index[real_num_nodes]);
	//work_arr.reset(new node_data_and_index[real_num_nodes]);
	ndai_dyn_arr arr_a(real_num_nodes), work_arr(real_num_nodes);
	
	
	{
	
	size_t temp = 0;
	node_contents temp_node;
	
	for ( s32 i=old_front_index; i!=-1; i=temp_node.next_index() )
	{
		temp_node = get_node_contents_at(i);
		
		//arr_a[temp] = get_node_at(i);
		arr_a[temp] = node_data_and_index( temp_node.data_ptr, 
			i );
		
		++temp;
	}
	
	}
	
	
	
	//bool use_arr_a = false;
	
	node_data_and_index * left_subarr, * right_subarr;
	size_t left_subarr_size = 0, right_subarr_size = 0;
	
	// Avoid recursion
	for ( size_t subarr_size=1;
		subarr_size<real_num_nodes;
		subarr_size*=2 )
	{
		auto get_merge_args = [&]( node_data_and_index* n_left_subarr )
			-> void
		{
			left_subarr = n_left_subarr;
			left_subarr_size = subarr_size;
			
			right_subarr = NULL;
			right_subarr_size = 0;
			
			
			if ( left_subarr_size >= real_num_nodes )
			{
				left_subarr_size = real_num_nodes;
				return;
			}
			
			right_subarr = &(left_subarr[left_subarr_size]);
			
			
			if ( left_subarr_size + subarr_size >= real_num_nodes )
			{
				right_subarr_size = real_num_nodes - left_subarr_size;
			}
			else
			{
				right_subarr_size = subarr_size;
			}
			
		};
		
		get_merge_args(&(arr_a[0]));
		
		for ( size_t i=0; i<real_num_nodes; i+=subarr_size*2 )
		{
			internal_func_subarr_merge( left_subarr, left_subarr_size,
				right_subarr, right_subarr_size, &(work_arr[i]) );
			
			if ( i + ( subarr_size * 2 ) < real_num_nodes )
			{
				get_merge_args( &(arr_a[i + ( subarr_size * 2 )]) );
			}
		}
		
		for ( s32 i=real_num_nodes-1; i>=0; --i )
		{
			arr_a[i] = work_arr[i];
		}
	}
	
	//for ( s32 i=real_num_nodes-1; i>=0; --i )
	//{
	//	node_contents temp_node = get_node_contents_at(arr_a[i].index);
	//	
	//	internal_func_move_unlinked_node_to_front( i, temp_node );
	//}
	
	//for ( u32 i=0; i<real_num_nodes; ++i )
	//{
	//	debug_arr_group::write_s32_and_inc(*(u32*)(arr_a[i].data_ptr));
	//}
	
	
	
	list_backend out_list(*this);
	
	while ( the_front_index >= 0 )
	{
		// Unlink every node so they can all be re-linked in sorted order.
		// Part of the strategy here is to avoid allocating and
		// deallocating node array indices.
		internal_func_unlink_at(the_front_index);
		
		
		////out_list.push_back(unlink_at_with_dealloc(the_front_index));
		//node_contents the_front_node 
		//	= get_node_contents_at(the_front_index);
		//move_linked_node_to_back( 
	}
	
	for ( u32 i=0; i<real_num_nodes; ++i )
	{
		const s32& curr_index = arr_a[i].index;
		node_contents temp_node = get_node_contents_at(curr_index);
		
		internal_func_move_unlinked_node_to_back( curr_index, temp_node );
	}
	
	//the_front_index = out_list.get_front_index();
	//the_back_index = out_list.get_back_index();
	
	//out_list.get_front_index() = -1;
	
	return the_front_index;
}


} // end of namespace sa_list_stuff

