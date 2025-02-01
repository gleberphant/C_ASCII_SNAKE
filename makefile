# Nome do executável
TARGET = snake

# Arquivos fonte
SRC = snake.c

# Compilador
CC = clang

# Flags de compilação
CFLAGS = -Wall

# Flags de ligação (bibliotecas)
LDFLAGS = -lncurses

# Regra padrão de compilação
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Regra para limpar os arquivos compilados
clean:
	rm -f $(TARGET)
