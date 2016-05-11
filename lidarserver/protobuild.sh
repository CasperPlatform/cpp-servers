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

SRCFILES="$SRCDIR/rosproto.cpp"


COMMAND="g++ $SRCFILES -o build/hello_world_node \
-I/opt/ros/hydro/include -L/opt/ros/hydro/lib -Wl,-rpath,/opt/ros/hydro/lib\
-lroscpp -lrosconsole -lrostime"

#COMMAND="gcc -o build/sens src/mqttClient.c \
#-I/usr/local/include  "-I$MQQTINCLUDE/" "$MQQTADDITIONAL" \
#-L/usr/local/lib "-L$MQQTINCLUDE/"  -lwiringPi"


echo "*****building*****"
echo ""
echo "$COMMAND"
echo ""
echo "*****************"
$COMMAND