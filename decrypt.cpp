#include <fstream>
#include <iostream>
#include <vector>
#include "main.h"
#include <algorithm>
#include <string>
#include <filesystem>
using namespace std;

ofstream fout;
int main() {
    cout << "Enter file to load from (no .mid neccesary):";
    string path_to;
    cin >> path_to;
    path_to += ".mid";
    if (!filesystem::exists(path_to)) {
        cout << "File dosn't exist ;-;";
        return 1;
    }
    
    cout << "Enter file to save to (extension is neccesary):";
    string path_tosave;
    cin >> path_tosave;
    fout.open(path_tosave, ios::binary | ios::out);
    ifstream midi_decrypt;
    midi_decrypt.open(path_to, std::ios_base::binary);
    
    char test[1];
    unsigned char c{};
    midi_decrypt >> std::noskipws;
    int index = 0;

    int track_num;

    while (midi_decrypt >> c) {
        test[0] = (int)c;
        if (index == 11) {
            track_num = (int)c;
        }
        index ++;
    }
    fout.close();
    midi_decrypt.close();
}