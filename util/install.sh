#!/bin/bash

#################################################
##  ___ _         _   ___ _               _    ##
## | _ ) |___  __| |_| _ \ |__ _ _ _  ___| |_  ##
## | _ \ / _ \/ _| / /  _/ / _` | ' \/ -_)  _| ##
## |___/_\___/\__|_\_\_| |_\__,_|_||_\___|\__| ##
##                                             ##
#################################################

# Copyright (c) MiJyn, Joel Leclerc <mijyn@mail.com>

#########################
## Installation Script ##
#########################

# Include utility script
. `readlink -f $0 | sed 's:\(.*\)/.*:\1/utility.sh:g'`

# Globals
VERSION=0.1
TARGET=`readlink -f "."`
NOTARGET=1

usage()
{
	echo "BlockPlanet Installation Script"
	echo "Usage: $0 [args]"
	echo
	displayhelp "-h" "Shows this help message" "-v" "Shows the version of this script" "-t TARGET" "Sets the target directory"
	echo
	echo "Copyright (c) MiJyn, Joel Leclerc <mijyn@mail.com>"
	exit $1
}

version()
{
	echo "BlockPlanet Installation Script version $VERSION"
	exit $1
}

while getopts ":hvt:" opt
do
	case $opt in
		h) usage;;
		v) version;;
		t) TARGET=`readlink -f $OPTARG`;NOTARGET=0;;
		\?) printe "Invalid option: $OPTARG"; usage 1;;
		:) printe "Option requires an argument: $OPTARG"; usage 1;;
	esac
done

if [ $NOTARGET -eq 1 ]
then
	printe "FATAL: No target specified"
	usage 1
fi
if [ -e $TARGET ]
then
	printe "FATAL: Target already exists"
	exit 1
fi

bboxes "BlockPlanet Installation Script"
echo
inst build-essential Essential_Build_Utilities libirrlicht-dev Irrlicht_Development_Files cmake CMake libbz2-dev BZ2_Development_Files libpng12-dev PNG_Development_Files libjpeg8-dev JPEG_Development_Files libxxf86vm-dev X11_Free86_Development_Files libgl1-mesa-dev GL_Development_Files libsqlite3-dev SQLite_Development_Files libogg-dev OGG_Development_Files libvorbis-dev Vorbis_Development_Files libopenal-dev OpenAL_Development_Files libcurl3 cURL_Library libcurl4-gnutls-dev cURL_Development_Files unzip Unzipper ncurses-bin Shell_NCurses
echo

echo "Downloading and extracting BlockPlanet Source"
export NOC=7
export NOCC=1
percent $NOC
rm -f /tmp/blockplanet.zip &> /dev/null
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
wget https://github.com/MiJyn/BlockPlanet/zipball/master -O /tmp/blockplanet.zip &> /dev/null
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
mkdir -p $TARGET &> /dev/null
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
cd $TARGET &> /dev/null
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
unzip /tmp/blockplanet.zip &> /dev/null
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
cd * &> /dev/null
percentfinish
echo
echo "Creating structure"
export NOC=4
export NOCC=1
percent $NOC
mkdir build
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
cd build
percentupd8 $NOC $NOCC
NOCC=$(($NOCC+1))
cmake .. && make
percentfinish
echo
echo "Installing BlockPlanet"
sudo make install


#EOF


