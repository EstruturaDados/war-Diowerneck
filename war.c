// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct de Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Cadastro do %dº território:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Função para exibir territórios
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("ID %d - Nome: %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================================\n");
}

// Função para atribuir uma missão aleatória a um jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função para exibir a missão do jogador
void exibirMissao(char* missao) {
    printf("\n🎯 Sua missão é: %s\n", missao);
}

// Simula ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante == defensor) {
        printf("Erro: Um território não pode atacar a si mesmo!\n");
        return;
    }

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("Erro: Tropas insuficientes para atacar (mínimo 2).\n");
        return;
    }

    printf("\nAtaque de '%s' (%s) -> '%s' (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Ataque bem-sucedido!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("Resultado: Defesa bem-sucedida!\n");
        atacante->tropas -= 1;
    }
}

// Função para verificar se uma missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo simples: verificar se há pelo menos 3 territórios seguidos da mesma cor
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        for (int i = 0; i <= tamanho - 3; i++) {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i + 2].cor) == 0) {
                return 1;
            }
        }
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) {
                return 0;
            }
        }
        return 1;
    }
    // Missões fictícias e simples
    else if (strcmp(missao, "Controlar todos os territórios") == 0) {
        char* corBase = mapa[0].cor;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corBase) != 0) {
                return 0;
            }
        }
        return 1;
    }
    else if (strcmp(missao, "Conquistar 2 territórios com mais de 5 tropas") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 5) {
                count++;
            }
        }
        if (count >= 2) return 1;
    }
    else if (strcmp(missao, "Ter pelo menos 15 tropas somadas") == 0) {
        int total = 0;
        for (int i = 0; i < tamanho; i++) {
            total += mapa[i].tropas;
        }
        if (total >= 15) return 1;
    }

    return 0;
}

// Libera memória de territórios e missões
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    int numTerritorios;
    printf("Digite o número de territórios: ");
    scanf("%d", &numTerritorios);

    // Alocação dinâmica de território
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, numTerritorios);

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar todos os territórios",
        "Conquistar 2 territórios com mais de 5 tropas",
        "Ter pelo menos 15 tropas somadas"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Missão do jogador (alocação dinâmica)
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    if (!missaoJogador) {
        printf("Erro ao alocar memória para a missão.\n");
        free(mapa);
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);
    exibirMapa(mapa, numTerritorios);

    char continuar;
    do {
        int idAtacante, idDefensor;

        printf("\nDigite o ID do território ATACANTE: ");
        scanf("%d", &idAtacante);
        printf("Digite o ID do território DEFENSOR: ");
        scanf("%d", &idDefensor);

        if (idAtacante >= 0 && idAtacante < numTerritorios &&
            idDefensor >= 0 && idDefensor < numTerritorios) {

            atacar(&mapa[idAtacante], &mapa[idDefensor]);
            exibirMapa(mapa, numTerritorios);

            // Verifica se missão foi concluída
            if (verificarMissao(missaoJogador, mapa, numTerritorios)) {
                printf("\n🎉 Missão cumprida! Você venceu o jogo! 🎉\n");
                break;
            }

        } else {
            printf("IDs inválidos. Tente novamente.\n");
        }

        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador);
    printf("Jogo encerrado. Obrigado por jogar!\n");
    return 0;
}
