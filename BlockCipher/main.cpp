#include "AES.h"
#include "GOST.h"

int main ()
{
    bool isTrue = true;
    string CypherMode;
    string FileIn, FileOut, FileVector, key;
    cout << " Type:" << endl;
    cout << " EncodeGOST - to cypher with \"GOST\" algorithm" << endl;
    cout << " DecodeGOST - to decode with \"GOST\" algorithm" << endl;	
    cout << " EncodeAES - to cypher with \"AES\" algorithm" << endl;
    cout << " DecodeAES - to decode with \"AES\" algorithm" << endl;
    do {
        cout << "Choose CypherMode: ";
        cin >> CypherMode;
        if (CypherMode == "EncodeGOST") {
            cout << "Type a file path: ";
            cin >> FileIn;
            cout << "Type a result file path: ";
            cin >> FileOut;
            cout << "Type a key: ";
            cin >> key;
            try {
                GOSTcypher enc(FileIn,FileOut,key);
                enc.encodeGost(enc);
            }  catch (const CryptoPP::Exception & ex) {
                cerr << ex.what() << endl;
            }
        }
        if (CypherMode == "EncodeAES") {
            cout << "Type a file path: ";
            cin >> FileIn;
            cout << "Type a result file path: ";
            cin >> FileOut;
            cout << "Type a key: ";
            cin >> key;
            try {
                AEScypher enc(FileIn,FileOut,key);
                enc.encodeAES(enc);
            }  catch (const CryptoPP::Exception & ex) {
                cerr << ex.what() << endl;
            }
        }
        if (CypherMode == "DecodeGOST") {
            cout << "Type a file path: ";
            cin >> FileIn;
            cout << "Type a result file path: ";
            cin >> FileOut;
            cout << "Type a vector init. file path: ";
            cin >> FileVector;
            cout << "Type a key: ";
            cin >> key;
            try {
                GOSTcypher dec(FileIn,FileOut,key,FileVector);
                dec.decodeGost(dec);
            }  catch (const CryptoPP::Exception & ex) {
                cerr << ex.what() << endl;
            } catch (const string & error) {
                cerr << error << endl;
            }
        }
        if (CypherMode == "DecodeAES") {
            cout << "Type a file path: ";
            cin >> FileIn;
            cout << "Type a result file path: ";
            cin >> FileOut;
            cout << "Type a vector init. file path: ";
            cin >> FileVector;
            cout << "Type a key: ";
            cin >> key;
            try {
                AEScypher dec(FileIn, FileOut, key, FileVector );
                dec.decodeAES(dec);
            } catch (const CryptoPP::Exception & ex) {
                cerr << ex.what() << endl;
            } catch (const string & error) {
                cerr << error << endl;
            }
        }
        if (CypherMode == "exit") {
            cout << "Exit." << endl;
            isTrue = false;
            break;
        }
    } while (isTrue != false);

    return 0;
}