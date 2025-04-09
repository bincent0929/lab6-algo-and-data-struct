// CSCI 311 - Spring 2025
// Lab 6 - Hash Table cpp
// Author: Vincent Roberson

#include <iostream>
#include <math.h>
#include "HashTable.h"

HashTable::HashTable(){
  size = 11;
  p = 11;
  // one of the constants for polynomial rolling hash should be 31
}

HashTable::HashTable(int s, int mult){
  size = s;
  p = mult;
  // one of the constants for polynomial rolling hash should be 31
}

int HashTable::getSize(){ return size; }
int HashTable::getNumElements(){ return numElements; }
int HashTable::getP(){ return p; }

void HashTable::printTable(){
  std::cout << "HASH TABLE CONTENTS" << std::endl;
  for (int i = 0; i < table.size(); i++){
    if (table[i].size() > 0){
      std::cout << i << ": ";
      for (int j = 0; j < table[i].size()-1; j++){
        std::cout << table[i][j] << ", ";
      }
      std::cout << table[i][table[i].size()-1] << std::endl;
    }
  }
}

int HashTable::search(std::string s){
  int hashedIndex = hash(s);
  for (int i = 0; i < table[hashedIndex].size(); i++) {
    if (table[hashedIndex][i] == s) {
      return i;
    }
    else break;
  }
  return -1;
}

void HashTable::insert(std::string s){
  int hashedIndex = hash(s);
  table[hashedIndex].push_back(s);
  /**
   * Apparently this adds the value in a chain at the index that was
   * hashed. So THERE ARE COLLISIONS.
   */
  numElements++;
}

void HashTable::remove(std::string s){
}

void HashTable::resize(int s){
}

/**
 * @return returns the hash of the value to be used as its index
 * please use a unsigned int variable to hold the cumulative sum
 * of the individual hash results of the chars in the string, and 
 * return the sum modulus the size of the table in the end as an int.
 * The above is required because of using the ASCII values and them
 * returning bit values
 */
int HashTable::hash(std::string s){
  uint32_t cumSum;
  int finalSum;
  for (int i = 0; i < s.length(); i++) {
    cumSum += static_cast<int>(s[i]) * pow(p, i);
  }

  // might need to check for overflow error
  // due to unsigned -> signed conversion
  finalSum = cumSum % s.length();

  return finalSum;
}