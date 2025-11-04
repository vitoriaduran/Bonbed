# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Iinclude

# Bibliotecas
LIBS = -lraylib -lm

# Diretórios
SRC = src
BIN = bonded

# Lista todos os arquivos .c da pasta src
SRCS = $(wildcard $(SRC)/*.c)

# Cria os arquivos .o correspondentes
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(BIN)

# Como compilar o executável
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LIBS)

# Para rodar o programa
run: $(BIN)
	./$(BIN)

# Para limpar arquivos compilados
clean:
	rm -f $(SRC)/*.o $(BIN)

