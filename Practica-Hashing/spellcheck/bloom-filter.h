#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <random>
#include <vector>
#include <cmath>
#include "hash.h"
using namespace std;

typedef long long LL;
typedef vector<bool> BV;
typedef vector<uint> UIV;


// A Bloom filter is a space-efficient probabilistic data structure
// that is used to test whether an element is a member of a set.
// False positive matches are possible, but false negatives are not.
// A query returns either "possibly in set" or "definitely not in set".
// Elements can be added to the set, but not removed
// This implementation works well with ints (or anything the same size)
template <typename H, typename=typename enable_if<is_base_of<Hasher, H>::value, H>::type>
class BloomFilter {

private:
  
  // m is number of bits in the aray
  // n is the number of elements (max capacity)
  // k is number of hash functions
  double fp;
  int n, m, k;
  BV bits;
  vector<H> hashers;
  
  
public:
  
  #ifdef VERBOSE
  LL hash_cnt=0;
  #endif
  
  BloomFilter(double fp, int n) : fp(fp), n(n) {
    const double ln2=log(2);
    m=ceil(-(n*log(fp)/(ln2*ln2)));
    k=ceil(ln2*m/n);
    bits=BV(m, 0);
    hashers=vector<H>(k);
  }
  
  void insert(int value) {
    for (int i=0; i<k; ++i) {
      #ifdef VERBOSE
      ++hash_cnt;
      #endif
      
      uint h=hashers[i].get_hash(value);
      bits[h%m]=1;
    }
  }
  
  bool contains(int value) {
    for (int i=0; i<k; ++i) {
      #ifdef VERBOSE
      ++hash_cnt;
      #endif
      
      uint h=hashers[i].get_hash(value);
      if (!bits[h%m]) return 0;
    }
    return 1;
  }
};


template <typename H, typename=typename enable_if<is_base_of<Hasher, H>::value, H>::type>
class SpectralBloomFilter {

private:
  
  double fp;
  int n, m, k;
  UIV bits;
  vector<H> hashers;
  
  
public:
  
  #ifdef VERBOSE
  LL hash_cnt=0;
  #endif
  
  SpectralBloomFilter(double fp, int n) : fp(fp), n(n) {
    const double ln2=log(2);
    m=ceil(-(n*log(fp)/(ln2*ln2)));
    k=ceil(ln2*m/n);
    bits=UIV(m, 0);
    hashers=vector<H>(k);
  }
  
  void insert(int value) {
    for (int i=0; i<k; ++i) {
      #ifdef VERBOSE
      ++hash_cnt;
      #endif
      
      uint h=hashers[i].get_hash(value);
      ++bits[h%m];
    }
  }
  
  bool contains(int value) {
    for (int i=0; i<k; ++i) {
      #ifdef VERBOSE
      ++hash_cnt;
      #endif
      
      uint h=hashers[i].get_hash(value);
      if (!bits[h%m]) return 0;
    }
    return 1;
  }
  
  // ASSUMES VALUE IS IN THE SET!!!
  void remove(int value) {
    for (int i=0; i<k; ++i) {
      #ifdef VERBOSE
      ++hash_cnt;
      #endif
      
      uint h=hashers[i].get_hash(value);
      --bits[h%m];
    }
  }
  
  // ASSUMES VALUE IS IN THE SET!!!
  uint count(int value) {
    uint c=-1;
    for (int i=0; i<k; ++i) {
      #ifdef VERBOSE
      ++hash_cnt;
      #endif
      
      uint h=hashers[i].get_hash(value);
      c=min(c, bits[h%m]);
    }
    return c;
  }
  
};



#endif
