all:
	g++ main.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o test

clean:
	rm test
