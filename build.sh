#!/bin/bash

echo "Compilando o sistema de estoque em C++..."
mkdir -p build

g++ -Wall -std=c++17 -Isrc -Iinclude \
src/main.cpp src/Produto.cpp src/Usuario.cpp src/GerenteEstoque.cpp \
-o build/sistema-estoque

if [ $? -eq 0 ]; then
    echo "Compilação concluída com sucesso!"
    echo "Executável gerado: build/sistema-estoque"
    echo "Para executar, digite: ./build/sistema-estoque"
else
    echo "Erro na compilação."
fi