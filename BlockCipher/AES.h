#pragma once
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
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

class AEScypher
{
private:
  string FileIn;
  string FileOut;
  string Key;
  string FileVector;
  string salt = "simplesalt";
public:
  AEScypher() = delete;
  AEScypher(const string& FileIn, const string& FileOut, const string& Pass);
  AEScypher(const string& FileIn, const string& FileOut, const string& Pass, const string & iv);
  void encodeAES (AEScypher enc);
  void decodeAES (AEScypher dec);
};