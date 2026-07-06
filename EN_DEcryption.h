#include <shopdb.h>
#include <cstdio>

void encrypt(const string& filename);
void decrypt(const string& filenameEnc);

bool file_check(const string& filename) {
    ifstream f(filename);
    return f.good();
}

char* make_pass()
{
    srand(time(nullptr));

    char* pass = new char[65];
    for (int i{}; i < 64; i++)
    {
        switch (rand()%3)
        {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
            break;
        }
    }
    pass[64] = '\0';
    return pass;
}

void encrypt(const string& filename)
{
    string filename_enc = filename + ".enc";
    char* password = make_pass();
    string command = "OpenSSL-Win64\\bin\\openssl enc -aes-256-cbc -e -in " + filename + " -out " + filename_enc + " -iter 200000 -k ";
    command += password;
    system(command.c_str());

    if (remove(filename.c_str()) != 0)
    {
        cout << "1 [ERR] - deleted file" << endl;
    }

    ofstream file;
    file.open("key.txt", ios::binary);
    file.write(password, 64);
    file.close();

    command = "OpenSSL-Win64\\bin\\openssl.exe pkeyutl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    system(command.c_str());
    if(remove("key.txt") != 0)
    {
        cout << "2 [ERR] - deleted file" << endl;
    }
}

void decrypt(const string& filenameEnc)
{
    string command = "OpenSSL-Win64\\bin\\openssl.exe pkeyutl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    system(command.c_str());
    if (remove("key.txt.enc") != 0)
    {
        cout << "[ERR] - deleted file" << endl;
    }

    char* password = new char[65];
    ifstream file;
    file.open("key.txt", ios::binary);
    file.read(password, 64);
    file.close();
    if (remove("key.txt") != 0)
    {
        cout << "[ERR] - deleted file" << endl;
    }
    string filenameEnc_enc = filenameEnc + ".enc";
    password[64] = '\0';
    command = "OpenSSL-Win64\\bin\\openssl enc -aes-256-cbc -d -in " + filenameEnc_enc + " -out " + filenameEnc + " -iter 200000 -k ";
    command += password;
    system(command.c_str());
    if (remove(filenameEnc_enc.c_str()) != 0)
    {
        cout << "[ERR] - deleted file" << endl;
    }
}
