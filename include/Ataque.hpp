#ifndef ATAQUE_HPP
#define ATAQUE_HPP

#include <string>

/**
 * @brief Enum que representa os tipos de ataques.
 */
enum class TipoAtaque {
    NORMAL,         /**< Ataque básico */
    ESPECIAL,       /**< Ataque especial com bônus */
    CRITICO,        /**< Ataque crítico */
    AREA,           /**< Ataque em área */
    DEFENSIVO,      /**< Ataque defensivo */
    CONTRA_ATAQUE   /**< Contra-ataque */
};

/**
 * @brief Estrutura que representa os modificadores de um ataque.
 */
struct ModificadoresAtaque {
    float multiplicadorDano;      /**< Multiplicador de dano */
    float chanceAcerto;           /**< Chance de acerto (0.0 a 1.0) */
    float chanceCritico;          /**< Chance de crítico (0.0 a 1.0) */
    int custoEnergia;             /**< Custo de energia/MP */
    int cooldown;                 /**< Cooldown em turnos */
    bool ignoraDefesa;            /**< Se ignora a defesa do alvo */
    bool causaEfeito;             /**< Se causa efeito especial */
    
    ModificadoresAtaque(float dano = 1.0f, float acerto = 0.9f, float critico = 0.1f,
                        int energia = 0, int cd = 0, bool ignora = false, bool efeito = false)
        : multiplicadorDano(dano), chanceAcerto(acerto), chanceCritico(critico),
          custoEnergia(energia), cooldown(cd), ignoraDefesa(ignora), causaEfeito(efeito) {}
};

/**
 * @brief Classe base abstrata para todos os ataques no RPG.
 *
 * Representa uma interface para ataques como golpes básicos, ataques especiais, etc.
 * Fornece métodos para executar ataques e calcular dano.
 */
class Ataque {
protected:
    std::string nome;
    TipoAtaque tipo;
    ModificadoresAtaque modificadores;
    std::string descricao;

public:
    /**
     * @brief Construtor do ataque.
     * @param nome Nome do ataque.
     * @param tipo Tipo do ataque.
     * @param modificadores Modificadores do ataque.
     * @param descricao Descrição do ataque.
     */
    Ataque(const std::string& nome, TipoAtaque tipo,
           const ModificadoresAtaque& modificadores,
           const std::string& descricao = "")
        : nome(nome), tipo(tipo), modificadores(modificadores), descricao(descricao) {}

    /**
     * @brief Destrutor virtual necessário para permitir destruição polimórfica.
     */
    virtual ~Ataque() {}

    /**
     * @brief Retorna o nome do ataque.
     * @return Nome do ataque como string.
     */
    virtual std::string getNome() const { return nome; }

    /**
     * @brief Retorna o tipo do ataque.
     * @return Tipo do ataque.
     */
    virtual TipoAtaque getTipo() const { return tipo; }

    /**
     * @brief Retorna os modificadores do ataque.
     * @return Estrutura com os modificadores.
     */
    virtual ModificadoresAtaque getModificadores() const { return modificadores; }

    /**
     * @brief Retorna a descrição do ataque.
     * @return Descrição do ataque.
     */
    virtual std::string getDescricao() const { return descricao; }

    /**
     * @brief Calcula o dano do ataque.
     * @param danoBase Dano base da arma.
     * @param ataqueFisico Ataque físico do atacante.
     * @param ataqueMagico Ataque mágico do atacante.
     * @param defesaAlvo Defesa do alvo.
     * @return Dano final calculado.
     */
    virtual int calcularDano(int danoBase, int ataqueFisico, int ataqueMagico, int defesaAlvo) const {
        int danoCalculado = static_cast<int>(danoBase * modificadores.multiplicadorDano);
        
        // Aplicar modificadores baseados no tipo de ataque
        if (tipo == TipoAtaque::ESPECIAL) {
            danoCalculado = static_cast<int>(danoCalculado * 1.3f);
        } else if (tipo == TipoAtaque::CRITICO) {
            danoCalculado = static_cast<int>(danoCalculado * 2.0f);
        }
        
        // Aplicar defesa do alvo (se não ignorar)
        if (!modificadores.ignoraDefesa) {
            int reducaoDefesa = static_cast<int>(defesaAlvo * 0.5f);
            danoCalculado = std::max(1, danoCalculado - reducaoDefesa);
        }
        
        return std::max(1, danoCalculado);
    }

    /**
     * @brief Verifica se o ataque acertou.
     * @param agilidadeAtacante Agilidade do atacante.
     * @param agilidadeAlvo Agilidade do alvo.
     * @return true se acertou, false caso contrário.
     */
    virtual bool verificarAcerto(int agilidadeAtacante, int agilidadeAlvo) const {
        // Cálculo baseado na diferença de agilidade
        float chanceBase = modificadores.chanceAcerto;
        float bonusAgilidade = (agilidadeAtacante - agilidadeAlvo) * 0.01f;
        float chanceFinal = std::min(0.95f, std::max(0.05f, chanceBase + bonusAgilidade));
        
        return (static_cast<float>(rand()) / RAND_MAX) < chanceFinal;
    }

    /**
     * @brief Verifica se o ataque foi crítico.
     * @return true se foi crítico, false caso contrário.
     */
    virtual bool verificarCritico() const {
        return (static_cast<float>(rand()) / RAND_MAX) < modificadores.chanceCritico;
    }

    /**
     * @brief Executa o ataque.
     * @param atacante Personagem atacante.
     * @param alvo Personagem alvo.
     * @param danoBase Dano base da arma.
     * @return Dano causado (0 se errou).
     */
    virtual int executarAtaque(class Personagem& atacante, class Personagem& alvo, int danoBase) const = 0;
};

#endif 