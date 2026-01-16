#include <fstream>
#include <iostream>
#include <vector>
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

    vector<vector<uint8_t>> tracks;
    vector<uint8_t> track;
    vector<uint8_t> whole;
    vector<int> entry_points;
    vector<int> exit_points;
    while (midi_decrypt >> c) {

        whole.push_back(c);
        if (index == 11) {
            track_num = (int)c;
        }
        if (index > 11) {
            if (whole[index-3] == 0x4d && whole[index-2] == 0x54 && whole[index-1] == 0x72 && whole[index] == 0x6b) {
                cout << "\nEntry:"<< index;
                entry_points.push_back(index + 1);
            }
            if (whole[index-3] == 0x00 && whole[index-2] == 0xff && whole[index-1] == 0x2f && whole[index] == 0x00) {
                cout << "\nExit:"<< index;
                exit_points.push_back(index);
            }
        }
        index ++;
    }
    
    // for (int i = 0; i < entry_points.size(); i++)
    // {
    //     char tempo[1];
    //     index = 13;
    //     while (entry_points[i] + index + 1 < exit_points[i])
    //     {
    //         tempo[0] = whole[entry_points[i] + index];
    //         fout.write(tempo, 1);
    //         tempo[0] = whole[entry_points[i] + index + 1];
    //         fout.write(tempo, 1);
    //         index += 4;
    //     }
    // }
    
    
    char tempo[1];
    index = 13;
    int size_v = entry_points.size();
    while (index + entry_points[0] + 1 < exit_points[0])
    {
        for (int i = 0; i < size_v; i++)
        {
            if (entry_points[i] + index + 1 >= exit_points[i]) {
                cout << i << " - SKIP\n";
                continue;
            }
            tempo[0] = whole[entry_points[i] + index];
            fout.write(tempo, 1);
            tempo[0] = whole[entry_points[i] + index + 1];
            fout.write(tempo, 1);
        }
        index += 4;
        // cout << index << "/" << exit_points[0] << "\n";
    }
    

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