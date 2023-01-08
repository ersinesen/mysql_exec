INCDIR := $(shell mysql_config --cxxflags) 
LIBDIR := $(shell mysql_config --libs)

mysql_exec:
	gcc -shared -fPIC $(INCDIR) mysql_exec.c $(LIBDIR) -o mysql_exec.so


