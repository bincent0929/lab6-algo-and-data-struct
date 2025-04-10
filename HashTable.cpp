// CSCI 311 - Spring 2025
// Lab 6 - Hash Table cpp
// Author: Vincent Roberson

#include <iostream>
#include <math.h>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
  size = 11;
  p = 31;
  numElements = 0;
  table.resize(size);
  // one of the constants for polynomial rolling hash should be 31
}

HashTable::HashTable(int s, int mult){
  size = s;
  p = mult;
  numElements = 0;
  table.resize(size);
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
      return hashedIndex;
      //std::cout << s << std::endl;
    }
  }
  return -1;
}

void HashTable::insert(std::string s){
  int hashedIndex = hash(s);
  table[hashedIndex].push_back(s);
  //std::cout << table[hashedIndex][0] << std::endl;
  /**
   * Apparently this adds the value in a chain at the index that was
   * hashed. So THERE ARE COLLISIONS.
   */
  numElements++;
}

void HashTable::remove(std::string s){
  int hashedIndex = hash(s);
  for (int i = 0; i < table[hashedIndex].size(); i++) {
    if (table[hashedIndex][i] == s) {
      table[hashedIndex].erase(table[hashedIndex].begin() + i);
      numElements--;
      return;
      // supposedly this removes the first occurence of the string
    }
  }
}

void HashTable::resize(int s){
  auto oldSizedTable = move(table); // saves the table's values to a new vector
  table.resize(s); // clears and resizes the vector
  size = s; // updates the size in the object

  if (numElements == 0) {
    return;
  }

  numElements = 0;
  // ^ important to update before because hashing uses
  // the size variable to calculate index
  for (int i = 0; i < oldSizedTable.size(); i++) {
    for (int j = 0; j < oldSizedTable[i].size(); j++) {
      insert(oldSizedTable[i][j]);
    }
  }
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
  unsigned int cumSum = 0;
  int index;

  for (int i = 0; i < s.length(); i++) {
    /*
    int exponentiatedV = 1;
    for (int j = 0; j < i; j++) {
      exponentiatedV *= p;
    }

    cumSum += static_cast<int>(s[i]) * exponentiatedV;
    */
    cumSum += static_cast<int>(s[i]) * pow(p, i);
  }

  //std::cout << "cumulative sum calculated" << std::endl;
  //std::cout << cumSum << std::endl;

  // might need to check for overflow error
  // due to unsigned -> signed conversion
  index = cumSum % size;
  //std::cout << "index calculated" << std::endl;
  //std::cout << index << std::endl;

  return index;
}