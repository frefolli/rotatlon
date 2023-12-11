EXE=./builddir/main.exe

@all: ${EXE}

${EXE}: include/rotatlon/*.hh src/*.cc
	meson setup builddir
	ninja -C builddir

run: ${EXE}
	${EXE}

clean:
	ninja -C builddir clean

depclean:
	rm -r builddir
