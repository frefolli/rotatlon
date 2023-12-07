EXE=./builddir/main.exe

@all: ${EXE}

${EXE}: src/*.cc
	meson setup builddir
	ninja -C builddir

run: ${EXE}
	${EXE}

clean:
	ninja -C builddir clean

depclean:
	rm -r builddir
