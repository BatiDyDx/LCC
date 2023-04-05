CC = gcc
CFLAGS = -Wall -Wextra -Werror

BIN = bin

%: %.c
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

.PHONY: clean
clean:
	@rm -r $(BIN) 2> /dev/null || true

