#include <fstream>
#include <iostream>
#include <vector>
#include "main.h"
#include <algorithm>
#include <string>
#include <filesystem>
using namespace std;
void bitCreator(vector<int> p_vector);
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
    vector<vector<int>> bufferer = {};
    vector<int> bufferer_er = {};
    //Vector buffer  pushed onto buffer
    int data_size = 0;
    while (midi_decrypt >> c) {
        holder[0] = c;
        buffer[buffer_index] = (int)c;
        if (index == 11) {
            track_num = (int)c;
        } 
        tracker -= 1;

        switch (tracker)
        {
        case 6:
        case 5:
            data_size ++;
            bufferer_er.push_back(holder[0]);
            break;
        case 4:
        case 3:
        break;
        case 2:
        case 1:
            data_size ++;
            bufferer_er.push_back(holder[0]);
            break;
        default:
            break;
        }

        if (buffer_index == 1) {
            if ((int)buffer[buffer_index] == (int)(-112+ track_cycle)) {
                tracker = 7;
            } else if ((int)buffer[buffer_index] == (int)(-112+ track_cycle+1))
            {
                tracker = 7;
                track_cycle ++;
                bufferer.push_back(bufferer_er);
                // bufferer_er.clear();
                /* code */
            } else 
            {
                buffer_index = 0;
            }
        } else 
        if (buffer[buffer_index] == 0) {
            buffer_index ++;
        }
        index ++;
    }
    bufferer.push_back(bufferer_er);
    // cout << index;
    // for (auto a : bufferer) {
    //     for (auto b : a)
    //     {
    //         cout << b << " ";
    //     }
    //     cout << "a";
    // }
    bool returner = false;
    int ind = 0;
    char tempo[1];
    while (!returner)
    {
        returner = true;
        for (auto b : bufferer) {
            if (b.size() > ind) {
                tempo[0] = (int)b[ind];
                returner = false;
                fout.write(tempo, 1);
            }
        }
        ind ++;
    }
    
    // track_cycle = 0;
    // int track_indexer = 0;
    // char quick_one[1] = {0};
    // for (int i = 0; i < data_size; i++)
    // {
    // // cout<< track_cycle << " " << track_indexer << "\n";
    // // cout << data_size << " " << i << "\n";
    // if (bufferer[track_cycle].size() > track_indexer){
    //     cout << "NOPE";
    //     quick_one[1] = (int)bufferer[track_cycle][track_indexer];
    // }
    // fout.write(quick_one, 1);
    // track_cycle ++;
    // if (track_cycle >= track_num ) {
    //         cout<<"B";
    //         track_cycle = 0;
    //         track_indexer ++;
    //     }
    // }
    

    fout.close();
    midi_decrypt.close();
}

void bitCreator(vector<int> p_vector){
    char* result = new char[p_vector.size()] {};
    for (int i = 0; i < p_vector.size(); i++)
    {
        result[i] = p_vector[i];
    }
    (result, p_vector.size());
}