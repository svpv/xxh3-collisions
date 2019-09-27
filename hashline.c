#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <xxh3.h>

int main()
{
    char *line = NULL;
    size_t alloc = 0;
    while (1) {
	ssize_t len = getline(&line, &alloc, stdin);
	if (len < 0)
	    break;
	// Mandatory newline, no empty lines.
	assert(len > 1);
	len--;
	assert(line[len] == '\n');
	// Prefix the line with its hash.
	XXH128_hash_t h = XXH128(line, len, 0);
	printf("%016" PRIx64 "%016" PRIx64 "\t", h.high64, h.low64);
	fwrite_unlocked(line, 1, len + 1, stdout);
    }
    free(line);
    return 0;
}
