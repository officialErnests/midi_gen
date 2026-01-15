#include <fstream>
#include <iostream>
#include "main.h"

using namespace std;

//docs used kek https://ccrma.stanford.edu/~craig/14q/midifile/MidiFileFormat.html
int main() {
    ofstream fout;
    fout.open("test.mid", ios::binary | ios::out);

    //Might as well be MThd but idc more fun >:))
    char header[4] = {0x4D,0x54,0x68,0x64};
    fout.write(header, sizeof(header));
    
    //Used for setting how big is the header
    //If i understood docs corectly dosn't even change XD
    char header_size[4] = {0x00,0x00,0x00,0x06};
    fout.write(header_size, sizeof(header_size));

    //Formating the midi
    // 0 = single track file format
    // 1 = multiple track file format
    // 2 = multiple song file format 
    // prob will stick to 1 since funni :DD
    char format_midi[4] = {0x00,0x01};
    fout.write(format_midi, sizeof(format_midi));

    //The tracks that follow
    char isntrument_amount[4] = {0x00,0x01};
    fout.write(isntrument_amount, sizeof(isntrument_amount));

    //Division aka the speed.. i tink?
    //Also just setting to whatever the lmms exported with ;PP
    char weird_tempo[4] = {0x00,0x80};
    fout.write(weird_tempo, sizeof(weird_tempo));

    trackChunkCreate(fout, weird_tempo);

    fout.close();
}
void trackChunkCreate(std::ofstream &fout, char weird_tempo[4])
{
    //jjust some testing
    char weird_tempo[4] = {0xFF, 0x00, 0x00, 0x43};
    fout.write(weird_tempo, sizeof(weird_tempo));
}