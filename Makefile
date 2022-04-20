CC := gcc
CLIBS := `sdl2-config --libs` -lSDL2_ttf -lm
CFLAGS := `sdl2-config --cflags` -Wall -Wshadow -pedantic -ansi -std=c99 -O3
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

TARGET := menu

.PHONY: all clean

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(CLIBS) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CLIBS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
