SRCDIR=$(PWD)
CC   = g++
SRC += $(SRCDIR)/src/camerahandler.cpp 
SRC += $(SRCDIR)/src/sockethandler.cpp 
SRC += $(SRCDIR)/src/videoserver.cpp 

TARGET = $(SRCDIR)/build/videoserver

LIBRARY += boost_system
LIBRARY += boost_date_time
LIBRARY += boost_thread
LIBRARY += jpeg
LIBRARY += raspicam 
LIBRARY += mmal 
LIBRARY += mmal_core 
LIBRARY += mmal_util
LIBRARY += pthread
LIBRARY += sqlite3
#LIBRARY += sqlite3


LIBRARYDIR += /usr/lib
LIBRARYDIR += /opt/vc/lib
LIBRARYDIR += /usr/local/lib


INCLUDEDIR += $(SRCDIR)/src
INCLUDEDIR += /usr/local
INCLUDEDIR += /usr/local/include
INCLUDEDIR += /usr/include
INCLUDEDIR += $(SRCDIR)/include


OPT = -std=c++11
DEBUG = -g
WARN= -Wall
PTHREAD= -pthread
LINK    = -Wl,-rpath,

INCDIR  = $(patsubst %,-I%,$(INCLUDEDIR))
LIBDIR  = $(patsubst %,-L%,$(LIBRARYDIR))
LIB    = $(patsubst %,-l%,$(LIBRARY))
LINKDIR = $(patsubst %,$(LINK)%,$(LINK_LIBDIR))

all:
	$(CC) $(OPT) $(SRC) -o $(TARGET) $(INCDIR) $(LIBDIR) $(LINKDIR) $(LIB) 

clean:
	rm -rf $(TARGET)