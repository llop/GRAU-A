#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
typedef vector<int> IV;

// nodo del arbol
struct Node {
  int val;    // valor
  int hei;    // altura
  Node* lef;  // subarbol izquierdo
  Node* rig;  // subarbol derecho
};

// implementacion del AVL
// permite elementos repetidos (como el 'multiset' de la stl)
class AVL {
  
private:
  
  // nodo raiz del arbol
  Node* root;
  
  // retorna la altura de 'nod'
  inline int height(Node* nod) {
    return nod==NULL?0:nod->hei;
  }
  
  // balance del arbol con raiz en 'nod':
  // sera negativo si el subarbol derecho es mas alto que el izquierdo
  // positivo si el subarbol izquierdo es el mas alto
  // o cero si son iguales
  inline int balance(Node* nod) {
    return nod==NULL?0:height(nod->lef)-height(nod->rig);
  }
  
  // actualiza la altura de 'nod'
  inline void update_height(Node* nod) {
    int hl=height(nod->lef);
    int hr=height(nod->rig);
    nod->hei=(hl>hr?hl:hr)+1;
  }
  
  // rotacion derecha sobre 'x'
  inline Node* rotate_right(Node* x) {
    Node* y=x->lef;
    Node* t2=y->rig;
    y->rig=x;
    x->lef=t2;
    update_height(x);
    update_height(y);
    return y;
  }
  
  // rotacion izquierda sobre 'x'
  inline Node* rotate_left(Node* x) {
    Node* y=x->rig;
    Node* t2=y->lef;
    y->lef=x;
    x->rig=t2;
    update_height(x);
    update_height(y);
    return y;
  }
  
  // rotacion doble a la derecha
  inline Node* double_rotate_right(Node* nod) {
    nod->lef=rotate_left(nod->lef);
    return rotate_right(nod);
  }
  
  // rotacion doble a la izquierda
  inline Node* double_rotate_left(Node* nod) {
    nod->rig=rotate_right(nod->rig);
    return rotate_left(nod);
  }
  
  // rotaciones: equilibran el arbol despues de una insercion o borrado
  // al acabar, es necesario recalcular las alturas de los nodos tratados
  // complejidad: O(1)
  inline Node* update_balance(Node* nod) {
    
    // si el arbol ha quedado desequilibrado hay que hacer algun tipo de rotacion
    int bal=balance(nod);
    if (bal>1) {
      // el subarbol izquierdo es mas alto que el derecho
      // hay que mirar su balance
      int bal_lef=balance(nod->lef);
      if (bal_lef>=0) {
        // el sub-subarbol izquierdo es tan o mas alto: rotacion simple derecha
        return rotate_right(nod);
      } else {
        // el hijo derecho del subarbol izquierdo de 'nod' es mas alto
        // rotacion doble derecha
        return double_rotate_right(nod);
      }
    } else if (bal<-1) {
      // el subarbol derecho es mas alto que el izquierdo
      // hay que mirar su balance
      int bal_rig=balance(nod->rig);
      if (bal_rig<=0) {
        // el sub-subarbol derecho es tan o mas alto: rotacion simple izquierda
        return rotate_left(nod);
      } else {
        // el hijo izquierdo del subarbol derecho de 'nod' es mas alto
        // rotacion doble izquierda
        return double_rotate_left(nod);
      }
    }
    
    // no hubo rotacion, devolver el nodo tal cual
    return nod;
  }
  
  // insercion: anadir 'val' en el (sub)arbol 'nod'
  // el re-balanceado se produce como mucho 1 vez
  // complejidad: O(log n)
  Node* insert(Node* nod, int val) {
    
    // nodo vacio, podemos insertar el valor aqui
    if (nod==NULL) return new Node({ val, 1, NULL, NULL });
    
    // si el valor a insertar es menor que el de 'nod'
    // insertar en el subarbol izquierdo
    // si es mayor o igual, ir al subarbol derecho
    // al acabar, recalcular la altura de 'nod'
    if (val < nod->val) nod->lef=insert(nod->lef, val);
    else nod->rig=insert(nod->rig, val);
    update_height(nod);
    
    // equilibrar el arbol si es necesario
    return update_balance(nod);
  }
  
  // devuelve el nodo de mayor valor del arbol con raiz en 'nod'
  inline Node* max_node(Node* nod) {
    while (nod->rig!=NULL) nod=nod->rig;
    return nod;
  }
  
  // borrado: eliminar 'val' del (sub)arbol 'nod'
  // el re-balanceado puede producirse en todos los padres del nodo borrado
  // complejidad: O(log n)
  Node* erase(Node* nod, int val) {
    
    // si el nodo esta vacio, no hay nada que borrar
    if (nod==NULL) return NULL;
    
    // si el valor a borrar es menor que el de 'nod' buscar en el subarbol izquierdo
    // si es mayor, ir al subarbol derecho
    if (val<nod->val) nod->lef=erase(nod->lef, val);
    else if (val>nod->val) nod->rig=erase(nod->rig, val);
    else {
      // el valor del nodo es el que queremos borrar
      // hay 3 posibilidades: 
      if (nod->lef==NULL&&nod->rig==NULL) {
        // 'nod' es una hoja -ponerlo a NULL, liberar memoria y retornar
        Node* leaf=nod;
        nod=NULL;
        delete leaf;
        return NULL;
      } else if (nod->lef==NULL||nod->rig==NULL) {
        // 'nod' es el padre de una hoja
        // sustituir 'nod' por su hijo, eliminar hoja y retornar
        Node* leaf=nod->lef==NULL?nod->rig:nod->lef;
        *nod=*leaf;
        delete leaf;
        return nod;
      } else {
        // sustituir 'nod' por el nodo de mayor valor de su subarbol izquierdo
        // y eliminar ese nodo de mayor valor
        Node* leaf=max_node(nod->lef);
        nod->val=leaf->val;
        nod->lef=erase(nod->lef, leaf->val);
      }
    }
    
    // actualizar altura, y a lo mejor equilibrar el arbol
    update_height(nod);
    return update_balance(nod);
  }
  
  // consulta: esta 'val' presente en el (sub)arbol 'nod'?
  // complejidad: O(log n)
  Node* find(Node* nod, int val) {
    
    #ifdef VERBOSE
    ++avl_iter_cnt;
    #endif
    
    // nodo vacio, el valor buscado no esta en el arbol
    if (nod==NULL) return NULL;
    
    // si el valor buscado es menor que el de 'nod'
    // buscar en el subarbol izquierdo
    // si es mayor, ir al subarbol derecho
    // si es el mismo, lo hemos encontrado :)
    if (val<nod->val) return find(nod->lef, val);
    else if (val>nod->val) return find(nod->rig, val);
    return nod;
  }
  
  
  //--------------------------------------------
  // Print to standard out methods
  //--------------------------------------------
  
  // imprimir los valores del arbol, en pre-orden
  // complejidad: O(n)
  void print_preorder(Node* nod) {
    if (nod!=NULL) {
      cout<<nod->val<<' ';
      print_preorder(nod->lef);
      print_preorder(nod->rig);
    } else cout<<"* ";
  }
  
  // imprimir los valores del arbol, en in-orden
  // complejidad: O(n)
  void print_inorder(Node* nod) {
    if (nod!=NULL) {
      print_inorder(nod->lef);
      cout<<nod->val<<' ';
      print_inorder(nod->rig);
    } else cout<<"* ";
  }
  
  // imprimir los valores del arbol, en post-orden
  // complejidad: O(n)
  void print_postorder(Node* nod) {
    if (nod!=NULL) {
      print_postorder(nod->lef);
      print_postorder(nod->rig);
      cout<<nod->val<<' ';
    } else cout << "* ";
  }
  
  
  //--------------------------------------------
  // Initializer methods
  //--------------------------------------------
  
  // build from avl preorder vector. Cost: O(n^2)
  Node* build_preorder(const IV &vals, int start, int end) {
    if (start>end) return NULL;
    int i=start+1;
    while (i<=end && vals[i]<vals[start]) ++i;
    Node* nod=new Node({ vals[start], 1, NULL, NULL });
    nod->lef=build_preorder(vals, start+1, i-1);
    nod->rig=build_preorder(vals, i, end);
    update_height(nod);
    return nod;
  }
  
  // build from avl preorder vector. Smarter way than previous method. Cost: O(n)
  Node* build_preorder2(const IV &vals, Node* &nod, int mx, int &pos, int len) {
    nod=new Node({ vals[pos], 0, NULL, NULL });
    ++pos;
    if (pos<len && vals[pos]<nod->val) build_preorder2(vals, nod->lef, nod->val, pos, len);
    if (pos<len && (mx==-1 || mx>vals[pos])) build_preorder2(vals, nod->rig, mx, pos, len);
    update_height(nod);
    return nod;
  }
  
  // build from sorted array. Cost: O(n)
  Node* build_sorted(const IV &vals, int start, int end) {
    if (start>end) return NULL;
    int m=(start+end)/2;
    Node* nod=new Node({ vals[m], 1, NULL, NULL });
    nod->lef=build_sorted(vals, start, m-1);
    nod->rig=build_sorted(vals, m+1, end);
    update_height(nod);
    return nod;
  }
  
  
public:
  
  #ifdef VERBOSE
  LL avl_iter_cnt=0;
  #endif
  
  void insert(int val) {
    root=insert(root, val);
  }
  
  void erase(int val) {
    root=erase(root, val);
  }
  
  bool find(int val) {
    return find(root, val)==NULL?0:1;
  }
  
  
  void print_preorder() {
    print_preorder(root);
    cout<<endl;
  }
  
  void print_inorder() {
    print_inorder(root);
    cout<<endl;
  }
  
  void print_postorder() {
    print_postorder(root);
    cout<<endl;
  }
  
  
  void init_preorder(const IV &preorder) {
    root=build_preorder(preorder, 0, preorder.size()-1);
  }
  
  void init_preorder2(const IV &preorder) {
    int i=0;
    build_preorder2(preorder, root, -1, i, preorder.size());
  }
  
  void init_sorted(const IV &sorted) {
    root=build_sorted(sorted, 0, sorted.size()-1);
  }
  
};



#endif
