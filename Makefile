all: bst

bst: bst.cpp
	g++ -o bst bst.cpp
clean:
	rm -f bst