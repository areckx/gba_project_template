#! /usr/bin/env python3

# This file is part of GBA Project Template.
# 
# Copyright 2015-2017 by Andrew Clark (FL4SHK).
# 
# GBA Project Template is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
# 
# GBA Project Template is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.



the_list = []

for i in range( 0x0, 0x100 ) :
	if ( i < 0x20 ) :
		the_list.append(' ')
	elif ( i < 0x80 ) :
		the_list.append(chr(i))
	else :
		the_list.append(' ')

for a in the_list :
	print ( "\'{}\', ".format(a), end="" )

print(len(the_list))
