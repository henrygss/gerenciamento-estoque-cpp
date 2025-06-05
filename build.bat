@echo off
setlocal

:: Caminhos
set SRC=src
set INCLUDE=include
set BIN=bin

:: Nome do executável
set OUTPUT=%BIN%\Teste3_GerenciamentoEstoque.exe

:: Cria pasta bin se necessário
if not exist %BIN% mkdir %BIN%

:: Compila com cl.exe (Visual Studio Developer Command Prompt deve estar aberto)
cl /EHsc /std:c++17 /I %INCLUDE% %SRC%\*.cpp /Fe:%OUTPUT%

echo Compilação concluída!
pause