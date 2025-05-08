@echo off
echo Compilando o sistema de estoque...

:: Cria a pasta build caso n�o exista
if not exist build (
    mkdir build
)

:: Compila todos os arquivos necess�rios
g++ -Wall -std=c++17 -Isrc -Iinclude ^
src\main.cpp src\Produto.cpp src\Usuario.cpp src\GerenteEstoque.cpp ^
-o build\sistema-estoque.exe

:: Verifica se houve erro
if %errorlevel% neq 0 (
    echo Houve um erro na compila��o.
) else (
    echo Compila��o conclu�da com sucesso!
    echo Execut�vel gerado: build\sistema-estoque.exe
)

pause