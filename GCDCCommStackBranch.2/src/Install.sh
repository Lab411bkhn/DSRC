#!/bin/bash
sudo modprobe ndiswrapper 
echo "Thuc hien qua trinh Insmod cac module"
sudo rmmod ath5k
sudo rmmod mac80211
sudo rmmod ath
sudo rmmod cfg80211
cd $PWD/kernel/wireless

sudo insmod lib80211.ko
sleep 1
sudo insmod lib80211_crypt_wep.ko
sleep 1
sudo insmod lib80211_crypt_tkip.ko
sleep 1
sudo insmod lib80211_crypt_ccmp.ko
sleep 1
sudo insmod cfg80211.ko
sleep 1
cd ../
pwd 
cd mac80211
sudo insmod mac80211.ko
sleep 1
cd ../
pwd
cd ath
sudo insmod ath.ko
sleep 1
cd ath5k
sudo insmod ath5k.ko
sleep 1
cd ../../../
pwd
cd iw-0.9.19
sudo ./iw reg set US
sudo ifconfig wlan0 down
sleep 1
sudo iwconfig wlan0 mode ad-hoc
sleep 1
sudo ifconfig wlan0 up
sleep 1
sudo ./iw dev wlan0 set channel 161
sleep 1
sudo ./iw dev wlan0 ibss leave
sleep 1
sudo ./iw wlan0 scan freq 5805
sleep 1
#[Lab411] Create ad-hoc networking
sudo stop network-manager
sleep 2
sudo ifconfig wlan0 down
sleep 1
sudo iwconfig wlan0 mode ad-hoc essid ITS-LAB411 channel 161 ap C2:7F:32:69:BC:54
sleep 1
sudo ifconfig wlan0 up 10.42.43.2/8
sleep 1
sudo iwconfig wlan0 rts 2347
sleep 1
sudo ip route add 192.168.2.0/24 via 10.42.43.1 dev wlan0
sleep 1
sudo ip route add 10.42.43.11 via 10.42.43.1 dev wlan0
sleep 1
sudo ip route add 239.255.10.10 dev wlan0
#sudo ifconfig wlan6 down
#sleep 1
#sudo iwconfig wlan6 mode ad-hoc essid CSDN channel 7 ap 26:76:8C:A3:B7:2C 
#sleep 1
#sudo ifconfig wlan6 up 192.168.2.1/24
echo "Insmod thanh cong cac module"
