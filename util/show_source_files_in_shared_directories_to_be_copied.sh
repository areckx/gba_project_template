#!/bin/bash

# This file is part of GBA Project Template.
# 
# Copyright 2015-2017 Andrew Clark (FL4SHK).
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


first_script=util/get_most_rsync_exclude_args.sh
second_script=util/convert_project_name_in_license.sh
third_script=util/get_shared_src_directories.sh

function quit()
{
	echo "Exiting...."
	exit 1
}

function quit_if_script_missing()
{
	if [ ! -f "$1" ]
	then
		echo "\"$1\" does not appear to exist."
		quit
	elif [ ! -x "$1" ]
	then
		echo "\"$1\" does not appear to be executable."
		quit
	fi
}


if [ ! -d "$1" ]
then
	echo "\"$1\" does not appear to be a valid directory."
	quit
fi

quit_if_script_missing "$first_script"
quit_if_script_missing "$second_script"
quit_if_script_missing "$third_script"


most_rsync_args=$($first_script)
shared_src_dirs=($("$third_script" . "$1"))

##rsync -avh --progress --dry-run --existing "$1"/src .
##rsync -avh --progress --dry-run --existing "$1"/src .
##bash -c "rsync -avuh --progress --existing \
##	--exclude=\"$second_script\" \
##	$most_rsync_args \
##	\"$1\"/ ."
#

##echo ${shared_src_dirs[@]}
#for dir in "${shared_src_dirs[@]}"
#do
#	echo "$dir"
#done

for dir in "${shared_src_dirs[@]}"
do
	bash -c "rsync -avh --progress --dry-run \
		$most_rsync_args[@] \
		--exclude=\"$second_script\" \
		\"$1\"/\"$dir\"/ ./\"$dir\""
done

#echo "Running \"$second_script\""
#$($second_script)
