CC = gcc
CFLAGS = -Wall -Wextra -g

# Kaynak dosyaları
SRCDIR = src
INCLUDEDIR = include
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,lib/%.o,$(SRCS))

# Derlenmiş dosyalar
BINDIR = bin
TARGET = main.exe

# Derleme kuralı
$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Nesne dosyaları oluşturma kuralı
lib/%.o: $(SRCDIR)/%.c
	@mkdir lib 2>/dev/null || :
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDEDIR)

.PHONY: run clean all

all: run

run: $(BINDIR)/$(TARGET)
	./$(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJS) $(BINDIR)/$(TARGET)
