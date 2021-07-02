all:
	./test
	g++ main.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o test
	
curve: 
	g++ testCurve.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o c1
	./c1
	
curve2:
	g++ main2.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o c2
	./c2
	
clean:
	rm test c1 c2
