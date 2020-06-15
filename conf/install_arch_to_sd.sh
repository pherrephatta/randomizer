#!/bin/bash

# NOTE: use printf instead of echo?

archfolder="/tmp/install_arch_to_sd"			# temp folder where drive is mounted and installed
archfile="ArchLinuxARM-rpi-latest.tar.gz"		# name of arch install zip
syspath=`pwd`									# current terminal path
drive=""										# read and store chosen drive

# Check for root
if [ "$EUID" -ne 0 ]
then 
  echo "Run as root!"
  exit
fi

# Choose drive
echo -n "Drive: "
read drive
if [[ ! "$drive" =~ /dev/sd[a-z]$ ]]
then
	echo "Bad drive name"
	exit
fi

# Partition drive
echo -e -n "\e[1m\e[31mPartitioning drive... \e[0m"
parted $drive --script mklabel msdos
parted $drive --script mkpart primary fat32 1 128
parted $drive --script mkpart primary ext4 128 100%
parted $drive --script set 1 boot on
echo "done!"

# Create filesystems
echo -e -n "\e[1m\e[31mCreating filesystems... \e[0m"
mkfs.vfat -F32 ${drive}1 > /dev/null 2>&1
mkfs.ext4 -F ${drive}2 > /dev/null 2>&1
echo "done!\n"

## Display drive info
echo ""
parted $drive print | tail -3 | head -2
echo ""

## Check if OS archive is present
if [ ! -f ${archfile} ]
then
	echo -e -n "\e[1m\e[31mDownloading ArchLinuxARM... \e[0m"
	wget http://os.archlinuxarm.org/os/ArchLinuxARM-rpi-latest.tar.gz > /dev/null 2>&1
	echo "done!"
fi

# Create temporary folders
echo -e -n "\e[1m\e[31mMaking folders at ${archfolder}... \e[0m"
mkdir -p ${archfolder}/{root,boot}
echo "done!"

# Mount drives and transfer files
echo -e -n "\e[1m\e[31mMounting drives... \e[0m"
mount ${drive}1 ${archfolder}/boot
mount ${drive}2 ${archfolder}/root
echo "done!"

# Unzip OS archives 
echo -e -n "\e[1m\e[31mUnzipping contents to ${archfolder}/root... \e[0m"
sudo tar -xf "$archfile" -C ${archfolder}/root > /dev/null 2>&1
echo "done!"

# Transfer boot files
echo -e -n "\e[1m\e[31mTransferring boot folder... \e[0m"
mv ${archfolder}/root/boot/* ${archfolder}/boot
echo "done!"

# Unmount drives
echo -e -n "\e[1m\e[31mUnmounting drives... \e[0m"
umount -R ${archfolder}/root
umount -R ${archfolder}/boot
echo -e "done!\n"

# Clean up
rm -rf ${archfolder}
echo -e "\e[1m\e[32mFinished all operations\e[0m"
exit
