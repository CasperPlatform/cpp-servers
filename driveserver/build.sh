#!/bin/bash

# MQQTINCLUDE="/home/pi/wiringpi/mqtt_client/sensorlib/include"
# MQQTADDITIONAL="$MQQTINCLUDE/MQTTConnectClient.c $MQQTINCLUDE/MQTTConnectServer.c \
# $MQQTINCLUDE/MQTTPacket.c $MQQTINCLUDE/MQTTSerializePublish.c \
# $MQQTINCLUDE/MQTTSubscribeServer.c $MQQTINCLUDE/MQTTDeserializePublish.c \
# $MQQTINCLUDE/MQTTSubscribeClient.c \
# $MQQTINCLUDE/MQTTUnsubscribeServer.c $MQQTINCLUDE/MQTTUnsubscribeClient.c \
# $MQQTINCLUDE/transport.c"

SRCDIR=src

if [ ! -d "$SRCDIR" ]; then
    echo "SRC-DIR Missing"
    exit 1
fi    

SRCFILES="$SRCDIR/serialhandler.c $SRCDIR/serialhandler.h

COMMAND=g++ -o serialtest main.cpp -I$SRCFILES -lboost_system -lboost_date_time -lboost_thread

COMMAND="g++ -o build/sens src/mqttClient.c \
-I/usr/local/include  "-I$MQQTINCLUDE/" "$MQQTADDITIONAL" \
-L/usr/local/lib "-L$MQQTINCLUDE/"  -lwiringPi"

echo "*****running*****"
echo ""
echo "$COMMAND"
echo ""
echo "*****************"
$COMMAND

