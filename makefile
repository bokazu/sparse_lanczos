gcc_options = -std=c++17 -Wall --pedantic-errors
l_b = -llapacke -lblas -lcblas

program : main.o printmat.o sparse_lanczos.o gso.o inputdata.o sparse_dgemv.o vec_Initialize.o eigenvec.o
	g++ -o $@ $^ $(l_b)

main.o : main.cpp
	g++ -c $< $(l_b)

printmat.o : printmat.cpp
	g++ -c $< $(l_b)

sparse_lanczos.o : sparse_lanczos.cpp
	g++ -c $< $(l_b)

gso.o : gso.cpp
	g++ -c $< $(l_b)

inputdata.o : inputdata.cpp
	g++ -c $< $(l_b)

sparse_dgemv.o : sparse_dgemv.cpp
	g++ -c $< $(l_b)

vec_Initialize.o : vec_Initialize.cpp
	g++ -c $< $(l_b)

eigenvec.o : eigenvec.cpp
	g++ -c $< $(l_b)

run : program
	./program

clean:
	rm -f ./program

.PHONY : run clean
