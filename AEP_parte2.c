Projeto da faculdade sobre criptografia na linguagem C++

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void Criptografar(char chave[]) {
	
    int tam_chave = strlen(chave);
    char texto[100000];
    int texto_cript[100000];
    int valor_chave, aux = 0;

    printf("\n\nDigite o texto a ser criptografado: \n");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = 0; // Remove o newline

    for (int i = 0; i < strlen(texto); i++) {
        texto_cript[i] = texto[i];
    }

    aux = 0; // Reset aux for loop
    while (aux < strlen(texto)) {
        for (int i = 0; i < tam_chave && aux < strlen(texto); i++) {
            valor_chave = chave[i];
            texto_cript[aux] *= valor_chave;
            aux++;
        }
    }

    FILE* arquivo = fopen("criptografado.txt", "w");
    if (arquivo == NULL) {
        printf("\n\nErro ao criar o arquivo....\n\n\n");
        return;
    }
    for (int i = 0; i < strlen(texto); i++) {
        fprintf(arquivo, "%d ", texto_cript[i]);
    }
    fclose(arquivo);
}

void Decriptografar(char chave[]) {
    int tam_chave = strlen(chave);
    int texto_decript[10000];
    int valor, pos_chave = 0, pos_texto = 0;

    FILE* arquivo = fopen("criptografado.txt", "r");
    if (arquivo == NULL) {
        printf("\n\nErro ao abrir o arquivo......\n\n\n");
        return;
    }
    while (fscanf(arquivo, "%d", &valor) == 1) {
        valor /= chave[pos_chave];
        texto_decript[pos_texto] = (char)valor;
        pos_texto++;

        pos_chave = (pos_chave + 1) % tam_chave;
    }
    fclose(arquivo);

    FILE* saida = fopen("descriptografado.txt", "w");
    for (int i = 0; i < pos_texto; i++) {
        fputc(texto_decript[i], saida);
    }
    fclose(saida);
    printf("\n\nO arquivo foi descriptado com sucesso! \n\n\n");
}

int main(void) {
    int opcao = 0;
    do {
        printf("\nSelecione uma opcao: \n 1 - Criptografar texto digitado. \n 2 - Descriptografar texto. \n 3 - Sair. \n");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do newline apï¿½s scanf
        switch (opcao) {
        case 1:
            Criptografar("Abcd");
            break;
        case 2:
            Decriptografar("Abcd");
            break;
        case 3:
            break;
        default:
            printf("\nOpcao invalida! tente novamente. \n\n");
        }
    } while (opcao != 3);
    return 0;
}
