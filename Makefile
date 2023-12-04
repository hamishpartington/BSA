CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 #-Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: driverbsa_s driverbsa fibmemo sieve_s isfactorial # extfibmemo_s

driverbsa_s: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa_s -I./Alloc $(SANITIZE)

driverbsa: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa -I./Alloc $(PRODUCTION)

driverbsa_v: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa_v -I./Alloc $(VALGRIND)

fibmemo: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo -I./Alloc $(PRODUCTION)

fibmemo_s: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo_s -I./Alloc $(SANITIZE)

isfactorial: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) isfactorial.c Alloc/alloc.c -o isfactorial -I./Alloc $(PRODUCTION)

isfactorial_s: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) isfactorial.c Alloc/alloc.c -o isfactorial_s -I./Alloc $(SANITIZE)

sieve: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve -I./Alloc $(PRODUCTION)

sieve_s: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve_s -I./Alloc $(SANITIZE)

sieve_v: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve_v -I./Alloc $(VALGRIND)

## Only if you do an extension. Uncomment in all, extfibmemo_s and run.
extfibmemo_s: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o extfibmemo_s -I./Extension $(SANITIZE)

run: driverbsa fibmemo sieve isfactorial # extfibmemo
	./driverbsa
	./isfactorial
	./fibmemo
	./sieve
	#./extfibmemo

run_s: driverbsa_s fibmemo_s sieve_s isfactorial_s # extfibmemo_s
	./driverbsa_s
	./isfactorial_s
	./fibmemo_s
	./sieve_s
	#./extfibmemo_s

clean:
	rm -f driverbsa_s driverbsa fibmemo extfibmemo_s isfactorial sieve_s
