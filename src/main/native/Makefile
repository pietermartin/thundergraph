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
IPROGS	= mdb_stat mdb_copy mtest_string_index_db
#mtest mtest2 mtest3 mtest4 mtest_persist_sequence mtest_property_key_db mtest2_property_key_db
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

libglmdb_jni.a:	glmdb_jni.o mdb.o midl.o
	ar rs $@ glmdb_jni.o mdb.o midl.o

libglmdb_jni.so:	glmdb_jni.o mdb.o midl.o
	$(CC) $(LDFLAGS) -pthread -shared -o $@ glmdb_jni.o mdb.o midl.o $(SOLIBS)

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
mtest_string_index_db:   mtest_string_index_db.o liblmdb.a

glmdb_jni.o: glmdb_jni.c glmdb_jni.h mdb.c lmdb.h midl.h
	$(CC) $(CFLAGS) -fPIC $(IFLAGS) $(CPPFLAGS) -c glmdb_jni.c

mdb.o: mdb.c lmdb.h midl.h
	$(CC) $(CFLAGS) -fPIC $(CPPFLAGS) -c mdb.c

midl.o: midl.c midl.h
	$(CC) $(CFLAGS) -fPIC $(CPPFLAGS) -c midl.c

%:	%.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o:	%.c lmdb.h
	$(CC) $(CFLAGS) $(IFLAGS)  $(CPPFLAGS) -c $<
