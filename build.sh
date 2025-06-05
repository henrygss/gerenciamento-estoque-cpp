#!/bin/bash

# Caminho dos arquivos-fonte e cabeçalhos
SRC_DIR="src"
INCLUDE_DIR="include"
BIN_DIR="bin"

# Nome do executável
OUTPUT="$BIN_DIR/Teste3_GerenciamentoEstoque"

# Cria a pasta bin se não existir
mkdir -p "$BIN_DIR"

# Compila todos os .cpp
g++ -std=c++17 "$SRC_DIR"/*.cpp -I"$INCLUDE_DIR" -o "$OUTPUT"

# Permissão de execução
chmod +x "$OUTPUT"

echo "Compilação concluída! Executável gerado em: $OUTPUT"