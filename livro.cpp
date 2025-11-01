#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_LIVROS 100

typedef struct {
    char nome[127];  
    char autor[127];
    int ano;
    char genero[63];
} Livro;

char busca[127];
int i = 0;
Livro li[MAX_LIVROS];
int opcao;
int conf;

void limpaBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void procurar() {
    if (i == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        printf("Digite o nome do livro que deseja deletar: ");
        if (fgets(busca, sizeof(busca), stdin) == NULL) busca[0] = '\0'; 
        size_t len_busca = strlen(busca);
        if (len_busca > 0 && busca[len_busca - 1] == '\n') busca[len_busca - 1] = '\0';
    }
}

void cadastrarLivro(){
    if (i >= MAX_LIVROS) {
        printf("Limite de livros atingido!\n");
        return;
    }

    printf("\n--- Cadastro do %d° Livro ---", i + 1);
    printf("\nNome: ");
    if (fgets(li[i].nome, sizeof li[i].nome, stdin) == NULL) li[i].nome[0] = '\0';
    size_t len_nome = strlen(li[i].nome);
    if (len_nome > 0 && li[i].nome[len_nome - 1] == '\n') li[i].nome[len_nome - 1] = '\0';

    printf("Autor: ");
    if (fgets(li[i].autor, sizeof li[i].autor, stdin) == NULL) li[i].autor[0] = '\0';
    size_t len_autor = strlen(li[i].autor);
    if (len_autor > 0 && li[i].autor[len_autor - 1] == '\n') li[i].autor[len_autor - 1] = '\0';

    printf("Ano: ");
    if (scanf("%d", &li[i].ano) != 1) li[i].ano = 0;
    limpaBuffer();

    printf("genero: ");
    if (fgets(li[i].genero, sizeof li[i].genero, stdin) == NULL) li[i].genero[0] = '\0';
    size_t len_cat = strlen(li[i].genero);
    if (len_cat > 0 && li[i].genero[len_cat - 1] == '\n') li[i].genero[len_cat - 1] = '\0';

    printf("Livro cadastrado com sucesso!\n");
    i++; // Incrementar o índice após cadastrar o livro
}

void listarLivros(){
    if (i == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
        } else {
            printf("\n--- Lista de livros ---\n");
    		for (int j = 0; j < i; ++j) {
    		    printf("\n--- %d° Livro ---\n", j + 1);
                printf("Nome: %s\n", li[j].nome);
                printf("Autor: %s\n", li[j].autor);
                printf("Ano: %d\n", li[j].ano);
                printf("genero: %s\n", li[j].genero);
            }
        }
}

void editarLivro() {
    procurar(); // usa a função existente para preencher 'busca'

    int encontrado = 0;
    int indiceLivro = -1;

    // Busca o livro pelo nome (armazenado em busca)
    for (int j = 0; j < i; j++) {
        if (strcmp(li[j].nome, busca) == 0) {
            encontrado = 1;
            indiceLivro = j;
            break;
        }
    }

    if (encontrado) {
        printf("\nLivro encontrado. Insira os novos dados:\n");

        printf("Novo Nome: ");
        if (fgets(li[indiceLivro].nome, sizeof(li[indiceLivro].nome), stdin) == NULL) li[indiceLivro].nome[0] = '\0';
        size_t len = strlen(li[indiceLivro].nome);
        if (len > 0 && li[indiceLivro].nome[len - 1] == '\n') li[indiceLivro].nome[len - 1] = '\0';

        printf("Novo Autor: ");
        if (fgets(li[indiceLivro].autor, sizeof(li[indiceLivro].autor), stdin) == NULL) li[indiceLivro].autor[0] = '\0';
        len = strlen(li[indiceLivro].autor);
        if (len > 0 && li[indiceLivro].autor[len - 1] == '\n') li[indiceLivro].autor[len - 1] = '\0';

        printf("Novo Ano de Publicação: ");
        if (scanf("%d", &li[indiceLivro].ano) != 1) li[indiceLivro].ano = 0;
        limpaBuffer();

        printf("Novo Gênero: ");
        if (fgets(li[indiceLivro].genero, sizeof(li[indiceLivro].genero), stdin) == NULL) li[indiceLivro].genero[0] = '\0';
        len = strlen(li[indiceLivro].genero);
        if (len > 0 && li[indiceLivro].genero[len - 1] == '\n') li[indiceLivro].genero[len - 1] = '\0';

        printf("Livro editado com sucesso!\n");
    } else {
        printf("Livro não encontrado.\n");
    }
}

void deletarLivro(){
    procurar(); // já preenche 'busca'

    int encontrado = 0;
    int indiceLivro = -1;

    for (int j = 0; j < i; j++) {
        if (strcmp(li[j].nome, busca) == 0) {
            encontrado = 1;
            indiceLivro = j;
            break;
        }
    }

    if (encontrado) {
        printf("\nLivro encontrado!\n");
        printf("Nome: %s\n", li[indiceLivro].nome);
        printf("Autor: %s\n", li[indiceLivro].autor);
        printf("Ano: %d\n", li[indiceLivro].ano);
        printf("Gênero: %s\n", li[indiceLivro].genero);

        printf("\nVocê tem certeza que deseja excluir este livro?\n");
        printf("(1) Sim    (2) Não\n");
        if (scanf("%d", &conf) != 1) {
            printf("Entrada inválida.\n");
            limpaBuffer();
            return;
        }
        limpaBuffer();

        if (conf == 1) {
            // desloca os livros para "tampar o buraco"
            for (int k = indiceLivro; k < i - 1; k++) {
                li[k] = li[k + 1];
            }
            i--; // atualiza o total de livros
            printf("Livro excluído com sucesso!\n");
        } else {
            printf("Operação cancelada.\n");
        }
    } else {
        printf("Livro não encontrado!\n");
    }
}   

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    do {
        printf("\n---------------------------\n");
        printf("........Biblioteca.........\n");
        printf("---------------------------\n");
        printf("1- Adicionar um livro;\n");
        printf("2- Lista de livros;\n");
        printf("3- Editar;\n");
        printf("4- Deletar;\n");
        printf("5- Sair.\n\n");
        printf("Escolha uma das opções: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            limpaBuffer();
            continue;
        }
        limpaBuffer(); // limpar resto da linha

        switch (opcao) {
        case 1:
            cadastrarLivro();
            break;
            
        case 2:
            listarLivros();
            break;

        case 3:
            editarLivro();
            break;
            
        case 4:
            deletarLivro();
            break;


        case 5:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 5);

    return 0;
}