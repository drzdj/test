CC=g++
OBJECT=ret

$(OBJECT) : 
	$(CC) main.cpp -o $(OBJECT) -std=c++11
clean:
	@rm -f $(OBJECT) f_*_*