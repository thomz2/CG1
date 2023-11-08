all:
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2m -lSDL2