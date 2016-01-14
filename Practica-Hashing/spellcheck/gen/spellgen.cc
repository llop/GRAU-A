#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
using namespace std;

typedef vector<uint> IV;
typedef set<uint> IS;


const char* TEST_PREFIX="test-";
const char* DIC_EXT=".dic";
const char* TXT_EXT=".txt";

const uint MAX=1e9;     // maximo "valor" de una palabra
const uint MAX_N=1e6;   // maximo numero de palabras en el diccionario

IS dict;    // diccionario
IV text;    // texto

// pregunta por el número de palabras n en el diccionario, y la proporción p que deben estar bien escritas en el texto.
// luego genera:
//    - un diccionario con n palbras (números enteros positivos) al azar
//    - un texto con 2n palabras al azar, de las que aproximadamente el (100.0*p)% están en el diccionario
int main() {
  // esta funcion accelera el cin/cout
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  srand(time(NULL));    // initialize random seed
  
  // cuantas palabras en el diccionario?
  // para el texto pondremos el doble
  uint n;
  cout<<"¿Cuántas palabras ponemos en el diccionario?"<<endl;
  cin>>n;
  while (n>MAX_N) {
    cout<<"Máximo "<<MAX_N<<" palabras en el diccionario. ¿Cuántas ponemos?"<<endl;
    cin>>n;
  }
  
  // proporcion de palabras en el diccionario que se encuentran en el texto? [0.0..1.0]
  float p;
  cout<<"¿Qué proporción de palabras deben estar bien escitas?"<<endl;
  cin>>p;
  while (p<0.0||p>1.0) {
    cout<<"La proporción de palabras bien escitas debe estar entre 0 y 1. ¿Cuánto ponemos?"<<endl;
    cin>>p;
  }
  
  cout<<"Generating dictionary ("<<n<<" words)"<<endl;
  // crea diccionario con n palabras
  while (dict.size()<n) {
    uint x=rand()%MAX;
    if (!dict.count(x)) dict.insert(x);
  }
  
  // pasar el diccionario a un array ordenado para acelerar el acceso a posiciones random
  auto it=dict.begin();
  uint dict_arr[n];
  for (uint i=0; i<n; ++i, ++it) dict_arr[i]=*it;
  sort(dict_arr, dict_arr+n);
  
  
  uint m=2*n;
  cout<<"Generating text ("<<m<<" words)"<<endl;
  // crea texto con 2n palabras
  text.resize(m);
  for (uint i=0; i<m; ++i) {
    float f=(rand()%100)/100.0;
    if (f<=p) {
      text[i]=dict_arr[rand()%n];
    } else {
      uint x=rand()%MAX;
      while (dict.count(x)) x=rand()%MAX;
      text[i]=x;
    }
  }
  
  // que proporcion de palabras del texto están en el diccionario...?
  uint c=0;
  for (uint x : text) if (dict.count(x)) ++c;
  //cout<<"Se supone que el "<<p*100<<"% de las palabras del texto están bien escritas, y realmente es el "<<(c/(2.0*n))*100<<"%"<<endl;
  
  
  string dic_file_name(TEST_PREFIX+to_string(n)+'-'+to_string(p)+DIC_EXT);
  cout<<"Writing dictionary file ("<<dic_file_name<<")"<<endl;
  // nombrar los fichero como test-n.dic y test-n.txt
  random_shuffle(dict_arr, dict_arr+n);   // desordenar el diccionario: que no se confíen!
  ofstream dic_file(dic_file_name);
  if (dic_file.is_open()) {
    for (uint i=0; i<n; ++i) dic_file<<dict_arr[i]<<'\n';
    dic_file.close();
  } else {
    cout<<"Could not write dictionary file '"<<dic_file_name<<"'"<<endl;
    exit(0);
  }
  
  string txt_file_name(TEST_PREFIX+to_string(n)+'-'+to_string(p)+TXT_EXT);
  cout<<"Writing text file ("<<txt_file_name<<")"<<endl;
  random_shuffle(text.begin(), text.end());
  ofstream txt_file(txt_file_name);
  if (txt_file.is_open()) {
    for (int x : text) txt_file<<x<<'\n';
    txt_file.close();
  } else {
    cout<<"Could not write text file '"<<txt_file_name<<"'"<<endl;
    exit(0);
  }
  
  return 0;
}

