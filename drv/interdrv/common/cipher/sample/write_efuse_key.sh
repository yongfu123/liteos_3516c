#!/bin/sh

#set key~key3
himm 0x12070000 0x00000001
himm 0x12070004 0x00000002
himm 0x12070008 0x00000003
himm 0x1207000c 0x00000004
sleep 1
@start write key to efuse of 1 [5:4]=otp_key_add, KEYÔÚOTPµÄµØÖ·.
himm 0x12070010 0x00000015
sleep 1

himd.l 0x12070014
#should be 0x88010000


