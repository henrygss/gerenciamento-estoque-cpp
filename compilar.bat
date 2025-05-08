@echo off
echo Compilando o sistema de estoque...

:: Cria a pasta build caso não exista
if not exist build (
    mkdir build
)

:: Compila todos os arquivos necessários
g++ -Wall -std=c++17 -Isrc -Iinclude ^
src\main.cpp src\Produto.cpp src\Usuario.cpp src\GerenteEstoque.cpp ^
-o build\sistema-estoque.exe

:: Verifica se houve erro
if %errorlevel% neq 0 (
    echo Houve um erro na compilação.
) else (
    echo Compilação concluída com sucesso!
    echo Executável gerado: build\sistema-estoque.exe
)

pause