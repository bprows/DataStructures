#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

// Global Variables
set<string> s;
vector<string> v;
map<string, string> wordmap;
map<string, vector<string>> wordmap2;
const int M = 2; // want 2 words for context

void splitHyphenSet(string str, set<string> &s) { 
    string word = ""; 
    for (int i = 0; i < str.length(); i++) { 
        if (str.at(i) == '-') { 
            if (word != "") {
                s.insert(word);
            }
            word = ""; 
        } 
        else { 
            word = word.append(1, tolower(str.at(i))); 
        } 
    }  
    if (word != "") {
        s.insert(word);   
    }
} 

void populate_set(string file) {
    string to_read;
    string word;
    ifstream ifs;
    
    to_read = file + ".txt";
    ifs.open(to_read);
    
    cout << "Reading from " << to_read << "." << endl;
    
    // FIXME how to split the double hyphens ??? 
    
    while (ifs >> word) {
    
        if (isalpha(word.at(0))) {
            if (!isalpha(word.at(word.length() - 1))) {
                word = word.erase(word.length() - 1);   
            }
            
            splitHyphenSet(word, s);
        
        }
    }
    
    cout << "Finished reading from " << to_read << "." << endl;

}

void print_set_to_file(string file, set<string> s) {
    ofstream ofs;
    string output_file;
    output_file = file + "_set.txt";
    
    cout << "Opening " << output_file << "." << endl;
    ofs.open(output_file);
    
    for (set<string>::iterator it = s.begin(); it != s.end(); it++) {
        ofs << *it << endl;
    }
    
    ofs.close();
    cout << "Closing " << output_file << "." << endl;
}

void splitHyphenVec(string str, vector<string> &v) { 
    string word = ""; 
    for (int i = 0; i < str.length(); i++) { 
        if (str.at(i) == '-') { 
            if (word != "") {
                v.push_back(word);
            }
            word = ""; 
        } 
        else { 
            word = word.append(1, tolower(str.at(i))); 
        } 
    }  
    if (word != "") {
        v.push_back(word);   
    }
} 


void populate_vector(string file) {
    string to_read;
    string word;
    ifstream ifs;
    
    to_read = file + ".txt";
    ifs.open(to_read);
    
    cout << "Reading from " << to_read << "." << endl;
    
    // FIXME how to split the double hyphens ??? 
    
    while (ifs >> word) {
    
        if (isalpha(word.at(0))) {
            if (!isalpha(word.at(word.length() - 1))) {
                word = word.erase(word.length() - 1);   
            }
            
            splitHyphenVec(word, v);
        
        }
    }
    
    cout << "Finished reading from " << to_read << "." << endl;

}

void print_vec_to_file(string file, vector<string> v) {
    ofstream ofs;
    string output_file;
    output_file = file + "_vector.txt";
    
    cout << "Opening " << output_file << "." << endl;
    ofs.open(output_file);
    
    for (vector<string>::iterator it = v.begin(); it != v.end(); it++) {
        ofs << *it << endl;
    }
    
    ofs.close();
    cout << "Closing " << output_file << "." << endl;
    
}

void generateMap1(map<string, string> &wordmap,
                  vector<string> v) {
    string last="";
    for (vector<string>::iterator it=v.begin(); it!=v.end(); it++) {
        wordmap[last]=*it;
        last = *it;
    }
}

void printMap1(string file, map<string, string> wordmap) {
    ofstream ofs;
    string output_file;
    output_file = file + "_1_1.txt";
    
    cout << "Opening " << output_file << "." << endl;
    ofs.open(output_file);
    
    for (map<string, string>::iterator it = wordmap.begin(); it != wordmap.end(); it++) {
        ofs << it->first << ", " << it->second << endl;
    }
    
    ofs.close();
    cout << "Closing " << output_file << "." << endl;
    
}

void firstText(map<string, string> m) {
    string state = "";
    for(int i = 0; i < 100; i++){
        cout << wordmap[state] << " ";
        state = wordmap[state];
    }   
    cout << endl;
}

void generateMap2(map<string, vector<string>> &wordmap2,
                  vector<string> v) {
    string state = "";
    for(vector<string>::iterator it = v.begin(); it !=v.end(); it++) {
        wordmap2[state].push_back(*it);
        state = *it;
    }
}

void generateSermon1(map<string, vector<string>> m) {
    srand(time(NULL)); // this line initializes the random number generated
                   // so you dont get the same thing every time
    string state = "";
    for (int i = 0; i < 100; i++) {
        int ind = rand() % m[state].size();
        cout << m[state][ind] << " ";
        state = m[state][ind];
    }
    cout << endl;
}

map<list<string>, vector<string>> generatePhraseMap(vector<string> v) {
    map<list<string>, vector<string>> wordmap3;
    list<string> state;
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }

    for (vector<string>::iterator it=v.begin(); it!=v.end(); it++) {
        wordmap3[state].push_back(*it);
        state.push_back(*it);
        state.pop_front();
    }
    return wordmap3;
}

void generateSermon2(map<list<string>, vector<string>> m) {
    list<string> state;
    state.clear();
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
    for (int i = 0; i < 100; i++) {
        int ind = rand() % m[state].size();
        cout << m[state][ind] << " ";
        state.push_back(m[state][ind]);
        state.pop_front();
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "not enough arguments." << endl;
        return 0;
    }
    
    string inputFile;
    inputFile = argv[1];
    
    // set
    populate_set(inputFile);
    cout << "s was populated and has " << s.size() << " elements." << endl;
    
    cout << "Outputting contents of set to " << inputFile << "_set.txt" << endl;
    print_set_to_file(inputFile, s);
    
    // vector
    populate_vector(inputFile);
    cout << "v was populated and has " << v.size() << " elements." << endl;
    
    cout << "Outputting contents of vector v to " << inputFile << "_vector.txt" << endl;
    print_vec_to_file(inputFile, v);

    generateMap1(wordmap, v);
    cout << "Outputting map to " << inputFile << "_1_1.txt" << endl;
    printMap1(inputFile, wordmap);
    
    cout << endl << "Printing the results of the first map" << endl;
    firstText(wordmap);
    
    generateMap2(wordmap2, v);
    
    
    map<string, vector<string>>::iterator iter = wordmap2.begin();
    advance(iter, 5);
    cout << endl << "Printing all the words that come after the 6th element: " << endl;
    for (int i = 0; i < iter->second.size(); i++) { 
        cout << iter->second.at(i) << " ";
    }
    cout << endl;
    
    cout << "The first sermon: " << endl;
    generateSermon1(wordmap2);
     
    cout << endl;
    
    cout << "Creating a map with 2 words as context." << endl;
    map<list<string>, vector<string>> wordmap3;
    wordmap3 = generatePhraseMap(v);
    
    cout << "Writing a sermon for you." << endl;
    generateSermon2(wordmap3);
    
    cout << endl;
    
    
    return 0;
}