SRCDIR=/src/ros
DRIVEDIR=$(SRCDIR)/driveserver
CC   = g++
SRC += $(LIDARDIR)/main.cpp 

TARGET = $(LIDARDIR)/build/driveserver

LIBRARY += boost_system
LIBRARY += boost_date_time
LIBRARY += boost_thread
LIBRARY += pthread
LIBRARY += roscpp
LIBRARY += rosconsole
LIBRARY += rostime
LIBRARY += sqlite3
#LIBRARY += sqlite3


LIBRARYDIR += /usr/lib
LIBRARYDIR += /usr/lib/arm-linux-gnueabihf
LIBRARYDIR += /lib




#NCLUDEDIR += $(SRCDIR)/src
INCLUDEDIR += /usr/include
INCLUDEDIR += $(DRIVEDIR)/src


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
	$(CC) $(SRC) -o $(TARGET) $(INCDIR) $(LIBDIR) $(LINKDIR) $(LIB) 

clean:
	rm -rf $(TARGET)
