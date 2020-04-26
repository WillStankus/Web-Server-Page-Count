all: filter
	
filter : filter.c 
	gcc -o filter filter.c
	./filter

.PHONY : all clean
clean: 
	rm filter
