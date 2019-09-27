RPM_OPT_FLAGS ?= -O2 -g -Wall
STD = -std=gnu11 -D_GNU_SOURCE
COMPILE = $(CC) $(RPM_OPT_FLAGS) $(STD)
all: hashline collisions.list
hashline: hashline.c xxHash/xxh3.h
	$(COMPILE) -IxxHash $< -o $@
collisions.list: hashline elfsym0u.zst
	zstd -d <elfsym0u.zst |./hashline | \
	sort -u     |awk -F'\t' '{print$$2"\t"$$1}' | \
	uniq -D -f1 |awk -F'\t' '{print$$2"\t"$$1}' >$@
