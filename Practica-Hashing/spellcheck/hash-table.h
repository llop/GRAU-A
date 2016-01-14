#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <set>
#include "hash.h"
using namespace std;

typedef vector<int*> IPV;
typedef set<int> IS;
typedef vector<IS> ISV;


// Open Addressing Hash Table
// Implementacion de una tabla de hash de direccionamiento abierto
// Viene a ser lo mismo que el unordered_set<int> de la STL
template <typename H, typename=typename enable_if<is_base_of<Hasher, H>::value, H>::type>
class OpenAddressingHashTable {
  
public:
  
  #ifdef VERBOSE
  LL hash_cnt=0;
  #endif
  
private:
  
  int cnt;      // numero de elementos
  IPV tbl;      // tabla de entradas
  H hasher;     // hashers
  
  // Encuentra la posicion de la tabla en la que se encuentra 'key'
  // O si la 'key' no esta en la tabla, encuentra la posicion (vacia)
  // en la que es posible insertar 'key'
  // En el caso peor habra que patearse la tabla entera O(n)
  // Igual el coste amortizado es O(1)
  inline uint slot(int key, const IPV &table) {
    #ifdef VERBOSE
    ++hash_cnt;
    #endif
    
    uint pos=hasher.get_hash(key)%table.size();
    while (table[pos]!=NULL) {
      if (*table[pos]==key) return pos;
      ++pos%=table.size();
    }
    return pos;
  }
  
  // Redimensiona la tabla
  // Crea una nueva tabla el doble de grande,
  // y anade los elementos de la tabla original uno a uno
  // Complejidad: O(n)
  void resize() {
    IPV tbl_tmp(2*tbl.size(), NULL);
    for (uint i=0; i<tbl.size(); ++i) {
      if (tbl[i]!=NULL) {
        uint pos=slot(*tbl[i], tbl_tmp);
        tbl_tmp[pos]=tbl[i];
      }
    }
    tbl=tbl_tmp;
  }
  
public:
  
  // Crea la hash table, con capacidad inicial de 11
  // Factor de carga: 0.8
  OpenAddressingHashTable() {
    cnt=0;
    tbl=IPV(11, NULL);
  }
  
  // Inserta un valor en la tabla
  // En el peor de los casos, todas las entradas irian a la misma posicion
  // de la tabla -complejidad O(n)
  // En el mejor caso, cada entrada se mapearia en una posicion distinta
  // en cuyo caso la complejidad seria O(1)
  // Coste amortizado: O(1)
  void insert(int key) {
    // Encontrar la posicion para la nueva entrada
    uint pos=slot(key, tbl);
    if (tbl[pos]==NULL) {
      // Hay hueco -> insertar ahi la nueva entrada
      ++cnt;
      tbl[pos]=new int(key);
      // Factor de carga rebasado: hay que redimensionar la tabla 
      if (cnt>=(int)(0.8*tbl.size())) resize();
    }
  }
  
  // Elimina 'key' del conjunto
  // Al igual que la insercion, el coste puede ser
  // entre O(1) -caso mejor-, y O(n) -caso peor.
  // Coste amortizado: O(1)
  void erase(int key) {
    // Encontrar entrada y eliminarla de la tabla
    uint pos=slot(key, tbl);
    if (tbl[pos]!=NULL) delete tbl[pos];
    // no puede haber huecos entre la posicion natural de una entrada
    // y su posicion establecida -si no, la busqueda de la funcion 'slot' fallaria
    // asi que hay que reubicar las entradas que caerian en la posicion eliminada
    uint nex_pos=pos;
    while (tbl[pos]!=NULL) {
      // eliminar la entrada
      tbl[pos]=NULL;
      bool loop=true;
      while (loop) {
        // si la siguiente posicion esta vacia, hemos terminado
        ++nex_pos%=tbl.size();
        if (tbl[nex_pos]==NULL) return;
        
        #ifdef VERBOSE
        ++hash_cnt;
        #endif
      
        // 'p' es la posicion natural por hash de la siguiente entrada en la tabla
        // si 'p' no esta dentro del intervalo ciclico [pos, next_pos],
        // hay que rellenar la posicion vacia con la entrada en nex_pos
        uint p=hasher.get_hash(*tbl[nex_pos])%tbl.size();
        loop=pos<=nex_pos?pos<p&&p<=nex_pos:pos<p||p<=nex_pos;
      }
      // hacer la reubicacion de la entrada conflictiva
      tbl[pos]=tbl[nex_pos];
      pos=nex_pos;
    }
  }
  
  // Retorna si 'key' pertenece al conjunto
  // Misma complejidad que 'insert' y 'erase'
  // Coste amortizado: O(1)
  bool contains(int key) {
    uint pos=slot(key, tbl);
    if (tbl[pos]!=NULL) return true;
    return false;
  }
  
};



// Separate Chaining Hash Table
// Implementacion de una tabla de hash de encadenamiento separado
// Viene a ser lo mismo que el unordered_map<int, int> de la STL
template <typename H, typename=typename enable_if<is_base_of<Hasher, H>::value, H>::type>
struct SeparateChainingHashTable {
  
public:
  
  #ifdef VERBOSE
  LL hash_cnt=0;
  #endif
  
private:
  
  int cnt;      // numero de elementos de la tabla
  ISV tbl;      // tabla de entradas
  H hasher;     // hashers
  
  
  // Redimensiona la tabla de entradas creando una nueva tabla el doble de grande,
  // e insertando ahi todas las entradas existentes
  // Complejidad: O(n)
  void resize() {
    ISV tbl_tmp(2*tbl.size());
    for (uint i=0; i<tbl.size(); ++i) {
      for (auto it=tbl[i].begin(); it!=tbl[i].end(); ++it) {
        #ifdef VERBOSE
        ++hash_cnt;
        #endif
      
        int key=*it;
        uint pos=hasher.get_hash(key)%tbl_tmp.size();
        tbl_tmp[pos].insert(key);
      }
    }
    tbl=tbl_tmp;
  }
  
  
public:
  // Capacidad inicial de 11
  // Factor de carga: 2
  SeparateChainingHashTable() {
    cnt=0;
    tbl=ISV(11);
  }
  
  // Inserta un elemento 'key' en la tabla
  // Coste amortizado: O(1)
  // En el peor de los casos, todas las entradas irian a la misma lista: O(n)
  void insert(int key) {
    #ifdef VERBOSE
    ++hash_cnt;
    #endif
    
    // Encontrar la posicion
    uint pos=hasher.get_hash(key)%tbl.size();
    auto it=tbl[pos].find(key);
    if (it!=tbl[pos].end()) return;
    
    // Si la 'key' es nueva, insertarla en la siguiente posicion libre
    tbl[pos].insert(key);
    ++cnt;
    // Si se ha superado el factor de carga, redimensionar
    if (cnt>=2*(int)tbl.size()) resize();
  }
  
  // Eliminar 'key' del conjunto
  // Coste amortizado: O(1)
  // Aunque si todas las entradas estan en la misma posicion, O(n)
  void erase(int key) {
    // Encontrar la posicion en la que se encontraria la entrada
    uint pos=hasher.get_hash(key)%tbl.size();
    auto it=tbl[pos].find(key);
    if (it!=tbl[pos].end()) tbl[pos].erase(it);
  }
  
  // Retorna si 'key' pertenece al conjunto
  // Misma complejidad que 'insert' y 'erase'
  bool contains(int key) {
    #ifdef VERBOSE
    ++hash_cnt;
    #endif
    
    uint pos=hasher.get_hash(key)%tbl.size();
    auto it=tbl[pos].find(key);
    if (it!=tbl[pos].end()) return true;
    return false;
  }
  
};



#endif
