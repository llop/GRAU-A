#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include <set>
#include <sys/time.h>
#include "avl.h"
#include "hash-table.h"
#include "bloom-filter.h"
using namespace std;

typedef long long LL;
typedef set<string> SS;
typedef vector<int> IV;


const char* TESTS_FOLDER="./tests/";
const char* DIC_EXT=".dic";
const char* TXT_EXT=".txt";

const string ALL_OPT="-all";


// variables
int algo;     // algoritmo
int hfun;     // funcion de hash
string test;  // el test que corremos (-all: todos; 
              // si no, será el nombre de unos ficheros .dic y .txt en la carpeta tests)

SS dicts;     // ficheros diccionario
SS texts;     // ficheros de texto


double init_secs, check_secs;   // contadores de tiempo
static double total_secs=0;
static double total_init=0;
static double total_chck=0;


// usage
inline void parse_args_error() {
  cout<<"Usage: spellchecker -binary (basic|avl) [-all|test]"<<endl;
  cout<<"       spellchecker -hash (oaht|scht|bf|sbf) (mur|fnv1|h3) [-all|test]"<<endl;
  exit(0);
}

// find out algorithm from program args
// print usage and exit if invalid input
void parse_args(int argc, char** argv) {
  
  int index=1;
  if (argc>index&&!strcmp(argv[index],"-binary")) {
    ++index;
    if (argc>index&&!strcmp(argv[index],"basic")) algo=1;
    else if (argc>index&&!strcmp(argv[index],"avl")) algo=2;
    else parse_args_error();
  } else if (argc>index&&!strcmp(argv[index],"-hash")) {
    // data structure?
    ++index;
    if (argc>index&&(!strcmp(argv[index],"oaht")||!strcmp(argv[index],"open-addressing-hash-table"))) algo=3;
    else if (argc>index&&(!strcmp(argv[index],"scht")||!strcmp(argv[index],"separate-chaining-hash-table"))) algo=4;
    else if (argc>index&&(!strcmp(argv[index],"bf")||!strcmp(argv[index],"bloom-filter"))) algo=5;
    else if (argc>index&&(!strcmp(argv[index],"sbf")||!strcmp(argv[index],"spectral-bloom-filter"))) algo=6;
    else parse_args_error();
    // hash function?
    ++index;
    if (argc>index&&(!strcmp(argv[index],"mur")||!strcmp(argv[index],"murmur"))) hfun=1;
    else if (argc>index&&!strcmp(argv[index],"fnv1")) hfun=2;
    else if (argc>index&&!strcmp(argv[index],"h3")) hfun=3;
    else parse_args_error();
  } else parse_args_error();
  
  ++index;
  test=ALL_OPT;
  if (argc>index) test=argv[index];
}


inline bool ends_with(const string &str, const string &suffix) {
  return str.size()>=suffix.size()&&str.compare(str.size()-suffix.size(), suffix.size(), suffix)==0;
}

// put dictionary and text file from 'tests' folder into 'dicts' and 'texts' sets
void get_dics_txts() {
  dicts=SS();
  texts=SS();
  
  DIR *pDIR;
  struct dirent *entry;
  if ((pDIR=opendir(TESTS_FOLDER))) {
    while ((entry=readdir(pDIR))) {
      const char* file_name=entry->d_name;
      if (strcmp(file_name, ".")!=0 && strcmp(file_name, "..")!=0) {
        const string name(file_name);
        if (ends_with(name, DIC_EXT)) dicts.insert(name.substr(0, name.size()-4));
        if (ends_with(name, TXT_EXT)) texts.insert(name.substr(0, name.size()-4));
      }
    }
    closedir(pDIR);
  }
}


// read dictionary and text files into dic and txt vectors
// exit if there was trouble reading files
void read_dic_txt(const string &d, IV &dic, IV &txt) {
  ifstream dic_file(TESTS_FOLDER+d+DIC_EXT);
  if (dic_file.is_open()) {
    int x;
    while (dic_file>>x) dic.push_back(x);
    dic_file.close();
  } else {
    cout<<"Could not read dictionary file '"<<TESTS_FOLDER+d+DIC_EXT+"'"<<endl;
    exit(0);
  }
  ifstream txt_file(TESTS_FOLDER+d+TXT_EXT);
  if (txt_file.is_open()) {
    int x;
    while (txt_file>>x) txt.push_back(x);
    txt_file.close();
  } else {
    cout<<"Could not read text file '"<<TESTS_FOLDER+d+TXT_EXT+"'"<<endl;
    exit(0);
  }
}


inline void update_timers(const struct timeval &t1, const struct timeval &t2, const struct timeval &t3) {
  double s1=t1.tv_sec+(t1.tv_usec/1000000.0);
  double s2=t2.tv_sec+(t2.tv_usec/1000000.0);
  double s3=t3.tv_sec+(t3.tv_usec/1000000.0);
  init_secs=s2-s1;
  check_secs=s3-s2;
  total_init+=init_secs;
  total_chck+=check_secs;
  total_secs+=init_secs+check_secs;
}


//----------------------------------------------------------------
// 
// Binary search
// 
//----------------------------------------------------------------

#ifdef VERBOSE
LL bin_iter_cnt;
#endif

// simple binary seach for an int
bool binary_search(int x, IV &v) {
  int l=0;
  int r=v.size();
  while (l<r) {
    
    #ifdef VERBOSE
    ++bin_iter_cnt;
    #endif
  
    int m=(l+r)>>1;
    if (x<v[m]) r=m;
    else if (x>v[m]) l=m+1;
    else return true;
  }
  return false;
}

int binary_spellcheck(IV &dic, IV &txt) {
  
  #ifdef VERBOSE
  bin_iter_cnt=0;
  #endif
  
  int correct=0;
  struct timeval t1, t2, t3;
  
  // init data structure
  gettimeofday(&t1, NULL);
  sort(dic.begin(), dic.end());
  
  // do spellcheck
  gettimeofday(&t2, NULL);  
  for (int x : txt) if (binary_search(x, dic)) ++correct;
  
  // update timers
  gettimeofday(&t3, NULL);
  update_timers(t1, t2, t3);
  
  #ifdef VERBOSE
  cout<<"\n  Binary search iterations "<<bin_iter_cnt<<"\n\n";
  #endif
  
  return correct;
}


//----------------------------------------------------------------
// 
// AVL search
// 
//----------------------------------------------------------------

int avl_spellcheck(IV &dic, IV &txt) {
  int correct=0;
  struct timeval t1, t2, t3;
  AVL avl;
  
  // init data structure
  gettimeofday(&t1, NULL);
  sort(dic.begin(), dic.end());
  avl.init_sorted(dic);
  
  // do spellcheck
  gettimeofday(&t2, NULL); 
  for (int x : txt) if (avl.find(x)) ++correct;
  
  // update timers
  gettimeofday(&t3, NULL);
  update_timers(t1, t2, t3);
  
  #ifdef VERBOSE
  cout<<"\n  AVL search iterations "<<avl.avl_iter_cnt<<"\n\n";
  #endif
  
  return correct;
}


#ifdef VERBOSE
LL tot_hash_cnt, init_hash_cnt, chck_hash_cnt;
#endif

// run a spellcheck with a particular data structure 'ds'
template<typename T> 
int typed_spellcheck(T &ds, IV &dic, IV &txt) {
  int correct=0;
  struct timeval t1, t2, t3;
  
  // init data structure
  gettimeofday(&t1, NULL);
  for (int x : dic) ds.insert(x);
  
  #ifdef VERBOSE
  init_hash_cnt=ds.hash_cnt;
  #endif
  
  // do spellcheck
  gettimeofday(&t2, NULL); 
  for (int x : txt) if (ds.contains(x)) ++correct;
  
  // update timers
  gettimeofday(&t3, NULL);
  update_timers(t1, t2, t3);
  
  #ifdef VERBOSE
  chck_hash_cnt=ds.hash_cnt-init_hash_cnt;
  tot_hash_cnt=ds.hash_cnt;
  cout<<"\n  Hashes during initialization "<<init_hash_cnt<<"\n";
  cout<<"  Hashes during spellcheck "<<chck_hash_cnt<<"\n";
  cout<<"  Total hashes "<<tot_hash_cnt<<"\n\n";
  #endif
  
  return correct;
}


//----------------------------------------------------------------
// 
// Hash table (open addressing)
// 
//----------------------------------------------------------------

int hash_table_open_addressing_spellcheck(IV &dic, IV &txt) {
  if (hfun==1) {
    OpenAddressingHashTable<Murmur3> ht;
    return typed_spellcheck(ht, dic, txt);
  } else if (hfun==2) {
    OpenAddressingHashTable<FNV1> ht;
    return typed_spellcheck(ht, dic, txt);
  } else if (hfun==3) {
    OpenAddressingHashTable<H3> ht;
    return typed_spellcheck(ht, dic, txt);
  }
  return -1;
}


//----------------------------------------------------------------
// 
// Hash table (separate chaining)
// 
//----------------------------------------------------------------

int hash_table_separate_chaining_spellcheck(IV &dic, IV &txt) {
  if (hfun==1) {
    SeparateChainingHashTable<Murmur3> ht;
    return typed_spellcheck(ht, dic, txt);
  } else if (hfun==2) {
    SeparateChainingHashTable<FNV1> ht;
    return typed_spellcheck(ht, dic, txt);
  } else if (hfun==3) {
    SeparateChainingHashTable<H3> ht;
    return typed_spellcheck(ht, dic, txt);
  }
  return -1;
}



//----------------------------------------------------------------
// 
// Bloom filter
// 
//----------------------------------------------------------------

int bloom_filter_spellcheck(IV &dic, IV &txt) {
  int n=dic.size();
  if (hfun==1) {
    BloomFilter<Murmur3> bf(n?1.0/n:0, n);
    return typed_spellcheck(bf, dic, txt);
  } else if (hfun==2) {
    BloomFilter<FNV1> bf(n?1.0/n:0, n);
    return typed_spellcheck(bf, dic, txt);
  } else if (hfun==3) {
    BloomFilter<H3> bf(n?1.0/n:0, n);
    return typed_spellcheck(bf, dic, txt);
  }
  return -1;
}


//----------------------------------------------------------------
// 
// Spectral Bloom filter
// 
//----------------------------------------------------------------

int spectral_bloom_filter_spellcheck(IV &dic, IV &txt) {
  int n=dic.size();
  if (hfun==1) {
    SpectralBloomFilter<Murmur3> sbf(n?1.0/n:0, n);
    return typed_spellcheck(sbf, dic, txt);
  } else if (hfun==2) {
    SpectralBloomFilter<FNV1> sbf(n?1.0/n:0, n);
    return typed_spellcheck(sbf, dic, txt);
  } else if (hfun==3) {
    SpectralBloomFilter<H3> sbf(n?1.0/n:0, n);
    return typed_spellcheck(sbf, dic, txt);
  }
  return -1;
}


int do_spellcheck(IV &dic, IV &txt) {
  switch (algo) {
    case 1: return binary_spellcheck(dic, txt);
    case 2: return avl_spellcheck(dic, txt);
    case 3: return hash_table_open_addressing_spellcheck(dic, txt);
    case 4: return hash_table_separate_chaining_spellcheck(dic, txt);
    case 5: return bloom_filter_spellcheck(dic, txt);
    case 6: return spectral_bloom_filter_spellcheck(dic, txt);
  }
  return -1;
}

inline void algo_hash_str(string &s) {
  if (algo<3) {
    if (algo==1) s="binary search";
    else if (algo==2) s="AVL tree";
  } else {
    if (algo==3) s="open addressing hash table";
    else if (algo==4) s="separate chaining hash table";
    else if (algo==5) s="Bloom filter";
    else if (algo==6) s="spectral Bloom filter";
    s+=" with ";
    if (hfun==1) s+="Murmur3";
    else if (hfun==2) s+="FNV1";
    else if (hfun==3) s+="H3";
    s+=" hash function";
  }
}


inline void print_test_settings(const string &d, const IV &dic, const IV &txt) {
  cout<<"Starting test: "<<d<<'\n';
  string hs;
  algo_hash_str(hs);
  cout<<"  Using "<<hs<<'\n';
  cout<<"  "<<dic.size()<<" word dictionary\n";
  cout<<"  "<<txt.size()<<" word text file"<<endl;
}

inline void print_test_results(int correct, int total) {
  if (correct==-1) cout<<"  Spell-check failed. Contact the author.\n"; 
  else cout<<"  Correct words in text: "<<correct<<" ("<<100.0*correct/total<<"%)\n"<<endl;
}


void run_one_test(const string &d) {
  IV dic, txt;
  read_dic_txt(d, dic, txt);
  
  print_test_settings(d, dic, txt);
  
  int correct=do_spellcheck(dic, txt);
  
  print_test_results(correct, txt.size());
}

void run_all_tests() {
  cout<<"RUNNING ALL TESTS\n\n";
  
  for (const string &d : dicts) if (texts.count(d)) 
    run_one_test(d);
}



// run all tests with a given algorithm
int main(int argc, char** argv) {
  // esta funcion accelera el cin/cout
  ios_base::sync_with_stdio(0);
  cin.tie(0);
    
  parse_args(argc, argv);
  get_dics_txts();
  
  total_secs=total_init=total_chck=0;
  
  if (test==ALL_OPT) run_all_tests();
  else run_one_test(test);
  
  cout<<"Total time (s): "<<total_secs<<"; init (s): "<<total_init<<"; check (s): "<<total_chck<<"\n\n";
  
  return 0;
}

