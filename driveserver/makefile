CC = g++

SRCDIR="${PWD}/src"

BASE_FLAGS = -wAll

SRCFILES="$SRCDIR/serialhandler.cpp"

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR HEADERS
LDFLAGS = -I/usr/local/include -I/opt/local/include

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR LIB FILES
LLIBFLAGS = -L/usr/local/Cellar/boost/1.50.0/

# SPECIFIY LINK OPTIONS
LINKFLAGS = -l boost_thread-mt -lboost_system

# FINAL FLAGS -- TO BE USED THROUGHOUT
FLAGS = $(BASE_FLAGS) $(LLIBFLAGS) $(LDFLAGS) $(LINKFLAGS)




# NOTE FOR BOOST -- YOU ONLY NEED TO INCLUDE THE PATH BECAUSE IT ONLY INSTALLS HEADER FILES
main: main.cpp
    $(CC) $(FLAGS) -o main.out main.cpp
