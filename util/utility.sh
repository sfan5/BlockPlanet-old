#!/bin/bash

#################################################
##  ___ _         _   ___ _               _    ##
## | _ ) |___  __| |_| _ \ |__ _ _ _  ___| |_  ##
## | _ \ / _ \/ _| / /  _/ / _` | ' \/ -_)  _| ##
## |___/_\___/\__|_\_\_| |_\__,_|_||_\___|\__| ##
##                                             ##
#################################################

# Copyright (c) MiJyn, Joel Leclerc <mijyn@mail.com>

#####################
## Utility Library ##
#####################

# Variables

# Color variables
Start='\e['
End='m'
Sep=';'
Normal='0'
Bold='1'
Underline='4'
Black='30'
Red='31'
Green='32'
Yellow='33'
Blue='34'
Purple='35'
Cyan='36'
White='37'
# Use the bak function to find out the background color value of any color
Background='10'

# Root
# 0 = not root, 1 = root
ROOT=0
if [ `id -u` -eq 0 ]
then
	ROOT=1
fi

# General Utilities

# Finds the background color of any color
# # Usage: #
# bak color
# # Arguments: #
# color = Color to find the background of
# # Example: #
# BAKCOLOR=`bak $Green`
bak()
{
	echo $(($1+$Background))
}

# Prints text in style
# # Usage: #
# prints text type color [bakcolor]
# # Arguments: #
# text = Text to print
# type = Type of text (normal, bold, underline)
# color = Color
# bakcolor = Background Color (you need to use the bak function to find this) [optional]
# # Example: #
# prints "Hello World" $Bold $Green `bak $Black`
prints()
{
	if [ $# -lt 4 ]
	then
		printf $Start$2$Sep$3$End"$1"$Start$End
	else
		printf $Start$2$Sep$3$Sep$4$End"$1"$Start$End
	fi
	echo
}

# Prints an error message
# # Usage: #
# printe text
# # Arguments: #
# text = Text to print
# # Example: #
# printe "Error displaying Hello World"
printe()
{
	prints "$@" $Bold $Red >&2
}

# Prints a message using grammar
# # Usage: #
# printg arg1 arg2 arg3
# # Arguments: #
# arg = random argument to format
# # Example: #
# printg Hello World
printg()
{
	NUM=0
	for i in "$@"
	do
		NUM=$(($NUM+1))
	done
	NUMCLONE=$NUM
	for x in "$@"
	do
		i=`echo $x | sed 's:_: :g'`
		if [ $NUM -eq 1 ]
		then
			echo -n $i
			NUM=$(($NUM-1))
		elif [ $NUM -eq 2 ]
		then
			echo -n $i
			if [ $NUMCLONE -eq 2 ]
			then
				echo -n " and "
			else
				echo -n ", and "
			fi
			NUM=$(($NUM-1))
		else
			echo -n $i", "
			NUM=$(($NUM-1))
		fi
	done
	echo
}

# Boxes in BASH
# # Usage: #
# bboxes text
# # Arguments: #
# text = text to format
# # Example: #
# bboxes "Hello World"
bboxes()
{
	PADDING=6
	CHAR="#"
	i=0
	TEXT="$*"
	END=$((${#TEXT}+$PADDING))
	while [ $i -lt $END ]
	do
		echo -n $CHAR
		i=$(($i+1))
	done
	echo
	echo "## $TEXT ##"
	i=0
	while [ $i -lt $END ]
	do
		echo -n $CHAR
		i=$(($i+1))
	done
	echo
}

# Displays a help message
# # Usage: #
# displayhelp arg desc ...
# # Arguments: #
# arg = Argument
# desc = Description
# # Example: #
# displayhelp "-h" "Displays This Help Message"
displayhelp()
{
	VAL=0
	LONGEST=0
	for i in "$@"
	do
		if [ $VAL -eq 0 ]
		then
			THIS=${#i}
			if [ $THIS -gt $LONGEST ]
			then
				LONGEST=$THIS
			fi
			VAL=1
		else
			VAL=0
		fi
	done
	space()
	{
		i=0
		while [ $i -le $1 ]
		do
			echo -n " "
			i=$(($i+1))
		done
	}
	for i in "$@"
	do
		if [ $VAL -eq 0 ]
		then
			echo -en "$i`space $(($LONGEST-${#i}+2))`"
			VAL=1
		else
			echo "$i"
			VAL=0
		fi
	done
}


# Percentage Utilities

tput init
export COLUMNS=`tput cols`

# Initializes a progress bar
# # Usage: #
# percent total
# # Arguments: #
# total = Total number of items
# # Example: #
# percent 20
percent()
{
	export COLS=$(($COLUMNS-3))
	export INCREASE=$(($COLS/$1))
	export DONE=1
	export COUNT=0
	export SPACE=0
	printf "\r"
	echo -n "["
	while [ $DONE -eq 1 ]
	do
		if [ $SPACE -ge $COLS ]
		then
			DONE=0
		else
			echo -n " "
			SPACE=$(($SPACE+1))
		fi
	done
	echo -n "]"
}

# Finishes a progress bar
# # Usage: #
# percentfinish
# # Example: #
# percentfinish
percentfinish()
{
	export COLS=$(($COLUMNS-3))
	DONE=1
	CURRENTNUM=0
	printf "\r"
	echo -n "["
	while [ $DONE -eq 1 ]
	do
		if [ $CURRENTNUM -eq $COLS ]
		then
			 DONE=0
		else
			echo -n "="
			CURRENTNUM=$(($CURRENTNUM+1))
		fi
	done
	echo -n "]"
}

# Updates a progress bar
# # Usage: #
# percentupd8 total current
# # Arguments: #
# total = Total number of items
# current = Current number
# # Example: #
# percentupd8 20 5
percentupd8()
{
	export COLS=$(($COLUMNS-3))
	tempans=$1
	export INCREASE=$(($COLS/$tempans))
	export DONE=1
	export FINISHED=$tempans
	helper1()
	{
		export DONEH1=1
		export COUNT=0
		export SPACE=0
		export TOTALCOUNT=$1
		echo -n "["
		while [ $DONEH1 -eq 1 ]
		do
			if [ $TOTALCOUNT -eq $COUNT ]
			then
				if [ $SPACE -ge $COLS ]
				then
					DONEH1=0
				else
					echo -n " "
					SPACE=$(($SPACE+1))
				fi
			else
				echo -n "="
				COUNT=$(($COUNT+1))
				SPACE=$(($SPACE+1))
			fi
		done
		echo -n "]"
	}
	helper2()
	{
		export ANS=0
		export DONEH2=1
		export CURRENTNUM=0
		export NUM=$1
		while [ $DONEH2 -eq 1 ]
		do
			if [ $CURRENTNUM -eq $NUM ]
			then
				DONEH2=0
			else
				ANS=$(($ANS+$INCREASE))
				CURRENTNUM=$(($CURRENTNUM+1))
			fi
		done
		echo $ANS
	}
	if [ $tempans -eq $2 ]
	then
		percentfinish
	else
		printf "\r"
		helper1 `helper2 $2`
	fi
}


# Installation Utilities


# Installs packages
# # Usage: #
# inst package packagename package2 packagename2 ...
# # Arguments: #
# package = Package to install
# packagename = Name shown to the user
# # Example: #
# inst g++ GNU_C++_Compiler gcc GNU_C_Compiler
inst()
{
	PAKLIST=""
	PAKNAMELIST=""
	VAL=0
	for i in "$@"
	do
		if [ $VAL -eq 0 ]
		then
			PAKLIST="$PAKLIST $i"
			VAL=1
		else
			PAKNAMELIST="$PAKNAMELIST $i"
			VAL=0
		fi
	done
	echo -n "Installing "
	printg $PAKNAMELIST
	echo
	if [ $ROOT -eq 1 ]
	then
		apt-get install $PAKLIST
	else
		sudo apt-get install $PAKLIST
	fi
	echo
	echo "Done"
}

