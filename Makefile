OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cjt_Clusters.o Cluster.o Cjt_Especies.o Especie.o 
	g++ -o program.exe *.o $(OPCIONS) 

Cjt_Clusters.o: Cjt_Clusters.cc Cjt_Clusters.hh Cluster.hh
	g++ -c Cjt_Clusters.cc $(OPCIONS) 

Cluster.o: Cluster.cc Cluster.hh 
	g++ -c Cluster.cc $(OPCIONS) 

Cjt_Especies.o: Cjt_Especies.cc Cjt_Especies.hh Cjt_Clusters.hh
	g++ -c Cjt_Especies.cc $(OPCIONS) 

Especie.o: Especie.cc Especie.hh
	g++ -c Especie.cc $(OPCIONS) 

program.o: program.cc Cjt_Especies.hh
	g++ -c program.cc $(OPCIONS) 

clean:
	rm -f *.o
	rm -f *.exe
