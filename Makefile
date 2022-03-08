all:
	g++ src/interpreter.cpp -o build/linux/scoop-interpreter
	g++ src/file-interpreter.cpp -o build/linux/scoop-file-interpreter
	g++ src/stringToScoop.cpp -o build/linux/string-to-scoop

install:
	cp build/linux/* ~/bin

windows:
	x86_64-w64-mingw32-g++ src/interpreter.cpp -o build/windows/scoop-interpreter.exe
	x86_64-w64-mingw32-g++ src/file-interpreter.cpp -o build/windows/scoop-file-interpreter.exe
	x86_64-w64-mingw32-g++ src/stringToScoop.cpp -o build/windows/string-to-scoop.exe
