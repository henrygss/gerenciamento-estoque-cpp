Sistema de Gerenciamento de Estoque – C++ (Console)

Este sistema permite:
- Login com autenticação por usuário e senha
- Criação de usuários apenas por administradores
- Listagem de todos os usuários criados (apenas administradores)
- Identificação de permissões (administrador ou operador)
- Cadastro de novos produtos com informações 
- Listagem de todos os produtos cadastrados
- Busca de produtos por ID ou nome
- Atualização de entrada e saída de estoque
- Remoção de produtos do sistema (apenas administradores)
- Alerta de estoque abaixo da quantidade mínima definida
- Salvamento e carregamento automático de dados(.txt)
------------------------------------

Como compilar no Windows

1. Clique duas vezes no arquivo:
   compilar.bat

O executável será gerado em:
   build\sistema-estoque.exe

2. Após a compilação, você pode:

- Executar o sistema com duplo clique em:
   build\sistema-estoque.exe

- Ou abrir o terminal na pasta do projeto e digitar:
   ./build/sistema-estoque.exe

------------------------------------

Como compilar no Linux

1. Abra o terminal e navegue até a pasta do projeto

2. Torne o script executável com o comando:
   chmod +x build.sh

3. Compile o sistema com:
   ./build.sh

O executável será gerado em:
   build/sistema-estoque

4. Para executar:
   ./build/sistema-estoque

------------------------------------

Como compilar no macOS

1. Abra o terminal e navegue até a pasta do projeto

2. Verifique se o compilador está instalado utilizando o comando:
   clang++ --version

   Se necessário, instale com:
   xcode-select --install

3. Compile o sistema com:
   clang++ -Wall -std=c++17 -Isrc -Iinclude \
   src/main.cpp src/Produto.cpp src/Usuario.cpp src/GerenteEstoque.cpp \
   -o build/sistema-estoque

4. Para executar:
   ./build/sistema-estoque

5. (Opcional) Use o script:
   chmod +x build.sh
   ./build.sh

------------------------------------

Pastas do projeto

src/       → Arquivos .cpp
include/   → Arquivos de cabeçalho .h
data/      → Produtos.txt e Usuarios.txt
build/     → Executável (.exe no Windows ou binário no Linux)
compilar.bat → Script para compilar no Windows
build.sh   → Script para compilar no Linux
README.txt → Instruções gerais

------------------------------------


Projeto multiplataforma pronto para uso