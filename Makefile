.RECIPEPREFIX := >

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = a.out

SOURCES = main.c create.c display.c inverted.c save.c search.c update.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
>$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c inverted.h
>$(CC) $(CFLAGS) -c $< -o $@

clean:
>rm -f $(OBJECTS) $(TARGET) a.out