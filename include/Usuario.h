//Evita que o mesmo arquivo de cabeçalho .h seja incluido mais de uma vez durante a compilação
#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
public:
	//Construtor com parâmetros
	Usuario(int IDUsuario, std::string NomeUsuario, std::string Senha, bool isAdm = false);

	//métodos que não alterarão nenhum atributo do objeto
	std::string getNomeUsuario() const;
	bool geteAdm() const;
	int getIDUsuario() const;

	//Autenticação
	bool ChecarSenha(const std::string& InserirSenha) const;

	//Serialização (salvar/ler em arquivos)
	std::string Serializar() const;

	//line é a linha do arquivo onde os dados do usuário estarão salvos em forma de texto
	static Usuario Desserializar(const std::string& Linha);

private:
	//Construtor auxiliar privado
	Usuario(int IDUsuario, std::string NomeUsuario, size_t SenhaHash, bool isAdm, bool viaDesserializacao);

	std::string NomeUsuario;
	size_t SenhaHash; //Hash da senha gerado por std::hash<std::string>
	bool isAdm;
	int IDUsuario;

};
#endif
