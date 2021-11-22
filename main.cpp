#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct localizacao{
  localizacao(): _x(0), _y(0){};
  localizacao(unsigned x, unsigned y): _x(x), _y(y) {};
  const unsigned _x;
  const unsigned _y;

  friend std::ostream & operator<<(std::ostream& os, const localizacao& loc) {
    os << '(' << loc._x << ", " << loc._y << ')';
    return os;
  }
};

vector<unsigned> ordenaByIndice(vector<double> lista){
  vector<unsigned> vetor;
  unsigned temp1 = 0;
  unsigned temp2 = 0;
  for(int k = 0; k < lista.size(); k++){
    vetor.push_back(k);
  }
  for (int i = 0; i < lista.size() - 1; i++){
    for (int j = 0; j < lista.size() - i - 1; j++){
      if (lista[j] < lista[j + 1]){
        temp2 = lista[j];
        temp1 = vetor[j];
        lista[j] = lista[j + 1];
        vetor[j] = vetor[j + 1];
        lista[j + 1] = temp2;
        vetor[j + 1] = temp1;
      }
    }
  }
  return vetor;    
}

int main() {
  unsigned N = 0;
  unsigned M = 0;
  unsigned numLojas = 0;
  unsigned numClientes = 0;
  vector<localizacao> localLojas;
  vector<localizacao> localClientes;
  vector<unsigned> estoqueLojas;
  vector<unsigned> estado;
  vector<unsigned> pagamento;
  vector<unsigned> idade;
  vector<double> score;
  char **grid;

  cin >> M;
  cin >> N;

  //aloca memória para o grid
  grid = (char**)malloc(N * sizeof(char*));
  for(int k = 0; k < N; k++){
    grid[k] = (char*)malloc(M * sizeof(char));
  }

  cin >> numLojas;
  int aux1 = 0;
  int aux2 = 0;
  string str = "";

  for(int i = 0; i < numLojas; i++){
    cin >> aux1;
    //cout << aux1;
    estoqueLojas.push_back(aux1);
    cin >> aux1;
    cin >> aux2;
    localLojas.push_back(localizacao(aux1, aux2));
  }

  cin >> numClientes;

  unsigned **listasPrefLojas;
  listasPrefLojas = (unsigned**)malloc(numLojas * sizeof(unsigned*));
  for(int i = 0; i < numLojas; i++){
    listasPrefLojas[i] = (unsigned*)malloc(numClientes * sizeof(unsigned));
  }


  unsigned **listasPrefClientes;
  listasPrefClientes = (unsigned**)malloc(numClientes * sizeof(unsigned*));
  for(int i = 0; i < numLojas; i++){
    listasPrefClientes[i] = (unsigned*)malloc(numLojas * sizeof(unsigned));
  }
  
  for(int i = 0; i < numClientes; i++){
    cin >> aux1;
    idade.push_back(aux1);
    cin >> str;
    if(str == "MG"){
      estado.push_back(0);
    }
    if(str == "PR"){
      estado.push_back(10);
    }
    if(str == "SP"){
      estado.push_back(20);
    }
    if(str == "SC"){
      estado.push_back(30);
    }
    if(str == "RJ"){
      estado.push_back(40);
    }
    if(str == "RN"){
      estado.push_back(50);
    }
    if(str == "RS"){
      estado.push_back(60);
    }
    
    cin >> str;
    if(str == "DINHEIRO"){
      pagamento.push_back(1);
    }
    if(str == "DEBITO"){
      pagamento.push_back(2);
    }
    if(str == "CREDITO"){
      pagamento.push_back(3);
    }

    cin >> aux1;
    cin >> aux2;
    localClientes.push_back(localizacao(aux1, aux2));

  }
  
  for(int i = 0; i < numClientes; i++){
    score.push_back((double)(abs((int)(60 - idade[i])) + estado[i])/pagamento[i]);
  }

  vector<unsigned> listaById;
  listaById = ordenaByIndice(score);

  //savar listaById em cada posicao da lista de pref da loja
  
//  for (vector<unsigned>::iterator it=listaById.begin(); it != listaById.end(); ++it){
//        cout << *it << endl;
//  }


//  for (vector<unsigned>::iterator it=pagamento.begin(); it != pagamento.end(); ++it){
//        cout << *it << endl;
//  }
  int x = 0;
  for (vector<double>::iterator it=score.begin(); it != score.end(); ++it){
        cout << x << "- " << *it << endl;
        x++;
  }  
/*
  for(unsigned i = 0; i < N; i++){
    for(unsigned j = 0; j < M; j++){
      grid[i][j] = 'X';
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cout << '\t' << grid[i][j];
    }
    cout << endl;
  }

  vector<list<unsigned>> grafo;
  for(int k = 0; k < N * M; k++){
    list<unsigned> lista;
    grafo.push_back(lista);
  }

  //constroi o grafo referente ao grid com relação aos vizinhos de cada quadrado
  unsigned x = 0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if((i - 1) >= 0) {
        grafo[x].push_back(grid[i - 1][j]);
      }
      if((i + 1) < N) {
        grafo[x].push_back(grid[i + 1][j]);
      }
      if((j - 1) >= 0) {
        grafo[x].push_back(grid[i][j - 1]);
      }
      if((j + 1) < M) {
        grafo[x].push_back(grid[i][j + 1]);
      }
      if((i - 1) >= 0 && (j - 1) >= 0) {
        grafo[x].push_back(grid[i - 1][j - 1]);
      }
      if((i - 1) >= 0 && (j + 1) < M) {
        grafo[x].push_back(grid[i - 1][j + 1]);
      }
      if((i + 1) < N && (j - 1) >= 0) {
        grafo[x].push_back(grid[i + 1][j - 1]);
      }
      if((i + 1) < N && (j + 1) < M) {
        grafo[x].push_back(grid[i + 1][j + 1]);
      }
      x++;
    }
  }

  cout << "Representação do grafo baseado no grid" << endl;
  for(int i = 0; i < N * M; i++){
    cout << i + 1<<"\t"; 
      for (list<unsigned>::iterator it=grafo[i].begin(); it != grafo[i].end(); ++it){
        cout << *it << "\t";
      }
      cout << endl;
  }
*/

  for(int j = 0; j < N; j++){
    free(grid[j]);
  }
  free(grid);

  for(int j = 0; j < numLojas; j++){
    free(listasPrefLojas[j]);
  }
  free(listasPrefLojas);

  for(int j = 0; j < numClientes; j++){
    free(listasPrefClientes[j]);
  }
  free(listasPrefClientes);

  return 0;
} 