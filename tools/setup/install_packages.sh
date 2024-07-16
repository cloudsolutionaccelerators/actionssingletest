#!/bin/sh

# Install packages
sudo pkg install -y git bash cmake gcc llvm

# Update package database
pkg update

# Upgrade installed packages
pkg upgrade