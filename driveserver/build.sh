#!/bin/bash

# MQQTINCLUDE="/home/pi/wiringpi/mqtt_client/sensorlib/include"
# MQQTADDITIONAL="$MQQTINCLUDE/MQTTConnectClient.c $MQQTINCLUDE/MQTTConnectServer.c \
# $MQQTINCLUDE/MQTTPacket.c $MQQTINCLUDE/MQTTSerializePublish.c \
# $MQQTINCLUDE/MQTTSubscribeServer.c $MQQTINCLUDE/MQTTDeserializePublish.c \
# $MQQTINCLUDE/MQTTSubscribeClient.c \
# $MQQTINCLUDE/MQTTUnsubscribeServer.c $MQQTINCLUDE/MQTTUnsubscribeClient.c \
# $MQQTINCLUDE/transport.c"

cd $(dirname $0)

if [ "$#" != 1 ]; then
    echo "usage: build.sh <compiler>"
fi

COMPILER=$1
SRCDIR="${PWD}/src"

echo $SRCDIR

ADDITIONALLIBS="-L/files/src/rpi_src/lib -L/files/src/rpi_src/lib/arm-linux-gnueabihf \
-L/files/src/rpi_src/usr/lib -L/files/src/rpi_src/usr/lib/arm-linux-gnueabihf"
ADDITIONALHEADERS="-I/files/src/rpi_src/usr/include -I/files/src/rpi_src/usr/include/arm-linux-gnueabihf"

if [ ! -d "$SRCDIR" ]; then
    echo "SRC-DIR Missing"
    exit 1
fi    

SRCFILES="$SRCDIR/serialhandler.cpp $SRCDIR/SocketHandler.cpp $SRCDIR/driveserver.cpp"
  

COMMAND="$COMPILER -std=c++11 main.cpp $SRCFILES -I/usr/local/include -I/usr/include "-I$SRCDIR"  \
$ADDITIONALHEADERS -L/usr/local/lib -L/usr/lib $ADDITIONALLIBS \
-lboost_system -lboost_date_time -lboost_thread-mt \
-lpthread -lsqlite3 -o build/serialtest"

#COMMAND="gcc -o build/sens src/mqttClient.c \
#-I/usr/local/include  "-I$MQQTINCLUDE/" "$MQQTADDITIONAL" \
#-L/usr/local/lib "-L$MQQTINCLUDE/"  -lwiringPi"


echo "*****building*****"
echo ""
echo "$COMMAND"
echo ""
echo "*****************"
$COMMAND

