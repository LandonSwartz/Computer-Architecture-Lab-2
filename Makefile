assem: assem.c 	
	gcc -Wall -g -O2 $^ -o $@  
.PHONY: clean 
clean: 	
	rm -rf *.o *~ assem
