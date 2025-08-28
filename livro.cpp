#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_LIVROS 100

typedef struct {
    char nome[127];  
    char autor[127];
    char isbn[50];
    char editora[50];
    int ano;
    int numeroP;
    char categoria[63];
    int copias;
} Livro;

void limpaBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    setlocale(LC_ALL, ""); // permite acentos no console (depende do SO)
    Livro li[MAX_LIVROS];
    int opcao;
    int n;
    int i = 0; // índice do próximo livro a ser cadastrado

    do {
        printf("\n---------------------------\n");
        printf("........Biblioteca........\n");
        printf("---------------------------\n");
        printf("1- Adicionar um livro;\n");
        printf("2- Buscar livro;\n");
        printf("3- Lista de livros;\n");
        printf("4- Sair.\n");
        printf("Escolha uma das opções: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            limpaBuffer();
            continue;
        }
        limpaBuffer(); // limpar resto da linha

        switch (opcao) {
        case 1:
            if (i >= MAX_LIVROS) {
                printf("Limite de livros atingido!\n");
                break;
            }

            {
                // Usando um bloco para limitar o escopo das variáveis
                printf("\nLivro %d Nome: ", i + 1);
                if (fgets(li[i].nome, sizeof li[i].nome, stdin) == NULL) li[i].nome[0] = '\0';
                size_t len_nome = strlen(li[i].nome);
                if (len_nome > 0 && li[i].nome[len_nome - 1] == '\n') li[i].nome[len_nome - 1] = '\0';

                printf("Livro %d Autor: ", i + 1);
                if (fgets(li[i].autor, sizeof li[i].autor, stdin) == NULL) li[i].autor[0] = '\0';
                size_t len_autor = strlen(li[i].autor);
                if (len_autor > 0 && li[i].autor[len_autor - 1] == '\n') li[i].autor[len_autor - 1] = '\0';

                printf("Livro %d ISBN: ", i + 1);
                if (fgets(li[i].isbn, sizeof li[i].isbn, stdin) == NULL) li[i].isbn[0] = '\0';
                size_t len_isbn = strlen(li[i].isbn);
                if (len_isbn > 0 && li[i].isbn[len_isbn - 1] == '\n') li[i].isbn[len_isbn - 1] = '\0';

                printf("Livro %d Editora: ", i + 1);
                if (fgets(li[i].editora, sizeof li[i].editora, stdin) == NULL) li[i].editora[0] = '\0';
                size_t len_editora = strlen(li[i].editora);
                if (len_editora > 0 && li[i].editora[len_editora - 1] == '\n') li[i].editora[len_editora - 1] = '\0';

                printf("Livro %d Ano: ", i + 1);
                if (scanf("%d", &li[i].ano) != 1) li[i].ano = 0;

                printf("Livro %d Número de Páginas: ", i + 1);
                if (scanf("%d", &li[i].numeroP) != 1) li[i].numeroP = 0;

                limpaBuffer();

                printf("Livro %d Categoria: ", i + 1);
                if (fgets(li[i].categoria, sizeof li[i].categoria, stdin) == NULL) li[i].categoria[0] = '\0';
                size_t len_cat = strlen(li[i].categoria);
                if (len_cat > 0 && li[i].categoria[len_cat - 1] == '\n') li[i].categoria[len_cat - 1] = '\0';

                printf("Livro %d Número de Cópias: ", i + 1);
                if (scanf("%d", &li[i].copias) != 1) li[i].copias = 0;

                limpaBuffer();
                printf("Livro cadastrado com sucesso!\n");
                i++; // Incrementar o índice após cadastrar o livro
            }
            break;

        case 2:
            if (i == 0) {
                printf("Nenhum livro cadastrado ainda.\n");
            } else {
                printf("Funcionalidade de busca ainda não implementada.\n");
            }
            break;

        case 3:
            if (i == 0) {
                printf("Nenhum livro cadastrado ainda.\n");
            } else {
                printf("\n--- Lista de livros ---\n");
    			for (int i = 0; i < n; ++i) {
        		printf("[%d]\n", i + 1);
        		printf("Nome: %s\n", li[i].nome);
        		printf("Autor: %s\n", li[i].autor);
        		printf("ISBN: %s\n", li[i].isbn);
        		printf("Editora: %s\n", li[i].editora);
        		printf("Ano: %d\n", li[i].ano);
       	 		printf("Número de Páginas: %d\n", li[i].numeroP);
        		printf("Categoria: %s\n", li[i].categoria);
        		printf("Número de Cópias: %d\n", li[i].copias);
    			}
            }
            break;

        case 4:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 4);

    return 0;
}