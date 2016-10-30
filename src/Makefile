CC = g++
CCSW = -O3 -Wno-deprecated-declarations
PLATFORM = `uname`

survival: graphics.o player_class.o
	@if [ ${PLATFORM} = "Linux" ]; \
	then $(CC) -o survival graphics.o player_class.o ${CCSW} -lGL -lGLU -lglut -lSOIL; \
	echo Linking for Linux; \
	elif [ ${PLATFORM} = "Darwin" ]; \
	then $(CC) -o survival graphics.o player_class.o ${CCSW} -lSOIL -framework GLUT -framework OpenGL -framework CoreFoundation; \
	echo Linking for Mac OS X; \
	else $(CC) -o survival graphics.o player_class.o ${CCSW} -lglut32 -lglu32 -lopengl32 -lSOIL; \
	echo Linking for Cygwin; \
	fi

graphics.o: graphics.h player_class.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o survival

all:	survival

