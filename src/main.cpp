#include <iostream>
#include <locale.h>
#include "GerenteEstoque.h"
#include <limits>
#include <Windows.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    system("CHCP 1252 > nul");
    unsigned PaginaCodigoAtual = GetConsoleOutputCP();

    GerenteEstoque estoque;

    estoque.CarregarUsuarios("Usuarios.txt");
    estoque.CriarAdminPadrao();
    estoque.CarregarProdutos("Produtos.txt");
    estoque.AtualizarUltimoIDProduto();


    int Opcao;
    do
    {
        std::cout << "\n--- MENU INICIAL ---" << std::endl;
        std::cout << "1. Login\n";
        std::cout << "2. Sair\n";
        std::cout << "Escolha uma das opções: \n";
        std::cin >> Opcao;

        do //Laço de repetição para validação de entrada caso o usuário digite algo diferente de 1 e 2
        {
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                std::cout << "Entrada inválida. Digite 1 para fazer login ou 2 para sair.\n";
                std::cin >> Opcao;

            }
        } while (Opcao != 1 && Opcao != 2); //Fim laço de repetição


        if (Opcao == 1)
        {
            std::string Usuario, Senha;
            std::cout << "Usuário: \n";
            std::cin >> Usuario;
            std::cout << "Senha: \n";
            std::cin >> Senha;

            if (estoque.Login(Usuario, Senha))
            {
                bool isAdm = estoque.getUsuarioAtual()->geteAdm();
                int Escolha;
                do
                {
                    std::cout << "\n--- MENU PRODUTOS ---\n";
                    std::cout << "1. Cadastrar produto\n";
                    std::cout << "2. Listar produtos\n";
                    std::cout << "3. Pesquisar produto por ID\n";
                    std::cout << "4. Pesquisar produto por nome\n";
                    std::cout << "5. Entrada de estoque\n";
                    std::cout << "6. Saída de estoque\n";

                    if (isAdm)
                    {
                        std::cout << "7. Remover produto\n";
                        std::cout << "8. Ver produtos com baixo estoque\n";
                        std::cout << "9. Criar novo usuário\n";
                        std::cout << "10. Listar usuários cadastrados\n";
                        std::cout << "11. Remover usuário\n";
                        std::cout << "12. Logout\n";
                    }
                    else
                    {
                        std::cout << "7. Logout\n";
                    }

                    std::cout << "Escolha uma das opções: \n";
                    std::cin >> Escolha;

                    do //Laço de repetição para validação de entrada caso o administrador e operador digitem algo diferente das opções disponíveis
                    {

                        if (std::cin.fail())
                        {
                            std::cin.clear();
                            std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                            std::cout << "Entrada inválida. Digite um número de acordo com a opção desejada.\n";
                            std::cin >> Escolha;
                        }
                        else
                        {
                            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                            break;
                        }
                    }
                    while ((isAdm && (Escolha < 1 || Escolha > 12)) || (!isAdm && (Escolha < 1 || Escolha > 7)));
                    

                    if (isAdm)
                    {
                        switch (Escolha)
                        {
                        case 1:
                        {
                            int ID = estoque.GerarProximoIdProduto();
                            int Qtd, QtdMin;
                            double Preco;
                            std::string Nome, Marca, Validade;

                            std::cout << "ID gerado automaticamente para o produto.\n";

                            while (true)
                            {
                                std::cout << "Digite o nome do produto a ser cadastrado: \n";
                                std::getline(std::cin, Nome);

                                if (!Nome.empty())
                                    break;
                                std::cout << "Entrada inválida. Tente novamente.\n";
                            }

                     
                            while (true)
                            {
                                std::cout << "Digite a marca do produto: \n";
                                std::getline(std::cin, Marca);

                                if (!Marca.empty())
                                    break;
                                std::cout << "Entrada inválida. Tente novamente.\n";
                            }

                        
                            while (true)
                            {
                                std::cout << "Digite o preço do produto: \n";
                                std::cin >> Preco;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite um número.\n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                                    break;
                                }
                            }

                       
                            while (true)
                            {
                                std::cout << "Digite a quantidade do produto: \n";
                                std::cin >> Qtd;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite um número inteiro.\n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                         
                            while (true)
                            {
                                std::cout << "Digite a validade do produto: \n";
                                std::getline(std::cin, Validade);

                                if (!Validade.empty())
                                    break;
                                std::cout << "Entrada inválida. Tente novamente.\n";
                            }

                         
                            while (true)
                            {
                                std::cout << "Digite a quantidade mínima para alerta de estoque baixo do produto: \n";
                                std::cin >> QtdMin;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite um número inteiro.\n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            estoque.AdicionarProduto(ID, Nome, Marca, Preco, Qtd, Validade, QtdMin);
                            break;
                        }
                        case 2:
                            estoque.ListarTodosOsProdutos();
                            break;
                        case 3:
                        {
                            int Id;

                            while (true)
                            {
                                std::cout << "Digite o ID do produto para buscá-lo: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o número do ID de algum produto para buscá-lo: \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            Produto* produto = estoque.LocalizarProdutoPorID(Id);
                            if (produto)
                            {
                                std::cout << "ID: " << produto->getIDProduto()
                                    << " | Nome: " << produto->getNomeProduto()
                                    << " | Marca: " << produto->getMarcaProduto()
                                    << " | Preço: " << produto->getPrecoProduto()
                                    << " | Quantidade: " << produto->getQuantidadeProduto()
                                    << " | Expira: " << produto->getDataExpiracao() << "\n";
                            }
                            else
                            {
                                std::cout << "Produto não encontrado.\n";
                            }
                            break;
                        }
                        case 4:
                        {
                            std::string NomeBusca;

                            while (true)
                            {
                                std::cout << "Digite o nome do produto para buscá-lo: \n";
                                std::getline(std::cin, NomeBusca);

                                bool Valido = true;

                                for (char c : NomeBusca)
                                {
                                    if (!std::isalpha(c) && c != ' ')
                                    {
                                        Valido = false;
                                        break;
                                    }
                                }

                                if (!Valido || NomeBusca.empty())
                                {
                                    std::cout << "Entrada inválida. Digite apenas letras. \n";
                                }
                                else
                                {
                                    break;
                                }
                            }

                            auto resultados = estoque.LocalizarProdutoPorNome(NomeBusca);

                            if (resultados.empty())
                            {
                                std::cout << "Nenhum produto encontrado. \n";
                            }
                            else
                            {
                                for (const auto& p : resultados)
                                {
                                    std::cout << "ID: " << p.getIDProduto()
                                        << " | Nome: " << p.getNomeProduto()
                                        << " | Marca: " << p.getMarcaProduto() << "\n";
                                }
                            }
                            break;
                    
                        }
                        case 5:
                        {
                            int Id, Qtd;

                            while (true)
                            {
                                std::cout << "Digite o ID do produto: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o ID do produto. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            while (true)
                            {
                                std::cout << "Quantidade do produto a ser adicionada: \n";
                                std::cin >> Qtd;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite a quantidade do produto a ser adicionada. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            estoque.AumentarProdutoEstoque(Id, Qtd);
                            break;
                        }
                        case 6:
                        {
                            int Id, Qtd;

                            while (true)
                            {
                                std::cout << "Digite o ID do produto: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o ID do produto. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            while (true)
                            {
                                std::cout << "Quantidade do produto a ser diminuída: \n";
                                std::cin >> Qtd;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite a quantidade do produto a ser diminuída. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            estoque.DiminuirProdutoEstoque(Id, Qtd);
                            break;
                        }
                        case 7:
                        {
                            int Id;


                            while (true)
                            {
                                std::cout << "Digite o ID do produto a ser removido: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o número do ID de algum produto para removê-lo: \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }
   
                            estoque.RemoverProduto(Id);
                            break;
                        }
                        case 8:
                            estoque.ListarProdutoBaixoEstoque();
                            break;
                        case 9:
                        {
                            std::string NovoNome, NovaSenha, RespostaStr;
                            bool NovoAdm;
                            char Resposta;
           
                            std::cout << "Nome do novo usuário: \n";
                            std::getline(std::cin, NovoNome);
                            std::cout << "Senha do novo usuário: \n";
                            std::getline(std::cin, NovaSenha);

                           
                            do
                            {
                              
                                std::cout << "O novo usuário será administrador?  (s/n) \n";
                                std::getline(std::cin, RespostaStr);

                                Resposta = (!RespostaStr.empty()) ? std::tolower(RespostaStr[0]) : ' ';

                                if (Resposta != 's' && Resposta != 'n')
                                {
                                    std::cout << "Resposta inválida. Digite 's' para sim ou 'n' para não. \n";
                                }
                            } while (Resposta != 's' && Resposta != 'n');

                            NovoAdm = (Resposta == 's');

                            estoque.CriarUsuario(NovoNome, NovaSenha, NovoAdm);
                            break;
                        }
                        case 10:
                        {
                            estoque.ListarUsuarios();
                            break;
                        }
                        case 11:
                        {
                            int IDRemover;


                            while (true)
                            {
                                std::cout << "Digite o ID do usuário a ser removido: \n";
                                std::cin >> IDRemover;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o número do ID de algum usuário para removê-lo: \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            estoque.RemoverUsuario(IDRemover);
                            break;
                        }
                        case 12:
                        {
                            estoque.Logout();
                            break;
                        default:
                        {
                            std::cout << "Opção inválida.\n";
                        }

                        }
                        } //fim switch
                    }
                    else
                    {
                        switch (Escolha)
                        {
                        case 1:
                        {
                            int ID = estoque.GerarProximoIdProduto();
                            int Qtd, QtdMin;
                            double Preco;
                            std::string Nome, Marca, Validade;

                            std::cout << "ID gerado automaticamente para o produto.\n";

                            while (true)
                            {
                                std::cout << "Digite o nome do produto a ser cadastrado: \n";
                                std::getline(std::cin, Nome);

                                if (!Nome.empty())
                                    break;
                                std::cout << "Entrada inválida. Tente novamente.\n";
                            }


                            while (true)
                            {
                                std::cout << "Digite a marca do produto: \n";
                                std::getline(std::cin, Marca);

                                if (!Marca.empty())
                                    break;
                                std::cout << "Entrada inválida. Tente novamente.\n";
                            }


                            while (true)
                            {
                                std::cout << "Digite o preço do produto: \n";
                                std::cin >> Preco;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite um número.\n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                                    break;
                                }
                            }


                            while (true)
                            {
                                std::cout << "Digite a quantidade do produto: \n";
                                std::cin >> Qtd;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite um número inteiro.\n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }


                            while (true)
                            {
                                std::cout << "Digite a validade do produto: \n";
                                std::getline(std::cin, Validade);

                                if (!Validade.empty())
                                    break;
                                std::cout << "Entrada inválida. Tente novamente.\n";
                            }


                            while (true)
                            {
                                std::cout << "Digite a quantidade mínima para alerta de estoque baixo do produto: \n";
                                std::cin >> QtdMin;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite um número inteiro.\n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            estoque.AdicionarProduto(ID, Nome, Marca, Preco, Qtd, Validade, QtdMin);
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


                            while (true)
                            {
                                std::cout << "Digite o ID do produto para buscá-lo: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o número do ID de algum produto para buscá-lo: \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }


                            Produto* produto = estoque.LocalizarProdutoPorID(Id);
                            if (produto)
                            {
                                std::cout << "ID: " << produto->getIDProduto()
                                    << " | Nome: " << produto->getNomeProduto()
                                    << " | Marca: " << produto->getMarcaProduto()
                                    << " | Preço: " << produto->getPrecoProduto()
                                    << " | Quantidade: " << produto->getQuantidadeProduto()
                                    << " | Expira: " << produto->getDataExpiracao() << "\n";
                            }
                            else
                            {
                                std::cout << "Produto não encontrado.\n";
                            }
                            break;
                        }
                        case 4:
                        {
                            std::string NomeBusca;

                            while (true)
                            {
                                std::cout << "Digite o nome do produto para buscá-lo: \n";
                                std::getline(std::cin, NomeBusca);

                                bool Valido = true;

                                for (char c : NomeBusca)
                                {
                                    if (!std::isalpha(c) && c != ' ')
                                    {
                                        Valido = false;
                                        break;
                                    }
                                }

                                if (!Valido || NomeBusca.empty())
                                {
                                    std::cout << "Entrada inválida. Digite apenas letras. \n";
                                }
                                else
                                {
                                    break;
                                }
                            }

                            auto resultados = estoque.LocalizarProdutoPorNome(NomeBusca);

                            if (resultados.empty())
                            {
                                std::cout << "Nenhum produto encontrado. \n";
                            }
                            else
                            {
                                for (const auto& p : resultados)
                                {
                                    std::cout << "ID: " << p.getIDProduto()
                                        << " | Nome: " << p.getNomeProduto()
                                        << " | Marca: " << p.getMarcaProduto() << "\n";
                                }
                            }
                            break;
                        }
                        case 5:
                        {
                            int Id, Qtd;

                            while (true)
                            {
                                std::cout << "Digite o ID do produto: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o ID do produto. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            while (true)
                            {
                                std::cout << "Quantidade do produto a ser adicionada: \n";
                                std::cin >> Qtd;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite a quantidade do produto a ser adicionada. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }
            
                            estoque.AumentarProdutoEstoque(Id, Qtd);
                            break;
                        }
                        case 6:
                        {
                            int Id, Qtd;

                            while (true)
                            {
                                std::cout << "Digite o ID do produto: \n";
                                std::cin >> Id;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite o ID do produto. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            while (true)
                            {
                                std::cout << "Quantidade do produto a ser diminuída: \n";
                                std::cin >> Qtd;

                                if (std::cin.fail())
                                {
                                    std::cin.clear();
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    std::cout << "Entrada inválida. Digite a quantidade do produto a ser diminuída. \n";
                                }
                                else
                                {
                                    std::cin.ignore((std::numeric_limits<std::streamsize>::max) (), '\n');
                                    break;
                                }
                            }

                            estoque.DiminuirProdutoEstoque(Id, Qtd);
                            break;
                        }
                        case 7:
                        {
                            estoque.Logout();
                            break;

                        default:
                            std::cout << "Opção inválida. \n";

                        }
                        }
                    }

                } while ((isAdm && Escolha != 12) || (!isAdm && Escolha != 7));
            }
        }

    } while (Opcao != 2);

    estoque.SalvarUsuarios("Usuarios.txt");
    estoque.SalvarProdutos("Produtos.txt");

    std::cout << "Sistema encerrado.\n";

    SetConsoleOutputCP(PaginaCodigoAtual);
    system("Pause");
}