#!/usr/bin/env bash

apt-get update
apt-get install -y build-essential
apt-get install -y gcc-arm-none-eabi
apt-get install -y cmake
apt-get install -y apache2
if ! [ -L /var/www ]; then
  rm -rf /var/www
  ln -fs /vagrant /var/www
fi