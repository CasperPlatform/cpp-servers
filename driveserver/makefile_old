CC = c++

SRCDIR="${PWD}/src"

BASE_FLAGS = -wAll

SRCFILES="$SRCDIR/serialhandler.cpp $SRCDIR/SocketTest.cpp $SRCDIR/sqlite3.c"

ENTRYPOINT=main.cpp

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR HEADERS
LDFLAGS = -I/usr/local/include -I/opt/local/include -I$(SRCDIR)

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR LIB FILES
LLIBFLAGS = -L/usr/local/lib

# SPECIFIY LINK OPTIONS
LINKFLAGS = -l boost_system boost_date_time boost_thread-mt pthread

# FINAL FLAGS -- TO BE USED THROUGHOUT
FLAGS = $(BASE_FLAGS) $(ENTRYPOINT) $(SRCFILES) $(LDFLAGS) $(LLIBFLAGS) $(LINKFLAGS)




# NOTE FOR BOOST -- YOU ONLY NEED TO INCLUDE THE PATH BECAUSE IT ONLY INSTALLS HEADER FILES
main: main.cpp
    $(CC) main.cpp $(FLAGS) -o build/main 


PROG=driverserver

SRCDIR="${PWD}/src"
SRC=${SRCDIR}/serialhandler.cpp ${SRCDIR}/SocketTest.cpp ${SRCDIR}/serialhandler.cpp

CIVETWEB_LIB_PATH=../articles/a16004
CIVETWEB_INC_PATH=../articles/a16004/include
CIVETWEB_LIB=libcivetweb.a

SQLITE_LIB_PATH=../articles/a16003/build/.libs
SQLITE_INC_PATH=../articles/a16003/build
SQLITE_LIB=libsqlite3.a

JSON_C_LIB_PATH=../articles/a16006/build/install/lib
JSON_C_INC_PATH=../articles/a16006/build/install/include/json-c
JSON_C_LIB=libjson-c.a

CFLAGS=-I${CIVETWEB_INC_PATH} -I${SQLITE_INC_PATH} -I${JSON_C_INC_PATH} -DUSE_WEBSOCKET -DNO_SSL
LIBS=-lpthread ${CIVETWEB_LIB_PATH}/${CIVETWEB_LIB} ${SQLITE_LIB_PATH}/${SQLITE_LIB} ${JSON_C_LIB_PATH}/${JSON_C_LIB}

include $(CIVETWEB_LIB_PATH)/resources/Makefile.in-os

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS)

clean:
	rm -f $(PROG)

.PHONY: all clean