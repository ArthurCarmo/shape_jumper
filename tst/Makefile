tst_rectangle : t_overlaps.cpp rectangle.o circle.o triangle.o
	g++ t_overlaps.cpp rectangle.o circle.o triangle.o -o tst_overlaps -lGL -lGLU -lglut

rectangle.o : ../rectangle.cpp ../rectangle.h ../line.h ../point.h
	g++ ../rectangle.cpp -lglut -lGL -lGLU -c

circle.o : ../circle.cpp ../circle.h ../line.h ../point.h
	g++ ../circle.cpp -lglut -lGL -lGLU -c
	
triangle.o : ../triangle.cpp ../triangle.h ../line.h ../point.h
	g++ ../triangle.cpp -lglut -lGL -lGLU -c
