#!/bin/bash

# MQQTINCLUDE="/home/pi/wiringpi/mqtt_client/sensorlib/include"
# MQQTADDITIONAL="$MQQTINCLUDE/MQTTConnectClient.c $MQQTINCLUDE/MQTTConnectServer.c \
# $MQQTINCLUDE/MQTTPacket.c $MQQTINCLUDE/MQTTSerializePublish.c \
# $MQQTINCLUDE/MQTTSubscribeServer.c $MQQTINCLUDE/MQTTDeserializePublish.c \
# $MQQTINCLUDE/MQTTSubscribeClient.c \
# $MQQTINCLUDE/MQTTUnsubscribeServer.c $MQQTINCLUDE/MQTTUnsubscribeClient.c \
# $MQQTINCLUDE/transport.c"

cd $(dirname $0)

SRCDIR="${PWD}/src"

echo $SRCDIR



if [ ! -d "$SRCDIR" ]; then
    echo "SRC-DIR Missing"
    exit 1
fi

SRCFILES="$SRCDIR/serialhandler.cpp $SRCDIR/SocketHandler.cpp $SRCDIR/driveserver.cpp"


COMMAND="g++ -std=c++11 main.cpp $SRCFILES -I/usr/local/include -I/usr/include "-I$SRCDIR"  \
-lboost_system -lboost_date_time -lboost_thread-mt \
-lpthread -lsqlite3 -L/usr/local/lib -L/usr/lib -o build/serialtest"

#COMMAND="gcc -o build/sens src/mqttClient.c \
#-I/usr/local/include  "-I$MQQTINCLUDE/" "$MQQTADDITIONAL" \
#-L/usr/local/lib "-L$MQQTINCLUDE/"  -lwiringPi"


echo "*****building*****"
echo ""
echo "$COMMAND"
echo ""
echo "*****************"
$COMMAND

