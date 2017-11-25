#!/bin/sh

#gate, power
himm 0x12150400 0x4
himm 0x12150010 0x4

#set key~key3
himm 0x12070800 0x00000001;
himm 0x12070804 0x00000002;
himm 0x12070808 0x00000003;
himm 0x1207080c 0x00000004;
sleep 1
@start write key to efuse of 1 [5:4]=otp_key_add, KEYÔÚOTPµÄµØÖ·.
himm 0x12070810 0x00000015
sleep 1

himd.l 0x12070814
#should be 0x88010000 0x8800c000


