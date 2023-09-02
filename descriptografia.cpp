#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

    string nomeArq;
    cout << "Digite o nome do arquivo com a extensao: " << endl;
    cin >> nomeArq;

    /** string que usaremos ao gerar o arquivo de saida no final */
    string arqOut = nomeArq;

    ifstream inFile(nomeArq);
    if (!inFile.is_open()) {
        cerr << "Nao foi possível abrir o arquivo." << endl;
        return 1;
    }


    /** descobrindo a maior palavra e o numero de linhas */
    string maiorPalavra;
    int test=0;
    int linhas=0;

    while (inFile >> maiorPalavra) {
        test = maiorPalavra.length();
        if (test > linhas) {
            linhas = test;
        }
    }

    inFile.clear(); // limpa os flags de erro depois da leitura anterior
    inFile.seekg(0, ios::beg); // retorna ao inicio do arquivo

    /** atribuindo o segredo a misterio */
    string misterio;

    while (!inFile.eof()) {
        getline(inFile, misterio);
    }

    /** calculando o numero de colunas */
    int colunas = misterio.length()/linhas;

    /** criando a matriz para transpor */
    char matriz[linhas][colunas];

    inFile.clear();
    inFile.seekg(0, ios::beg);

    /** preenchendo a matriz com o segredo */
    int pos=0;

    for (int i=0; i<colunas; i++) {
        for (int j=0; j<linhas; j++) {
            matriz[j][i]=misterio[pos];
            if(j==(linhas-1)){
                pos++;
            }
            pos++;
        }
    }

    /** preenchendo o vetor com o numero de colunas */
    int numcol[colunas];

    for (int i=0; i<colunas; i++) {
        numcol[i]=i;
    }

    /** exibindo todas o resultado na tela do computador */
    cout << "\nAs mensagens possiveis sao:\n";
    int num=1;
    do {
        cout << "Chave[" << num << "]: ";
        num++;
        for (int i=0; i<linhas+1; i++) {
            for (int j=0; j<colunas; j++) {
                cout << matriz[i][numcol[j]];
                }
            }
            cout << endl;
        } while (next_permutation(numcol, numcol + colunas));
        /** usando next_permutation para testar todas as possibilidades */

    cout << "As informacoes exibidas foram salvas no arquivo de saida!" << endl;


    /** criando o arquivo de saida */
    ofstream outFile;

    /** retirando o '.txt' e adicionando o '_dec' */
    size_t posicao = arqOut.find('.');
    arqOut.insert(posicao, "_dec");

    outFile.open(arqOut, ios::out); // abre o arquivo para saída
    if(!outFile){
        cerr << "O arquivo de saida nao pode ser gerado." << endl;
        return -1;
    }

    outFile << "As mensagens possiveis sao:\n";
    int numero=1;
    do {
        outFile << "Chave[" << numero << "]: ";
        numero++;
        for (int k=0; k<linhas+1; k++) {
            for (int l=0; l<colunas; l++) {
                outFile << matriz[k][numcol[l]];
                }
            }
            outFile << endl;
        } while (next_permutation(numcol, numcol + colunas));

    outFile << "Todas as informacoes foram salvas neste arquivo!" << endl;

    return 0;
}
