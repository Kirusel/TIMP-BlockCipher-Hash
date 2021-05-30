#include "GOST.h"
GOSTcypher::GOSTcypher(const string& FileIn, const string& FileOut, const string& pass)
{
    this->FileIn = FileIn;
    this->FileOut = FileOut;
    this->Key = pass;
}

GOSTcypher::GOSTcypher(const string& FileIn, const string& FileOut, const string& pass, const string & iv)
{
    this->FileIn = FileIn;
    this->FileOut = FileOut;
    this->Key = pass;
    this->FileVector = iv;
}

void GOSTcypher::encodeGost (GOSTcypher enc)
{
    //Генерируем ключ
    SecByteBlock key(GOST::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA512> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)enc.Key.data(), enc.Key.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    //Генерируем вектор инициализации(IV)
    AutoSeededRandomPool prng;
    byte iv[GOST::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    ofstream v_IV(string(enc.FileOut + ".iv").c_str(), ios::out | ios::binary);
    v_IV.write((char*)iv, GOST::BLOCKSIZE);
    v_IV.close();

    cout << "Vector file was created.\nPath: " << enc.FileOut << ".iv" << endl;

    //Шифрование. 
    CBC_Mode<GOST>::Encryption encr;
    encr.SetKeyWithIV(key, key.size(), iv);
    FileSource fs(enc.FileIn.c_str(), true, new StreamTransformationFilter(encr, new FileSink(enc.FileOut.c_str())));
    cout << "Encrypted file path:\n" << enc.FileOut << endl;
}

void GOSTcypher::decodeGost (GOSTcypher dec)
{
    //Генерируем ключ 
    SecByteBlock key(GOST::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA512> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)dec.Key.data(), Key.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    //Записываем вектор инициализации(IV) 
    byte iv[GOST::BLOCKSIZE];
    ifstream v_IV(dec.FileVector.c_str(), ios::in | ios::binary);
 
    if (v_IV.good()) {
        v_IV.read(reinterpret_cast<char*>(&iv), GOST::BLOCKSIZE);
        v_IV.close();
    } else if (!v_IV.is_open()) {
        throw string ("Error: IV file was not opened");
        v_IV.close();
    } else {
        throw string ("Error: IV file is not true");
        v_IV.close();
    }
    //Расшифрование
    CBC_Mode<GOST>::Decryption decr;
    decr.SetKeyWithIV(key, key.size(), iv);
    FileSource fs(dec.FileIn.c_str(), true, new StreamTransformationFilter(decr, new FileSink(dec.FileOut.c_str())));
    cout << "Decode result path:\n" << dec.FileOut << endl;
}