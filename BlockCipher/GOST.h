#pragma once
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/gost.h>
#include <cryptopp/base64.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include "cryptopp/modes.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace CryptoPP;

class GOSTcypher
{
private:
  string FileIn;
  string FileOut;
  string FileVector;
  string Key;
  string salt = "simplesalt";
public:
  GOSTcypher() = delete;
  GOSTcypher(const string& FileIn, const string& FileOut, const string& pass);
  GOSTcypher(const string& FileIn, const string& FileOut, const string& pass, const string & iv);
  void encodeGost (GOSTcypher enc);
  void decodeGost (GOSTcypher dec);
};