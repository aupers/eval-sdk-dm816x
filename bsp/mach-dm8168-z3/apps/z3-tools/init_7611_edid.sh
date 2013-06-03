#! /bin/sh

PATH=/usr/local/sbin:${PATH}:/usr/sbin:/root:.

set -- `cat /proc/cpuinfo |grep '^Hardware'`
MACHINE=$3

case "${MACHINE}" in
*814*)  IDGPIO=/sys/class/gpio/gpio2/value  
        LATCHBASE=0x8000
        I2CBUS2=3
        ;;
*)      IDGPIO=/sys/class/gpio/gpio21/value  
        LATCHBASE=0x0
        I2CBUS2=2
        ;;
esac

write_latch1()
{
    LATCH1FILE=/proc/fpga/latch1

    if [ -f /proc/fpga/latch1 ] ;  then
        echo "$@" > /proc/fpga/latch1
    else
        devmem2 0x1000000 h "$@"
    fi
}

boardid=0
if [ -f ${IDGPIO} ] ; then
     # Initialize latch -- just in case 
    write_latch1 $(( LATCHBASE | 0x0000 ))
    usleep 100000

    write_latch1 $(( LATCHBASE | 0x800 ))
    usleep 10000
    boardid=$(( 2 * boardid + `cat ${IDGPIO}` ))

    write_latch1 $(( LATCHBASE | 0x400 ))
    usleep 10000
    boardid=$(( 2 * boardid + `cat ${IDGPIO}` ))

    write_latch1 $(( LATCHBASE | 0x200 ))
    usleep 10000
    boardid=$(( 2 * boardid + `cat ${IDGPIO}` ))

    write_latch1 $(( LATCHBASE | 0x100 ))
    usleep 10000
    boardid=$(( 2 * boardid + `cat ${IDGPIO}` ))

    echo "0x${boardid}" > /proc/fpga/board_id

else
    boardid=`cat /proc/fpga/board_id`
fi

echo "BoardID=${boardid}" > /dev/tty


if [ ${boardid} = 1 ] ; then

##############################################
# First take care of TVP5150
#
# Enable power to TVP5150
write_latch1 $(( LATCHBASE | 0x227b ))
sleep 1
# Assert RST# to TVP5150's
write_latch1 $(( LATCHBASE | 0x2273 ))
sleep 1

# Release RST# to TVP5150's
write_latch1 $(( LATCHBASE | 0x227b ))
sleep 1

# Do it again just to pass some time
write_latch1 $(( LATCHBASE | 0x217b ))
sleep 1

# Tri-state both TVP5150's
# Do it twices because some times the 1st time fails
i2cset -y ${I2CBUS2} 0x5c 0x03 0x00 b
i2cset -y ${I2CBUS2} 0x5c 0x03 0x00 b
i2cset -y ${I2CBUS2} 0x5d 0x03 0x00 b
i2cset -y ${I2CBUS2} 0x5d 0x03 0x00 b
#
##############################################


##############################################
# Now take TVP7002's out of the bus
#
# Tri-state the TVP7002
i2cset -y 1 0x5c 0x17 0x01 b
i2cset -y 1 0x5d 0x17 0x01 b
#
##############################################


##############################################
# Reset ADV7611 and resample I2C addresses
write_latch1 $(( LATCHBASE | 0x285a ))
write_latch1 $(( LATCHBASE | 0x257b ))

# Do it again just to pass some time
write_latch1 $(( LATCHBASE | 0x257b ))
i2cset -y 1 0x4c 0x1b 0x01 b
sleep 1
HDMI_LIST="HDMI1 HDMI2"

elif [ ${boardid} = 2 ] ; then

HD_3GIGSDI_OUT_LATCH2=0xf600
HD_SDI_OUT_LATCH2=0xf400
SD_SDI_OUT_LATCH2=0xf100
HD_SDI_IN_LATCH2=0x001d
SD_SDI_IN_LATCH2=0x0014

echo $(( LATCHBASE |  0x2007 )) > /proc/fpga/latch1

echo $(( HD_3GIGSDI_OUT_LATCH2 | HD_SDI_IN_LATCH2 )) > /proc/fpga/latch2

sleep 1

HDMI_LIST="HDMI1"

else
exit 0
fi

for PARAM in ${HDMI_LIST} ; do

case "${PARAM}" in
	0X4C|PRIMARY|HDMI1|HDMIA)
		ADV7611ADDR=0x4c
		DPLL_SLAVE=0x3F
		CEC_SLAVE=0x40
		INFOFRAME_SLAVE=0x3E
		KSV_SLAVE=0x32
		EDID_SLAVE=0x36
		HDMI_SLAVE=0x34
		CP_SLAVE=0x22
		;;
	0X4D|SECONDARY|HDMI2|HDMIB)
		ADV7611ADDR=0x4d
		DPLL_SLAVE=0x45
		CEC_SLAVE=0x46
		INFOFRAME_SLAVE=0x47
		KSV_SLAVE=0x48
		EDID_SLAVE=0x49
		HDMI_SLAVE=0x4a
		CP_SLAVE=0x4b
		;;
	*)
		echo "Invalid parameter $1"
		exit 1
		;;
esac


# Reset chip
sleep 1

#
# Assign I2C addresses - 0x40-0x4b
#
# sometimes the first write fails ...
i2cset -y 1 "${ADV7611ADDR}" 0xf4 $((${CEC_SLAVE}*2))

dmesg -n 7

i2cset -y 1 "${ADV7611ADDR}" 0xf4 $((${CEC_SLAVE}*2))

i2cset -y 1 "${ADV7611ADDR}" 0xf5 $((${INFOFRAME_SLAVE}*2))
i2cset -y 1 "${ADV7611ADDR}" 0xf8 $((${DPLL_SLAVE}*2))
i2cset -y 1 "${ADV7611ADDR}" 0xf9 $((${KSV_SLAVE}*2))
i2cset -y 1 "${ADV7611ADDR}" 0xfa $((${EDID_SLAVE}*2))
i2cset -y 1 "${ADV7611ADDR}" 0xfb $((${HDMI_SLAVE}*2))
i2cset -y 1 "${ADV7611ADDR}" 0xfd $((${CP_SLAVE}*2))

#
# BEGIN 7611 init
#

# 1080P-60 setting
i2cset -y 1 "${ADV7611ADDR}" 0x01 0x06 b
i2cset -y 1 "${ADV7611ADDR}" 0x02 0xf5 b
i2cset -y 1 "${ADV7611ADDR}" 0x03 0x80 b
i2cset -y 1 "${ADV7611ADDR}" 0x05 0x2c b
i2cset -y 1 "${ADV7611ADDR}" 0x06 0xa6 b ; # Invert HS, VS pins


# Bring chip out of powerdown and disable tristate 
i2cset -y 1 "${ADV7611ADDR}" 0x0b 0x44 b
i2cset -y 1 "${ADV7611ADDR}" 0x0c 0x42 b
i2cset -y 1 "${ADV7611ADDR}" 0x14 0x3f b
i2cset -y 1 "${ADV7611ADDR}" 0x15 0xA0 b
# LLC DLL enable
i2cset -y 1 "${ADV7611ADDR}" 0x19 0x83 b
i2cset -y 1 "${ADV7611ADDR}" 0x33 0x40 b

# Force HDMI Free run 
i2cset -y 1 ${CP_SLAVE} 0xba 0x01 b

# Disable HDCP 1.1
i2cset -y 1 ${KSV_SLAVE} 0x40 0x81 b

i2cset -y 1 ${HDMI_SLAVE}  0x9B 0x03 b ; # ADV7611-VER.2.6.c

#Following writes are recommended for non-fast switching applications:
i2cset -y 1 ${HDMI_SLAVE}  0xC1 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC2 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC3 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC4 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC5 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC6 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC7 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC8 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xC9 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xCA 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xCB 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE}  0xCC 0x01 b ; # ADI recommended setting


i2cset -y 1 ${HDMI_SLAVE} 0x00 0x00 b ; # Set HDMI Input Port A
i2cset -y 1 ${HDMI_SLAVE} 0x83 0xFE b ; # Enable clock terminator for port A
i2cset -y 1 ${HDMI_SLAVE} 0x6F 0x08 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE} 0x85 0x1F b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE} 0x87 0x70 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE} 0x8D 0x04 b ; # LFG
i2cset -y 1 ${HDMI_SLAVE} 0x8E 0x1E b ; # HFG
i2cset -y 1 ${HDMI_SLAVE} 0x1A 0x8A b ; # unmute audio
i2cset -y 1 ${HDMI_SLAVE} 0x57 0xDA b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE} 0x58 0x01 b ; # ADI recommended setting
i2cset -y 1 ${HDMI_SLAVE} 0x75 0x10 b ; # DDC drive strength


#
# END 7611 init
#


#
# reset, reload and enable EDID
EDIDINDEX=$(( ADV7611ADDR - 0x4b ))

edid --i2cbus=1 --i2caddr=${EDID_SLAVE} --monitorid=8168APP02 > /dev/null  2> /dev/null
i2cset -y 1 ${HDMI_SLAVE} 0x5a 0x08 ; # Reset EDID
edid --i2cbus=1 --i2caddr=${EDID_SLAVE} --monitorid=8168APP02 > /dev/null  2> /dev/null
usleep 100000
if [ "$?" = "0" ] ; then
    echo EDID${EDIDINDEX} success > /dev/tty
else
    echo EDID${EDIDINDEX} failed, retry > /dev/tty
    edid --i2cbus=1 --i2caddr=${EDID_SLAVE} --monitorid=8168APP02 > /dev/null 2> /dev/null
fi
i2cset -y 1 ${KSV_SLAVE} 0x74 0x01 ; # Enable EDID A
# Do it twice. Some times the first write fails.
i2cset -y 1 ${KSV_SLAVE} 0x74 0x01 ; # Enable EDID A


done

#modprobe adv7611 debug=2
#modprobe tvp7002 debug=2
