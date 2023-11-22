// ----------------------------------------------------------------------------------------------------------------------------
// Início do código fornecido pelo professor
// Não adicione ou remova nada.

// Se estiver no Windows e não conseguir ver a imagem colorida, pode ser que seu terminal não suporte Ascii Escape Colors.
// Para habilitá-la, execute o comando abaixo no terminal com permissão de Administrador.
// Após executado, o terminado deve ser fechado e aberto novamente para ter o suporte às cores habilitado.
// Comando:
// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/// Estrutura que representa uma imagem em Ascii
struct asciiImg_s {
    uint8_t* bytes;
    int nBytes;
};

/// Tipo "Imagem ASCII"
typedef struct asciiImg_s asciiImg_t;

// Tamanho do buffer para cada linha da imagem
#define BUFFER_TAMANHO  50000

// Tamanho máximo da linha de comando
#define LINHA_COMANDO   10000

// Limiar inferior que considera o download com sucesso
#define LIMIAR_INFERIOR_TAMANHO_IMAGEM  500

// Nome do executável da ferramenta de download e conversão da imagem
#ifdef __unix__
#define FERRAMENTA_IMAGEM   "./ascii-image-converter.bin"
#else
#define FERRAMENTA_IMAGEM   "ascii-image-converter.exe"
#endif

// Nome do arquivo de saída temporário da imagem
#define ARQUIVO_IMAGEM_TMP  "ascii_art.txt"

/**
 *  \brief Função que carrega uma imagem informada na URL.
 *
 *  \param [in] colorido Define se a imagem será colorida.
 *  \param [in] largura Define a largura da imagem gerada.
 *  \return Endereço da estrutura com a imagem.
 *          Caso a imagem não tenha sido carregada corretamente, a função
 *          retornará NULL.
 */
asciiImg_t* insta_carregaImagem(char url[], bool colorido, int largura) {

    FILE* arquivo;
    char buffer[BUFFER_TAMANHO];
    int nBytes, nBytesTotal = 0;
    char linhaComando[LINHA_COMANDO];

    asciiImg_t* img;

    // Aloca espaço para uma imagem
    img = malloc(sizeof(asciiImg_t));
    if (img == NULL) return NULL;

    // Inicializa a estrutura
    img->bytes = NULL;
    img->nBytes = 0;

    // Monta a linha de comando
    (void)sprintf(linhaComando, "%s %s %s -W %d -c > %s", FERRAMENTA_IMAGEM, url, (colorido ? "-C" : ""), largura, ARQUIVO_IMAGEM_TMP);

    // Chama o programa para fazer o download da imagem
    (void)system(linhaComando);

    // Tenta abrir o arquivo recem criado
    arquivo = fopen(ARQUIVO_IMAGEM_TMP, "r");
    if (arquivo != NULL) {

        while (!feof(arquivo)) {

            // Limpa a linha
            (void)memset(buffer, 0, sizeof(buffer));

            // Tenta ler uma linha
            if (fgets(buffer, BUFFER_TAMANHO, arquivo) == NULL) continue;

            // Descobre o número de bytes da linha
            for (nBytes = 0; buffer[nBytes] != 0; nBytes++);

            // Aloca o espaço
            img->bytes = realloc(img->bytes, sizeof(unsigned char) * (nBytesTotal + nBytes));

            // Copia para o espaço alocado
            (void)memcpy(&(img->bytes[nBytesTotal]), buffer, nBytes);
            nBytesTotal += nBytes;
        }

        // Finaliza a imagem colocando o \0 final e o tamanho
        img->bytes = realloc(img->bytes, sizeof(unsigned char) * (nBytesTotal + 1));
        img->bytes[nBytesTotal++] = '\0';
        img->nBytes = nBytesTotal;

        // Fecha o arquivo
        fclose(arquivo);
    }

    // Verifica se a imagem é válida
    if (img->nBytes < LIMIAR_INFERIOR_TAMANHO_IMAGEM) {
        // Libera todo o espaço alocado
        free(img->bytes);
        free(img);

        return NULL;
    }

    // Retorna a imagem carregada
    return img;
}

/**
 *  \brief Função que imprime uma Imagem ASCII.
 *
 *  \param [in] img Endereço da estrutura com os dados da imagem.
 */
void insta_imprimeImagem(asciiImg_t* img) {
    printf("%s", img->bytes);
}

/**
 *  \brief Função que libera a memória alocada por uma imagem.
 *
 *  \param [in] img Endereço da estrutura com os dados da imagem a ser liberada.
 */
void insta_liberaImagem(asciiImg_t* img) {
    free(img->bytes);
    free(img);
}

// Fim do código fornecido pelo professor
// ----------------------------------------------------------------------------------------------------------------------------
/*Coltegram desnvolvido por
    Lucas Lemos Ricaldoni
    Matheus Procopio Fonseca 
    Todos os direitos reservados à ambos
*/
/* Inclusões */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

/* Erros */

// Constante que associa o código de erro 0 a execução esperada.
#define SUCESSO 0
#define ERRO -1
#define VALIDO 1
#define DESISTENCIA 2

// Falha ao carregar a imagem fornecida
#define ERRO_CARREGAR_IMAGEM 1

/* Constantes */

// Número de colunas da imagem
#define IMAGEM_NUMERO_COLUNAS     120

// Definição de imagem colorida
#define IMAGEM_COLORIDA           true
// Definição de imagem preto/branco
#define IMAGEM_PRETO_BRANCO      false
// Definição de imagem utilizada
#define MODO_IMAGEM               IMAGEM_COLORIDA
// Definição do tamanho das strings
#define MAX_DESCRICAO (100 + 1)
#define MAX_URL (500 + 1)
#define MAX_ID (20 + 1)    
#define MAX_NOME (30 + 1)  
#define MAX_EMAIL (40 + 1)
#define MAX_SENHA (20 + 1)
#define MAX_BIO (150 + 1)
#define MAX_LINHA (1000 + 1)
#define TAMANHOESCOLHA (1 + 1)
#define MAX_COR (4 + 1)
#define MAX_FOTO (3 + 1)
#define MAX_COMENTARIO (200 + 1)

// Definição das costantes literais
#define LARGURA 100
#define MAX_FOTOS_POST 10
#define MAX_POSTAGENS 100
#define MAX_NUM_COMENTARIOS 50
#define OPC_CONTINUAR_POST 4
#define MAX_CURTIDAS 500
#define MUDAR_POST 1
#define SAIR 0
#define DESLOGAR 8
#define ADD_FOTO 2
#define NOME 3
#define EMAIL 2
#define PRIMEIRO_EMAIL 4
#define ID 1
#define TODOS 99
#define UNICO 98
#define UM 1
#define ZERO 0
#define TAMANHO_INICIAL 100
#define DOIS 2
/* Definição das Structs*/
//struct para postagens
typedef struct {
    char urlImagemPost[MAX_URL];
    char urlLidas[MAX_URL][MAX_FOTOS_POST];
    int numCurtidasPost;
    char descricaoPost[MAX_DESCRICAO];
    int numComentariosPost;
    char comentariosPost[MAX_NUM_COMENTARIOS][MAX_DESCRICAO];
    char cor[MAX_COR];
    char idPerfil[MAX_ID];
    int id;
    int qntFotosPost;
}postStruct;
// struct para o guardar os dados do perfil
typedef struct {
    char id[MAX_ID];
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
    char urlFotoPerfil[MAX_URL];
    char bioPerfil[MAX_BIO];
    char cor[MAX_COR];
    bool possuiFoto;
} perfilStruct;
// struct para o login
typedef struct {
    char id[MAX_ID];
    char senha[MAX_SENHA];
    bool logado;
    bool curtido[MAX_POSTAGENS];
    postStruct postagens[MAX_POSTAGENS];
} loginStruct;
// struct usada de busca
typedef struct {
    char id[MAX_ID];
    int  idFoto;
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
    char auxiliar[MAX_EMAIL];
    char bioPerfil[MAX_BIO];
    char urlFotoPerfil[MAX_URL];
    char cor[MAX_COR];
    bool possuiFoto;
} buscaStruct;
//struct para dados de postagens temporarios
typedef struct {
    char urlImagemPost[MAX_URL];
    int numCurtidasPost;
    char descricaoPost[MAX_DESCRICAO];
    int numComentariosPost;
    bool cor;
    char idPerfil[MAX_ID];
    int id;
} postTempStruct;

/* Funções de seguir
- numSeguindo - calcula o numero de perfis que determinado id esta seguindo
- numSeguidores - calcula o numero de seguidores de determinado id
- deixarDeSeguir - remove o id recebido da lista dos seguidores
- verificaSeguida - verifica se o id recebido ja segue outro id recebido
- seguirPerfil - adiciona o id recebido a uma lista dos seguidores de outro id recebido
*/

int numSeguindo(char idPerfil[]) {
    FILE* arquivoSeguidas;
    char linha[MAX_LINHA];
    char seguidorTemp[MAX_ID];
    char idPerfilTemp[MAX_ID];
    int numeroDeSeguindo = 0;
    arquivoSeguidas = fopen("seguidas.txt", "a+");
    fseek(arquivoSeguidas, ZERO, SEEK_SET);
    while (fgets(linha, MAX_LINHA, arquivoSeguidas) != NULL) {
        sscanf(linha, "Seguidor: %[^\t]\tIdPerfil: %[^\t]\t\n", seguidorTemp, idPerfilTemp);
        if (strcmp(seguidorTemp, idPerfil) == SUCESSO) {
            numeroDeSeguindo++;
        }
    }
    return numeroDeSeguindo;
}

int numSeguidores(char idPerfil[]) {
    FILE* arquivoSeguidas;
    char linha[MAX_LINHA];
    char seguidorTemp[MAX_ID];
    char idPerfilTemp[MAX_ID];
    int numeroDeSeguidores = 0;
    arquivoSeguidas = fopen("seguidas.txt", "a+");
    fseek(arquivoSeguidas, ZERO, SEEK_SET);
    while (fgets(linha, MAX_LINHA, arquivoSeguidas) != NULL) {
        sscanf(linha, "Seguidor: %[^\t]\tIdPerfil: %[^\t]\t\n", seguidorTemp, idPerfilTemp);
        if (strcmp(idPerfil, idPerfilTemp) == SUCESSO) {
            numeroDeSeguidores++;
        }
    }
    return numeroDeSeguidores;
}

int deixarDeSeguir(char seguidor[], char idPerfil[]) {
    FILE* arquivoSeguidas, * arquivoAuxSeguidas;
    char idPerfilTemp[MAX_ID];
    char seguidorTemp[MAX_ID], linha[MAX_LINHA];

    arquivoSeguidas = fopen("seguidas.txt", "r");
    arquivoAuxSeguidas = fopen("seguidasAuxiliar.txt", "w");
    if (arquivoSeguidas == NULL || arquivoAuxSeguidas == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoSeguidas, ZERO, SEEK_SET);
        while (fgets(linha, MAX_LINHA, arquivoSeguidas) != NULL) {
            sscanf(linha, "Seguidor: %[^\t]\tIdPerfil: %[^\t]\t\n", seguidorTemp, idPerfilTemp);
            if (strcmp(seguidor, seguidorTemp) == SUCESSO) {
                if (strcmp(idPerfil, idPerfilTemp) == SUCESSO) {
                    //nao faz nada
                }
                else {
                    fprintf(arquivoAuxSeguidas, "Seguidor: %s\tIdPerfil: %s\t\n", seguidorTemp, idPerfilTemp);
                }
            }
            else {
                fprintf(arquivoAuxSeguidas, "Seguidor: %s\tIdPerfil: %s\t\n", seguidorTemp, idPerfilTemp);
            }
        }
    }
    fclose(arquivoSeguidas);
    fclose(arquivoAuxSeguidas);

    arquivoAuxSeguidas = fopen("seguidasAuxiliar.txt", "r");
    arquivoSeguidas = fopen("seguidas.txt", "w");

    if (arquivoSeguidas == NULL || arquivoAuxSeguidas == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    //passa os dados lidos para o arquivo definitivo
    fseek(arquivoAuxSeguidas, ZERO, SEEK_SET);
    while (fgets(linha, MAX_LINHA, arquivoAuxSeguidas) != NULL) {
        sscanf(linha, "Seguidor: %[^\t]\tIdPerfil: %[^\t]\t\n", seguidorTemp, idPerfilTemp);
        if (strcmp(seguidor, seguidorTemp) == ZERO) {
            if (strcmp(idPerfil, idPerfilTemp) == SUCESSO) {
                //nao faz nada
            }
            else {
                fprintf(arquivoSeguidas, "Seguidor: %s\tIdPerfil: %s\t\n", seguidorTemp, idPerfilTemp);
            }
        }
        else {
            fprintf(arquivoSeguidas, "Seguidor: %s\tIdPerfil: %s\t\n", seguidorTemp, idPerfilTemp);
        }
    }
    printf("Agora você deixou de seguir @%s.\n", idPerfil);
    fclose(arquivoAuxSeguidas);
    fclose(arquivoSeguidas);
    return SUCESSO;
}

bool verificaSeguida(char seguidor[], char idPerfil[]) {
    FILE* arquivoSeguidas;
    char linhaSeguida[MAX_LINHA];
    char seguidorTemp[MAX_ID], idPerfilTemp[MAX_ID];

    arquivoSeguidas = fopen("seguidas.txt", "a+");
    if (arquivoSeguidas == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return ERRO;
    }
    fseek(arquivoSeguidas, ZERO, SEEK_SET);
    while (fgets(linhaSeguida, MAX_LINHA, arquivoSeguidas) != NULL) {
        sscanf(linhaSeguida, "Seguidor: %[^\t]\tIdPerfil: %[^\t]\t\n", seguidorTemp, idPerfilTemp);
        if (strcmp(seguidorTemp, seguidor) == SUCESSO) {
            if (strcmp(idPerfilTemp, idPerfil) == SUCESSO) {
                fclose(arquivoSeguidas);
                return true;//ja segue
            }
        }
    }
    fclose(arquivoSeguidas);
    return false; //se chegou ate aqui é por que não 
}

int seguirPerfil(char seguidor[], char idPerfil[]) {
    FILE* arquivoSeguidas;

    arquivoSeguidas = fopen("seguidas.txt", "a");
    if (arquivoSeguidas == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return ERRO;
    }
    fseek(arquivoSeguidas, ZERO, SEEK_SET);
    fprintf(arquivoSeguidas, "Seguidor: %s\tIdPerfil: %s\t\n", seguidor, idPerfil);
    fclose(arquivoSeguidas);
    printf("\nAgora voce esta seguindo o perfil de @%s\n", idPerfil);
    return SUCESSO;
}

/* Funções essencias
* util_removeQuebraLinhaFinal; remove o \n
* reallocLimite; caso os perfis atingam o tamanho maximo a função realloca o tamanho
* ordenacaoBuble, ordena em ordem alfabetica as strings
* opcaoOrdenacao; selecionar qual parametro (id/nome/email) sera usado na ordenação
* imprimeTabela; imprime a tabela com os dados dos perfis cadastrados
* maiorIdPost; retorna o maior id presente no arquivo postagens.txt
* mostraImagem; imprime na tela a imagem desejada pelo usuario, junto com os dados dela
*/

// Funçao para tirar o "\n"
void util_removeQuebraLinhaFinal(char dados[]) {
    int tamanho;
    tamanho = strlen(dados);
    if ((tamanho > ZERO) && (dados[tamanho - UM] == '\n')) {
        dados[tamanho - UM] = '\0';
    }
}

void reallocLimite(perfilStruct** perfil, int* QNT_Perfil, int* limiteContas, int* novoLimiteContas) {
    if (*QNT_Perfil >= *limiteContas) {
        perfilStruct* perfilExtra = realloc(*perfil, (*novoLimiteContas) * sizeof(perfilStruct));//realloca o perfil
        if (perfilExtra == NULL) { //memoria alocada foi negada
            printf("Memoria nao foi alocada\n");
            free(*perfil); //libera a memoria
        }
        else {
            *perfil = perfilExtra;
            *limiteContas = *novoLimiteContas;
        }
    }
}

void ordenacaoBuble(perfilStruct string[], int tamanho, int tipo) { // recebe a variavel string, o tamanho e o tipo
    int i, j;
    perfilStruct aux;
    for (i = ZERO; i < tamanho; i++) {
        for (j = ZERO; j < tamanho - i - UM; j++) {
            if (tipo == ID && strcmp(string[j].id, string[j + UM].id) > ZERO) {// verifica se o tipo for ID
                aux = string[j];
                string[j] = string[j + UM];
                string[j + UM] = aux;
            }
            else if (tipo == NOME && strcmp(string[j].nome, string[j + UM].nome) > ZERO) { // verifica se o tipo for nome
                aux = string[j];
                string[j] = string[j + UM];
                string[j + UM] = aux;
            }
            else if (tipo == EMAIL && strcmp(string[j].email, string[j + UM].email) > ZERO) { // verifica se o tipo for email
                aux = string[j];
                string[j] = string[j + UM];
                string[j + UM] = aux;
            }
        }
    }
}

int opcaoOrdenacao() {
    char escolhaListagem[TAMANHOESCOLHA];
    //armazen por qual dados será ordenado
    printf("Os perfis serão ordenados por\n'i' = id\n'e' = email\n'n' = nome\n");
    fgets(escolhaListagem, TAMANHOESCOLHA, stdin);
    util_removeQuebraLinhaFinal(escolhaListagem);
    if (strcmp(escolhaListagem, "i") == SUCESSO) {
        //envia id para ser ordenado
        return ID;
    }
    else if (strcmp(escolhaListagem, "e") == SUCESSO) {
        //envia email para ser ordenado
        return EMAIL;
    }
    else if (strcmp(escolhaListagem, "n") == SUCESSO) {
        //envia nome para ser ordenado        
        return NOME;
    }
    else {
        printf("Opção de ordenação inválida!\n");
        return ERRO;
    }
}

void imprimeTabela(perfilStruct* perfil, int qnt_linha) {
    int ordenacaoEscolha;
    char temFoto[MAX_FOTO];
    ordenacaoEscolha = opcaoOrdenacao(); // chama a funcao de escolha de ordenação
    printf("\n%-20s|%-30s|%-40s|%-20s|%-8s|%-20s|%-15s\n", "ID", "NOME", "EMAIL", "SENHA", "FOTO", "SEGUIDORES", "SEGUINDO");
    if (ordenacaoEscolha == ID) {
        ordenacaoBuble(perfil, qnt_linha, ID);  // recebe o array de structs, tamanho e o seu tipo de ordenacao
    }
    else if (ordenacaoEscolha == EMAIL) {
        ordenacaoBuble(perfil, qnt_linha, EMAIL); // recebe o array de structs, tamanho e o seu tipo de ordenacao
    }
    else if (ordenacaoEscolha == NOME) {
        ordenacaoBuble(perfil, qnt_linha, NOME); // recebe o array de structs, tamanho e o seu tipo de ordenacao
    }
    for (int i = ZERO; i < qnt_linha; i++) {
        if (perfil[i].possuiFoto == true) {
            //copia o "sim" para a variavel "temFoto"
            strcpy(temFoto, "Sim");
        }
        if (perfil[i].possuiFoto == false) {
            //copia "não" para a variavel "temFoto"
            strcpy(temFoto, "Nao");
        }

        printf("%-20s|%-30s|%-40s|%-20s|%-8s|%-20d|%-15d\n", perfil[i].id, perfil[i].nome, perfil[i].email, perfil[i].senha, temFoto, numSeguidores(perfil[i].id), numSeguindo(perfil[i].id));
    }
}

int maiorIdPost() {
    FILE* arquivoFotos;
    postTempStruct dadosTemp;
    int maiorId = -1;
    char cor[MAX_COR];
    char linha[MAX_LINHA];
    arquivoFotos = fopen("postagens.txt", "r");
    if (arquivoFotos == NULL) {
        printf("Erro ao abrir arquivo!\n");
        fclose(arquivoFotos);
        return ERRO;
    }
    fseek(arquivoFotos, ZERO, SEEK_SET);
    while (fgets(linha, MAX_LINHA, arquivoFotos) != NULL) {
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n",
            dadosTemp.urlImagemPost, cor, &dadosTemp.id, dadosTemp.descricaoPost, dadosTemp.idPerfil, &dadosTemp.numCurtidasPost, &dadosTemp.numComentariosPost);
        if (dadosTemp.id >= maiorId) {
            maiorId = dadosTemp.id;
        }
    }
    fclose(arquivoFotos);
    return maiorId + 1;
}



void mostraImagem(int fotosTotais, int fotoNumero, char* url, bool cor, char descricao[], char idPerfil[], int curtidas, int comentarios) {
    asciiImg_t* imagem;
    imagem = insta_carregaImagem(url, cor, LARGURA);
    printf("=========================================================================================================\n");
    insta_imprimeImagem(imagem);
    insta_liberaImagem(imagem);
    printf("Foto numero %d/%d\n", fotoNumero, fotosTotais);
    printf("Curtidas: %d\tComentarios: %d\n", curtidas, comentarios);
    printf("@%s: %s\n", idPerfil, descricao);
    printf("=========================================================================================================\n");
}

/*Funções de comentários
- verComentarios = mostra todos os comentarios de determinado id de post
- verificaComentarios = verifica
- editarComentario = dá a opcao de editar seu comentario
- retirarComentarioArquivo = diminui o numero de comentarios no arquivo postagens.txt em um
- apagarComentarios = da a opcao de apagar determinado comentario
- adicionarNumComentario = aumenta o numero de comentarios no arquivo postagens.txt em um
- comentarPerfil = dá a opção de comentar em determinado post
- secaoComentarios = menu simples para deixar o usuário escolher o que quer
*/

int verComentarios(int idPost) {
    FILE* arquivoComentarios;
    printf("\n");
    char nLinha[MAX_LINHA], comentario[MAX_COMENTARIO], idPerfil[MAX_ID];
    int idComentario;
    buscaStruct structTemp;
    arquivoComentarios = fopen("comentarios.txt", "r");
    if (arquivoComentarios == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
    else {
        printf("Comentarios: \n");
        fseek(arquivoComentarios, ZERO, SEEK_SET);
        while (fgets(nLinha, MAX_LINHA, arquivoComentarios) != NULL) {
            sscanf(nLinha, "IdPost: %d\tIdPerfil: %[^\t]\tIdComentario: %d\tComentario: %[^\t]\t\n", &structTemp.idFoto, idPerfil, &idComentario, comentario);
            if (structTemp.idFoto == idPost) {
                printf("[%d] @%s: %s\n", idComentario, idPerfil, comentario);
            }
        }
        printf("\n");
    }
    fclose(arquivoComentarios);
    return SUCESSO;
}

bool verificaComentario(char id[MAX_ID], int idPost) {
    FILE* arquivoComentario;
    int idTempPost, idTempComentario;
    char nLinha[MAX_LINHA], idTemp[MAX_ID], comentarioTemp[MAX_COMENTARIO];
    arquivoComentario = fopen("comentarios.txt", "r");
    fseek(arquivoComentario, ZERO, SEEK_SET);
    while (fgets(nLinha, MAX_LINHA, arquivoComentario) != NULL) {
        sscanf(nLinha, "IdPost: %d\tIdPerfil: %[^\t]\tIdComentario: %d\t Comentario: %[^\t]\t\n", &idTempPost, idTemp, &idTempComentario, comentarioTemp);
        if (idTempPost == idPost) {

            if (strcmp(id, idTemp) == ZERO) {
                fclose(arquivoComentario);
                return true;
                // o post ja estava comentado pela pessoa do determinado id
            }
        }
    }
    fclose(arquivoComentario);
    return false;
    //o post nao estava comentado por ela
}

int editarComentario(int idPost, char logindado[MAX_ID]) {
    FILE* arquivoComentarios, * arquivoAuxComentarios;
    char nLinha[MAX_LINHA], comentario[MAX_COMENTARIO], idPerfil[MAX_ID];
    int idTempPost, idComentario, escolhaId;
    arquivoComentarios = fopen("comentarios.txt", "r");
    arquivoAuxComentarios = fopen("fotoAuxiliar.txt", "w");
    if (arquivoComentarios == NULL || arquivoAuxComentarios == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoComentarios, ZERO, SEEK_SET);
        while (fgets(nLinha, MAX_LINHA, arquivoComentarios) != NULL) {
            sscanf(nLinha, "IdPost: %d\tIdPerfil: %[^\t]\tIdComentario: %d\tComentario: %[^\t]\t\n", &idTempPost, idPerfil, &idComentario, comentario);
            fprintf(arquivoAuxComentarios, "IdPost: %d\tIdPerfil: %s\tIdComentario: %d\tComentario: %s\t\n", idTempPost, idPerfil, idComentario, comentario);
            if (idTempPost == idPost) {
                printf("Comentarios:\n");
                printf("[%d] @%s: %s\n", idComentario, idPerfil, comentario);
            }
        }
        printf("Deseja editar o comentario de que id (primeiro numero) ? ");
        scanf("%d", &escolhaId);
        getchar();
        fclose(arquivoAuxComentarios);
        fclose(arquivoComentarios);
    }
    arquivoAuxComentarios = fopen("fotoAuxiliar.txt", "r");
    arquivoComentarios = fopen("comentarios.txt", "w");
    if (arquivoAuxComentarios == NULL || arquivoComentarios == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoAuxComentarios, ZERO, SEEK_SET);
        while (fgets(nLinha, MAX_LINHA, arquivoAuxComentarios) != NULL) { //passando para o definitivo
            sscanf(nLinha, "IdPost: %d\tIdPerfil: %[^\t]\tIdComentario: %d\tComentario: %[^\t]\t\n", &idTempPost, idPerfil, &idComentario, comentario);
            if (escolhaId == idComentario) {
                if (strcmp(idPerfil, logindado) == SUCESSO) {
                    printf("Digite o comentario, editado\n");
                    printf("@%s: ", idPerfil);
                    fgets(comentario, MAX_COMENTARIO, stdin);
                    util_removeQuebraLinhaFinal(comentario);
                    printf("\n");
                }
                else {
                    printf("Você nao é o dono do comentario!\n");
                }
                fprintf(arquivoComentarios, "IdPost: %d\tIdPerfil: %s\tIdComentario: %d\tComentario: %s\t\n", idTempPost, idPerfil, idComentario, comentario);
            }
            else {
                fprintf(arquivoComentarios, "IdPost: %d\tIdPerfil: %s\tIdComentario: %d\tComentario: %s\t\n", idTempPost, idPerfil, idComentario, comentario);
            }
        }
        fclose(arquivoAuxComentarios);
        fclose(arquivoComentarios);
    }
    return SUCESSO;
}

int retirarComentarioArquivo(int idPost) {
    FILE* arquivoComentario, * arquivoAuxComentario;
    char linha[MAX_LINHA];
    postStruct structTemp;
    arquivoComentario = fopen("postagens.txt", "r");
    arquivoAuxComentario = fopen("curtidasAuxiliar.txt", "w");
    if (arquivoAuxComentario == NULL || arquivoComentario == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoComentario, ZERO, SEEK_SET);
        while (fgets(linha, MAX_LINHA, arquivoComentario) != NULL) {
            sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, &structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, &structTemp.numCurtidasPost, &structTemp.numComentariosPost);
            if (structTemp.id == idPost) {
                structTemp.numComentariosPost--;

            }
            fprintf(arquivoAuxComentario, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, structTemp.numCurtidasPost, structTemp.numComentariosPost);
        }
        fclose(arquivoComentario);
        fclose(arquivoAuxComentario);
    }
    arquivoComentario = fopen("postagens.txt", "w");
    arquivoAuxComentario = fopen("curtidasAuxiliar.txt", "r");
    if (arquivoComentario == NULL) {
        printf("o problema é o normal\n");
    }
    if (arquivoAuxComentario == NULL) {
        printf("Erro ao abrir o arquivo\n");

    }
    else {
        fseek(arquivoAuxComentario, ZERO, SEEK_SET);
        while (fgets(linha, MAX_LINHA, arquivoAuxComentario) != NULL) {
            sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, &structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, &structTemp.numCurtidasPost, &structTemp.numComentariosPost);
            fprintf(arquivoComentario, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, structTemp.numCurtidasPost, structTemp.numComentariosPost);
        }
    }
    fclose(arquivoComentario);
    fclose(arquivoAuxComentario);
}

int apagarComentarios(int idPost) {
    FILE* arquivoComentarios, * arquivoAuxComentarios;
    char nLinha[MAX_LINHA], comentario[MAX_COMENTARIO], idPerfil[MAX_ID];
    int idTempPost, idComentario, escolhaId, idTemp = MAX_NUM_COMENTARIOS, verificacao = 0;
    arquivoComentarios = fopen("comentarios.txt", "r");
    arquivoAuxComentarios = fopen("fotoAuxiliar.txt", "w");
    if (arquivoComentarios == NULL || arquivoAuxComentarios == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoComentarios, ZERO, SEEK_SET);
        while (fgets(nLinha, MAX_LINHA, arquivoComentarios) != NULL) {
            sscanf(nLinha, "IdPost: %d\tIdPerfil: %[^\t]\tIdComentario: %d\tComentario: %[^\t]\t\n", &idTempPost, idPerfil, &idComentario, comentario);
            fprintf(arquivoAuxComentarios, "IdPost: %d\tIdPerfil: %s\tIdComentario: %d\tComentario: %s\t\n", idTempPost, idPerfil, idComentario, comentario);
            if (idTempPost == idPost) {
                printf("[%d] @%s: %s\n", idComentario, idPerfil, comentario);
            }

        }
        printf("\n");
        printf("Deseja apagar o comentario de que id? ");
        scanf("%d", &escolhaId);
        getchar();
        fclose(arquivoAuxComentarios);
        fclose(arquivoComentarios);
        arquivoAuxComentarios = fopen("fotoAuxiliar.txt", "r");
        arquivoComentarios = fopen("comentarios.txt", "w");
        if (arquivoAuxComentarios == NULL || arquivoComentarios == NULL) {
            printf("Erro ao abrir o arquivo\n");
            return ERRO;
        }
        else {
            fseek(arquivoAuxComentarios, ZERO, SEEK_SET);
            while (fgets(nLinha, MAX_LINHA, arquivoAuxComentarios) != NULL) {
                sscanf(nLinha, "IdPost: %d\tIdPerfil: %[^\t]\tIdComentario: %d\tComentario: %[^\t]\t\n", &idTempPost, idPerfil, &idComentario, comentario);
                if (escolhaId == idComentario) {
                    verificacao++;
                    idTemp = idComentario;
                    retirarComentarioArquivo(idPost);
                }
                else {
                    if (idTemp < idComentario) {
                        idComentario--;
                    }
                    fprintf(arquivoComentarios, "IdPost: %d\tIdPerfil: %s\tIdComentario: %d\tComentario: %s\t\n", idTempPost, idPerfil, idComentario, comentario);
                }
            }
            if (verificacao == ZERO) {
                printf("Comentario de id [ %d ] nao foi encontrado!\n", escolhaId);
                fclose(arquivoComentarios);
                return ERRO;
            }
            else {
                printf("Comentario apagado com sucesso!\n\n");
                fclose(arquivoComentarios);
                return SUCESSO;
            }
            fclose(arquivoAuxComentarios);
        }
    }
}

int adicionarNumComentario(int idPost) {
    FILE* arquivoComentario, * arquivoAuxComentario;
    char linha[MAX_LINHA];
    postStruct structTemp;
    arquivoComentario = fopen("postagens.txt", "r");
    arquivoAuxComentario = fopen("fotoAuxiliar.txt", "w");
    if (arquivoAuxComentario == NULL || arquivoComentario == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoComentario, ZERO, SEEK_SET);
        while (fgets(linha, MAX_LINHA, arquivoComentario) != NULL) {
            sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, &structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, &structTemp.numCurtidasPost, &structTemp.numComentariosPost);
            if (structTemp.id == idPost) {
                structTemp.numComentariosPost++;

            }
            fprintf(arquivoAuxComentario, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, structTemp.numCurtidasPost, structTemp.numComentariosPost);
        }
        fclose(arquivoComentario);
        fclose(arquivoAuxComentario);
    }
    arquivoComentario = fopen("postagens.txt", "w");
    arquivoAuxComentario = fopen("fotoAuxiliar.txt", "r");

    if (arquivoAuxComentario == NULL || arquivoComentario == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }

    else {
        fseek(arquivoAuxComentario, ZERO, SEEK_SET);
        while (fgets(linha, MAX_LINHA, arquivoAuxComentario) != NULL) {
            sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, &structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, &structTemp.numCurtidasPost, &structTemp.numComentariosPost);
            fprintf(arquivoComentario, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n",
                structTemp.urlImagemPost, structTemp.cor, structTemp.id, structTemp.descricaoPost, structTemp.idPerfil, structTemp.numCurtidasPost, structTemp.numComentariosPost);
        }
    }
    fclose(arquivoComentario);
    fclose(arquivoAuxComentario);
    return SUCESSO;

}

int comentarPerfil(loginStruct* logindados, int numComentarios, int idPost) {
    FILE* arquivoComentarios;
    char comentario[MAX_COMENTARIO];
    arquivoComentarios = fopen("comentarios.txt", "a");
    if (arquivoComentarios == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoComentarios, ZERO, SEEK_SET);
        printf("Escreva abaixo seu comentario!\n");
        printf("@%s: ", logindados->id);
        fgets(comentario, MAX_COMENTARIO, stdin);
        util_removeQuebraLinhaFinal(comentario);
        fprintf(arquivoComentarios, "IdPost: %d\tIdPerfil: %s\tIdComentario: %d\tComentario: %s\t\n", idPost, logindados->id, numComentarios, comentario);
        fclose(arquivoComentarios);
        printf("Comentario adicionado!\n\n");
    }
    return SUCESSO;
}

int secaoComentarios(char idPostador[], loginStruct* logindados, int numComentarios, int idPost, bool logado) {
    int escolhaSecaoComentarios;
    printf("\n");
    if (numComentarios == ZERO && logado == false) {
        printf("Não há nenhum comentário, esteja logado para poder fazer o primeiro comentário no post de @%s!\n", idPostador);
        return numComentarios;
    }
    do {
        printf("Bem vindo ao menu de Comentarios!\nEscolha uma das opções abaixo\n[0] Sair para menu de postagens\n");
        if (logado == true) {
            printf("[1] Comentar\n");
        }
        if (numComentarios > ZERO) {
            printf("[2] Ver comentarios\n");
            if (logado == true) {
                if (verificaComentario(logindados->id, idPost) == true) {
                    printf("[3] Editar comentario\n[4] Apagar comentarios\n");
                }
            }
        }
        scanf("%d", &escolhaSecaoComentarios);
        getchar();
        switch (escolhaSecaoComentarios) {
        case 0:
            break;
        case 1:
            if (logado == true) {
                comentarPerfil(logindados, numComentarios, idPost);
                adicionarNumComentario(idPost);
                numComentarios++;
            }
            else {
                printf("Você não está logado!\n\n");
            }
            break;
        case 2:
            if (numComentarios > ZERO) {
                verComentarios(idPost);
            }
            else {
                printf("\nNão há comentarios nesse post! Seja o primeiro a comentar!\n\n");
            }
            break;
        case 3:
            if (logado == true && verificaComentario(logindados->id, idPost) == true) {
                if (numComentarios > ZERO) {
                    editarComentario(idPost, logindados->id);
                }
            }
            else {
                printf("Voce não possui comentarios para editar!\n\n");
            }
            break;
        case 4:
            if (numComentarios > ZERO) {
                if (logado == true && verificaComentario(logindados->id, idPost) == true) {
                    if (apagarComentarios(idPost) == SUCESSO) {
                        numComentarios--;
                    }
                }
                else {
                    printf("Você não possui comentarios nesse post, para poder apaga-los!\n\n");
                }
            }
            else {
                printf("Não há comentarios no post para você apagar!\n\n");
            }
            break;
        default:
            printf("Opção invalida!\n\n");
            break;
        }
    } while (escolhaSecaoComentarios != ZERO);
    return numComentarios;
}

/*FUNÇÕES DE CURTIDAS
- verificaCurtida = verifica se o id do usuario logado ja curtiu o post
- retirarCurtidas = retira o id de quem curtiu do arquivo
- listarCurtidas = adiciona o id de quem curtiu no arquivo
- verCurtidas = possibilita uma lista de quem curtiu o post
- curtirPost = possibilita o id logado curtir o post de determinado id
*/
bool verificaCurtida(char id[MAX_ID], int idPost) {
    FILE* arquivoCurtidas;
    char idTemp[MAX_ID], nLinha[MAX_LINHA];
    int idTempPost;
    arquivoCurtidas = fopen("curtidas.txt", "r");
    fseek(arquivoCurtidas, ZERO, SEEK_SET);
    while (fgets(nLinha, MAX_LINHA, arquivoCurtidas) != NULL) {
        sscanf(nLinha, "ID:%[^\t]\tIdFoto:%d\t\n", idTemp, &idTempPost);
        if (idTempPost == idPost) {
            if (strcmp(id, idTemp) == ZERO) {
                fclose(arquivoCurtidas);
                return true;
                // o post ja esta curtido
            }
        }
    }
    fclose(arquivoCurtidas);
    return false;
    //nao esta curtido
}

int retirarCurtidas(char id[], int idPost) {
    FILE* arquivoCurtidas, * arquivoAuxCurtidas;
    int idTempPost;
    char idTemp[MAX_ID], nLinha[MAX_LINHA];
    arquivoCurtidas = fopen("curtidas.txt", "r");
    arquivoAuxCurtidas = fopen("curtidasAuxiliar.txt", "w");
    if (arquivoCurtidas == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoCurtidas, ZERO, SEEK_SET);
        while (fgets(nLinha, MAX_LINHA, arquivoCurtidas) != NULL) {
            sscanf(nLinha, "ID:%[^\t]\tIdFoto:%d\t\n", idTemp, &idTempPost);
            if (strcmp(id, idTemp) == SUCESSO) {
                if (idTempPost != idPost) {
                    //imprime no arquivo todos as curtidas do perfil, retirando apenas a desejada
                    fprintf(arquivoAuxCurtidas, "ID:%s\tIdFoto:%d\t\n", idTemp, idTempPost);
                }
            }
            else {
                //imprime no arquivo todas as curtidas de id diferente
                fprintf(arquivoAuxCurtidas, "ID:%s\tIdFoto:%d\t\n", idTemp, idTempPost);
            }
        }
    }
    fclose(arquivoCurtidas);
    fclose(arquivoAuxCurtidas);

    arquivoAuxCurtidas = fopen("curtidasAuxiliar.txt", "r");
    arquivoCurtidas = fopen("curtidas.txt", "w");

    if (arquivoAuxCurtidas == NULL || arquivoAuxCurtidas == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    //passa os dados lidos para o arquivo definitivo
    while (fgets(nLinha, MAX_LINHA, arquivoAuxCurtidas) != NULL) {
        sscanf(nLinha, "ID:%[^\t]\tIdFoto:%d\t\n", idTemp, &idTempPost);
        if (strcmp(id, idTemp) == ZERO) {
            if (idPost != idTempPost) {
                //nao faz nada
            }
            else {
                fprintf(arquivoCurtidas, "ID:%s\tIdFoto:%d\t\n", idTemp, idTempPost);
            }
        }
        else {
            fprintf(arquivoCurtidas, "ID:%s\tIdFoto:%d\t\n", idTemp, idTempPost);
        }
    }
    fclose(arquivoAuxCurtidas);
    fclose(arquivoCurtidas);
    return SUCESSO;
}

int listarCurtidas(char id[], int idPost) {
    FILE* arquivoCurtidas;
    arquivoCurtidas = fopen("curtidas.txt", "a+");
    if (arquivoCurtidas == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {
        fseek(arquivoCurtidas, ZERO, SEEK_SET);
        fprintf(arquivoCurtidas, "ID:%s\tIdFoto:%d\t\n", id, idPost);
        fclose(arquivoCurtidas);
    }
    return SUCESSO;
}

int verCurtidas(int idPost) {
    FILE* arquivoCurtidas;
    char idTemp[MAX_ID], linhaCurtidas[MAX_LINHA];
    int idTempPost;
    arquivoCurtidas = fopen("curtidas.txt", "r");

    if (arquivoCurtidas == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    else {

        fseek(arquivoCurtidas, ZERO, SEEK_SET);
        printf("As pessoas que curtiram esse post, de id %d, são:\n", idPost);
        while (fgets(linhaCurtidas, MAX_LINHA, arquivoCurtidas) != NULL) {
            sscanf(linhaCurtidas, "ID:%[^\t]\tIdFoto:%d\t\n", idTemp, &idTempPost);
            if (idTempPost == idPost) {
                printf("%s\n", idTemp);
            }

        }

        fclose(arquivoCurtidas);
    }
    return SUCESSO;
}

bool curtirPost(loginStruct* logindados, postStruct curtidasPost, int idPost, bool curtido) {
    FILE* arquivoFoto;
    FILE* arquivoAuxFoto;
    int numCurtidasCerto = 0;
    bool jaPassou = false;
    arquivoFoto = fopen("postagens.txt", "r");
    arquivoAuxFoto = fopen("fotoAuxiliar.txt", "w");
    if (arquivoAuxFoto == NULL || arquivoFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
    else {
        char linhaFoto[MAX_LINHA], nLinha[MAX_LINHA];
        fseek(arquivoFoto, ZERO, SEEK_SET);
        while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
            sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", curtidasPost.urlImagemPost, curtidasPost.cor, &curtidasPost.id, curtidasPost.descricaoPost, curtidasPost.idPerfil, &curtidasPost.numCurtidasPost, &curtidasPost.numComentariosPost);
            if (jaPassou == false) {
                if (curtido == false) {
                    curtidasPost.numCurtidasPost++;
                    curtido = true;
                    logindados->curtido[idPost] = true;
                    jaPassou = true; //agora esta curtido
                }
                else {
                    curtidasPost.numCurtidasPost--;
                    curtido = false;
                    logindados->curtido[idPost] = false;
                    jaPassou = true; //nao esta mais curtido
                }
                numCurtidasCerto = curtidasPost.numCurtidasPost;
            }
            //caso o id do post for igual imprime os dados novos da curtida
            if (idPost == curtidasPost.id) {
                if (jaPassou == true) {
                    fprintf(arquivoAuxFoto, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n", curtidasPost.urlImagemPost, curtidasPost.cor, curtidasPost.id, curtidasPost.descricaoPost, curtidasPost.idPerfil, numCurtidasCerto, curtidasPost.numComentariosPost);
                }
                else {
                    fprintf(arquivoAuxFoto, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n", curtidasPost.urlImagemPost, curtidasPost.cor, curtidasPost.id, curtidasPost.descricaoPost, curtidasPost.idPerfil, curtidasPost.numCurtidasPost, curtidasPost.numComentariosPost);
                }
            }
            // caso diferente imprime a linha inteira
            else {
                fprintf(arquivoAuxFoto, "%s", linhaFoto);
            }
        }
        if (curtido == true) {
            listarCurtidas(logindados->id, idPost);//adiciona o nome na lista de quem curtiu
        }
        else {
            retirarCurtidas(logindados->id, idPost);//tira o nome na lista de qm curtiu
        }
        fclose(arquivoAuxFoto);
        fclose(arquivoFoto);
        arquivoAuxFoto = fopen("fotoAuxiliar.txt", "r");
        arquivoFoto = fopen("postagens.txt", "w");
        if (arquivoAuxFoto == NULL || arquivoFoto == NULL) {
            printf("Erro ao abrir o arquivo\n");
            return ERRO;
        }
        else {
            //passa os dados lidos para o arquivo definitivo
            while (fgets(nLinha, MAX_LINHA, arquivoAuxFoto) != NULL) {
                sscanf(nLinha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", curtidasPost.urlImagemPost, curtidasPost.cor, &curtidasPost.id, curtidasPost.descricaoPost, curtidasPost.idPerfil, &curtidasPost.numCurtidasPost, &curtidasPost.numComentariosPost);
                fprintf(arquivoFoto, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n", curtidasPost.urlImagemPost, curtidasPost.cor, curtidasPost.id, curtidasPost.descricaoPost, curtidasPost.idPerfil, curtidasPost.numCurtidasPost, curtidasPost.numComentariosPost);
            }
            fclose(arquivoAuxFoto);
            fclose(arquivoFoto);
            return curtido;
        }
    }
}

/** Funções essencias 2
* numFotosPost; usada pra determinar a qnt de fotos por post
* verificaPost; verifica se determinado id possui postagem
* menuFotos; imprime os posts e gera um menu de escolha
* fotoDePerfil; salva e gera a foto de perfil do usuario
*/

int numFotosPost(int idPost) {
    int contagem = 0;
    FILE* arquivoFotos;
    char linhaFoto[MAX_LINHA];
    postStruct fotosArquivo;
    arquivoFotos = fopen("postagens.txt", "r");
    if (arquivoFotos == NULL) {
        printf("Nenhuma foto cadastrada no sistema!\n");
        return ZERO;
    }
    fseek(arquivoFotos, ZERO, SEEK_SET);
    while (fgets(linhaFoto, MAX_LINHA, arquivoFotos) != NULL) {
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, &fotosArquivo.id, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, &fotosArquivo.numCurtidasPost, &fotosArquivo.numComentariosPost);
        if (fotosArquivo.id == idPost) {
            contagem++;
        }
    }

    fclose(arquivoFotos);
    return contagem;
}
bool verificaPost(char id[]) {
    FILE* arquivoFoto;
    char linhaFoto[MAX_LINHA];
    postStruct fotosArquivo;
    arquivoFoto = fopen("postagens.txt", "r");
    if (arquivoFoto == NULL) {
        printf("Nenhuma foto cadastrada no sistema!\n");
        return false;
    }
    fseek(arquivoFoto, ZERO, SEEK_SET);
    while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, &fotosArquivo.id, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, &fotosArquivo.numCurtidasPost, &fotosArquivo.numComentariosPost);
        if (strcmp(fotosArquivo.idPerfil, id) == SUCESSO) {
            fclose(arquivoFoto);
            return true; //o id ja postou algo
        }
    }
    fclose(arquivoFoto);

    return false; //se chegou ate aqui é por que o id ainda nao postou nada

}

int menuFotos(char id[], loginStruct* logindados, bool logado) {
    FILE* arquivoFoto, * arquivoCurtidas;
    int escolhaArquivoFoto = 1;
    int idAnterior = -1;
    bool continuarMsmId = false;
    int numCurtidasCerto;
    int numFotosNoPost, numFotosTotal;
    int fotoNumero;
    char linhaFoto[MAX_LINHA];
    bool corFoto = true;
    postStruct fotosArquivo;
    arquivoFoto = fopen("postagens.txt", "r");
    //verificação de erro de abertura do arquivo
    if (arquivoFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    // loop para ler a linha do arquivo
    fseek(arquivoFoto, ZERO, SEEK_SET);
    while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, &fotosArquivo.id, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, &fotosArquivo.numCurtidasPost, &fotosArquivo.numComentariosPost);
        //verifica qual a cor da foto
        if (continuarMsmId == false) {
            numFotosNoPost = (numFotosPost(fotosArquivo.id));
            numFotosTotal = numFotosNoPost;
            if (fotosArquivo.id == idAnterior) {
                continue;
            }
        }
        else {
            numFotosNoPost--;
        }
        if (idAnterior == fotosArquivo.id) {
            fotoNumero++;
        }
        else {
            fotoNumero = 1;
        }
        if (strcmp(fotosArquivo.cor, "s") == SUCESSO || strcmp(fotosArquivo.cor, "S") == SUCESSO) {
            corFoto = true;
        }
        else if (strcmp(fotosArquivo.cor, "n") == SUCESSO || strcmp(fotosArquivo.cor, "N") == SUCESSO) {
            corFoto = false;
        }
        if (strcmp(id, fotosArquivo.idPerfil) == SUCESSO) {
            // função para mostrar as fotos
            if (continuarMsmId == true) {
                mostraImagem(numFotosTotal, fotoNumero, fotosArquivo.urlImagemPost, corFoto, fotosArquivo.descricaoPost, id, numCurtidasCerto, fotosArquivo.numComentariosPost);
            }
            else {
                mostraImagem(numFotosTotal, fotoNumero, fotosArquivo.urlImagemPost, corFoto, fotosArquivo.descricaoPost, id, fotosArquivo.numCurtidasPost, fotosArquivo.numComentariosPost);
            }
        }
        else {
            continue;
        }

        do {
            arquivoCurtidas = fopen("curtidas.txt", "a");
            fclose(arquivoCurtidas);
            if (arquivoCurtidas == NULL) {
                printf("Erro ao abrir o arquivo\n");
                return ERRO;
            }
            printf("\nEscolha uma das opções para o post %i\n[0] Sair\n[1] Ver mais postagens de @%s\n[2] Secao de comentarios\n[3] Ver curtidas\n", fotosArquivo.id, id);
            if (numFotosNoPost > UM) {
                printf("[4] Ver mais fotos do post\n");
            }

            if (logado == true) {
                if (verificaCurtida(logindados->id, fotosArquivo.id) == true) {
                    printf("[5] Descurtir\n");
                }
                else {
                    printf("[5] Curtir\n");
                }
            }
            scanf("%d", &escolhaArquivoFoto);
            getchar();
            if (escolhaArquivoFoto == MUDAR_POST) {
                continuarMsmId = false;
            }
            switch (escolhaArquivoFoto) {
            case 0:
                printf("Saindo!\n");
                return SAIR;
                break;
            case 1:
                break;

            case 2:
                if (secaoComentarios(id, logindados, fotosArquivo.numComentariosPost, fotosArquivo.id, logado) > fotosArquivo.numComentariosPost, logado) {
                    fotosArquivo.numComentariosPost++;
                }
                break;

            case 3:
                if (fotosArquivo.numCurtidasPost == ZERO) {
                    printf("\nNão há curtidas ainda! Seja o primeiro a curtir o post de @%s!\n", id);
                }
                else {
                    verCurtidas(fotosArquivo.id);
                }
                break;
            case 4:
                if (numFotosNoPost > UM) {
                    numCurtidasCerto = fotosArquivo.numCurtidasPost;
                    continuarMsmId = true;
                }
                else {
                    continuarMsmId = false;
                    printf("Não há mais fotos para você ver nesse post!\n\n");
                }
                break;
            case 5:
                if (logado == true) {
                    if (verificaCurtida(logindados->id, fotosArquivo.id) == true) {//o post ja estava curtido
                        logindados->curtido[fotosArquivo.id] = true;
                        curtirPost(logindados, fotosArquivo, fotosArquivo.id, logindados->curtido[fotosArquivo.id]);
                        logindados->curtido[fotosArquivo.id] = false;
                        fotosArquivo.numCurtidasPost--;
                        printf("Descurtido!\n");
                    }
                    else { //nao estava curtido
                        logindados->curtido[fotosArquivo.id] = false;
                        curtirPost(logindados, fotosArquivo, fotosArquivo.id, logindados->curtido[fotosArquivo.id]);
                        logindados->curtido[fotosArquivo.id] = true;
                        fotosArquivo.numCurtidasPost++;
                        printf("Curtido!\n");
                    }
                    break;
                }
                else {
                    printf("Você não está logado! Faça o login para obter acesso ao Coltegram inteiro!\n");
                }

            default:
                printf("Opção invalida!\n");
                break;
            }
            if (escolhaArquivoFoto == SAIR) {
                break;
            }
            if (continuarMsmId == true) {
                break;
            }
        } while (escolhaArquivoFoto != UM);
        if (escolhaArquivoFoto == SAIR) {
            break;
        }
        idAnterior = fotosArquivo.id;
    }
    fclose(arquivoFoto);
    return SUCESSO;
}

int fotoDePerfil(perfilStruct* perfil) {
    // declara as variaveis
    char colorido;
    bool cor;
    asciiImg_t* fotoPerfil;
    // abre o arquivo
    FILE* arquivoCadastro;
    arquivoCadastro = fopen("dadosLogin.txt", "a");
    if (arquivoCadastro == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    printf("Cole a url da imagem que deseja utilizar no perfil(termine em .png, .jpeg, etc): ");
    fgets(perfil->urlFotoPerfil, MAX_URL, stdin);
    util_removeQuebraLinhaFinal(perfil->urlFotoPerfil);
    fprintf(arquivoCadastro, "URL: %s\t", perfil->urlFotoPerfil);

    printf("Deseja que a imagem seja colorida? [s/n] ");
    scanf("%c", &colorido);
    getchar();
    if (colorido == 's' || colorido == 'S') {
        fprintf(arquivoCadastro, "Cor: s\t");
        //muda a variavel booleana para "true" caso tenha cor
        cor = true;
    }
    else if (colorido == 'n' || colorido == 'N') {
        fprintf(arquivoCadastro, "Cor: n\t");
        //muda a variavel booleana para "false" caso não tenha cor
        cor = false;
    }
    fclose(arquivoCadastro);
    printf("Preview: \n");
    fotoPerfil = insta_carregaImagem(perfil->urlFotoPerfil, cor, LARGURA);
    insta_imprimeImagem(fotoPerfil);
    printf("\nSua foto de perfil foi definida\n");
    insta_liberaImagem(fotoPerfil);
    return SUCESSO;
}

/* Funções Minhas Fotos
* listafotos; lista os dados da fotos do usuario logado
  visualizaFoto; imprime a foto do usario escolhida por ele
  editaPost; edita uma publicação já existente
  apagaFotos; possui a opção de apagar todas as fotos ou apagar uma unica foto (escolhida pelos usuario)
*/
int listafotos(char IdPerfil[]) {
    printf("Fotos do @%s\n", IdPerfil);
    printf("%-50s|%-5s|%-15s|%-15s|\n", "Descrição", "ID", "Curtidas", "Comentarios");
    //declara as a variaveis
    char linhaFoto[MAX_LINHA];
    int qnt_linha = ZERO, i = ZERO;
    postStruct* post;
    //aloca dinamicamente a struct
    post = malloc(sizeof(postStruct) * MAX_POSTAGENS); //ax que tem que mudar
    // verifica se a alocação deu certo
    if (post == NULL) {
        printf("Erro na alocação de memoria!\n");
        free(post);
        return ERRO;
    }
    FILE* arquivoFoto;
    arquivoFoto = fopen("postagens.txt", "r");
    if (arquivoFoto == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        free(post);
        return ERRO;
    }
    // loop de leitura do arquivo
    while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", post[qnt_linha].urlImagemPost, post[qnt_linha].cor, &post[qnt_linha].id, post[qnt_linha].descricaoPost, post[qnt_linha].idPerfil, &post[qnt_linha].numCurtidasPost, &post[qnt_linha].numComentariosPost);
        if (strcmp(IdPerfil, post[qnt_linha].idPerfil) == SUCESSO) {
            printf("%-50s|%-5i|%-15i|%-15i|\n", post[qnt_linha].descricaoPost, post[qnt_linha].id, post[qnt_linha].numCurtidasPost, post[qnt_linha].numComentariosPost);
        }
        qnt_linha++;
    }
    //fecha os dados do arquivo
    fclose(arquivoFoto);
    //libera a memoria alocada
    free(post);
}

int visualizaFoto(loginStruct* logindados, char id[]) {
    FILE* arquivoFoto;
    buscaStruct busca;
    postStruct* post;
    bool cor = true;
    int idAnterior = -1, fotoNumero;
    int numFotosNoPost, numFotosTotal;
    int qnt_linha = ZERO;
    char linha[MAX_LINHA];
    //aloca dinamicamente a struct
    post = malloc(sizeof(postStruct) * MAX_POSTAGENS);
    // verifica se a alocação deu certo
    if (post == NULL) {
        printf("Erro na alocação de memoria\n");
        free(post);
        return ERRO;
    }
    arquivoFoto = fopen("postagens.txt", "r");
    if (arquivoFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    printf("Informe o id da postagem\n");
    scanf("%d", &busca.idFoto);
    getchar();
    while (fgets(linha, MAX_LINHA, arquivoFoto) != NULL) {
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", post[qnt_linha].urlImagemPost, post[qnt_linha].cor, &post[qnt_linha].id, post[qnt_linha].descricaoPost, post[qnt_linha].idPerfil, &post[qnt_linha].numCurtidasPost, &post[qnt_linha].numComentariosPost);
        //verifica se o id é igual

        if (idAnterior == post[qnt_linha].id) {
            fotoNumero++;
        }
        else {
            fotoNumero = 1;
        }
        if (post[qnt_linha].id == busca.idFoto) {
            // verifica se o post pertence ao usuario logado
            if (strcmp(post[qnt_linha].idPerfil, id) == SUCESSO) {
                if (strcmp(post[qnt_linha].cor, "s") == SUCESSO || strcmp(post[qnt_linha].cor, "S") == SUCESSO) {
                    cor = true;
                }
                else if (strcmp(post[qnt_linha].cor, "n") == SUCESSO || strcmp(post[qnt_linha].cor, "N") == SUCESSO) {
                    cor = false;
                }
                numFotosTotal = (numFotosPost(post[qnt_linha].id));
                mostraImagem(numFotosTotal, fotoNumero, post[qnt_linha].urlImagemPost, cor, post[qnt_linha].descricaoPost, post[qnt_linha].idPerfil, post[qnt_linha].numCurtidasPost, post[qnt_linha].numComentariosPost);
            }
            else {
                printf("Esse post não é seu!\n");
            }

            qnt_linha++;
        }
        idAnterior = post[qnt_linha].id;
    }
}

int editaPost(loginStruct* logindados, char perfil[]) {
    //declara as variaveis
    FILE* arquivoFoto, * arquivoAUXFoto;
    int numFotosTotal;
    char linhaFoto[MAX_LINHA], linhaAux[MAX_LINHA], novaURL[MAX_URL], escolhaEditar, colorido[MAX_COR];
    postStruct postArquivo;
    bool urlAdquiridas = false;
    bool cor = true, verificacaoPostou = false;
    int fotoNumero = 1, idAnterior = -1, contaFoto = 0;

    // abre os arquivos
    arquivoAUXFoto = fopen("fotoAuxiliar.txt", "w");
    arquivoFoto = fopen("postagens.txt", "r");

    // verifica a abertura dos arquivos
    if (arquivoAUXFoto == NULL || arquivoFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }

    // obtem o id da publicação
    printf("Informe o id da publicação para editá-la: ");
    scanf("%d", &logindados->postagens->id);
    getchar();

    // loop para ler a linha do arquivo até o final
    while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
        // usa o sscanf para armazenar os dados da string em variáveis
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %s\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", postArquivo.urlImagemPost, postArquivo.cor, &postArquivo.id, postArquivo.descricaoPost, postArquivo.idPerfil, &postArquivo.numCurtidasPost, &postArquivo.numComentariosPost);

        if (idAnterior == postArquivo.id) {
            fotoNumero++;
        }
        else {
            fotoNumero = 1;
        }
        // verifica se o id é igual

        if (logindados->postagens->id == postArquivo.id) {
            //verifica se a foto é do perfil logado
            if (strcmp(perfil, postArquivo.idPerfil) == SUCESSO) {
                //verifica qual a cor da postagem
                if (strcmp(postArquivo.cor, "s") == SUCESSO || strcmp(postArquivo.cor, "S") == SUCESSO) {
                    cor = true;
                }
                else if (strcmp(postArquivo.cor, "n") == SUCESSO || strcmp(postArquivo.cor, "N") == SUCESSO) {
                    cor = false;
                }
                //carrega a imagem daquele id
                numFotosTotal = numFotosPost(logindados->postagens->id);
                mostraImagem(numFotosTotal, fotoNumero, postArquivo.urlImagemPost, cor, postArquivo.descricaoPost, postArquivo.idPerfil, postArquivo.numCurtidasPost, postArquivo.numComentariosPost);
                if (fotoNumero != numFotosTotal) {
                    idAnterior = postArquivo.id;
                    continue;
                }
                printf("Deseja editar essa post? [s/n]\n");
                scanf(" %c", &escolhaEditar);
                getchar();

                if (escolhaEditar == 's' || escolhaEditar == 'S') {
                    contaFoto = ZERO;
                    printf("Quantas imagens serão no post? [LIMITE: 10 FOTOS] \n");
                    scanf("%d", &logindados->postagens->qntFotosPost);
                    getchar();
                    do {
                        fotoNumero = ZERO;
                        printf("Informe a url da nova imagem\n");
                        fotoNumero++;
                        fgets(novaURL, MAX_URL, stdin);
                        util_removeQuebraLinhaFinal(novaURL);
                        fprintf(arquivoAUXFoto, "URL: %s\t", novaURL);

                        printf("A imagem será colorida? [s/n] ");
                        fgets(colorido, MAX_COR, stdin);
                        util_removeQuebraLinhaFinal(colorido);
                        if (strcmp(colorido, "s") == SUCESSO || strcmp(colorido, "S") == SUCESSO) {
                            fprintf(arquivoAUXFoto, "Cor: s\t");
                            cor = true;
                        }
                        else if (strcmp(colorido, "n") == SUCESSO || strcmp(colorido, "N") == SUCESSO) {
                            fprintf(arquivoAUXFoto, "Cor: n\t");
                            cor = false;
                        }
                        logindados->postagens->id = maiorIdPost();
                        fprintf(arquivoAUXFoto, "Id do post: %d\t", postArquivo.id);

                        if (contaFoto == ZERO) {
                            printf("Digite a descricao do post: ");
                            fgets(logindados->postagens->descricaoPost, MAX_DESCRICAO, stdin);
                            util_removeQuebraLinhaFinal(logindados->postagens->descricaoPost);
                        }
                        fprintf(arquivoAUXFoto, "Descricao: %s\t", logindados->postagens->descricaoPost);
                        printf("Seu novo Post\n");

                        mostraImagem(logindados->postagens->qntFotosPost, fotoNumero, novaURL, cor, logindados->postagens->descricaoPost, perfil, postArquivo.numCurtidasPost, postArquivo.numComentariosPost);
                        fotoNumero++;
                        fprintf(arquivoAUXFoto, "ID: %s\t", postArquivo.idPerfil);
                        fprintf(arquivoAUXFoto, "Curtidas: %d\t", postArquivo.numCurtidasPost);
                        fprintf(arquivoAUXFoto, "Comentarios: %d\t\n", postArquivo.numComentariosPost);
                        contaFoto++;

                    } while (contaFoto < logindados->postagens->qntFotosPost);
                    printf("\nO id da foto continua o mesmo!\nSua Alteração foi salva!\n");

                }
                else if (escolhaEditar == 'n' || escolhaEditar == 'N') {
                    printf("A sua foto não foi editada!\n");
                    return DESISTENCIA;
                }
            }
            else {
                printf("\nEssa postagem não pertence a você!\n");
                return ERRO;
            }
        }
        else {
            fprintf(arquivoAUXFoto, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n", postArquivo.urlImagemPost, postArquivo.cor, postArquivo.id, postArquivo.descricaoPost, postArquivo.idPerfil, postArquivo.numCurtidasPost, postArquivo.numComentariosPost);
        }
        idAnterior = postArquivo.id;
    }
    // fecha os arquivos
    fclose(arquivoFoto);
    fclose(arquivoAUXFoto);

    // abre os arquivos novamente para atualização
    arquivoAUXFoto = fopen("fotoAuxiliar.txt", "r");
    arquivoFoto = fopen("postagens.txt", "w");

    // verifica a abertura dos arquivos
    if (arquivoAUXFoto == NULL || arquivoFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }

    // lê a linha do arquivo auxiliar e imprime no arquivo definitivo
    while (fgets(linhaAux, MAX_LINHA, arquivoAUXFoto) != NULL) {
        fprintf(arquivoFoto, "%s", linhaAux);
    }

    // fecha e salva os dados do arquivo
    fclose(arquivoAUXFoto);
    fclose(arquivoFoto);
    return SUCESSO;
}

int apagaFotos(char id[], int tipo) {
    //declara as variaveis
    char linhaFoto[MAX_LINHA], escolhaApagar;
    int idPesquisa, novoID = 0;
    int idAnterior = -1;
    int numFotosTotal;
    int fotoNumero = 1;
    FILE* arquivoFoto, * arquivoAUXFoto;
    bool cor = true;
    //usa a variavel para armazenar temporiamente os dados
    postStruct fotosArquivo;
    //abre os arquivos
    arquivoFoto = fopen("postagens.txt", "r");
    arquivoAUXFoto = fopen("fotoAuxiliar.txt", "w");
    if (arquivoFoto == NULL || arquivoAUXFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    if (tipo == UNICO) {
        printf("Informe o id da publicação para apagar-la: ");
        scanf("%d", &idPesquisa);
        getchar();
    }
    while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, &fotosArquivo.id, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, &fotosArquivo.numCurtidasPost, &fotosArquivo.numComentariosPost);
        if (idAnterior == fotosArquivo.id) {
            fotoNumero++;
        }
        else {
            fotoNumero = 1;
        }
        //defini 98 como apaga um unico post
        if (tipo == UNICO) {
            if (idPesquisa == fotosArquivo.id) {
                //verifica se a foto é do perfil logado
                if (strcmp(id, fotosArquivo.idPerfil) == SUCESSO) {
                    //verifica qual a cor da postagem
                    if (strcmp(fotosArquivo.cor, "s") == SUCESSO || strcmp(fotosArquivo.cor, "S") == SUCESSO) {
                        cor = true;
                    }
                    else if (strcmp(fotosArquivo.cor, "n") == SUCESSO || strcmp(fotosArquivo.cor, "N") == SUCESSO) {
                        cor = false;
                    }
                    //chama a função para carregar a imagem
                    numFotosTotal = numFotosPost(idPesquisa);

                    mostraImagem(numFotosTotal, fotoNumero, fotosArquivo.urlImagemPost, cor, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, fotosArquivo.numCurtidasPost, fotosArquivo.numComentariosPost);
                    if (fotoNumero != numFotosTotal) {
                        idAnterior = fotosArquivo.id;
                        continue;
                    }
                    printf("Deseja apagar essa[s] imagem[ns]? [s/n]\n");
                    scanf(" %c", &escolhaApagar);
                    getchar();
                    if (escolhaApagar == 's' || escolhaApagar == 'S') {
                        printf("Sua imagem foi apagada!\n");
                    }
                    else if (escolhaApagar == 'n' || escolhaApagar == 'N') {
                        printf("A sua foto não foi apagada!\n");
                        return DESISTENCIA;
                    }
                }
                else {
                    printf("\nEssa postagem não pertence a você!\n");
                    return ERRO;
                }
            }
            else {
                if (idPesquisa < fotosArquivo.id) {
                    fotosArquivo.id--;
                }
                // se não for a imagem pra ser apagada, escreve no arquivo auxiliar
                fprintf(arquivoAUXFoto, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, fotosArquivo.id, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, fotosArquivo.numCurtidasPost, fotosArquivo.numComentariosPost);
            }
        }
        //defini 99 como apaga todos os posts
        else if (tipo == TODOS) {

            // se o id do usuario for diferente do id informado
            if (strcmp(id, fotosArquivo.idPerfil) != SUCESSO) {
                fprintf(arquivoAUXFoto, "URL: %s\tCor: %s\tId do post: %d\tDescricao: %s\tID: %s\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, novoID, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, fotosArquivo.numCurtidasPost, fotosArquivo.numComentariosPost);
                novoID++;
            }
        }
        idAnterior = fotosArquivo.id;

    }
    fclose(arquivoAUXFoto);
    fclose(arquivoFoto);
    arquivoAUXFoto = fopen("fotoAuxiliar.txt", "r");
    arquivoFoto = fopen("postagens.txt", "w");
    //verifica se o arquivo esta NULL
    if (arquivoFoto == NULL || arquivoAUXFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    while (fgets(linhaFoto, MAX_LINHA, arquivoAUXFoto) != NULL) {
        //passa os dados do arquivo auxiliar para o principal
        fprintf(arquivoFoto, "%s", linhaFoto);
    }
    if (tipo == TODOS) {
        // retorna SUCESSO caso todas as fotos do perfil forem apagadas
        return SUCESSO;
    }
    fclose(arquivoAUXFoto);
    fclose(arquivoFoto);
}

/* Funções para o cadastro de um Perfil
* verificaDadoIgual; responsavel por verificar se os novos dados enviados já estao no arquivos
* verificaIdIgual; utiliza a função verifica DadoIgual para verificar apenas os IDs
* verificaEmailIgual; utiliza a função verifica DadoIgual para apenas os emails
* cadastroPerfil; cadastra uma conta no Coltegram
*/

int verificaDadoIgual(char dado[], int tipo) {
    //declara as variaveis
    buscaStruct busca;
    char escolha[TAMANHOESCOLHA], linha[MAX_LINHA];
    FILE* arquivoCadastro;
    //abre  arquivo
    arquivoCadastro = fopen("dadosLogin.txt", "r");
    //verificações
    if (arquivoCadastro == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return ERRO;
    }
    // caso seja o primeiro perfil cadastrado para verificar o uso de @
    if (tipo == EMAIL) {
        if (fgets(linha, MAX_LINHA, arquivoCadastro) == NULL) {
            return PRIMEIRO_EMAIL;
        }
    }
    // caso seja o primeiro perfil cadastrado para verificar o id
    if (tipo == ID) {
        if (fgets(linha, MAX_LINHA, arquivoCadastro) == NULL) {
            return VALIDO;
        }
    }
    fseek(arquivoCadastro, ZERO, SEEK_SET);
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", busca.urlFotoPerfil, busca.cor, busca.id, busca.nome, busca.email, busca.senha, busca.bioPerfil);
        if (tipo == ID) {
            if (strcmp(busca.id, dado) == SUCESSO) {
                printf("O id já está sendo utilizado\n");
                printf("Você deseja alterá-lo? [s/n]\n");

                fgets(escolha, TAMANHOESCOLHA, stdin);
                getchar();
                util_removeQuebraLinhaFinal(escolha);
                if (strcmp(escolha, "s") == SUCESSO || strcmp(escolha, "S") == SUCESSO) {
                    fclose(arquivoCadastro);
                    return SUCESSO;
                }
                else if (strcmp(escolha, "n") == SUCESSO || strcmp(escolha, "N") == SUCESSO) {
                    fclose(arquivoCadastro);
                    return DESISTENCIA;
                }
            }
        }
        else if (tipo == EMAIL) {
            if (strcspn("@", dado) != SUCESSO) {
                //veriica se o email possui
                printf("Email não possui @!\n");
                printf("Você deseja alterá-lo? [s/n]\n");
                fgets(escolha, TAMANHOESCOLHA, stdin);
                getchar();
                util_removeQuebraLinhaFinal(escolha);
                if (strcmp(escolha, "s") == SUCESSO || strcmp(escolha, "S") == SUCESSO) {
                    fclose(arquivoCadastro);
                    return SUCESSO;
                }
                else if (strcmp(escolha, "n") == SUCESSO || strcmp(escolha, "N") == SUCESSO) {
                    fclose(arquivoCadastro);
                    return DESISTENCIA;
                }
            }
            if (strcspn(".", dado) != SUCESSO) {
                printf("Email não possui um dominio válido!\n");
                printf("Você deseja alterá-lo? [s/n]\n");
                fgets(escolha, TAMANHOESCOLHA, stdin);
                getchar();
                util_removeQuebraLinhaFinal(escolha);
                if (strcmp(escolha, "s") == SUCESSO || strcmp(escolha, "S") == SUCESSO) {
                    fclose(arquivoCadastro);
                    return SUCESSO;
                }
                else if (strcmp(escolha, "n") == SUCESSO || strcmp(escolha, "N") == SUCESSO) {
                    fclose(arquivoCadastro);
                    return DESISTENCIA;
                }
            }

            else {
                if (strcmp(busca.email, dado) == SUCESSO) {
                    printf("O email já está sendo utilizado\n");
                    printf("Você deseja alterá-lo? [s/n]\n");
                    fgets(escolha, TAMANHOESCOLHA, stdin);
                    getchar();
                    util_removeQuebraLinhaFinal(escolha);
                    if (strcmp(escolha, "s") == SUCESSO || strcmp(escolha, "S") == SUCESSO) {
                        fclose(arquivoCadastro);
                        return SUCESSO;
                    }
                    else if (strcmp(escolha, "n") == SUCESSO || strcmp(escolha, "N") == SUCESSO) {
                        fclose(arquivoCadastro);
                        return DESISTENCIA;
                    }
                }
            }
        }
    }
    fclose(arquivoCadastro);
    return VALIDO;
}

int verificaIdIgual(char id[]) {
    return verificaDadoIgual(id, ID);
}

int verificaEmailIgual(char email[]) {
    return verificaDadoIgual(email, EMAIL); //retorna o email como parametro
}

void cadastroPerfil(perfilStruct** perfil, int* QNT_Perfil, int* limiteContas, int* novoLimiteContas) {
    //variaveis para armazenar a saida da funçao
    char querFotoOuN;
    int IdVerificado = SUCESSO, emailVerificado = SUCESSO;
    bool diferenteId = false, diferenteEmail = false;
    FILE* arquivoCadastro;
    arquivoCadastro = fopen("dadosLogin.txt", "a+"); // Abrir o arquivo para leitura e gravação sem excluir o conteúdo anterior
    if (arquivoCadastro == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return; // Retorna sem sucesso
    }

    printf("Para o cadastro de um perfil no Coltegram, informe:\n");
    //loop para verificar id igual
    while (diferenteId == false) {
        printf("ID              [MAX 20 CARACTERES]: ");
        fgets((*perfil)[*QNT_Perfil].id, MAX_ID, stdin);
        util_removeQuebraLinhaFinal((*perfil)[*QNT_Perfil].id);
        IdVerificado = verificaIdIgual((*perfil)[*QNT_Perfil].id);
        if (IdVerificado == VALIDO) {
            diferenteId = true; // caso id for valido passa a variavel booleana pra true, encerrando o loop
        }
        else {
            if (IdVerificado == DESISTENCIA) {
                fclose(arquivoCadastro);
                return; // Retorna sem sucesso
            }
        }
    }

    printf("Nome de usuário [MAX 30 CARACTERES]: ");
    fgets((*perfil)[*QNT_Perfil].nome, MAX_NOME, stdin);
    util_removeQuebraLinhaFinal((*perfil)[*QNT_Perfil].nome);

    //loop para verificar email Igual
    while (diferenteEmail == false) {
        printf("Email           [MAX 40 CARACTERES]: ");
        fgets((*perfil)[*QNT_Perfil].email, MAX_EMAIL, stdin);
        util_removeQuebraLinhaFinal((*perfil)[*QNT_Perfil].email);
        emailVerificado = verificaEmailIgual((*perfil)[*QNT_Perfil].email);
        //caso seja o primeiro perfil cadastrado
        if (emailVerificado == PRIMEIRO_EMAIL) {
            if (strcspn("@", (*perfil)[*QNT_Perfil].email) != SUCESSO) {
                printf("Emai não possui @!\n");
            }
            else if (strcspn(".", (*perfil)[*QNT_Perfil].email) != SUCESSO) {
                printf("Email não possui dominio valido\n");
            }
            else {
                // quebra do loop caso tenha @
                break;
            }
        }
        //email valido, passa a variavel booleana para true
        else if (emailVerificado == VALIDO) {
            diferenteEmail = true;
        }
        else if (emailVerificado == DESISTENCIA) {
            fclose(arquivoCadastro);
            return; // Retorna sem sucesso
        }
    }
    printf("Senha           [MAX 20 CARACTERES]: ");
    fgets((*perfil)[*QNT_Perfil].senha, MAX_SENHA, stdin);
    util_removeQuebraLinhaFinal((*perfil)[*QNT_Perfil].senha);

    printf("BIO             [MAX 150 CARACTERES]: ");
    fgets((*perfil)[*QNT_Perfil].bioPerfil, MAX_BIO, stdin);
    util_removeQuebraLinhaFinal((*perfil)[*QNT_Perfil].bioPerfil);

    printf("Deseja utilizar foto de perfil? [s/n] ");
    scanf("%c", &querFotoOuN);
    getchar();
    if (querFotoOuN == 's' || querFotoOuN == 'S') {
        fotoDePerfil(*perfil);
        (*perfil)[*QNT_Perfil].possuiFoto = true;
    }
    else {
        fprintf(arquivoCadastro, "URL: nada\t");
        fprintf(arquivoCadastro, "Cor: nada\t");
        (*perfil)[*QNT_Perfil].possuiFoto = false;
    }

    fprintf(arquivoCadastro, "ID: %s\t", (*perfil)[*QNT_Perfil].id);
    fprintf(arquivoCadastro, "NOME: %s\t", (*perfil)[*QNT_Perfil].nome);
    fprintf(arquivoCadastro, "EMAIL: %s\t", (*perfil)[*QNT_Perfil].email);
    fprintf(arquivoCadastro, "SENHA: %s\t", (*perfil)[*QNT_Perfil].senha);
    fprintf(arquivoCadastro, "BIO: %s\t\n", (*perfil)[*QNT_Perfil].bioPerfil);
    (*QNT_Perfil)++;
    fclose(arquivoCadastro);
    printf("\nSua conta foi cadastrada com sucesso!\n\n");
}

/* Funções para o Login de um Perfil
* verificaIdLogin; verifica se o id inserido já esta no arquivo, e envia a linha que ele ocupa para a verificação da senha
* verificaSenhaLogin; verifica se a senha inserida já esta no arquivo e na linha coorespondente
* logaPerfil; chama as funções de verificação e passa a variavel boooleana para logado
*/

int verificaIdLogin(char id[], int* linhaAtual) {
    buscaStruct busca;
    (*linhaAtual) = ZERO;
    // Verifica se o id é válido
    if (id == NULL) {
        printf("Id inválido.\n");
        return ERRO;
    }
    // Abre o arquivo dadosLogin.txt para leitura
    FILE* arquivoCadastro;
    arquivoCadastro = fopen("dadosLogin.txt", "r");
    if (arquivoCadastro == NULL) { //verifica se o arquivo foi aberto com ERRO
        printf("Erro ao abrir o arquivo.\n");
        return ERRO;
    }
    // Cria uma variável para armazenar cada linha do arquivo
    char linha[MAX_LINHA];
    fseek(arquivoCadastro, ZERO, SEEK_SET);
    // le cada linha linha do arquivo ate o final
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        (*linhaAtual)++;
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", busca.urlFotoPerfil, busca.cor, busca.id, busca.nome, busca.email, busca.senha, busca.bioPerfil);
        // Compara o id com o id do arquivo usando strcmp
        if (strcmp(busca.id, id) == SUCESSO) {
            fclose(arquivoCadastro);
            return *linhaAtual;
        }
    }
    // Fecha e salva os dados do arquivo
    fclose(arquivoCadastro);
    printf("\nId nao encontrado!\n\n");
    return ERRO;
}

int verificaSenhaLogin(char senha[], int* linhaAtual, loginStruct* logindados) {
    buscaStruct busca;
    int linhaSenha = ZERO;
    // Abre o arquivo dadosLogin.txt para leitura
    FILE* arquivoCadastro;
    arquivoCadastro = fopen("dadosLogin.txt", "r");
    if (arquivoCadastro == NULL) { //verifica se o arquivo foi aberto com ERRO
        printf("Erro ao abrir o arquivo.\n");
        return ERRO;
    }
    // Cria uma variável para armazenar cada linha do arquivo
    char linha[MAX_LINHA];
    fseek(arquivoCadastro, ZERO, SEEK_SET); //posiciona o ponteiro para o inicio do arquivo
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        linhaSenha++;
        if (*linhaAtual == linhaSenha) {
            // Armazena os dados da linha em string que são separada até o próximo \t.
            sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", busca.urlFotoPerfil, busca.cor, busca.id, busca.nome, busca.email, busca.senha, busca.bioPerfil);
            // Compara se a senha da linha é igual
            if (strcmp(senha, busca.senha) == SUCESSO) {
                fclose(arquivoCadastro);
                logindados->logado = true;
                return SUCESSO;
            }
            else {
                fclose(arquivoCadastro);
                printf("\nSenha incorreta!\n\n");
                return ERRO;
            }
        }
    }
    fclose(arquivoCadastro);
}

int logaPerfil(loginStruct* logindados, int linhaAtual, buscaStruct* busca, perfilStruct* perfil) {
    int verificaId, verificaSenha, escolhaLogin;
    // verifica o id do usuario para login
    printf("Informe seu id: ");
    fgets(logindados->id, MAX_ID, stdin);
    util_removeQuebraLinhaFinal(logindados->id);
    verificaId = verificaIdLogin(logindados->id, &linhaAtual);
    if (verificaId == ERRO) {
        return logindados->logado = false;
    }
    //verifica se a senha do usuario para login
    printf("Informe sua senha: ");
    fgets(logindados->senha, MAX_SENHA, stdin);
    util_removeQuebraLinhaFinal(logindados->senha);
    verificaSenha = verificaSenhaLogin(logindados->senha, &linhaAtual, logindados);
    if (verificaSenha == ERRO) {
        return logindados->logado = false;
    }
    return logindados->logado = true;
}


/** Funções apos estar logado
* listaPerfils; lê os perfis cadastrados e envia para a função imprimeTabela
* buscaPerfil; busca os caracteres semelhantes e procura nos arquivos id/email/nome iguais
* apagaPerfil; apaga todos os dados de um perfil
* apagaFoto; utilizada junto com a apagaPerfil para apagar as publicações daquele usuario
* postaFoto; salva a publicação do usuario em um arquivo
* visitaPerfil; lista os dados e as fotos do perfil procurado
* feedPostagens; carrega o feed com todos os post do coltegram
* minhasFoto; menu que possibilita ações usando apenas fotos do usuario
* iniciaLogin; responsavel pelo menu e chamar todas a funções apos estar logado
*/

int listarPerfils() {
    //declara as a variaveis
    char linha[MAX_LINHA];
    int qnt_linha = ZERO;
    perfilStruct* perfilArquivo;
    //aloca dinamicamente a struct
    perfilArquivo = malloc(sizeof(perfilStruct) * TAMANHO_INICIAL);
    // verifica se a alocação deu certo
    if (perfilArquivo == NULL) {
        printf("Erro na alocação de memoria\n");
        free(perfilArquivo);
        return ERRO;
    }
    FILE* arquivoCadastro;
    arquivoCadastro = fopen("dadosLogin.txt", "r");
    if (arquivoCadastro == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        free(perfilArquivo);
        return ERRO;
    }
    // loop de leitura do arquivo
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", perfilArquivo[qnt_linha].urlFotoPerfil, perfilArquivo[qnt_linha].cor, perfilArquivo[qnt_linha].id, perfilArquivo[qnt_linha].nome, perfilArquivo[qnt_linha].email, perfilArquivo[qnt_linha].senha, perfilArquivo[qnt_linha].bioPerfil);
        if (strcmp(perfilArquivo[qnt_linha].urlFotoPerfil, "nada") == SUCESSO) {
            // passa a variavel boolena para false
            perfilArquivo[qnt_linha].possuiFoto = false;
        }
        else {
            // passa o array da variavel booleana para true
            perfilArquivo[qnt_linha].possuiFoto = true;
        }
        qnt_linha++;
    }
    //fecha os dados do arquivo
    fclose(arquivoCadastro);
    // imprime a tabela com os dados dos perfis
    imprimeTabela(perfilArquivo, qnt_linha);
    //libera a memoria alocada
    free(perfilArquivo);
    return SUCESSO;
}

int buscaPerfil(buscaStruct* busca) {
    //declaração de variaveis
    FILE* arquivoCadastro;
    char linha[MAX_LINHA];
    int  nPerfis = ZERO;
    perfilStruct* perfisEncontrados;
    /// aloca dinamicamente perfisEncontrados
    perfisEncontrados = malloc(sizeof(perfilStruct) * TAMANHO_INICIAL);
    //verifica a alocação dinamica
    if (perfisEncontrados == NULL) {
        printf("Erro na alocação de memoria\n");
        return ERRO;
    }
    //abre o arquivo
    arquivoCadastro = fopen("dadosLogin.txt", "r");
    //verifica se o arquivo abriu com Sucesso
    if (arquivoCadastro == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return ERRO;
    }
    printf("Informe o id ou email ou o nome para pesquisar o perfil\n");
    fgets(busca->auxiliar, MAX_EMAIL, stdin);
    util_removeQuebraLinhaFinal(busca->auxiliar);
    //loop para leitura do arquivo
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", perfisEncontrados[nPerfis].urlFotoPerfil, perfisEncontrados[nPerfis].cor, perfisEncontrados[nPerfis].id, perfisEncontrados[nPerfis].nome, perfisEncontrados[nPerfis].email, perfisEncontrados[nPerfis].senha, perfisEncontrados[nPerfis].bioPerfil);
        //declara um ponteiro de string
        char* idEncontrado, * emailEncontrado, * nomeEncontrado;
        //usa a função strstr para comparar uma substring com a string
        idEncontrado = strstr(perfisEncontrados[nPerfis].id, busca->auxiliar);
        emailEncontrado = strstr(perfisEncontrados[nPerfis].email, busca->auxiliar);
        nomeEncontrado = strstr(perfisEncontrados[nPerfis].nome, busca->auxiliar);
        // verifica se encontrou o id email ou nome
        if (idEncontrado != NULL || emailEncontrado != NULL || nomeEncontrado != NULL) {
            // comparacao para ver se o usuario possui foto de perfil
            if (strcmp(perfisEncontrados[nPerfis].urlFotoPerfil, "nada") == SUCESSO) {
                perfisEncontrados[nPerfis].possuiFoto = false;
            }
            else {
                perfisEncontrados[nPerfis].possuiFoto = true;
            }
            nPerfis++;
        }
    }
    //caso tenha mais de um perfil imprime a tabela
    if (nPerfis > ZERO) {
        imprimeTabela(perfisEncontrados, nPerfis);
    }
    //caso não tenha perfis
    if (nPerfis == ZERO) {
        printf("\nNenhum perfil foi encontrado!\n");
    }
    // fecha e salva os dados do arquivo
    fclose(arquivoCadastro);
    free(perfisEncontrados);
    return SUCESSO;
}

int apagaPerfil(buscaStruct* busca, loginStruct* logindados, char idPerfil[]) {
    char linha[MAX_LINHA], escolhaDelete[TAMANHOESCOLHA], linhaFoto[MAX_LINHA], opcaoApagar;
    FILE* arquivoCadastro, * arquivoAUX; //declaração do arquivo de dados
    perfilStruct perfilArquivo;
    arquivoCadastro = fopen("dadosLogin.txt", "r");
    arquivoAUX = fopen("auxiliar.txt", "w");
    if (arquivoCadastro == NULL || arquivoAUX == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    printf("Qual o id do perfil?\n");
    fgets(busca->id, MAX_ID, stdin);
    util_removeQuebraLinhaFinal(busca->id);
    //verifica se é do perfil logado a conta que será apagada
    if (strcmp(busca->id, idPerfil) != SUCESSO) {
        printf("\nEsse perfil não pertence a você!\n");
        return ERRO;
    }
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", perfilArquivo.urlFotoPerfil, perfilArquivo.cor, perfilArquivo.id, perfilArquivo.nome, perfilArquivo.email, perfilArquivo.senha, perfilArquivo.bioPerfil);
        if (strcmp(busca->id, perfilArquivo.id) == SUCESSO) {
            printf("ID: %s\n", perfilArquivo.id);
            printf("NOME: %s\n", perfilArquivo.nome);
            printf("EMAIL: %s\n", perfilArquivo.email);
            printf("Você deseja apagar esse perfil, com os dados acima? [s/n]\n");
            fgets(escolhaDelete, TAMANHOESCOLHA, stdin);
            util_removeQuebraLinhaFinal(escolhaDelete);
            if (strcmp(escolhaDelete, "s") == SUCESSO) {
                //apaga os dados no arquvio cadastro e as fotos do perfil
                apagaFotos(busca->id, TODOS);
            }
            if (strcmp(escolhaDelete, "n") == SUCESSO) {
                printf("\nAção Cancelada!\n");
                //fecha os dados do arquio
                fclose(arquivoAUX);
                fclose(arquivoCadastro);
                return DESISTENCIA;
            }
        }
        else {
            // imprime os dados em outro arquivo
            fprintf(arquivoAUX, "%s", linha);
        }
    } //fecha os arquivos
    fclose(arquivoCadastro);
    fclose(arquivoAUX);
    //seção de reescrever
    arquivoCadastro = fopen("dadosLogin.txt", "w"); //abre na funcao de escrever o arquivo
    arquivoAUX = fopen("auxiliar.txt", "r"); //abre na funcao de ler o arquivo
    if (arquivoCadastro == NULL || arquivoAUX == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    fseek(arquivoAUX, ZERO, SEEK_SET); // passa para o inicio do arquivo
    while (fgets(linha, MAX_LINHA, arquivoAUX) != NULL) {
        fprintf(arquivoCadastro, "%s", linha); // printa no arquivo Cadastro tudo que esta no auxiliar
    }
    //fecha e salva os arquivos
    fclose(arquivoCadastro);
    fclose(arquivoAUX);
    return SUCESSO;
}

int postaFotos(loginStruct* logindados, char idPerfil[]) {
    FILE* arquivoFoto;
    postTempStruct* postTemp;
    postTemp = malloc(sizeof(postTempStruct) * MAX_POSTAGENS);
    bool verificacaoPostou = false;
    // declara as variaveis
    int numFotosTotal;
    char colorido;
    int fotoNumero = 0;
    int opcaoPostagem, largura, adicao = 0, contaFoto = 0;
    bool cor;
    printf("Bem vindo a seção de postagem do coltegram!\n");
    do {
        printf("Escolha uma das opções abaixo:\n");
        printf("[0] Sair da seção de postagens\n[1] Publicar um post\n");
        scanf("%d", &opcaoPostagem);
        getchar();
        switch (opcaoPostagem) {
        case 1:
            arquivoFoto = fopen("postagens.txt", "a");
            if (arquivoFoto == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return ERRO;
            }
            contaFoto = ZERO;
            printf("Quantas imagens serão no post? [LIMITE: 10 FOTOS] \n");
            scanf("%d", &logindados->postagens->qntFotosPost);
            getchar();
            //armazena a url da imagem
            do {
                printf("Cole a url da imagem que deseja postar(termine em .png, .jpeg, etc): ");
                fotoNumero++;
                fgets(logindados->postagens->urlImagemPost, MAX_URL, stdin);
                util_removeQuebraLinhaFinal(logindados->postagens->urlImagemPost);
                // escreve no arquivo a url
                fprintf(arquivoFoto, "URL: %s\t", logindados->postagens->urlImagemPost);
                // verifica se o id da foto ja foi postado
                if (verificacaoPostou == false) {
                    printf("Deseja que a imagem seja colorida? [s/n] ");
                    scanf("%c", &colorido);
                    getchar();
                    //verifica se a imagem é coloida
                    if (colorido == 's' || colorido == 'S') {
                        fprintf(arquivoFoto, "Cor: s\t");
                        //muda a variavel booleana para true
                        cor = true;
                    }
                    else if (colorido == 'n' || colorido == 'N') {
                        fprintf(arquivoFoto, "Cor: n\t");
                        // muda a variavel booleana para false
                        cor = false;
                    }
                    // armazena a o maior id retornado pela função
                    logindados->postagens->id = maiorIdPost();
                    fprintf(arquivoFoto, "Id do post: %d\t", logindados->postagens->id);
                    // so é acionado quando é a primeira foto
                    if (contaFoto == ZERO) {
                        printf("Digite a descricao do post: ");
                        fgets(logindados->postagens->descricaoPost, MAX_DESCRICAO, stdin);
                        util_removeQuebraLinhaFinal(logindados->postagens->descricaoPost);
                    }
                    fprintf(arquivoFoto, "Descricao: %s\t", logindados->postagens->descricaoPost);

                    printf("Preview: \n");
                    mostraImagem(logindados->postagens->qntFotosPost, fotoNumero, logindados->postagens->urlImagemPost, cor, logindados->postagens->descricaoPost, logindados->id, ZERO, ZERO);

                    fprintf(arquivoFoto, "ID: %s\t", idPerfil);
                    fprintf(arquivoFoto, "Curtidas: %d\t", ZERO);
                    fprintf(arquivoFoto, "Comentarios: %d\t\n", ZERO);
                    contaFoto++;
                }

                else {

                    if (colorido == 's' || colorido == 'S') {
                        fprintf(arquivoFoto, "Cor: s\t");
                        //muda a variavel booleana para true
                        cor = true;
                    }
                    else if (colorido == 'n' || colorido == 'N') {
                        fprintf(arquivoFoto, "Cor: n\t");
                        // muda a variavel booleana para false
                        cor = false;
                    }

                    fprintf(arquivoFoto, "Id do post: %d\t", postTemp->id);
                    fprintf(arquivoFoto, "Descricao: %s\t", postTemp->descricaoPost);
                    fprintf(arquivoFoto, "ID: %s\t", postTemp->idPerfil);
                    fprintf(arquivoFoto, "Curtidas: %d\t", ZERO);
                    fprintf(arquivoFoto, "Comentarios: %d\t\n", ZERO);
                }

            } while (contaFoto < logindados->postagens->qntFotosPost);

            printf("\nSeu post foi concluido! O id do post é %i\n", logindados->postagens->id);
            logindados->curtido[logindados->postagens->id] = false;
            adicao++;
            fclose(arquivoFoto);
            break;
        case 0:
            break;
        default:
            printf("Opção Inválida!\n");
            break;
        }

    } while (opcaoPostagem != SAIR);
    verificacaoPostou = false;
}

int visitaPerfil(buscaStruct* busca, loginStruct* logindados, bool logado) {
    char linha[MAX_LINHA];
    int escolha, saidaMenuFotos;
    bool verificaPostagem, verificacaoSeguir;
    perfilStruct perfilArquivo;
    bool corFoto;
    FILE* arquivoCadastro;
    asciiImg_t* fotoPerfil;
    arquivoCadastro = fopen("dadosLogin.txt", "r");

    if (arquivoCadastro == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    printf("Informe o ID do perfil que deseja visitar\n");
    fgets(busca->id, MAX_ID, stdin);
    util_removeQuebraLinhaFinal(busca->id);
    // comparar os ids
    while (fgets(linha, MAX_LINHA, arquivoCadastro) != NULL) {
        // Armazena os dados da linha em string que são separada até o próximo \t.
        sscanf(linha, "URL: %[^\t]\tCor: %[^\t]\tID: %[^\t]\tNOME: %[^\t]\tEMAIL: %[^\t]\tSENHA: %[^\t]\tBIO: %[^\t]\t\n", perfilArquivo.urlFotoPerfil, perfilArquivo.cor, perfilArquivo.id, perfilArquivo.nome, perfilArquivo.email, perfilArquivo.senha, perfilArquivo.bioPerfil);
        if (strcmp(busca->id, perfilArquivo.id) == SUCESSO) {
            if (strcmp(perfilArquivo.urlFotoPerfil, "nada") == SUCESSO) {
                printf("Usuário não possui foto de perfil!\n");
            }
            else {
                printf("Foto de Perfil\n");
                if (strcmp(perfilArquivo.cor, "s") == SUCESSO || strcmp(perfilArquivo.cor, "S") == SUCESSO) {
                    corFoto = true;
                }
                else if (strcmp(perfilArquivo.cor, "n") == SUCESSO || strcmp(perfilArquivo.cor, "N") == SUCESSO) {
                    corFoto = false;
                }
                fotoPerfil = insta_carregaImagem(perfilArquivo.urlFotoPerfil, corFoto, LARGURA);
                insta_imprimeImagem(fotoPerfil);
                insta_liberaImagem(fotoPerfil);
            }
            printf("Perfil @%s\n", busca->id);
            printf("NOME: %s\n", perfilArquivo.nome);
            printf("EMAIL: %s\n", perfilArquivo.email);
            printf("BIO: %s\n", perfilArquivo.bioPerfil);
            printf("SEGUIDORES: %d\nSEGUINDO: %d\n\n", numSeguidores(busca->id), numSeguindo(busca->id));
            do {
                verificacaoSeguir = verificaSeguida(logindados->id, busca->id);
                printf("Escolha uma opção:\n");
                if (logado == false || strcmp(busca->id, logindados->id) != SUCESSO) {
                    printf("[1] Ver postagens de @%s\n", busca->id);
                    if (logado == true) {
                        if (verificacaoSeguir == true) {
                            printf("[2] Deixar de seguir\n");
                        }
                        else {
                            printf("[2] Seguir\n");
                        }
                    }
                }
                else {
                    printf("[1] Ver suas postagens\n");
                }
                printf("[0] Sair\n");
                scanf("%d", &escolha);
                getchar();
                switch (escolha) {
                case 0:
                    fclose(arquivoCadastro);
                    break;
                case 1:
                    verificaPostagem = verificaPost(busca->id);
                    if (verificaPostagem == true) {
                        saidaMenuFotos = menuFotos(busca->id, logindados, logindados->logado);
                    }
                    else {
                        printf("Nenhuma foto de @%s foi postada!\n", busca->id);
                    }
                    if (saidaMenuFotos == SAIR) {
                        return SAIR;
                    }
                    break;
                case 2:
                    if (logado == true) {
                        if (strcmp(busca->id, logindados->id) != SUCESSO) {
                            if (verificacaoSeguir == true) {
                                deixarDeSeguir(logindados->id, busca->id);
                            }
                            else {
                                seguirPerfil(logindados->id, busca->id);
                            }
                        }
                        else {
                            printf("Você não pode seguir você mesmo!\n");
                        }
                    }
                    else {
                        printf("Você não está logado! Faça o login para obter acesso ao Coltegram inteiro!\n");
                    }
                    break;
                default:
                    printf("Opção Inválida!\n");
                    fclose(arquivoCadastro);
                    break;
                }
            } while (escolha != ZERO);
            return SUCESSO;
        }
    }
    printf("\nID não encontrado!\n");
}

int feedPostagens(char id[], loginStruct* logindados) {
    FILE* arquivoFoto, * arquivoCurtidas;
    int escolhaArquivoFoto = 1, numCurtidasCerto;
    char linhaFoto[MAX_LINHA];
    int numFotosTotal;
    bool corFoto = true;
    bool continuarMsmId = false;
    int idAnterior = -1, numFotosNoPost;
    int fotoNumero;
    bool logado = logindados->logado;
    postStruct fotosArquivo;
    arquivoFoto = fopen("postagens.txt", "r");
    //verificação de erro de abertura do arquivo
    if (arquivoFoto == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return ERRO;
    }
    // loop para ler a linha do arquivo
    fseek(arquivoFoto, ZERO, SEEK_SET);
    while (fgets(linhaFoto, MAX_LINHA, arquivoFoto) != NULL) {
        sscanf(linhaFoto, "URL: %[^\t]\tCor: %[^\t]\tId do post: %d\tDescricao: %[^\t]\tID: %[^\t]\tCurtidas: %d\tComentarios: %d\t\n", fotosArquivo.urlImagemPost, fotosArquivo.cor, &fotosArquivo.id, fotosArquivo.descricaoPost, fotosArquivo.idPerfil, &fotosArquivo.numCurtidasPost, &fotosArquivo.numComentariosPost);
        if (continuarMsmId == false) {
            numFotosNoPost = (numFotosPost(fotosArquivo.id));
            numFotosTotal = numFotosNoPost;

            if (fotosArquivo.id == idAnterior) {
                continue;
            }
        }
        else {
            numFotosNoPost--;
        }
        if (idAnterior == fotosArquivo.id) {
            fotoNumero++;
        }
        else {
            fotoNumero = 1;
        }
        if (strcmp(fotosArquivo.cor, "s") == SUCESSO || strcmp(fotosArquivo.cor, "S") == SUCESSO) {
            corFoto = true;
        }
        else if (strcmp(fotosArquivo.cor, "n") == SUCESSO || strcmp(fotosArquivo.cor, "N") == SUCESSO) {
            corFoto = false;
        }
        // função para a postagem de fotos
        if (continuarMsmId == true) {
            continuarMsmId = false;
            mostraImagem(numFotosTotal, fotoNumero, fotosArquivo.urlImagemPost, corFoto, fotosArquivo.descricaoPost, id, fotosArquivo.numCurtidasPost, fotosArquivo.numComentariosPost);
        }
        else {
            mostraImagem(numFotosTotal, fotoNumero, fotosArquivo.urlImagemPost, corFoto, fotosArquivo.descricaoPost, id, fotosArquivo.numCurtidasPost, fotosArquivo.numComentariosPost);
        }
        do {
            arquivoCurtidas = fopen("curtidas.txt", "a");
            fclose(arquivoCurtidas);
            if (arquivoCurtidas == NULL) {
                printf("Erro ao abrir o arquivo\n");
                return ERRO;
            }
            printf("\nEscolha uma das opções para o post %i\n[0] Sair\n[1] Ver mais postagens\n[2] Secao de comentarios\n[3] Ver curtidas\n", fotosArquivo.id);
            if (numFotosPost(fotosArquivo.id) > UM) {
                printf("[4] Ver mais fotos do post\n");
            }
            if (logado == true) {
                if (verificaCurtida(logindados->id, fotosArquivo.id) == true) {
                    printf("[5] Descurtir\n");
                }
                else {
                    printf("[5] Curtir\n");
                }
            }
            bool verificacaoSeguir = verificaSeguida(logindados->id, fotosArquivo.idPerfil);
            if (logado == true) {
                if (strcmp(fotosArquivo.idPerfil, logindados->id) != SUCESSO) {
                    if (verificacaoSeguir == true) {
                        printf("[6] Deixar de seguir @%s\n", fotosArquivo.idPerfil);
                    }
                    else {
                        printf("[6] Seguir @%s\n", fotosArquivo.idPerfil);
                    }
                }
            }
            scanf("%d", &escolhaArquivoFoto);
            getchar();
            switch (escolhaArquivoFoto) {
            case 0:
                return SAIR;
                break;
            case 1:
                break;
            case 2:
                if (secaoComentarios(id, logindados, fotosArquivo.numComentariosPost, fotosArquivo.id, logindados->logado) > fotosArquivo.numComentariosPost) {
                    fotosArquivo.numComentariosPost++;
                }
                break;
            case 3:
                if (fotosArquivo.numCurtidasPost == ZERO) {
                    printf("\nNão há curtidas ainda! Seja o primeiro a curtir o post de @%s!\n", fotosArquivo.idPerfil);
                }
                else {
                    verCurtidas(fotosArquivo.id);
                }
                break;
            case 4:
                if (numFotosNoPost > UM) {
                    numCurtidasCerto = fotosArquivo.numCurtidasPost;
                    continuarMsmId = true;
                }
                else {
                    continuarMsmId = false;
                    printf("\nNão há mais fotos para você ver nesse post!\n");
                }
                break;
            case 5:
                if (logado == true) {
                    if (verificaCurtida(logindados->id, fotosArquivo.id) == true) {//o post ja estava curtido
                        logindados->curtido[fotosArquivo.id] = true;
                        curtirPost(logindados, fotosArquivo, fotosArquivo.id, logindados->curtido[fotosArquivo.id]);
                        logindados->curtido[fotosArquivo.id] = false;
                        fotosArquivo.numCurtidasPost--;
                        printf("Descurtido!\n");
                    }
                    else { //nao estava curtido
                        logindados->curtido[fotosArquivo.id] = false;
                        curtirPost(logindados, fotosArquivo, fotosArquivo.id, logindados->curtido[fotosArquivo.id]);
                        logindados->curtido[fotosArquivo.id] = true;
                        fotosArquivo.numCurtidasPost++;
                        printf("Curtido!\n");
                    }
                }
                else {
                    printf("Você não está logado!\n");
                }
                break;
            case 6:
                if (logado == true) {
                    if (strcmp(fotosArquivo.idPerfil, logindados->id) != SUCESSO) {
                        if (verificacaoSeguir == true) {
                            deixarDeSeguir(logindados->id, fotosArquivo.idPerfil);
                        }
                        else {
                            seguirPerfil(logindados->id, fotosArquivo.idPerfil);
                        }
                    }
                    else {
                        printf("Você não pode seguir você mesmo!\n");
                    }
                }
                else {
                    printf("Você não está logado!\n");
                }
                break;

            default:
                printf("Opção invalida!\n");
                break;
            }
            if (escolhaArquivoFoto == SAIR) {
                break;
            }
            if (continuarMsmId == true) {
                break;
            }
        } while (escolhaArquivoFoto != UM);
        if (escolhaArquivoFoto == SAIR) {
            break;
        }
        idAnterior = fotosArquivo.id;
    }
    fclose(arquivoFoto);
}


int minhasFotos(loginStruct* logindados, char idPerfil[]) {
    int opcaoMfotos;
    printf("@%s, Bem vindo a seção com suas fotos!\n", idPerfil);
    do {
        printf("\nEscolha uma das opções abaixo\n[1] = Listar dados das publicações\n[2] = Visualizar Publicação\n[3] = Apagar Publicação\n[4] = Editar publicação\n[0] = Sair\n");
        scanf("%d", &opcaoMfotos);
        getchar();
        switch (opcaoMfotos) {
        case 1:
            //função de listar dados da publicação
            listafotos(idPerfil);
            break;
        case 2:
            //função de visualizar as fotos do perfil
            visualizaFoto(logindados, idPerfil);
            break;
        case 3:
            //funcao de apagar foto unica
            apagaFotos(idPerfil, UNICO);
            break;
        case 4:
            //funcao de edita publicação
            editaPost(logindados, idPerfil);
            break;
        case 0:
            printf("Saindo da seção com suas fotos!\n");
            break;
        }
    } while (opcaoMfotos != SAIR);
}

int iniciaLogin(loginStruct* logindados, int* linhaAtual, buscaStruct* busca, perfilStruct* perfil) {
    int escolhaLogin = ZERO, apagaPerfilSaida = ZERO;
    do {
        if (logindados->logado == false) {
            printf("\nVocê não está logado!\n");
        }
        else {
            printf("\nBem vindo de volta @%s!\n", logindados->id);
        }
        printf("[1] Listar Perfis\n[2] Buscar Perfil\n[3] Visitar Perfil\n[4] Apagar Perfil\n");
        if (logindados->logado == false) {
            printf("[5] Postar\n[6] Feed de Postagens\n[7] Minhas Fotos\n[8] Retornar ao menu inicial\n");
        }
        else {
            printf("[5] Postar, como @%s\n[6] Feed de Postagens\n[7] Minhas Fotos\n[8] Deslogar\n", logindados->id);
        }
        scanf("%i", &escolhaLogin);
        getchar();
        printf("\n");
        switch (escolhaLogin) {
        case 1:
            listarPerfils();
            break;
        case 2:
            buscaPerfil(busca);
            break;
        case 3:
            visitaPerfil(busca, logindados, logindados->logado);
            break;
        case 4:
            if (logindados->logado == true) {
                apagaPerfilSaida = apagaPerfil(busca, logindados, logindados->id);
                if (apagaPerfilSaida == SUCESSO) {
                    printf("\nSeu perfil não existe mais! Você foi desconectado.\n\n");
                    return SUCESSO;
                }
            }
            else {
                printf("\nVocê não está com perfil logado!\nFaça seu login para ter acesso completo ao Coltegram.\n");
            }
            break;
        case 5:
            if (logindados->logado == false) {
                printf("\nVocê não está com perfil logado!\nFaça seu login para ter acesso completo ao Coltegram.\n");
            }
            else {
                postaFotos(logindados, logindados->id);
            }
            break;
        case 6:
            feedPostagens(logindados->id, logindados);
            break;
        case 7:
            if (logindados->logado == false) {
                printf("\nVocê não está com perfil logado!\nFaça seu login para ter acesso completo ao Coltegram.\n");
            }
            else {
                minhasFotos(logindados, logindados->id);
            }
            break;
        case 8:
            if (logindados->logado == false) {
                printf("Retornando ao menu incial!\n\n");
            }
            else {
                printf("Perfl @%s foi deslogado com sucesso.\n\n", logindados->id);
                logindados->logado = false;
            }
            break;
        default:
            printf("Opção Inválida\n");
            break;
        }
    } while (escolhaLogin != DESLOGAR);
}

/**
 *  \brief Função principal.
 *
 *  \param [in] argc Número de argumentos.
 *  \param [in] argv Valores dos argumentos.
 *  \return Código de erro indicando o que aconteceu com o programa.
 */
int main(int argc, char** argv) {
    setlocale(LC_ALL, "Portuguese");
    int escolha, QNT_Perfil = ZERO, limiteContas = TAMANHO_INICIAL, novoLimiteContas = UM, linhaAtual = 0;
    bool loginLogado;
    // alocação dinâmica de memória do array da struct
    perfilStruct* perfil = malloc(sizeof(perfilStruct) * limiteContas);
    loginStruct* logindados = malloc(sizeof(loginStruct) * limiteContas);
    postStruct* postagens = malloc(sizeof(postStruct) * MAX_POSTAGENS);
    buscaStruct* busca = malloc(sizeof(buscaStruct) * limiteContas);
    if (perfil == NULL || logindados == NULL || busca == NULL || postagens == NULL) {
        printf("Erro na alocação de memória!\n");
        free(perfil);
        free(logindados);
        free(busca);
        free(postagens);
        return ERRO;
    }
    // loop com ações para o usuário
    printf("Bem vindo ao Coltegram, o Instagram em C!\n");
    do {
        printf("Deseja cadastrar a sua conta ou entrar com uma existente?\n");
        printf("[1] Cadastro\n[2] Login\n[3] Usar o Coltegram sem logar\n[0] Sair\n");
        scanf("%i", &escolha);
        getchar();
        switch (escolha) {
        case 1:
            cadastroPerfil(&perfil, &QNT_Perfil, &limiteContas, &novoLimiteContas);
            if (QNT_Perfil >= limiteContas) {
                reallocLimite(&perfil, &QNT_Perfil, &limiteContas, &novoLimiteContas);
            }
            break;
        case 2:
            loginLogado = logaPerfil(logindados, linhaAtual, busca, perfil);
            if (loginLogado == true) {
                iniciaLogin(logindados, &linhaAtual, busca, perfil);
            }
            break;
        case 3:
            logindados->logado = false;
            iniciaLogin(logindados, &linhaAtual, busca, perfil);
            break;
        case 0:
            printf("Saindo! Obrigado por usar o Coltegram, o Instagram em C!\n");
            break;
        default:
            printf("Opção invalida.\n");
        }
    } while (escolha != SAIR);
    free(perfil);
    free(logindados);
    free(busca);
    free(postagens);
    // Se chegou até aqui é porque deu tudo certo
    return SUCESSO;
}
