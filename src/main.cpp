#include <iostream>
#include "GerenteEstoque.h"
#include <locale.h>
#include <Windows.h>


int main()
{
	setlocale(LC_ALL, "Portuguese");
	system("CHCP 1252 > nul");
	unsigned PaginaCodigoAtual = GetConsoleOutputCP();

	GerenteEstoque estoque;

	estoque.CarregarUsuarios("Usuarios.txt");
	estoque.CriarAdminPadrao(); //Cria um administrador padrão
	estoque.CarregarProdutos("Produtos.txt");

	int Opcao;

	do
	{
		
		std::cout << "\n--- MENU INICIAL ---\n";
		std::cout << "1. Login \n";
		std::cout << "2. Sair \n";

		std::cout << "Escolha uma das opções: \n ";
		std::cin >> Opcao;

		//Tratamento de entrada inválida, como letras ou símbolos
		if (std::cin.fail())
		{
			std::cin.clear(); //Limpa o erro de leitura
			std::cin.ignore(1000, '\n'); //Descarta o conteúdo inválido
			Opcao = 0; //Força opção inválida
		}


		if (Opcao == 1)
		{
			std::string Usuario, Senha;
			std::cout << "Usuário:  \n";
			std::cin >> Usuario;
			std::cout << "Senha:  \n";
			std::cin >> Senha;

			if (estoque.Login(Usuario, Senha))
			{
				bool isAdm = estoque.getUsuarioAtual()->geteAdm();
				int Escolha;
				do
				{
					std::cout << "\n--- MENU PRODUTOS ---\n";
					std::cout << "1. Cadastrar produto \n";
					std::cout << "2. Listar produtos cadastrados \n";
					std::cout << "3. Pesquisar produto por ID \n";
					std::cout << "4. Pesquisar produto por nome \n";
					std::cout << "5. Atualizar entrada de estoque \n";
					std::cout << "6. Atualizar saída de estoque \n";

					if (isAdm)
					{
						std::cout << "7. Remover produto \n";
						std::cout << "8. Ver produtos com baixo estoque \n";
						std::cout << "9. Criar usuário \n";
						std::cout << "10. Listar usuários cadastrados \n";
						std::cout << "11. Logout \n";
					}
					else
					{
						std::cout << "7. Logout \n";
					}


					std::cout << "Escolha uma das opções : \n";
					std::cin >> Escolha;

					if (isAdm)
					{
						switch (Escolha)
						{
						case 1:
						{
							int Qtd, QtdMin;
							double Preco;
							std::string Nome, Marca, Validade;
							int Id = estoque.GerarProximoId();

							std::cout << "ID gerado automaticamente para o produto:  \n";
							std::cin.ignore();
							std::cout << "Informe o nome do produto:  \n";
							std::getline(std::cin, Nome);
							std::cout << "Informe a marca do produto:  \n";
							std::getline(std::cin,Marca);
							std::cout << "Informe o preço do produto:  \n";
							std::cin >> Preco;
							std::cout << "Informe a quantidade do produto: \n";
							std::cin >> Qtd;
							std::cout << "Informe a data de vencimento do produto: \n";
							std::cin >> Validade;
							std::cout << "Informe a quantidade mínima do produto para alerta: \n ";
							std::cin >> QtdMin;

							Produto p(Id, Nome, Marca, Preco, Qtd, Validade, QtdMin);
							estoque.AdicionarProduto(p);
							break;
						}

						case 2:
						{
							estoque.ListarTodosOsProdutos();
							break;
						}
						case 3:
						{
							int Id;
							std::cout << "Digite o ID do produto para buscar: \n";
							std::cin >> Id;

							Produto* produto = estoque.LocalizarProdutoPorID(Id);
							if (produto != nullptr)
							{
								std::cout << "ID: " << produto->getIDProduto()
									<< " | Nome: " << produto->getNomeProduto()
									<< " | Marca: " << produto->getMarcaProduto()
									<< " | Preço: " << produto->getPrecoProduto()
									<< " | Quantidade: " << produto->getQuantidadeProduto()
									<< " | Expira: " << produto->getDataExpiracao();
								break;
							}
							else
							{
								std::cout << "Nenhum produto encontrado. \n";
								break;
							}
						}
						case 4:
						{
							std::string BuscarPorNome;
							std::cout << "Digite o nome do produto para buscar \n";
							std::cin >> BuscarPorNome;

							auto resultados = estoque.LocalizarProdutoPorNome(BuscarPorNome);
							if (resultados.empty())
							{
								std::cout << "Nenhum produto encontrado. \n";
							}
							else
							{
								for (const auto& p : resultados)
								{
									std::cout <<
										"Nome: " << p.getNomeProduto() << "\n" <<
										"Marca: " << p.getMarcaProduto() << "\n" <<
										"Preço: " << p.getPrecoProduto() << "\n" <<
										"Quantidade: " << p.getQuantidadeProduto() << "\n" <<
										"Expira: " << p.getDataExpiracao() << "\n";
								}
							}
							break;
						}
						case 5:
						{
							int Id, Qtd;
							std::cout << "ID do produto: \n";
							std::cin >> Id;
							std::cout << "Quantidade a adicionar: \n";
							std::cin >> Qtd;

							estoque.AumentarProdutoEstoque(Id, Qtd);
							break;
						}
						case 6:
						{
							int Id, Qtd;
							std::cout << "ID do produto: \n";
							std::cin >> Id;
							std::cout << "Quantidade a remover: \n";
							std::cin >> Qtd;

							estoque.DiminuirProdutoEstoque(Id, Qtd);
							break;
						}
						case 7:
						{
							int Id;
							std::cout << "ID do produto a remover: \n";
							std::cin >> Id;
							estoque.RemoverProduto(Id);
							break;
						}
						case 8:
						{
							estoque.ListarProdutoBaixoEstoque();
							break;
						}
						case 9:
						{
							std::string NovoNome, NovaSenha;
							char tipo;
							bool NovoAdm = false;

							std::cin.ignore();
							std::cout << "Digite o nome do novo usuário: \n";
							std::getline(std::cin, NovoNome);

							std::cout << "Digite a senha: \n";
							std::getline(std::cin, NovaSenha);
							std::cout << "Esse usuário será administrador ? (s/n): \n";
							std::cin >> tipo;

							if (tipo == 's' || tipo == 'S')
							{
								NovoAdm = true;
							}
							estoque.CriarUsuario(NovoNome, NovaSenha, NovoAdm);
							break;
						}

						case 10:
						{
							std::cout << "--- USUÁRIOS CADASTRADOS --- \n";
							for (const auto& u : estoque.getUsuarios())
							{
								std::cout
									<< "ID: " << u.getIDUsuario()
									<< " | Nome: " << u.getNomeUsuario()
									<< " | Tipo: " << (u.geteAdm() ? "Administrador" : "Funcionário") << "\n";
							}
							break;
							
						}
						case 11:
						{
							estoque.Logout();
							break;
						}
						default:
						{
							std::cout << "Opção inválida. \n";
						}

						}
					}
					else
					{
						switch (Escolha)
						{
						case 1:
						{
							int Qtd, QtdMin;
							double Preco;
							std::string Nome, Marca, Validade;
							int Id = estoque.GerarProximoId();

							std::cout << "ID atribuído automaticamente para o produto:  \n";
							std::cin.ignore();
							std::cout << "Informe o nome do produto:  \n";
							std::getline(std::cin, Nome);
							std::cout << "Informe a marca do produto:  \n";
							std::getline(std::cin, Marca);
							std::cout << "Informe o preço do produto:  \n";
							std::cin >> Preco;
							std::cout << "Informe a quantidade do produto: \n";
							std::cin >> Qtd;
							std::cout << "Informe a data de vencimento do produto: \n";
							std::cin >> Validade;
							std::cout << "Informe a quantidade mínima do produto para alerta: \n ";
							std::cin >> QtdMin;

							Produto p(Id, Nome, Marca, Preco, Qtd, Validade, QtdMin);
							estoque.AdicionarProduto(p);
							break;
						}
						case 2:
						{
							estoque.ListarTodosOsProdutos();
							break;
						}
						case 3:
						{
							int Id;
							std::cout << "Digite o ID do produto para buscar: \n";
							std::cin >> Id;

							Produto* produto = estoque.LocalizarProdutoPorID(Id);
							if (produto != nullptr)
							{
								std::cout << "ID: " << produto->getIDProduto() << "\n"
									<< " | Nome: " << produto->getNomeProduto() << "\n"
									<< " | Marca: " << produto->getMarcaProduto() << "\n"
									<< " | Preço: " << produto->getPrecoProduto() << "\n"
									<< " | Quantidade: " << produto->getQuantidadeProduto() << "\n"
									<< " | Expira: " << produto->getDataExpiracao() << "\n";
								break;
							}
							else
							{
								std::cout << "Nenhum produto encontrado. \n";
								break;
							}
						}
						case 4:

						{
							std::string BuscarPorNome;
							std::cout << "Digite o nome do produto para buscar \n";
							std::cin >> BuscarPorNome;

							auto resultados = estoque.LocalizarProdutoPorNome(BuscarPorNome);
							if (resultados.empty())
							{
								std::cout << "Nenhum produto encontrado. \n";
							}
							else
							{
								for (const auto& p : resultados)
								{
									std::cout <<
										" | Nome: " << p.getNomeProduto() << "\n" <<
										" | Marca: " << p.getMarcaProduto() << "\n" <<
										" | Preço: " << p.getPrecoProduto() << "\n" <<
										" | Quantidade: " << p.getQuantidadeProduto() << "\n" <<
										" | Expira: " << p.getDataExpiracao() << "\n";
								}
							}
							break;
						}
						case 5:
						{
							int Id, Qtd;
							std::cout << "ID do produto: \n";
							std::cin >> Id;
							std::cout << "Quantidade a adicionar: \n";
							std::cin >> Qtd;

							estoque.AumentarProdutoEstoque(Id, Qtd);
							break;
						}
						case 6:
						{
							int Id, Qtd;
							std::cout << "ID do produto: \n";
							std::cin >> Id;
							std::cout << "Quantidade a remover: \n";
							std::cin >> Qtd;

							estoque.DiminuirProdutoEstoque(Id, Qtd);
							break;
						}
						case 7:
						{
							estoque.Logout();
							break;
						}
						default:
						{
							std::cout << "Opção inválida. \n";
						}
						}
					}
				} while ((isAdm && Escolha != 9 && Escolha != 10 && Escolha != 11) || (!isAdm && Escolha != 7));
			}
		}
		else if (Opcao != 2)
		{
			std::cout << "Opção inválida. Digite 1 para fazer Login ou 2 para Sair. \n";
		}
	}
	while (Opcao != 2);
		
	//Salva os dados ao sair
	estoque.SalvarUsuarios("Usuarios.txt");
	estoque.SalvarProdutos("Produtos.txt");

	std::cout << "Sistema encerrado. \n";

	SetConsoleOutputCP(PaginaCodigoAtual);
	system("PAUSE");
	return 0;

}