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
    char buffer[2];
    int track_cycle = 0;
    int buffer_index = 0;
    int tracker = 0;
    char holder[1];
    int temp_inc = 0;
    while (midi_decrypt >> c) {
        holder[1] = c;
        buffer[buffer_index] = (int)c;
        if (index == 11) {
            track_num = (int)c;
        } 
        tracker -= 1;

        switch (tracker)
        {
        case 6:
        case 5:
            fout.write(holder, 1);
        case 4:
        case 3:
            break;
        case 1:
        case 0:
            fout.write(holder, 1);
        default:
            break;
        }

        if (buffer_index == 1) {
            cout << (int)buffer[buffer_index] << " " << (int)(-111+ track_cycle) << "\n";
            if ((int)buffer[buffer_index] == (int)(-111+ track_cycle)) {
                tracker = 7;
                cout << "YESS";
                track_cycle = (track_cycle+1)%track_num;
            } else {
                buffer_index = 0;
            }
        } else 
        if (buffer[buffer_index] == 0) {
            buffer_index ++;
        }
        index ++;
    }
    fout.close();
    midi_decrypt.close();
}