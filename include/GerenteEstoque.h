#ifndef GERENTE_ESTOQUE_H
#define GERENTE_ESTOQUE_H

#include "Usuario.h"
#include "Produto.h"
#include <vector>

std::string toLower(const std::string& texto);

class GerenteEstoque
{
public:

	
	GerenteEstoque();

	//Autenticação 
	bool Login(const std::string& NomeUsuario, const std::string& Senha);
	bool Logout();
	//Só cria um novo usuário se UsuarioAtual for o administrador
	bool CriarUsuario(const std::string& NomeUsuario, std::string& Senha, bool isAdm);

	//Gerenciamento de Produtos
	bool AdicionarProduto(const Produto& produto);
	bool RemoverProduto(int id);
	Produto* LocalizarProdutoPorID(int id);
	std::vector<Produto> LocalizarProdutoPorNome(const std::string& Nome) const;
	void ListarTodosOsProdutos() const;
	int GerarProximoId() const;

	//Controle de Estoque
	bool AumentarProdutoEstoque(int id, int Quantia);
	bool DiminuirProdutoEstoque(int id, int Quantia);
	void ListarProdutoBaixoEstoque();

	//Salvamento e Carregamento de dados em arquivos
	bool CarregarUsuarios(const std::string& NomeArquivo);
	bool SalvarUsuarios(const std::string& NomeArquivo);

	//Salvar Produtos
	bool SalvarProdutos(const std::string& NomeArquivo);

	//Carregar Produtos
	bool CarregarProdutos(const std::string& NomeArquivo);

	Usuario* getUsuarioAtual() const;

	void CriarAdminPadrao();

	const std::vector<Usuario>& getUsuarios() const;


private:

	std::vector<Usuario> Usuarios; //Lista de usuários cadastrados, armazena todos os usuários do sistema
	std::vector<Produto> Produtos; //Lista de produtos em estoque, armazena todos os produtos do estoque
	Usuario* UsuarioAtual; //Ponteiro para o usuário logado, representa quem está usando o sistema(após o login)
	
};


#endif 

