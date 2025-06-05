#include <fstream>
#include <algorithm>
#include "GerenteEstoque.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <cwctype>

//M�todo de normalizar texto
std::string NormalizarTexto(const std::string& texto)
{
    try
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(texto);
        std::wstring resultado;

        for (wchar_t c : wide)
        {
            switch (c)
            {
            case L'�': case L'�': case L'�': case L'�': case L'�': c = L'a'; break;
            case L'�': case L'�': case L'�': case L'�': c = L'e'; break;
            case L'�': case L'�': case L'�': case L'�': c = L'i'; break;
            case L'�': case L'�': case L'�': case L'�': case L'�': c = L'o'; break;
            case L'�': case L'�': case L'�': case L'�': c = L'u'; break;
            case L'�': c = L'c'; break;

            case L'�': case L'�': case L'�': case L'�': case L'�': c = L'a'; break;
            case L'�': case L'�': case L'�': case L'�': c = L'e'; break;
            case L'�': case L'�': case L'�': case L'�': c = L'i'; break;
            case L'�': case L'�': case L'�': case L'�': case L'�': c = L'o'; break;
            case L'�': case L'�': case L'�': case L'�': c = L'u'; break;
            case L'�': c = L'c'; break;
            }

            resultado += std::towlower(c);
        }

        return converter.to_bytes(resultado);
    }
    catch (const std::exception& )
    {
        return texto;
    }
}


GerenteEstoque::GerenteEstoque()
{
    UsuarioAtual = nullptr;
    UltimoIDProduto = 0;
    UltimoIDUsuario = 0;
}

// Login
bool GerenteEstoque::Login(const std::string& NomeUsuario, const std::string& Senha)
{
    for (auto& usuario : Usuarios)
    {
        if (usuario.getNomeUsuario() == NomeUsuario && usuario.ChecarSenha(Senha))
        {
            UsuarioAtual = &usuario;
            std::cout << "Login realizado com sucesso.\n";
            return true;
        }
    }
    std::cout << "Usu�rio ou senha incorretos.\n";
    return false;
}

bool GerenteEstoque::Logout()
{
    if (UsuarioAtual != nullptr)
    {
        UsuarioAtual = nullptr;
        std::cout << "Logout realizado.\n";
        return true;
    }
    std::cout << "Nenhum usu�rio est� logado.\n";
    return false;
}

bool GerenteEstoque::CriarUsuario(const std::string& NomeUsuario, const std::string& Senha, bool isAdm)
{
    if (UsuarioAtual == nullptr || !UsuarioAtual->geteAdm())
    {
        std::cout << "Apenas administradores podem criar novos usu�rios.\n";
        return false;
    }
    for (const auto& usuario : Usuarios)
    {
        if (usuario.getNomeUsuario() == NomeUsuario)
        {
            std::cout << "J� existe um usu�rio com esse nome.\n";
            return false;
        }
    }

    int NovoID = GerarProximoIdUsuario();
    Usuario novo(NovoID, NomeUsuario, Senha, isAdm);
    Usuarios.push_back(novo);
    SalvarUsuarios("Usuarios.txt");
    std::cout << "Usu�rio criado com sucesso.\n";
    std::cout << "ID gerado automaticamente. \n";
    return true;
}

//Remover usu�rio
bool GerenteEstoque::RemoverUsuario(int ID)
{
    if (UsuarioAtual == nullptr || !UsuarioAtual->geteAdm())
    {
        std::cout << "Apenas administradores podem remover usu�rios. \n";
        return false;
    }

    for (auto it = Usuarios.begin(); it != Usuarios.end(); ++it)
    {
        if (it->getIDUsuario() == ID)
        {
            if (UsuarioAtual->getIDUsuario() == ID)
            {
                std::cout << "Voc� n�o pode remover a si mesmo. \n";
                return false;
            }

            Usuarios.erase(it);
            SalvarUsuarios("Usuarios.txt");
            std::cout << "Usu�rio removido com sucesso. \n";
            return true;
        }
    }

    std::cout << "Usu�rio com ID " << ID << " n�o encontrado. \n";
    return false;
}

//Listar usu�rios
void GerenteEstoque::ListarUsuarios() const
{
    if (Usuarios.empty())
    {
        std::cout << "Nenhum usu�rio cadastrado. \n";
    }

    std::cout << "Lista de usu�rios cadastrados: \n";

    for (const auto& usuario : Usuarios)
    {
        std::cout
            << "ID: " << usuario.getIDUsuario()
            << " | Nome: " << usuario.getNomeUsuario()
            << " | Tipo: " << (usuario.geteAdm() ? "Administrador" : "Operador") << "\n";
    }
}

// Gerenciamento de Produtos
bool GerenteEstoque::AdicionarProduto(int ID, std::string Nome, std::string Marca, double Preco, int Quantidade, std::string Validade, int QuantidadeMinima)
{

    Produto NovoProduto(ID, Nome, Marca, Preco, Quantidade, Validade, QuantidadeMinima);

    Produtos.push_back(NovoProduto);
    SalvarProdutos("Produtos.txt");
    std::cout << "Produto adicionado com sucesso.\n";
    return true;



}

bool GerenteEstoque::RemoverProduto(int id)
{
    for (auto it = Produtos.begin(); it != Produtos.end(); ++it)
    {
        if (it->getIDProduto() == id)
        {
            Produtos.erase(it);
            SalvarProdutos("Produtos.txt");
            std::cout << "Produto removido com sucesso.\n";
            return true;
        }
    }
    std::cout << "Produto n�o encontrado.\n";
    return false;
}

Produto* GerenteEstoque::LocalizarProdutoPorID(int id)
{
    for (auto& produto : Produtos)
    {
        if (produto.getIDProduto() == id)
        {
            return &produto;
        }
    }
    return nullptr;
}

std::vector<Produto> GerenteEstoque::LocalizarProdutoPorNome(const std::string  & Nome) const
{
    std::vector<Produto> encontrados;
    std::string NomeBusca = NormalizarTexto(Nome);

    for (const Produto& produto : Produtos)
    {
        std::string nomeProdutoNormalizado = NormalizarTexto(produto.getNomeProduto());
    
        if (nomeProdutoNormalizado.find(NomeBusca) != std::string::npos)
        {
            encontrados.push_back(produto);
        }
    }
    return encontrados;
}

void GerenteEstoque::ListarTodosOsProdutos() const
{
    if (Produtos.empty())
    {
        std::cout << "Nenhum produto cadastrado.\n";
        return;
    }
    for (const auto& produto : Produtos)
    {
        std::cout << "ID: " << produto.getIDProduto()
            << " | Nome: " << produto.getNomeProduto()
            << " | Marca: " << produto.getMarcaProduto()
            << " | Pre�o: " << produto.getPrecoProduto()
            << " | Quantidade: " << produto.getQuantidadeProduto()
            << " | Expira: " << produto.getDataExpiracao() << "\n";
    }
}

int GerenteEstoque::GerarProximoIdUsuario() 
{
    return ++UltimoIDUsuario;
}

int GerenteEstoque::GerarProximoIdProduto()
{
    AtualizarUltimoIDProduto();
    return ++UltimoIDProduto;
}

void GerenteEstoque::AtualizarUltimoIDProduto()
{
    for (const auto& produto : Produtos)
    {
        if (produto.getIDProduto() > UltimoIDProduto)
        {
            UltimoIDProduto = produto.getIDProduto();
        }
    }
}


// Controle de Estoque
bool GerenteEstoque::AumentarProdutoEstoque(int id, int Quantia)
{
    Produto* produto = LocalizarProdutoPorID(id);
    if (produto)
    {
        produto->AumentarEstoque(Quantia);
        SalvarProdutos("Produtos.txt");
        std::cout << "Estoque aumentado com sucesso.\n";
        return true;
    }
    std::cout << "Produto n�o encontrado.\n";
    return false;
}

bool GerenteEstoque::DiminuirProdutoEstoque(int id, int Quantia)
{
    Produto* produto = LocalizarProdutoPorID(id);
    if (produto)
    {
        if (produto->getQuantidadeProduto() < Quantia)
        {
            std::cout << "Erro: estoque insuficiente.\n";
            return false;
        }
        produto->DiminuirEstoque(Quantia);
        std::cout << "Estoque diminu�do com sucesso.\n";
        SalvarProdutos("Produtos.txt");
        return true;
    }
    std::cout << "Produto n�o encontrado.\n";
    return false;
}

void GerenteEstoque::ListarProdutoBaixoEstoque()
{
    bool encontrou = false;
    for (const auto& produto : Produtos)
    {
        if (produto.isEstoqueBaixo())
        {
            encontrou = true;
            std::cout << "Produto em baixa: " << produto.getNomeProduto()
                << " | ID: " << produto.getIDProduto()
                << " | Quantidade: " << produto.getQuantidadeProduto()
                << " | M�nimo: " << produto.getQuantidadeMinima() << "\n";
        }
    }
    if (!encontrou)
    {
        std::cout << "Todos os produtos est�o com estoque adequado.\n";
    }
}

// Sistema de Arquivos
bool GerenteEstoque::CarregarUsuarios(const std::string& NomeArquivo)
{
    std::ifstream arquivo(NomeArquivo);
    if (!arquivo.is_open())
    {
        std::cout << "\n [ERRO] arquivo de usu�rio n�o encontrado. Ser� criado um novo. \n \n";
        return false;
    }
    Usuarios.clear();
    UltimoIDUsuario = 0;

    std::string linha;
    while (std::getline(arquivo, linha))
    {
        if (!linha.empty())
        {
            Usuario usuario = Usuario::Desserializar(linha);
            Usuarios.push_back(usuario);

            if (usuario.getIDUsuario() > UltimoIDUsuario)
            {
                UltimoIDUsuario = usuario.getIDUsuario();
            }
        }
    }
    arquivo.close();
    return true;
}

bool GerenteEstoque::SalvarUsuarios(const std::string& NomeArquivo)
{
    std::ofstream arquivo(NomeArquivo);
    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo para salvar os usu�rios.\n";
        return false;
    }
    for (const auto& usuario : Usuarios)
    {
        arquivo << usuario.Serializar() << '\n';
    }
    arquivo.close();
    return true;
}

bool GerenteEstoque::SalvarProdutos(const std::string& NomeArquivo)
{
    std::ofstream arquivo(NomeArquivo);
    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir o arquivo de produtos.\n";
        return false;
    }
    for (const auto& produto : Produtos)
    {
        arquivo << produto.Serializar() << '\n';
    }
    arquivo.close();
    return true;
}

bool GerenteEstoque::CarregarProdutos(const std::string& NomeArquivo)
{
    std::ifstream arquivo(NomeArquivo);
    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir arquivo de produtos.\n";
        return false;
    }
    Produtos.clear();
    std::string linha;
    int MaiorID = 0;

    while (std::getline(arquivo, linha))
    {
        if (!linha.empty())
        {
            Produto produto = Produto::Desserializar(linha);
            Produtos.push_back(produto);

            if (produto.getIDProduto() > MaiorID)
            {
                MaiorID = produto.getIDProduto();
            }
        }
    }
    arquivo.close();
    UltimoIDProduto = MaiorID;
    return true;
}

Usuario* GerenteEstoque::getUsuarioAtual() const
{
    return UsuarioAtual;
}

void GerenteEstoque::CriarAdminPadrao()
{
    bool ExisteAdmin = false;
    for (const auto& usuario : Usuarios)
    {
        if (usuario.geteAdm())
        {
            ExisteAdmin = true;
            break;
        }
    }
    if (!ExisteAdmin)
    {
        std::string Nome = "admin";
        std::string Senha = "admin123";
        int ID = GerarProximoIdUsuario();
        Usuarios.emplace_back(ID, Nome, Senha, true);
        std::cout << "Usu�rio admin padr�o criado (login: admin | senha: admin123).\n";
    }
}

const std::vector<Usuario>& GerenteEstoque::getUsuarios() const
{
    return Usuarios;
}
