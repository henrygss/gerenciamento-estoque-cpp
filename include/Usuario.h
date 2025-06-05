//Evita que o mesmo arquivo de cabe�alho .h seja incluido mais de uma vez durante a compila��o
#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
public:
	//Construtor com par�metros
	Usuario(int IDUsuario, std::string NomeUsuario, std::string Senha, bool isAdm);

	//Construtor para desserializa��o
	Usuario(int IDUsuario, std::string NomeUsuario, size_t SenhaHash, bool isAdm, bool dummy);

	//m�todos que n�o alterar�o nenhum atributo do objeto
	std::string getNomeUsuario() const;
	bool geteAdm() const;
	int getIDUsuario() const;

	//Setter
	void setIDUsuario(int NovoID);

	//Autentica��o
	bool ChecarSenha(const std::string& InserirSenha) const;

	//Serializa��o (salvar/ler em arquivos)
	std::string Serializar() const;

	//line � a linha do arquivo onde os dados do usu�rio estar�o salvos em forma de texto
	static Usuario Desserializar(const std::string& Linha);

private:

	std::string NomeUsuario;
	size_t SenhaHash; //Hash da senha gerado por std::hash<std::string>
	bool isAdm;
	int IDUsuario;
	static int ProximoID;
	static int GerarID();

};
#endif
