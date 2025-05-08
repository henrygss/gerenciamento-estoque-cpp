#include "Produto.h"
#include <sstream> //Usado para Desserializar
#include <vector>
#include <iostream>


Produto::Produto(int IDProduto, std::string NomeProduto, std::string MarcaProduto,
	double PrecoProduto, int QuantidadeProduto, std::string DataExpiracao, int QuantidadeMinima)
	:IDProduto(IDProduto), NomeProduto(NomeProduto), MarcaProduto(MarcaProduto), PrecoProduto(PrecoProduto),
	QuantidadeProduto(QuantidadeProduto), DataExpiracao(DataExpiracao), QuantidadeMinima(QuantidadeMinima) { }

int Produto::getIDProduto() const
{
	return IDProduto;
}

std::string Produto::getNomeProduto() const
{
	return NomeProduto;
}

std::string Produto::getMarcaProduto() const
{
	return MarcaProduto;
}

double Produto::getPrecoProduto() const
{
	return PrecoProduto;
}

int Produto::getQuantidadeProduto() const
{
	return QuantidadeProduto;
}

std::string Produto::getDataExpiracao() const
{
	return DataExpiracao;
}

int Produto::getQuantidadeMinima() const
{
	return QuantidadeMinima;
}

//

void Produto::setQuantidadeProduto(int NovaQuantidade)
{
	QuantidadeProduto = NovaQuantidade;
}

void Produto::setPrecoProduto(double NovoPreco)
{
	PrecoProduto = NovoPreco;
}

void Produto::setQuantidadeMinima(int NovaQuantidade)
{
	QuantidadeMinima = NovaQuantidade;
}

void Produto::AumentarEstoque(int Quantia)
{
	QuantidadeProduto += Quantia;
}

void Produto::DiminuirEstoque(int Quantia)
{
	if (Quantia > QuantidadeProduto)
	{
		std::cout << "Erro: Estoque insuficiente! \n";
		return;
	}
	QuantidadeProduto -= Quantia;
}

bool Produto::isEstoqueBaixo() const
{
	return QuantidadeProduto < QuantidadeMinima;
}

//Serializar e Desserializar. Aqui os métodos convertem os objetos para texto e reconvertem ao carregar

//Serializar
std::string Produto::Serializar() const
{
	return std::to_string(IDProduto) + ";" + NomeProduto + ";" + MarcaProduto + ";" +
		std::to_string(PrecoProduto) + ";" + std::to_string(QuantidadeProduto) + ";" +
		DataExpiracao + ";" + std::to_string(QuantidadeMinima);
}

//Desserializar
Produto Produto::Desserializar(const std::string& linha)
{
	std::stringstream ss(linha);
	std::string item;
	std::vector<std::string> campos;

	while (std::getline(ss, item, ';'))
	{
		campos.push_back(item);
	}

	if (campos.size() != 7)
	{
		throw std::runtime_error("Erro ao desserializar produtos: formato inválido. \n");
	}

	return Produto(
		std::stoi(campos[0]), //IDProduto
		campos[1],	//NomeProduto
		campos[2],	//MarcaProduto
		std::stod(campos[3]),	//PrecoProduto
		std::stoi(campos[4]),	//QuantidadeProduto
		campos[5],	//DataExpiracao
		std::stoi(campos[6])	//QuantidadeMinima
	);


}