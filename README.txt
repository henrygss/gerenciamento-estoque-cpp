===============================
SISTEMA DE GERENCIAMENTO DE ESTOQUE
===============================

Este projeto é um sistema de gerenciamento de estoque desenvolvido em C++ que permite o cadastro de produtos e usuários, controle de estoque, login com permissões administrativas, salvamento em arquivos e execução multiplataforma.

------------------------------------
REQUISITOS MÍNIMOS POR SISTEMA OPERACIONAL
------------------------------------

**WINDOWS:**
- Sistema operacional: Windows 10 ou superior
- Compilador: MinGW (g++) ou Visual Studio (já embutido)
- Terminal: CMD, PowerShell ou Git Bash

**LINUX:**
- Distribuição: Qualquer baseada em Unix (Ubuntu, Fedora, etc)
- Compilador: g++
- Terminal: Bash

**macOS:**
- macOS 10.14 ou superior
- Compilador: g++ (via Xcode Command Line Tools)
- Terminal: Terminal padrão (bash/zsh)

-------------------
INSTRUÇÕES DE USO
-------------------

# WINDOWS

1. Acesse a pasta 'bin/'.
2. Dê um duplo clique no arquivo 'build.bat' para compilar.
3. Após a compilação, execute 'estoque.exe'.

Caso não tenha o MinGW instalado:
- Instale o [MinGW](https://sourceforge.net/projects/mingw/)
- Adicione o caminho do 'g++' às variáveis de ambiente.

# LINUX

1. Abra o terminal na pasta raiz do projeto.
2. Torne o script executável:
   chmod +x build.sh
3. Compile o projeto:
   ./build.sh
4. Rode o executável:
   ./estoque

# macOS

1. Instale o compilador:
   xcode-select --install
2. No Terminal, navegue até a pasta raiz do projeto.
3. Torne o script executável:
   chmod +x build.sh
4. Compile:
   ./build.sh
5. Rode:
   ./estoque

---------------------
ESTRUTURA DO PROJETO
---------------------

/bin
  - build.bat           # Script de compilação para Windows
  - estoque.exe         # Executável compilado (Windows)

/include
  - *.h                 # Arquivos de cabeçalho das classes

/src
  - *.cpp               # Código-fonte das classes e do main

build.sh                # Script de compilação para Linux/macOS
README.txt              # Arquivo de instruções

----------------------------

Desenvolvido por: Henry Gabriel da Silva
23/05/2025