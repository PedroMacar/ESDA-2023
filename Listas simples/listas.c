#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados para representar uma pessoa
typedef struct {
    int id;
    char nome[50];
    char data_nascimento[11]; // formato: DD/MM/AAAA
} Pessoa;

// Nó de uma lista encadeada de pessoas
typedef struct PessoaNode {
    Pessoa pessoa;
    struct PessoaNode* proximo;
} PessoaNode;

// Função para adicionar uma pessoa no final da lista
void adicionar_pessoa(PessoaNode** cabeca, Pessoa pessoa) {
    PessoaNode* novo_no = (PessoaNode*) malloc(sizeof(PessoaNode));
    novo_no->pessoa = pessoa;
    novo_no->proximo = NULL;

    if (*cabeca == NULL) {
        // Se a lista estiver vazia, o novo nó é a cabeça da lista
        *cabeca = novo_no;
    } else {
        // Se a lista não estiver vazia, percorre a lista até o último nó
        PessoaNode* ultimo_no = *cabeca;
        while (ultimo_no->proximo != NULL) {
            ultimo_no = ultimo_no->proximo;
        }

        // Insere o novo nó após o último nó
        ultimo_no->proximo = novo_no;
    }
}

// Função para mostrar todas as pessoas da lista
void mostrar_pessoas(PessoaNode* cabeca) {
    printf("ID\tNome\tData de nascimento\n");
    printf("--\t----\t--------------------\n");

    PessoaNode* no_atual = cabeca;
    while (no_atual != NULL) {
        printf("%d\t%s\t%s\n", no_atual->pessoa.id, no_atual->pessoa.nome, no_atual->pessoa.data_nascimento);
        no_atual = no_atual->proximo;
    }
}

// Função para encontrar a pessoa mais velha na lista
void pessoa_mais_velha(PessoaNode* cabeca) {
PessoaNode* no_atual = cabeca;
Pessoa pessoa_mais_velha = no_atual->pessoa;
while (no_atual != NULL) {
    // Converte as datas de nascimento para um formato que possa ser comparado
    int dia1, mes1, ano1, dia2, mes2, ano2;
    sscanf(pessoa_mais_velha.data_nascimento, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(no_atual->pessoa.data_nascimento, "%d/%d/%d", &dia2, &mes2, &ano2);

    // Compara as datas de nascimento para determinar a pessoa mais velha
    if (ano2 < ano1 || (ano2 == ano1 && mes2 < mes1) || (ano2 == ano1 && mes2 == mes1 && dia2 < dia1)) {
        pessoa_mais_velha = no_atual->pessoa;
    }

    no_atual = no_atual->proximo;
}

printf("A pessoa mais velha da lista eh: %s, nascida em %s\n", pessoa_mais_velha.nome, pessoa_mais_velha.data_nascimento);
}


// Função para excluir uma pessoa da lista pelo ID
void excluir_pessoa(PessoaNode** cabeca, int id) {
    PessoaNode* no_atual = *cabeca;
    PessoaNode* no_anterior = NULL;

    // Percorre a lista até encontrar o nó com o ID desejado ou até o final da lista
    while (no_atual != NULL && no_atual->pessoa.id != id) {
        no_anterior = no_atual;
        no_atual = no_atual->proximo;
    }

    if (no_atual != NULL) {
        // Se encontrou a pessoa com o ID desejado, remove o nó correspondente da lista
        if (no_anterior == NULL) {
            // Se o nó a ser removido é a cabeça da lista
            *cabeca = no_atual->proximo;
        } else {
            // Se o nó a ser removido não é a cabeça da lista
            no_anterior->proximo = no_atual->proximo;
        }
        free(no_atual);
    }
}

// Função principal para testar a lista de pessoas
int main() {
    // Cria as três pessoas
    Pessoa pessoa1 = {1, "Joao", "01/01/1990"};
    Pessoa pessoa2 = {2, "Maria", "02/02/1991"};
    Pessoa pessoa3 = {3, "Pedro", "03/03/1992"};

    // Cria a cabeça da lista
    PessoaNode* cabeca = NULL;
    int id_para_excluir;
 PessoaNode* no_atual = cabeca;
 Pessoa nova_pessoa;
    int opcao = 0;
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar pessoa\n");
        printf("2 - Mostrar pessoas\n");
        printf("3 - Excluir pessoa\n");
        printf("4 - pessoa mais velha\n");
        printf("5 - Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                
                printf("Digite o ID da pessoa: ");
                scanf("%d", &nova_pessoa.id);
                printf("Digite o nome da pessoa: ");
                scanf("%s", nova_pessoa.nome);
                printf("Digite a data de nascimento da pessoa (no formato DD/MM/AAAA): ");
                scanf("%s", nova_pessoa.data_nascimento);
                // Adiciona a nova pessoa na lista
                adicionar_pessoa(&cabeca, nova_pessoa);
                break;
            case 2:
                mostrar_pessoas(cabeca);
                break;
            case 3:
                
                printf("Digite o ID da pessoa que deseja excluir: ");
                scanf("%d", &id_para_excluir);
                excluir_pessoa(&cabeca, id_para_excluir);
                break;
            case 4:
				pessoa_mais_velha(cabeca);
			case 5:
                // Limpa a lista liberando a memória dos nós
               
                while (no_atual != NULL) {
                    PessoaNode* proximo_no = no_atual->proximo;
                    free(no_atual);
                    no_atual = proximo_no;
                }
                return 0;
            default:
                printf("Opcao invalida, tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

