CC = gcc
CFLAGS = -std=gnu99 -Wall -g -pthread
OBJS = list.o threadpool.o main.o
EXEC = sort random_num input.txt caculate output.txt random_num exe_time.txt runtime.png

.PHONY: all clean test

GIT_HOOKS := .git/hooks/pre-commit

all: $(GIT_HOOKS) sort

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

deps := $(OBJS:%.o=.%.o.d)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -MMD -MF .$@.d -c $<

sort: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -rdynamic

random_num: random_num.c
	$(CC) $(CFLAGS) $^ -o $@

input.txt:random_num
	./random_num $ 10000

bench: input.txt
	for i in 1 2 4 8 16 32 64; do \
    	while read line;do \
			echo $$line ; \
    done < input.txt  | ./sort $$i $ 10000 ;\
    done
	
caculate: caculate.c
	$(CC) $(CFLAGS) $^ -o $@

output.txt: input.txt caculate
	for i in `seq 1 100` ; do \
		for j in 1 2 4 8 16 32 64; do \
    		while read line; do \
				echo $$line ; \
    		done < input.txt  | ./sort $$j $ 10000 ;\
    done  ; \
    done && ./caculate


plot: output.txt
	gnuplot scripts/runtime.gp

clean:
	rm -f $(OBJS)  $(EXEC)
	@rm -rf $(deps)

-include $(deps)
