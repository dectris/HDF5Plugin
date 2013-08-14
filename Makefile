CFLAGS = -fPIC -g -O3 -std=c99
CC = gcc
# install directory of HDF5 1.8.11 #
HDF5_INSTALL = /home/det/hdf5-1.8.11/hdf5/
MAJOR = 0
MINOR = 2
NAME1 = h5zlz4
VERSION = $(MAJOR).$(MINOR)


INCLUDES = -I./ -I$(HDF5_INSTALL)/include 

lib: lib$(NAME1).so.$(VERSION)

$(NAME1).o: $(NAME1).c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(NAME1).c 

lz4.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c lz4.c


lib$(NAME1).so.$(VERSION): $(NAME1).o lz4.o
	#$(CC) -shared -Wl,soname,lib$(NAME1).so.$(MAJOR) $^ -o $@ 
	$(CC) -shared  $^ -o $@ 
	ln -sf lib$(NAME1).so.$(VERSION) lib$(NAME1).so
	ln -sf lib$(NAME1).so.$(VERSION) lib$(NAME1).so.$(MAJOR)
clean:
	$(RM) *.o *.so*

distclean:		
	$(RM) *.o *.so*