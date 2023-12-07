CC=gcc
PG= -fno-inline-small-functions -pg
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: driverbsa_s driverbsa fibmemo sieve_s isfactorial

driverbsa_s: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa_s -I./Alloc $(SANITIZE)

extdriverbsa_s: bsa.h Extension/specific.h Extension/extension.c extdriver.c
	$(CC) extdriver.c Extension/extension.c  -o extdriverbsa_s -I./Extension $(SANITIZE)

extdriverbsa: bsa.h Extension/specific.h Extension/extension.c extdriver.c
	$(CC) extdriver.c Extension/extension.c  -o extdriverbsa -I./Extension $(PRODUCTION)

extdriverbsa_v: bsa.h Extension/specific.h Extension/extension.c extdriver.c
	$(CC) extdriver.c Extension/extension.c  -o extdriverbsa_v -I./Extension $(VALGRIND)

driverbsa: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa -I./Alloc $(PRODUCTION)

driverbsa_prof: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) $(PG) driver.c Alloc/alloc.c -o driverbsa_prof -I./Alloc $(COMMON)

driverbsa_v: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa_v -I./Alloc $(VALGRIND)

fibmemo: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo -I./Alloc $(PRODUCTION)

fibmemo_s: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo_s -I./Alloc $(SANITIZE)

fibmemo_v: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo_v -I./Alloc $(VALGRIND)

fibmemo_prof: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) $(PG) fibmemo.c Alloc/alloc.c -o fibmemo_prof -I./Alloc $(COMMON)

isfactorial: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) isfactorial.c Alloc/alloc.c -o isfactorial -I./Alloc $(PRODUCTION)

isfactorial_prof: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) $(PG) isfactorial.c Alloc/alloc.c -o isfactorial_prof -I./Alloc $(COMMON)

isfactorial_s: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) isfactorial.c Alloc/alloc.c -o isfactorial_s -I./Alloc $(SANITIZE)

isfactorial_v: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) isfactorial.c Alloc/alloc.c -o isfactorial_v -I./Alloc $(VALGRIND)

sieve: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve -I./Alloc $(PRODUCTION)

sieve_s: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve_s -I./Alloc $(SANITIZE)

sieve_v: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve_v -I./Alloc $(VALGRIND)

extfibmemo_s: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o extfibmemo_s -I./Extension $(SANITIZE)

extfibmemo_prof: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) $(PG) fibmemo.c Extension/extension.c -o extfibmemo_prof -I./Extension $(COMMON)

extfibmemo: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o extfibmemo -I./Extension $(PRODUCTION)

extfibmemo_v: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o extfibmemo_v -I./Extension $(VALGRIND)

extsieve: bsa.h Extension/specific.h Extension/extension.c sieve.c
	$(CC) sieve.c Extension/extension.c -o extsieve -I./Extension $(PRODUCTION)

extsieve_s: bsa.h Extension/specific.h Extension/extension.c sieve.c
	$(CC) sieve.c Extension/extension.c -o extsieve_s -I./Extension $(SANITIZE)

extsieve_v: bsa.h Extension/specific.h Extension/extension.c sieve.c
	$(CC) sieve.c Extension/extension.c -o extsieve_v -I./Extension $(VALGRIND)

extisfactorial: bsa.h Extension/specific.h Extension/extension.c isfactorial.c
	$(CC) isfactorial.c Extension/extension.c -o extisfactorial -I./Extension $(PRODUCTION)

extisfactorial_s: bsa.h Extension/specific.h Extension/extension.c isfactorial.c
	$(CC) isfactorial.c Extension/extension.c -o extisfactorial_s -I./Extension $(SANITIZE)

extisfactorial_v: bsa.h Extension/specific.h Extension/extension.c isfactorial.c
	$(CC) isfactorial.c Extension/extension.c -o extisfactorial_v -I./Extension $(VALGRIND)

run: driverbsa fibmemo sieve isfactorial extfibmemo
	time ./driverbsa
	time ./fibmemo
	time ./sieve
	time ./isfactorial

run_s: driverbsa_s fibmemo_s sieve_s isfactorial_s
	./driverbsa_s
	./fibmemo_s
	./sieve_s
	./isfactorial_s

run_v: driverbsa_v fibmemo_v sieve_s isfactorial_v
	valgrind ./driverbsa_v
	valgrind ./fibmemo_v
	valgrind ./sieve_v
	valgrind ./isfactorial_v

run_ext: extdriverbsa extfibmemo extsieve extisfactorial
	time ./extdriverbsa
	time ./extfibmemo
	time ./extsieve
	time ./extisfactorial

run_ext_s: extdriverbsa_s extfibmemo_s extsieve_s extisfactorial_s
	./extdriverbsa_s
	./extfibmemo_s
	./extsieve_s
	./extisfactorial_s

run_ext_v: extdriverbsa_v extfibmemo_v extsieve_v extisfactorial_v
	valgrind ./extdriverbsa_v
	valgrind ./extfibmemo_v
	valgrind ./extsieve_v
	valgrind ./extisfactorial_v

clean:
	rm -f extdriverbsa_v extfibmemo_v extsieve_v extisfactorial_v extdriverbsa_s extfibmemo_s extsieve_s extisfactorial_s extdriverbsa extfibmemo extsieve extisfactorial extdriverbsa extfibmemo extsieve extisfactorial driverbsa_v fibmemo_v sieve_s isfactorial_v driverbsa_s fibmemo_s sieve_s isfactorial_s driverbsa fibmemo sieve isfactorial extfibmemo
