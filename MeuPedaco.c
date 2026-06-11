#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void limparTela(){
    system("cls");
}

void voltarAoMenu(){
    char resposta;
    do {
        printf("\nDigite 1 para voltar ao menu: ");
        scanf(" %c", &resposta);
        limparBuffer();
    } while(resposta != '1');
    limparTela();
}

void paraMinusculas(char texto[]){
    int i;
    for(i = 0; texto[i] != '\0'; i++){
        texto[i] = tolower(texto[i]);
    }
}

typedef struct {
    char nome[100];
    char categoria[50];
    char endereco[150];
} Local;

void cadastrarLocal() {
    FILE *arquivo = fopen("locais.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de locais!\n");
        return;
    }

    Local l;
    int catOpcao = 0;

    printf("\n--- Cadastrar Novo Local ---\n");
    printf("Nome do local (ex: Parque Vaca Brava, Hospital Santa Helena): ");
    scanf(" %99[^\n]", l.nome);
    limparBuffer();

    printf("Categoria:\n");
    printf("  1 - Lazer\n");
    printf("  2 - Cuidado\n");
    printf("  3 - Saude\n");
    printf("Escolha (1-3): ");
    while(scanf("%d", &catOpcao) != 1 || catOpcao < 1 || catOpcao > 3){
        limparBuffer();
        printf("Opcao invalida. Digite 1, 2 ou 3: ");
    }
    limparBuffer();

    switch(catOpcao){
        case 1: strcpy(l.categoria, "Lazer");   break;
        case 2: strcpy(l.categoria, "Cuidado"); break;
        case 3: strcpy(l.categoria, "Saude");   break;
    }

    printf("Endereco: ");
    scanf(" %149[^\n]", l.endereco);
    limparBuffer();

    fprintf(arquivo, "%s|%s|%s\n", l.nome, l.categoria, l.endereco);
    fclose(arquivo);
    printf("\nLocal cadastrado com sucesso!\n");
}

void listarLocais() {
    FILE *arquivo = fopen("locais.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum local cadastrado ainda.\n");
        return;
    }

    Local l;
    int total = 0;

    printf("\n--- Lista de Locais Cadastrados ---\n");
    while (fscanf(arquivo, " %99[^|]|%49[^|]|%149[^\n]", l.nome, l.categoria, l.endereco) == 3) {
        total++;
        printf("\n%d. %s\n", total, l.nome);
        printf("   Categoria: %s\n", l.categoria);
        printf("   Endereco:  %s\n", l.endereco);
    }
    fclose(arquivo);

    if (total == 0) {
        printf("Nenhum local cadastrado ainda.\n");
    } else {
        printf("\nTotal: %d local(is) cadastrado(s).\n", total);
    }
}

void buscarLocal() {
    FILE *arquivo = fopen("locais.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum local cadastrado ainda.\n");
        return;
    }

    Local l;
    char termo[50];
    char nomeMin[100], categoriaMin[50];
    int encontrou = 0;

    printf("\n--- Buscar Local ---\n");
    printf("Digite a categoria ou nome para buscar: ");
    scanf(" %49[^\n]", termo);
    limparBuffer();

    paraMinusculas(termo);

    printf("\nResultados encontrados para '%s':\n", termo);
    while (fscanf(arquivo, " %99[^|]|%49[^|]|%149[^\n]", l.nome, l.categoria, l.endereco) == 3) {
        strcpy(nomeMin, l.nome);
        strcpy(categoriaMin, l.categoria);
        paraMinusculas(nomeMin);
        paraMinusculas(categoriaMin);

        if (strstr(nomeMin, termo) != NULL || strstr(categoriaMin, termo) != NULL) {
            printf("\n- %s\n", l.nome);
            printf("  Categoria: %s\n", l.categoria);
            printf("  Endereco:  %s\n", l.endereco);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum local encontrado com esse termo.\n");
    }
    fclose(arquivo);
}

int carregarLocais(Local locais[], int max){
    FILE *arquivo = fopen("locais.txt", "r");
    if (arquivo == NULL) {
        return 0;
    }

    int total = 0;
    while (total < max &&
           fscanf(arquivo, " %99[^|]|%49[^|]|%149[^\n]",
                  locais[total].nome, locais[total].categoria, locais[total].endereco) == 3) {
        total++;
    }
    fclose(arquivo);
    return total;
}

void salvarLocais(Local locais[], int total){
    FILE *arquivo = fopen("locais.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de locais!\n");
        return;
    }

    int i;
    for (i = 0; i < total; i++) {
        fprintf(arquivo, "%s|%s|%s\n", locais[i].nome, locais[i].categoria, locais[i].endereco);
    }
    fclose(arquivo);
}

void editarLocal() {
    Local locais[100];
    int total = carregarLocais(locais, 100);

    if (total == 0) {
        printf("\nNenhum local cadastrado ainda.\n");
        return;
    }

    listarLocais();

    int escolha;
    printf("\n--- Editar Local ---\n");
    printf("Digite o numero do local que deseja editar (0 para cancelar): ");
    while (scanf("%d", &escolha) != 1 || escolha < 0 || escolha > total) {
        limparBuffer();
        printf("Opcao invalida. Digite um numero entre 0 e %d: ", total);
    }
    limparBuffer();

    if (escolha == 0) {
        printf("Edicao cancelada.\n");
        return;
    }

    Local *l = &locais[escolha - 1];

    printf("\nEditando: %s\n", l->nome);
    printf("Novo nome: ");
    scanf(" %99[^\n]", l->nome);
    limparBuffer();

    int catOpcao;
    printf("Nova categoria:\n");
    printf("  1 - Lazer\n");
    printf("  2 - Cuidado\n");
    printf("  3 - Saude\n");
    printf("Escolha (1-3): ");
    while (scanf("%d", &catOpcao) != 1 || catOpcao < 1 || catOpcao > 3) {
        limparBuffer();
        printf("Opcao invalida. Digite 1, 2 ou 3: ");
    }
    limparBuffer();

    switch (catOpcao) {
        case 1: strcpy(l->categoria, "Lazer");   break;
        case 2: strcpy(l->categoria, "Cuidado"); break;
        case 3: strcpy(l->categoria, "Saude");   break;
    }

    printf("Novo endereco: ");
    scanf(" %149[^\n]", l->endereco);
    limparBuffer();

    salvarLocais(locais, total);
    printf("\nLocal editado com sucesso!\n");
}

void excluirLocal() {
    Local locais[100];
    int total = carregarLocais(locais, 100);

    if (total == 0) {
        printf("\nNenhum local cadastrado ainda.\n");
        return;
    }

    listarLocais();

    int escolha;
    printf("\n--- Excluir Local ---\n");
    printf("Digite o numero do local que deseja excluir (0 para cancelar): ");
    while (scanf("%d", &escolha) != 1 || escolha < 0 || escolha > total) {
        limparBuffer();
        printf("Opcao invalida. Digite um numero entre 0 e %d: ", total);
    }
    limparBuffer();

    if (escolha == 0) {
        printf("Exclusao cancelada.\n");
        return;
    }

    char confirma;
    printf("Tem certeza que deseja excluir '%s'? (S/N): ", locais[escolha - 1].nome);
    scanf(" %c", &confirma);
    limparBuffer();

    if (confirma != 'S' && confirma != 's') {
        printf("Exclusao cancelada.\n");
        return;
    }

    int i;
    for (i = escolha - 1; i < total - 1; i++) {
        locais[i] = locais[i + 1];
    }
    total--;

    salvarLocais(locais, total);
    printf("\nLocal excluido com sucesso!\n");
}

void cadastrarUsuario(){
    FILE *cadastro = fopen("cadastro.txt", "w");
    if(cadastro == NULL){
        printf("Erro, nao foi possivel criar o arquivo de cadastro\n");
        return;
    }

    char nome[100];
    int idade;

    printf("\n--- Criar Cadastro ---\n");
    printf("Digite seu nome: ");
    scanf(" %99[^\n]", nome);
    limparBuffer();

    printf("Digite sua idade: ");
    while(scanf("%d", &idade) != 1 || idade < 1 || idade > 120){
        limparBuffer();
        printf("Idade invalida. Digite um numero entre 1 e 120: ");
    }
    limparBuffer();

    fprintf(cadastro, "Nome: %s\n", nome);
    fprintf(cadastro, "Idade: %d\n", idade);
    fclose(cadastro);

    printf("Cadastro de usuario realizado com sucesso!\n");
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    FILE *cadastro;
    char nome[100], login;
    int logado = 0;

    printf("+==========================================+\n");
    printf("|   Bem-vindo ao MeuPedaÃ§o - Apoio 60+!   |\n");
    printf("+==========================================+\n");

    do {
        printf("Ja possui login? (S/N): ");
        scanf(" %c", &login);
        limparBuffer();

        if(login == 'N' || login == 'n'){
            cadastrarUsuario();
            logado = 1;
        }
        else if(login == 'S' || login == 's'){
            cadastro = fopen("cadastro.txt", "r");
            if(cadastro == NULL){
                printf("\nNenhum cadastro encontrado! Vamos criar o seu agora.\n");
                cadastrarUsuario();
                logado = 1;
            } else {
                int leu = fscanf(cadastro, "Nome: %99[^\n]", nome);
                fclose(cadastro);
                if(leu != 1){
                    printf("\nSeu cadastro estava vazio ou corrompido. Vamos criar um novo.\n");
                    cadastrarUsuario();
                }
                logado = 1;
            }
        }
        else {
            printf("Opcao invalida! Digite S ou N.\n");
        }
    } while(logado == 0);

    int idade = 0;
    cadastro = fopen("cadastro.txt", "r");
    if(cadastro != NULL){
        if(fscanf(cadastro, "Nome: %99[^\n]", nome) != 1){
            strcpy(nome, "visitante");
        }
        fscanf(cadastro, " Idade: %d", &idade);
        fclose(cadastro);
    } else {
        strcpy(nome, "visitante");
    }

    limparTela();
    printf("Bem-vindo(a), %s!\n", nome);
    if(idade >= 60){
        printf("Voce faz parte do nosso publico especial 60+. Seja muito bem-vindo(a)!\n");
    }

    int opcao;
    do {
        printf("\n+==========================================+\n");
        printf("|              MENU PRINCIPAL              |\n");
        printf("+==========================================+\n");
        printf("|  1 - Cadastrar Local                     |\n");
        printf("|  2 - Listar Locais                       |\n");
        printf("|  3 - Buscar Local (categoria ou nome)    |\n");
        printf("|  4 - Editar Local                        |\n");
        printf("|  5 - Excluir Local                       |\n");
        printf("|  0 - Sair                                |\n");
        printf("+==========================================+\n");
        printf("Escolha uma opcao: ");
        if(scanf("%d", &opcao) != 1){
            opcao = -1;
        }
        limparBuffer();

        limparTela();

        switch(opcao) {
            case 1:
                cadastrarLocal();
                voltarAoMenu();
                break;
            case 2:
                listarLocais();
                voltarAoMenu();
                break;
            case 3:
                buscarLocal();
                voltarAoMenu();
                break;
            case 4:
                editarLocal();
                voltarAoMenu();
                break;
            case 5:
                excluirLocal();
                voltarAoMenu();
                break;
            case 0:
                printf("Saindo do sistema. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
