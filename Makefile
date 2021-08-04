all:
	g++ main.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o test
	./test
curve: 
	g++ testCurve.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o c1
	./c1
	
curve2:
	g++ main2.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o c2
	./c2
	
testNew:
	g++ main3.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -o main3
	./main3
clean:
	rm test c1 c2
