#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main ()
{
    
    CryptoPP::SHA256 hash; // создание хэш-объекта

    cout <<"Algorithm: " << hash.AlgorithmName() << endl; // Имя алгоритма
    cout << "Diget size:" << hash.DigestSize() << endl; //размер хэша
    cout << "Block size:" << hash.BlockSize() << endl; // размер внутреннего Блока
    fstream file;
    string path = "/home/osboxes/Рабочий стол/hash/hash.txt"; // Путь до файла
    string StringLine, FileContent;
    file.open(path);
    if(!file.is_open()) {
        cout << "Error: file isn't open" << endl;
        return 1;
    }
    while(true) {
        getline(file,StringLine);
        if (file.fail()) 
            break;
        FileContent += StringLine;
    }
    cout << "File content: " << FileContent << endl; // содержимое файла

    vector<CryptoPP::byte> digest (hash.DigestSize());

    hash.Update(reinterpret_cast<const CryptoPP::byte*>(FileContent.data()),FileContent.size()); // формируем хэш
    hash.Final(digest.data()); // получаем хэш

    cout << "HASH in HEX format: ";
    CryptoPP::StringSource(digest.data(),digest.size(),true, new  CryptoPP::HexEncoder(new  CryptoPP::FileSink(cout))); // выводим хэш в формате "hex"
    cout << endl;
    return 0;
}