SRCDIR=/files/src/buildsrc/driveserver/src
ARM_PREFIX= arm-linux-gnueabihf-
CC   = $(ARM_PREFIX)g++
SRC += $(SRCDIR)/serialhandler.cpp 
SRC += $(SRCDIR)/SocketHandler.cpp 
SRC += $(SRCDIR)/driveserver.cpp
TARGET = driveserver

LIBRARY += boost_system
LIBRARY += boost_date_time
LIBRARY += boost_thread-mt
LIBRARY += pthread
LIBRARY += sqlite3


LIBRARYDIR += /files/src/rpi_src/lib/arm-linux-gnueabihf
LIBRARYDIR += /files/src/rpi_src/usr/lib/arm-linux-gnueabihf
LIBRARYDIR += /files/src/rpi_src/lib
LIBRARYDIR += /files/src/rpi_src/usr/lib

XLINK_LIBDIR += /files/src/rpi_src/lib/arm-linux-gnueabihf
XLINK_LIBDIR += /files/src/rpi_src/usr/lib/arm-linux-gnueabihf
XLINK_LIBDIR += /files/src/rpi_src/usr/lib

INCLUDEDIR += $(SRCDIR)
INCLUDEDIR += /files/src/rpi_src/usr/include
INCLUDEDIR += /files/src/rpi_src/usr/include/arm-linux-gnueabihf
# INCLUDEDIR += $(HOME)/rpi/usr/include/atk-1.0
# INCLUDEDIR += $(HOME)/rpi/usr/include/cairo
# INCLUDEDIR += $(HOME)/rpi/usr/include/gdk-pixbuf-2.0
# INCLUDEDIR += $(HOME)/rpi/usr/include/freetype2
# INCLUDEDIR += $(HOME)/rpi/usr/include/glib-2.0
# INCLUDEDIR += $(HOME)/rpi/usr/lib/arm-linux-gnueabihf/glib-2.0/include
# INCLUDEDIR += $(HOME)/rpi/usr/include/pixman-1
# INCLUDEDIR += $(HOME)/rpi/usr/include/libpng12

OPT = -std=c++11
DEBUG = -g
WARN= -Wall
PTHREAD= -pthread

INCDIR  = $(patsubst %,-I%,$(INCLUDEDIR))
LIBDIR  = $(patsubst %,-L%,$(LIBRARYDIR))
LIB    = $(patsubst %,-l%,$(LIBRARY))
XLINKDIR = $(patsubst %,-Xlinker -rpath-link=%,$(XLINK_LIBDIR))

all:
	$(CC) $(OPT) $(DEBUG) $(LIBDIR) $(PTHREAD) $(INCDIR) $(XLINKDIR) -nostartfiles $(LIB) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)
