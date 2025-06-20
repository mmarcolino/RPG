#ifndef ARMA_HPP
#define ARMA_HPP

#include <string>
#include <vector>

/**
 * @brief Enum que representa os tipos de armas disponíveis.
 */
enum class TipoArma {
    ESPADA_CURTA,      /**< Espada curta - rápida e ágil */
    ESPADA_LONGA,      /**< Espada longa - balanceada */
    MACHADO,           /**< Machado - alto dano, lento */
    LANCA,             /**< Lança - alcance médio */
    ARCO,              /**< Arco - alcance longo */
    CAJADO,            /**< Cajado - foco mágico */
    MARTELO,           /**< Martelo - alto dano, muito lento */
    ADAGA,             /**< Adaga - muito rápida, baixo dano */
    CLAYMORE,          /**< Claymore - espada pesada */
    BASTAO             /**< Bastão - simples e versátil */
};

/**
 * @brief Enum que representa os tipos de dano.
 */
enum class TipoDano {
    CORTE,             /**< Dano cortante */
    PERFURANTE,        /**< Dano perfurante */
    CONTUNDENTE,       /**< Dano contundente */
    MAGICO             /**< Dano mágico */
};

/**
 * @brief Estrutura que representa os modificadores de uma arma.
 */
struct ModificadoresArma {
    float modificadorAtaqueFisico;    /**< Modificador para ataque físico */
    float modificadorAtaqueMagico;    /**< Modificador para ataque mágico */
    float modificadorDefesa;          /**< Modificador para defesa */
    float modificadorAgilidade;       /**< Modificador para agilidade */
    int bonusDano;                    /**< Bônus de dano fixo */
    int alcance;                      /**< Alcance da arma (1 = corpo a corpo) */
    
    ModificadoresArma(float atkF = 1.0f, float atkM = 1.0f, float def = 1.0f, 
                      float agi = 1.0f, int dano = 0, int alc = 1)
        : modificadorAtaqueFisico(atkF), modificadorAtaqueMagico(atkM),
          modificadorDefesa(def), modificadorAgilidade(agi),
          bonusDano(dano), alcance(alc) {}
};

/**
 * @brief Classe base abstrata para todas as armas no RPG.
 *
 * Representa uma interface para armas como espadas, machados, arcos, etc.
 * Fornece métodos para recuperar informações da arma e seus modificadores.
 */
class Arma {
protected:
    std::string nome;
    TipoArma tipo;
    TipoDano tipoDano;
    ModificadoresArma modificadores;
    int nivelMinimo;
    std::string descricao;

public:
    /**
     * @brief Construtor da arma.
     * @param nome Nome da arma.
     * @param tipo Tipo da arma.
     * @param tipoDano Tipo de dano causado.
     * @param modificadores Modificadores de atributos.
     * @param nivelMinimo Nível mínimo para usar a arma.
     * @param descricao Descrição da arma.
     */
    Arma(const std::string& nome, TipoArma tipo, TipoDano tipoDano,
         const ModificadoresArma& modificadores, int nivelMinimo = 1,
         const std::string& descricao = "")
        : nome(nome), tipo(tipo), tipoDano(tipoDano), modificadores(modificadores),
          nivelMinimo(nivelMinimo), descricao(descricao) {}

    /**
     * @brief Destrutor virtual necessário para permitir destruição polimórfica.
     */
    virtual ~Arma() {}

    /**
     * @brief Retorna o nome da arma.
     * @return Nome da arma como string.
     */
    virtual std::string getNome() const { return nome; }

    /**
     * @brief Retorna o tipo da arma.
     * @return Tipo da arma.
     */
    virtual TipoArma getTipo() const { return tipo; }

    /**
     * @brief Retorna o tipo de dano da arma.
     * @return Tipo de dano.
     */
    virtual TipoDano getTipoDano() const { return tipoDano; }

    /**
     * @brief Retorna os modificadores da arma.
     * @return Estrutura com os modificadores.
     */
    virtual ModificadoresArma getModificadores() const { return modificadores; }

    /**
     * @brief Retorna o nível mínimo para usar a arma.
     * @return Nível mínimo.
     */
    virtual int getNivelMinimo() const { return nivelMinimo; }

    /**
     * @brief Retorna a descrição da arma.
     * @return Descrição da arma.
     */
    virtual std::string getDescricao() const { return descricao; }

    /**
     * @brief Retorna os ataques disponíveis para esta arma.
     * @return Vetor com os nomes dos ataques.
     */
    virtual std::vector<std::string> getAtaquesDisponiveis() const = 0;

    /**
     * @brief Calcula o dano base da arma.
     * @param ataqueFisico Ataque físico do personagem.
     * @param ataqueMagico Ataque mágico do personagem.
     * @return Dano base calculado.
     */
    virtual int calcularDanoBase(int ataqueFisico, int ataqueMagico) const {
        int danoFisico = static_cast<int>(ataqueFisico * modificadores.modificadorAtaqueFisico);
        int danoMagico = static_cast<int>(ataqueMagico * modificadores.modificadorAtaqueMagico);
        return danoFisico + danoMagico + modificadores.bonusDano;
    }
};

#endif 