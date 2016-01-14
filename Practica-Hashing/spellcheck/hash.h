#ifndef HASH_H
#define HASH_H

#include <random>
#include <limits>
#include <vector>
using namespace std;

typedef vector<uint> UIV;
typedef vector<UIV> IM;


// clase abstracta de la que heredaran nuestros hashers
class Hasher {
public:  
  virtual uint get_hash(int data) const=0;
};


// H3 hasher for simple types
class H3 : public Hasher {

private:
  
  static size_t const bits_per_byte=numeric_limits<unsigned char>::digits;
  constexpr static size_t byte_range=numeric_limits<unsigned char>::max()+1U;
  
  IM bytes;
  size_t siz;
  
  
public:
  
  // constructor
  // only simple types: do not use too large a size!!!
  H3(uint seed=rand()) {
    siz=sizeof(int);  // n = sizeof(objects_to_hash)
    minstd_rand0 prng(seed);
    uint bits[siz*bits_per_byte];
    for (uint bit=0; bit<siz*bits_per_byte; ++bit) {
      bits[bit]=0;
      for (uint i=0; i<sizeof(int)/2; ++i)
        bits[bit]=(bits[bit]<<16)|(prng()&0xFFFF);
    }
    bytes=IM(siz, UIV(byte_range));
    for (uint byte=0; byte<siz; ++byte) for (uint val=0; val<byte_range; ++val) {
      bytes[byte][val]=0;
      for (uint bit=0; bit<bits_per_byte; ++bit) if (val&(1U<<bit))
        bytes[byte][val]^=bits[byte*bits_per_byte+bit];
    }
  }
  
  // hash an obect
  uint get_hash(int data) const {
    int offset=0;
    auto *p=static_cast<unsigned char const*>((void const*)&data);
    uint result=0;
    // Duff's Device.
    uint n=(siz+3)/4;
    switch (siz%4) {
      case 0: do { result^=bytes[offset++][*p++];
      case 3:      result^=bytes[offset++][*p++];
      case 2:      result^=bytes[offset++][*p++];
      case 1:      result^=bytes[offset++][*p++];
              } while (--n>0);
    }
    return result;
  }
  
};




// Fowler–Noll–Vo hash function for int type
class FNV1 : public Hasher {
  
private:
  
  uint fnv_prime;
  uint fnv_offset_basis;
  
public:
  
  FNV1() {
    static uint index=0;
    static const uint prim[]={104395069, 103660133,
      102919889, 102183511, 101447123, 100710977,
      99972791, 99236399, 98498003, 97761161,
      97025821, 96291841, 95554541, 94822691,
      94087991, 93354307, 92619853, 91885789,
      91152661, 90419179, 89687243, 88952401, 
      88221223, 87491093, 86758523, 86028157};
    fnv_prime=prim[index];
    ++index%=26;
    fnv_offset_basis=2166136261U;
  }
  
  uint get_hash(int x) const {
    uint h=fnv_offset_basis;      // hash = FNV_offset_basis
    auto *p=static_cast<unsigned char const*>((void const*)&x);
    for (uint i=0; i<4; ++i) {    // for each byte_of_data to be hashed
      h*=fnv_prime;               // hash = hash × FNV_prime
      h^=*p++;                    // hash = hash XOR byte_of_data
    }
    return h;                     // return hash
  }
  
};


// Basado en http://code.google.com/p/smhasher/source/browse/trunk/MurmurHash3.cpp
#define ROTL(x, n) (((x)<<(n))|((x)>>(32-(n))))
class Murmur3 : public Hasher {
  
private:
  
  uint mseed;
  
  
public:
  
  Murmur3(uint seed=rand()) {
    mseed=seed;
  }
  
  uint get_hash(int x) const {
    uint h=mseed;
    
    const uint c1=0xcc9e2d51;
    const uint c2=0x1b873593;
    
    uint k=x;
    k*=c1;
    k=ROTL(k, 15);
    k*=c2;
    
    h^=k;
    h=ROTL(h, 13); 
    h=h*5+0xe6546b64;
    
    h^=1U;
    //h=fmix(h);
    h^=h>>16;
    h*=0x85ebca6b;
    h^=h>>13;
    h*=0xc2b2ae35;
    h^=h>>16;
    
    return h;
  }
  
  // Murmur2
  // uint get_hash(int x) const {
  //   const uint m=0x5bd1e995;
  //   const int r=24;
  //   
  //   uint h=mseed;
  //   
  //   //mmix(h, k);
  //   uint k=x;
  //   k*=m; k^=k>>r; k*=m; h*=m; h^=k;
  //   
  //   //mmix(h, 0U);
  //   k=0U;
  //   k*=m; k^=k>>r; k*=m; h*=m; h^=k;
  //  
  //   //mmix(h, 1U);
  //   k=1U;
  //   k*=m; k^=k>>r; k*=m; h*=m; h^=k;
  //   
  //   h^=h>>13;
  //   h*=m;
  //   h^=h>>15;
  //   
  //   return h;
  // }
};


#endif
