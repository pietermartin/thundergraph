# Makefile for liblmdb (Lightning memory-mapped database library).

########################################################################
# Configuration. The compiler options must enable threaded compilation.
#
# Preprocessor macros (for CPPFLAGS) of interest...
# Note that the defaults should already be correct for most
# platforms; you should not need to change any of these.
# Read their descriptions in mdb.c if you do:
#
# - MDB_USE_POSIX_SEM
# - MDB_DSYNC
# - MDB_FDATASYNC
# - MDB_USE_PWRITEV
#
# There may be other macros in mdb.c of interest. You should
# read mdb.c before changing any of them.
#
CC	= gcc
W	= -W -Wall -Wno-unused-parameter -Wbad-function-cast
THREADS = -pthread
OPT = -O2 -g
CFLAGS	= $(THREADS) $(OPT) $(W) $(XCFLAGS)
LDLIBS	= 
SOLIBS	=
prefix	= /usr/local
IFLAGS  = -I/usr/lib/jvm/java-7-openjdk-amd64/include

########################################################################

IHDRS	= lmdb.h
ILIBS	= libglmdb_jni.a libglmdb_jni.so
IPROGS	= mdb_stat mdb_copy mtest4 delete_edge_test test_get_first_next_vertex test_get_firstedge_nextedge_for_label_vertex
#mtest
#mtest2 mtest3 mtest4 mtest_persist_sequence mtest_property_key_db mtest2_property_key_db
IDOCS	= mdb_stat.1 mdb_copy.1
PROGS	= $(IPROGS) 
all:	$(ILIBS) $(PROGS)
	cp libglmdb_jni.so ../../../target/classes 

install: $(ILIBS) $(IPROGS) $(IHDRS)
	for f in $(IPROGS); do cp $$f $(DESTDIR)$(prefix)/bin; done
	for f in $(ILIBS); do cp $$f $(DESTDIR)$(prefix)/lib; done
	for f in $(IHDRS); do cp $$f $(DESTDIR)$(prefix)/include; done
	for f in $(IDOCS); do cp $$f $(DESTDIR)$(prefix)/man/man1; done

clean:
	rm -rf $(PROGS) *.[ao] *.so *~ testdb
	mkdir testdb

test:	all
	mkdir testdb
	./mtest && ./mdb_stat testdb

libglmdb_jni.a:	glmdb_jni.o thundergraph_string.o thundergraph_int.o thundergraph_long.o thundergraph_float.o \
thundergraph_double.o thundergraph_boolean.o thundergraph_short.o thundergraph_char.o thundergraph_byte.o thundergraph_generic.o mdb.o midl.o
	ar rs $@ glmdb_jni.o thundergraph_string.o thundergraph_int.o thundergraph_long.o thundergraph_float.o thundergraph_double.o \
	thundergraph_boolean.o thundergraph_short.o thundergraph_char.o thundergraph_byte.o thundergraph_generic.o mdb.o midl.o

libglmdb_jni.so:	glmdb_jni.o thundergraph_string.o thundergraph_int.o thundergraph_long.o thundergraph_float.o \
thundergraph_double.o thundergraph_boolean.o thundergraph_short.o thundergraph_char.o thundergraph_byte.o thundergraph_generic.o mdb.o midl.o
	$(CC) $(LDFLAGS) -pthread -shared -o $@ glmdb_jni.o thundergraph_string.o thundergraph_int.o thundergraph_long.o \
	thundergraph_float.o thundergraph_double.o thundergraph_boolean.o thundergraph_short.o thundergraph_char.o thundergraph_byte.o thundergraph_generic.o mdb.o midl.o $(SOLIBS)

liblmdb.a:	mdb.o midl.o
	ar rs $@ mdb.o midl.o

mdb_stat: mdb_stat.o liblmdb.a
mdb_copy: mdb_copy.o liblmdb.a
#mtest:    mtest.o    liblmdb.a
#mtest2:	  mtest2.o   liblmdb.a
#mtest3:	  mtest3.o   liblmdb.a
#mtest4:	  mtest4.o liblmdb.a
#mtest_persist_sequence:  mtest_persist_sequence.o liblmdb.a 
#mtest_property_key_db:   mtest_property_key_db.o liblmdb.a
#mtest2_property_key_db:  mtest2_property_key_db.o liblmdb.a
mtest4:   mtest4.o libglmdb_jni.a liblmdb.a
delete_edge_test:	delete_edge_test.o libglmdb_jni.a liblmdb.a
test_get_first_next_vertex:   test_get_first_next_vertex.o libglmdb_jni.a liblmdb.a
test_get_firstedge_nextedge_for_label_vertex: test_get_firstedge_nextedge_for_label_vertex.o libglmdb_jni.a liblmdb.a

glmdb_jni.o: glmdb_jni.c glmdb_jni.h thundergraph_structs.h thundergraph_string.c thundergraph_string.h \
thundergraph_int.c thundergraph_int.h thundergraph_long.c thundergraph_long.h thundergraph_float.c thundergraph_float.h \
thundergraph_double.c thundergraph_double.h thundergraph_boolean.c thundergraph_boolean.h thundergraph_short.c thundergraph_short.h \
thundergraph_char.c thundergraph_char.h thundergraph_byte.c thundergraph_byte.h thundergraph_generic.c thundergraph_generic.h mdb.c lmdb.h midl.h
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c glmdb_jni.c

thundergraph_string.o: thundergraph_string.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_string.c

thundergraph_int.o: thundergraph_int.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_int.c

thundergraph_long.o: thundergraph_long.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_long.c

thundergraph_double.o: thundergraph_double.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_double.c

thundergraph_boolean.o: thundergraph_boolean.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_boolean.c

thundergraph_short.o: thundergraph_short.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_short.c

thundergraph_char.o: thundergraph_char.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_char.c

thundergraph_byte.o: thundergraph_byte.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_byte.c

thundergraph_float.o: thundergraph_float.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_float.c

thundergraph_generic.o: thundergraph_generic.c
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c thundergraph_generic.c

mdb.o: mdb.c lmdb.h midl.h
	$(CC) $(CFLAGS) -fPIC $(CPPFLAGS) -c mdb.c

midl.o: midl.c midl.h
	$(CC) $(CFLAGS) -fPIC $(CPPFLAGS) -c midl.c

%:	%.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o:	%.c lmdb.h
	$(CC) $(CFLAGS) $(IFLAGS)  $(CPPFLAGS) -c $<
