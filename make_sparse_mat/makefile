gcc_options = -std=c++17 -Wall --pedantic-errors
l_b = -llapacke -lblas

program : make_mat_main.o make_dns_mat.o make_coo_mat.o
		g++ -o $@ $^ $(l_b)

make_mat_main.o : make_mat_main.cpp
		g++ -c $< $(l_b)

make_dns_mat.o : make_dns_mat.cpp
		g++ -c $< $(l_b)

make_coo_mat.o : make_coo_mat.cpp
		g++ -c $< $(l_b)

run : program
		./program

clean:
		rm -f ./program

.PHONY : run clean