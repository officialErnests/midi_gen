#include <fstream>
#include <iostream>
#include <vector>
#include "main.h"
#include <algorithm>
using namespace std;

//docs used kek https://ccrma.stanford.edu/~craig/14q/midifile/MidiFileFormat.html
ofstream fout;
void bitCreator(vector<int> p_vector);
int main() {
    fout.open("test.mid", ios::binary | ios::out);

    vector<int> Header = {
        0x4d, 0x54, 0x68, 0x64,
        0x00, 0x00, 0x00, 0x06,
        0x00, 0x01,
        0x00, 0x02,
        0x00, 0x80
    };

    bitCreator(Header);
    fout.close();
}
void bitCreator(vector<int> p_vector){
    char* result = new char[p_vector.size()] {};
    for (int i = 0; i < p_vector.size(); i++)
    {
        result[i] = p_vector[i];
    }
    fout.write(result, p_vector.size());
}