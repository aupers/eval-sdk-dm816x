#Check if this is an agregated interface
if ifconfig $1 | grep -q SLAVE ; then
    MAC=`ifconfig $1 | grep HWaddr | awk '{print $5}'`
    IFACE=`ifconfig | grep $MAC | grep bond | awk '{print $1}'`
    ifconfig $IFACE 2>/dev/null |  awk '/inet addr/ { sub(/inet addr:/,"") ; print $1 }'
else
    ifconfig $1 2>/dev/null | awk '/inet addr/ { sub(/inet addr:/,"") ; print $1 }'
fi