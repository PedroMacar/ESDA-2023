#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PESSOAS 100

typedef struct {
    int id;
    char nome[50];
    char apelido[50];
    char data_nascimento[11];
} Pessoa;

Pessoa pessoas[MAX_PESSOAS];
int num_pessoas = 0;

void adicionar_pessoa() {
    if (num_pessoas >= MAX_PESSOAS) {
        printf("Limite de pessoas atingido.\n");
        return;
    }
    
    Pessoa nova_pessoa;
    nova_pessoa.id = num_pessoas + 1;
    
    printf("Digite o nome: ");
    scanf("%s", nova_pessoa.nome);
    
    printf("Digite o apelido: ");
    scanf("%s", nova_pessoa.apelido);
    
    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    scanf("%s", nova_pessoa.data_nascimento);
    
    pessoas[num_pessoas] = nova_pessoa;
    num_pessoas++;
    
    printf("Pessoa adicionada com sucesso.\n");
}

void remover_pessoa() {
    int id;
    printf("Digite o ID da pessoa que deseja remover: ");
    scanf("%d", &id);
    
    int index = -1;
    for (int i = 0; i < num_pessoas; i++) {
        if (pessoas[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Pessoa com ID %d não encontrada.\n", id);
        return;
    }
    
    for (int i = index; i < num_pessoas - 1; i++) {
        pessoas[i] = pessoas[i+1];
    }
    num_pessoas--;
    
    printf("Pessoa removida com sucesso.\n");
}

void listar_pessoas() {
    printf("ID\tNome\tApelido\tData de Nascimento\n");
    for (int i = 0; i < num_pessoas; i++) {
        printf("%d\t%s\t%s\t%s\n", pessoas[i].id, pessoas[i].nome, pessoas[i].apelido, pessoas[i].data_nascimento);
    }
}

Pessoa pessoa_mais_velha() {
    Pessoa mais_velha = pessoas[0];
    for (int i = 1; i < num_pessoas; i++) {
        if (strcmp(pessoas[i].data_nascimento, mais_velha.data_nascimento) < 0) {
            mais_velha = pessoas[i];
        }
    }
    return mais_velha;
}

Pessoa segunda_pessoa_mais_nova() {
    Pessoa mais_nova = pessoas[0];
    Pessoa segunda_mais_nova = pessoas[0];
    
    for (int i = 1; i < num_pessoas; i++) {
        if (strcmp(pessoas[i].data_nascimento, mais_nova.data_nascimento) > 0) {
            segunda_mais_nova = mais_nova;
            mais_nova = pessoas[i];
        } else if (strcmp(pessoas[i].data_nascimento, segunda_mais_nova.data_nascimento) > 0) {
            segunda_mais_nova = pessoas[i];
        }
    }
    
    return segunda_mais_nova;
}
bool eh_primo(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void remover_primos() {
    int num_removidos = 0;
    
    for (int i = 0; i < num_pessoas; i++) {
        int ano_nascimento = atoi(strtok(pessoas[i].data_nascimento, "/"));
        if (eh_primo(ano_nascimento)) {
            for (int j = i; j < num_pessoas - 1; j++) {
                pessoas[j] = pessoas[j+1];
            }
            num_pessoas--;
            num_removidos++;
            i--;
        }
    }
    
    printf("%d pessoas foram removidas.\n", num_removidos);
}

int main() {
    int opcao;
    
    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adicionar pessoa\n");
        printf("2 - Remover pessoa\n");
        printf("3 - Listar pessoas\n");
        printf("4 - Pessoa mais velha\n");
        printf("5 - Segunda pessoa mais nova\n");
        printf("6 - Remover pessoas com ano de nascimento primo\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                adicionar_pessoa();
                break;
            case 2:
                remover_pessoa();
                break;
            case 3:
                listar_pessoas();
                break;
            case 4:
                printf("Pessoa mais velha:\n");
                Pessoa mais_velha = pessoa_mais_velha();
                printf("%d\t%s\t%s\t%s\n", mais_velha.id, mais_velha.nome, mais_velha.apelido, mais_velha.data_nascimento);
                break;
            case 5:
                printf("Segunda pessoa mais nova:\n");
                Pessoa segunda_mais_nova = segunda_pessoa_mais_nova();
                printf("%d\t%s\t%s\t%s\n", segunda_mais_nova.id, segunda_mais_nova.nome, segunda_mais_nova.apelido, segunda_mais_nova.data_nascimento);
                break;
            case 6:
                remover_primos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
    
    return 0;
}

