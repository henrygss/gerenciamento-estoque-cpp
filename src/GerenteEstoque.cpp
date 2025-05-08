#include <fstream> //permite que abra, leia e escreva arquivos
#include "GerenteEstoque.h" 
#include <iostream>
#include <algorithm> //Para std::transform
#include <cctype> //Para std::toLower

//Converte uma string para min�sculas
std::string toLower(const std::string& texto)
{
	std::string resultado = texto;
	std::transform(resultado.begin(), resultado.end(), resultado.begin(),
		[](unsigned char c)
		{
			return std::tolower(c); 
		});
	return resultado;
}

//Login implementa��o
bool GerenteEstoque::Login(const std::string& NomeUsuario, const std::string& Senha)
{
	for (auto& usuario : Usuarios)
	{
		if (toLower(usuario.getNomeUsuario()) == toLower(NomeUsuario) && usuario.ChecarSenha(Senha))
		{
			UsuarioAtual = &usuario;
			std::cout << "Login realizado com sucesso. \n";
			return true;
		}
	}
	std::cout << "Usu�rio ou senha incorretos. \n";
	return false;
}

//Logout implementa��o
bool GerenteEstoque::Logout()
{
	if (UsuarioAtual != nullptr)
	{
		UsuarioAtual = nullptr;
		std::cout << "Logout realizado. \n";
		return true;
	}
	std::cout << "Nenhum usu�rio est� logado. \n";
	return false;
}

//CriarUsuario implementa��o
bool GerenteEstoque::CriarUsuario(const std::string& NomeUsuario, std::string& Senha, bool isAdm)
{
	if (UsuarioAtual == nullptr || !UsuarioAtual->geteAdm())
	{
		std::cout << "Apenas administradores podem criar novos usu�rios. \n";
		return false;
	}
	//Verifica se j� existe usu�rio com o mesmo nome
	for (const auto& usuario : Usuarios)
	{
		if (usuario.getNomeUsuario() == NomeUsuario)
		{
			std::cout << "J� existe um usu�rio com esse nome. \n";
			return false;
		}
	}
	int NovoID = GerarProximoId();
	Usuarios.emplace_back(NovoID, NomeUsuario, Senha, isAdm);
	std::cout << "Usu�rio criado com sucesso. \n";
	return true;
}

//Gerenciamento de produtos implementa��o

//Adicionar Produto
bool GerenteEstoque::AdicionarProduto(const Produto& produto)
{
	//Verifica se j� existe um produto com o mesmo ID
	for (const auto& p : Produtos)
	{
		if (p.getIDProduto() == produto.getIDProduto())
		{
			std::cout << "J� existe um produto com esse ID. \n";
			return false;
		}
	}
	Produtos.push_back(produto);
	std::cout << "Produto adicionado com sucesso. \n";
	return true;
}

//Remover produto
bool GerenteEstoque::RemoverProduto(int id)
{
	for (auto it = Produtos.begin(); it != Produtos.end(); ++it)
	{
		if (it->getIDProduto() == id)
		{
			Produtos.erase(it);
			std::cout << "Produto removido com sucesso. \n";
			return true;
		}
	}
	std::cout << "Produto n�o encontrado. \n";
	return false;
}

//Gerar ID automaticamente
int GerenteEstoque::GerarProximoId() const
{
	int MaxId = 0;
	for (const auto& produto : Produtos)
	{
		if (produto.getIDProduto() > MaxId)
		{
			MaxId = produto.getIDProduto();
		}
	}
	return MaxId + 1;

}

//Localizar Produto por ID
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

//Localizar Produto por Nome
std::vector<Produto> GerenteEstoque::LocalizarProdutoPorNome(const std::string & Nome) const
{
	std::vector<Produto> encontrados;
	for (const Produto & produto : Produtos)
	{
		if (toLower(produto.getNomeProduto()).find(toLower(Nome)) != std::string::npos)
		{
			encontrados.push_back(produto);
		}
	}
	return encontrados;

}

//Listar todos os produtos
void GerenteEstoque::ListarTodosOsProdutos() const
{
	if (Produtos.empty())
	{
		std::cout << "Nenhum produto cadastrado. \n";
		return;
	}
	for (const auto& produto : Produtos)
	{
		std::cout << "ID: " << produto.getIDProduto() << " | Nome: " << produto.getNomeProduto() << " | Marca: " << produto.getMarcaProduto()
			<< " | Pre�o R$" << produto.getPrecoProduto() << " | Quantidade: " << produto.getQuantidadeProduto()
			<< " | Expira: " << produto.getDataExpiracao() << "\n";
	}
}

//Controle de estoque implementa��o

//Aumentar Produto em Estoque
bool GerenteEstoque::AumentarProdutoEstoque(int id, int Quantia)
{
	Produto* produto = LocalizarProdutoPorID(id);
	if (produto)
	{
		produto->AumentarEstoque(Quantia);
		std::cout << "Estoque aumentado com sucesso. \n";
		return true;
	}
	std::cout << "Produto n�o encontrado. \n";
	return false;
}

//Diminuir Produto em Estoque
bool GerenteEstoque::DiminuirProdutoEstoque(int id, int Quantia)
{
	Produto* produto = LocalizarProdutoPorID(id);
	if (produto)
	{
		if (produto->getQuantidadeProduto() < Quantia)
		{
			std::cout << "Erro: estoque insuficiente. \n";
			return false;
		}
		produto->DiminuirEstoque(Quantia);
		std::cout << "Estoque diminu�do com sucesso.\n";
		return true;
	}
	std::cout << "Produto n�o encontrado. \n";
	return false;
}


//Listar Produto com Estoque Baixo
void GerenteEstoque::ListarProdutoBaixoEstoque()
{
	bool encontrou = false;

	for (const auto& produto : Produtos)
	{
		if (produto.isEstoqueBaixo())
		{
			encontrou = true;
			std::cout << "Produto em baixa: " << produto.getNomeProduto() << " | ID: " << produto.getIDProduto()
				<< " | Quantidade: " << produto.getQuantidadeProduto() << " | M�nimo: " << produto.getQuantidadeMinima() << "\n";
		}
	}
	if (!encontrou)
	{
		std::cout << "Todos os produtos est�o com estoque adequado. \n";
	}

}

//Carregamento e Salvamento de dados em arquivos implementa��o

//Carregar Usu�rios 

bool GerenteEstoque::CarregarUsuarios(const std::string& NomeArquivo)
{
	std::ifstream arquivo(NomeArquivo);
	if (!arquivo.is_open())
	{
		std::cout << "Erro ao abrir arquivo de usu�rio.\n";
		return false;
	}
	Usuarios.clear(); //Evita que haja duplicatas

	std::string linha;
	while (std::getline(arquivo, linha))
	{
		if (!linha.empty())
		{
			try
			{
				Usuario usuario = Usuario::Desserializar(linha);
				Usuarios.push_back(usuario);
			}
			catch (const std::exception & e)
			{
				std::cerr << "Erro ao carregar usu�rio: " << e.what() << "\n";
			}
			
		}
	}
	arquivo.close();
	return true;
}

//Salvar Usu�rios
bool GerenteEstoque::SalvarUsuarios(const std::string& NomeArquivo)
{
	std::ofstream arquivo(NomeArquivo);
	if (!arquivo.is_open())
	{
		std::cout << "Erro ao abrir o arquivo para salvar os usu�rios. \n";
		return false;
	}
	for (const auto& usuario : Usuarios)
	{
		arquivo << usuario.Serializar() << '\n';
	}

	arquivo.close();
	return true;
}

//Salvar Produtos implementa��o
bool GerenteEstoque::SalvarProdutos(const std::string& NomeArquivo)
{
	std::ofstream arquivo(NomeArquivo);
	if (!arquivo.is_open())
	{
		std::cout << "Erro ao abrir o arquivo de produtos. \n";
		return false;
	}
	for (const auto& produto : Produtos)
	{
		arquivo << produto.Serializar() << '\n';
	}
	arquivo.close();
	return true;
}

//Carregar Produtos implementa��o
bool GerenteEstoque::CarregarProdutos(const std::string& NomeArquivo)
{
	std::ifstream arquivo(NomeArquivo);
	
		if (!arquivo.is_open())
		{
			std::cout << "Erro ao abrir arquivo de produtos. \n";
			return false;
		}
		Produtos.clear(); //Evita duplicatas

		std::string linha;
		while (std::getline(arquivo, linha))
		{
			if (!linha.empty())
			{
				try
				{
					Produto produto = Produto::Desserializar(linha);
					Produtos.push_back(produto);
				}
				catch (const std::exception& e)
				{
					std::cerr << "Erro ao carregar produto: " << e.what() << "\n";
				}
			}
		}
		arquivo.close();
		return true;
	
}

Usuario* GerenteEstoque::getUsuarioAtual() const
{
	return UsuarioAtual;
}

GerenteEstoque::GerenteEstoque()
{
	UsuarioAtual = nullptr;
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
		int ID = GerarProximoId();

		Usuarios.emplace_back(ID, Nome, Senha, true);
		
		std::cout << "Usu�rio admin padr�o criado	(login: admin	| senha: admin123). \n";
	}
}

const std::vector<Usuario>& GerenteEstoque::getUsuarios() const
{
	return Usuarios;
}