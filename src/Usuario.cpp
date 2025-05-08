#include "Usuario.h"
#include <stdexcept>
#include <sstream>
#include <vector>
#include <functional>

Usuario::Usuario(int IDUsuario, std::string NomeUsuario, std::string Senha, bool isAdm)
	: IDUsuario(IDUsuario), NomeUsuario(NomeUsuario), isAdm(isAdm) 
{
	std::hash<std::string> hash_fn;
	SenhaHash = hash_fn(Senha);
}

//Construtor exclusivo para uso interno da desserialização
Usuario::Usuario(int IDUsuario, std::string NomeUsuario, size_t SenhaHash, bool isAdm, bool)
	: IDUsuario(IDUsuario), NomeUsuario(NomeUsuario), SenhaHash(SenhaHash),isAdm(isAdm) { };

//Getters
int Usuario::getIDUsuario() const
{
	return IDUsuario;
}

std::string Usuario::getNomeUsuario() const
{
	return NomeUsuario;
}

bool Usuario::geteAdm() const
{
	return isAdm;
}

bool Usuario::ChecarSenha(const std::string& InserirSenha) const
{
	std::hash<std::string> hash_fn;
	return hash_fn(InserirSenha) == SenhaHash;
}

std::string Usuario::Serializar() const
{
	return std::to_string(IDUsuario) + ';' + NomeUsuario + ";" + std::to_string(SenhaHash) + ";" + (isAdm ? "1" : "0");
}

Usuario Usuario::Desserializar(const std::string& Linha)
{
	std::stringstream ss(Linha);
	std::string item;
	std::vector<std::string> campos;
	
	while (std::getline(ss, item, ';'))
	{
		campos.push_back(item);
	}

	if (campos.size() != 4)
	{
		throw std::runtime_error("Erro ao desserializar usuário. \n");
	}

	int ID = std::stoi(campos[0]);
	std::string nome = campos[1];
	size_t hash = std::stoull(campos[2]);
	bool adm = campos[3] == "1";

	return Usuario(ID, nome, hash, adm, true);
}
