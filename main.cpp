#include <fstream>
#include <iostream>
#include <vector>
#include "main.h"
#include <algorithm>
using namespace std;

//docs used kek https://ccrma.stanford.edu/~craig/14q/midifile/MidiFileFormat.html
ofstream fout;
void noteInsert(vector<int>& track, int value, int value2, int value3, int value4);
void bitCreator(vector<int> p_vector);
int main() {
    fout.open("test1.mid", ios::binary | ios::out);
    ifstream funimg;
    funimg.open("funy.png", std::ios_base::binary);

    vector<int> Header_chunk = {
        0x4d, 0x54, 0x68, 0x64,
        0x00, 0x00, 0x00, 0x06,
        0x00, 0x01,
        0x00, 0x01, // following tracks
        0x00, 0x80
    };

    vector<int> Track_event_1 = {
        //Sets tempo
        0x00, 0xff,
        0x51,
        0x03,
        0x06, 0x8a, 0x1b,
    };
    //My heart to you <33
    // Source - https://stackoverflow.com/a
    // Posted by Waqar, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-01-15, License - CC BY-SA 4.0

    unsigned char c{};
    funimg >> std::noskipws;
    int  buffer[4];
    int index = 0;
    while (funimg >> c) {
        buffer[index] = (int)c;
        index ++;
        if (index > 3) {
            index = 0;
            noteInsert(Track_event_1, buffer[0], buffer[1], buffer[2], buffer[3]);
        }
    }
    while (index < 3)
    {
        buffer[index] = 50;
        index ++;
    }
    noteInsert(Track_event_1, buffer[0], buffer[1], buffer[2], buffer[3]);
    
    //End of paste
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 53, 50);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 50);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // noteInsert(Track_event_1, 53);
    // Track_event_1.insert(Track_event_1.end(),{
    //     //first key press and relese
    //     0x00, 0x90, 0x3c, 0x40,
    //     0x10, 0x80, 0x3c, 0x40,
    // });
    //end
    Track_event_1.insert(Track_event_1.end(),{
        0x00, 0xff,
        0x2f, 0x00,
    });
    
    //THXX LAD!!
    // Source - https://stackoverflow.com/a
    // Posted by caf, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-01-15, License - CC BY-SA 3.0

    unsigned char bytes[4];
    unsigned long n = Track_event_1.size();

    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
    // END OF PASTED



    vector<int> Track_chunk = {
        0x4d, 0x54, 0x72, 0x6b,
        bytes[0], bytes[1], bytes[2], bytes[3], // sets size the funny way XD
    };
    
    

    bitCreator(Header_chunk);
    bitCreator(Track_chunk);
    bitCreator(Track_event_1);
    fout.close();
    funimg.close();
}
void noteInsert(vector<int>& track, int value, int value2, int value3, int value4){
    track.insert(track.end(),{
        //first key press and relese
        0x00, 0x90, value, value3,
        0x10, 0x80, value, value4,
    });
}

void bitCreator(vector<int> p_vector){
    char* result = new char[p_vector.size()] {};
    for (int i = 0; i < p_vector.size(); i++)
    {
        result[i] = p_vector[i];
    }
    fout.write(result, p_vector.size());
}