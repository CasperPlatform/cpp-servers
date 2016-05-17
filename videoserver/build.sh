cd $(dirname $0)

SRCDIR="${PWD}/src"

echo $SRCDIR

if [ ! -d "$SRCDIR" ]; then
    echo "SRC-DIR Missing"
    exit 1
fi

SRCFILES="$SRCDIR/videoserver.cpp $SRCDIR/sockethandler.cpp $SRCDIR/camerahandler.cpp"

COMMAND="g++ -std=c++11 main.cpp $SRCFILES -I/usr/local/include -I/usr/include -I/usr/local -I$SRCDIR \
 -lsqlite3 -ljpeg -lboost_system -lboost_thread-mt -lpthread -lraspicam -lmmal -lmmal_core -lmmal_util \
 -L/usr/local/lib -L/usr/lib -L/opt/vc/lib -L/usr/local/Cellar/boost/1.59.0/lib -o build/videoserver"

echo "*****building*****"
echo ""
echo "$COMMAND"
echo ""
echo "*****************"
$COMMAND