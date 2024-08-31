AN = proj4
SHELL = /bin/bash
CWD = $(shell pwd | sed 's/.*\///g')
HOST = $(shell echo $$HOSTNAME | grep 'kh1262-[0-9][0-9]')
CPU = $(shell lscpu | grep 'i7-7700')
CC = gcc
CFLAGS = -Wall -Werror -O1 -g

.PHONY: all clean zip test

all: matrix_main matmul_main

matrix_main: matrix_main.c matrix_funcs.o matrix_funcs_student.o
	$(CC) $(CFLAGS) -o $@ $^

matmul_main: matmul_main.c matrix_funcs.o matrix_funcs_student.o \
	matmul.o matmul_student.o
	$(CC) $(CFLAGS) -o $@ $^

matrix_funcs.o: matrix_funcs.c matrix.h
	$(CC) $(CFLAGS) -c matrix_funcs.c

matrix_funcs_student.o: matrix_funcs_student.c matrix.h
	$(CC) $(CFLAGS) -c matrix_funcs_student.c

matmul.o: matmul.c matrix.h
	$(CC) $(CFLAGS) -c matmul.c

matmul_student.o: matmul_student.c
	$(MAKE) -f Makefile_matmul $@

test: matrix_main
	@echo "------Running speed test with nicely sized matrix------"
	@./matrix_main --even | tee evenResults.txt
	@echo "------Running speed test with oddly-sized matrix------"
	@./matrix_main --odd | tee nonEvenResults.txt
	@cat evenResults.txt nonEvenResults.txt | grep '^Ratio' > ratios.txt

testmul: matmul_main
	@./matmul_main 2357 3001 1693 | tee matmul.txt

clean:
	rm -f *.o *.gch matrix_main matmul_main

clean-results:
	rm -f ratios.txt evenResults.txt nonEvenResults.txt matmul.txt

zip: test testmul clean
	@if [[ "$(HOST)" == "" ]]; then echo "ERROR: It appears that you are not running this on a kh1262 machine. Please use a kh1262 machine to submit your code."; exit 2; fi
	@if [[ "$(CPU)" == "" ]]; then echo "ERROR: It appears that you are not running this on a machine with an i7-7700 CPU. Plese use a machine with the proper CPU to submit your code".; exit 2; fi
	rm -f $(AN)-code.zip
	zip -r $(AN)-code.zip *
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi
