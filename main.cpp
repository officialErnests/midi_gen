#include <fstream>
#include <iostream>
#include <vector>
#include "main.h"
#include <algorithm>
#include <string>
#include <filesystem>
using namespace std;

//docs used kek https://ccrma.stanford.edu/~craig/14q/midifile/MidiFileFormat.html
ofstream fout;
void noteInsert(vector<int>& track, int value, int value2, int value3, int value4, int i);
void bitCreator(vector<int> p_vector);
int main() {
    string path;
    cout << "Hello to noob.encrypt ;DD\nPlease select file name to save to (no .mid neccesary):";
    cin >> path;
    path += ".mid";
    string path_load;
    cout << "Pleas name file to load from (including extension):";
    cin >> path_load;
    fout.open(path, ios::binary | ios::out);
    ifstream funimg;
    funimg.open(path_load, std::ios_base::binary);

    
    int track_num;
    cout << "number of tracks ;PP\n(atm only supported max 15.. i think?)";
    cin >> track_num;
    track_num = clamp(track_num, 1, 15);
    int track_cycle = 0;
    vector<vector<int>> Track_events;

    vector<int> Header_chunk = {
        0x4d, 0x54, 0x68, 0x64,
        0x00, 0x00, 0x00, 0x06,
        0x00, 0x01,
        0x00, track_num, // following tracks
        0x00, 0x80
    };
    for (int i = 0; i < track_num; i++){
        vector<int> temp;
        temp.insert(temp.end(), {
            //Sets tempo
            0x00, 0xff,
            0x51,
            0x03,
            0x06, 0x8a, 0x1b,
        });
        Track_events.push_back(temp);
    }
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
            noteInsert(Track_events[track_cycle], buffer[0], buffer[1], buffer[2], buffer[3], track_cycle);
            track_cycle = (track_cycle+1)%track_num;
        }
    }
    while (index < 3)
    {
        buffer[index] = 50;
        index ++;
    }
    noteInsert(Track_events[track_cycle], buffer[0], buffer[1], buffer[2], buffer[3], track_cycle);

    vector<vector<int>> track_chunks;
    for (int i = 0; i < track_num; i++)
    {
        Track_events[i].insert(Track_events[i].end(),{
            0x00, 0xff,
            0x2f, 0x00,
        });
        //THXX LAD!!
        // Source - https://stackoverflow.com/a
        // Posted by caf, modified by community. See post 'Timeline' for change history
        // Retrieved 2026-01-15, License - CC BY-SA 3.0
    
        unsigned char bytes[4];
        unsigned long n = Track_events[i].size();
    
        bytes[0] = (n >> 24) & 0xFF;
        bytes[1] = (n >> 16) & 0xFF;
        bytes[2] = (n >> 8) & 0xFF;
        bytes[3] = n & 0xFF;
        // END OF PASTED
        vector<int> track_chunk = {
            0x4d, 0x54, 0x72, 0x6b,
            bytes[0], bytes[1], bytes[2], bytes[3], // sets size the funny way XD
        };
        track_chunks.push_back(track_chunk);
    }
    
    bitCreator(Header_chunk);
    for (int i = 0; i < track_num; i++)
    {
        bitCreator(track_chunks[i]);
        bitCreator(Track_events[i]);
    }
    fout.close();
    funimg.close();
}
void noteInsert(vector<int>& track, int value, int value2, int value3, int value4, int i){

    track.insert(track.end(),{
        //first key press and relese
        0x00, 144 + i, value, value2,
        0x10, 128 + i, value3, value4,
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