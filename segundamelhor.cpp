#include <bits/stdc++.h>
using namespace std;

// usado para implementar o algoritmo de busca de união
int pai[100005];

// para acompanhar as arestas no MST
vector<int> atual;


// para acompanhar o número de arestas
// em árvores geradoras diferentes do MST
int edg;

// uma estrutura para representar uma
// aresta ponderada no grafo
struct aresta {
	int saida, entrada, peso;
} arestas[100005];
// vetor de arestas is of type aresta.

// Compara duas arestas de acordo
// com seus pesos.
// Usado em sort() para somar
// um vetor de arestas
bool comparar(aresta x, aresta y)
{
	return x.peso < y.peso;
}

// inicializando o array -
// cada vértice é seu próprio pai
// inicialmente
void initialise(int n)
{
	// 1-indexado
	for (int i = 1; i <= n; i++)
		pai[i] = i;
}

// Implementando o algoritmo union-find
int find(int x)
{
	if (pai[x] == x)
		return x;
	return pai[x] = find(pai[x]);
}

// Função para encontrar a união
// para a árvore geradora mínima
int union1(int i, int soma)
{
	int x, y;
	x = find(arestas[i].saida);
	y = find(arestas[i].entrada);
	if (x != y) {

		// pai de x = y (LCA) -
        // ambos são conectados por aresta
		pai[x] = y;

		// keeping track of arestas in MST
		atual.push_back(i);

        // encontrando a soma dos pesos
        // de arestas no MST
		soma += arestas[i].peso;
	}
	return soma;
}

// Função para encontrar o segundo
// melhor árvore geradora mínima
int union2(int i, int soma)
{
	int x, y;
	x = find(arestas[i].saida);
	y = find(arestas[i].entrada);
	if (x != y) {
        // pai de x = y (LCA) -
        // ambos são conectados por aresta
		pai[x] = y;

        // soma dos pesos das arestas
        // na árvore geradora
		soma += arestas[i].peso;
		edg++;
	}
	return soma;
}

int programa() {
    // V-> Número de vértices,
    // E-> Número de arestas
	int V, E;
    cout << "Digite o numero de vertices seguido do numero de arestas: ";
    cin >> V >> E;
    
    // inicializando o vetor para
    // ser usado para encontrar união
    int vertEntrada, vertSaida, peso;
	initialise(V);

    vector<int> vertsSaida;

    vector<int> vertsEntrada;

    vector<int> pesos;
    
    cout<< "Digite o vertice de saida, o de entrada e o peso da aresta \n ";
    for (int i=0; i<E; i++){
        cin >> vertSaida >> vertEntrada >> peso;
        vertsSaida.push_back(vertSaida);
        vertsEntrada.push_back(vertEntrada);
        pesos.push_back(peso);
    }

	for (int i = 0; i < E; i++) {
		arestas[i].saida = vertsSaida[i];
		arestas[i].entrada = vertsEntrada[i];
		arestas[i].peso = pesos[i];
	}

    // ordenando o vetor de arestas
    // com base nos pesos das arestas
	sort(arestas, arestas + E, comparar);

	int soma = 0;
	for (int i = 0; i < E; i++) {
		soma = union1(i, soma);
	}

	// imprimindo o custo da primeira arvore
	cout << "primeira arvore geradora minima: " << soma << "\n";

	// inicializando o custo da segunda arvore geradora
	int seg_melhor_arv = INT_MAX;

	// setando a soma para ZERO
	soma = 0;
	int j;
	for (j = 0; j < atual.size(); j++) {
		initialise(V);
		edg = 0;
		for (int i = 0; i < E; i++) {

            // excluindo uma aresta da
            //arvore geradora minima de cada vez
            // e formando a árvore geradora
            // com o restante
            // arestas
			if (i == atual[j])
				continue;
			soma = union2(i, soma);
		}
            // verificando se o número de arestas = V-1 ou não
            // já que o número de arestas em uma árvore geradora de
            // gráfico com V vértices é (V-1)
		if (edg != V - 1) {
			soma = 0;
			continue;
		}

		// // armazenando a soma mínima
        // em seg_melhor_arv
		if (seg_melhor_arv > soma)
			seg_melhor_arv = soma;
		soma = 0;
	}

	// imprimindo o custo da segunda arvore
	cout << "segunda arvore geradora minima: "
		<< seg_melhor_arv << "\n";
	return 0;
}



int main()
{
    int nCasos, n=0; 
    cout << "Digite o numero de casos: ";
    cin >> nCasos;

    while (n<nCasos){
        programa();
        n++;
    }

}
