#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>


class Produto
{
public:
	//Construtor
	Produto(int IDProduto, std::string NomeProduto, std::string MarcaProduto, double PrecoProduto, int QuantidadeProduto,
		std::string DataExpiracao = " ", int QuantidadeMinima = 0);

	//Getters
	int getIDProduto() const;
	std::string getNomeProduto() const;
	std::string getMarcaProduto() const;
	double getPrecoProduto() const;
	int getQuantidadeProduto() const;
	std::string getDataExpiracao() const;
	int getQuantidadeMinima() const;

	//Setters(Atualiza��es)
	void setQuantidadeProduto(int NovaQuantidade);
	void setPrecoProduto(double NovoPreco);
	void setQuantidadeMinima(int NovaQuantidade);

	//A��es de estoque
	void AumentarEstoque(int Quantia);
	void DiminuirEstoque(int Quantia);


	//Verifica��es
	bool isEstoqueBaixo()const; //Retorna true se Quantidade < QuantidadeMinima

	//Serializa��o
	std::string Serializar() const;
	static Produto Desserializar(const std::string& Linha);


private:
	int IDProduto;
	std::string NomeProduto;
	std::string MarcaProduto;
	double PrecoProduto;
	int QuantidadeProduto;
	std::string DataExpiracao;
	int QuantidadeMinima;
};

#endif
