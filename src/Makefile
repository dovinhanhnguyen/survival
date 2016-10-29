CC = g++
CCSW = -O3 -Wno-deprecated-declarations
PLATFORM = `uname`

survival: graphics.o
	@if [ ${PLATFORM} = "Linux" ]; \
	then $(CC) -o survival graphics.o ${CCSW} -lGL -lGLU -lglut -lSOIL; \
	echo Linking for Linux; \
	elif [ ${PLATFORM} = "Darwin" ]; \
	then $(CC) -o survival graphics.o ${CCSW} -lSOIL -framework GLUT -framework OpenGL; \
	echo Linking for Mac OS X; \
	fi

graphics.o: graphics.h

.cpp.o:
	$(CC) ${CCSW} -c $<

clean:
	echo cleaning up; /bin/rm -f core *.o survival

all:	survival

