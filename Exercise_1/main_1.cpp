#include <string>
#include <locale>
#include <iostream>
#include <fstream>
using namespace std;

int vowels_counter(istream& words, bool file){
    const string vowels = "aeiouy";
    string user_input;
    int vowels_count = 0;
    int not_vowels = 0;
    int others = 0;
    while( words >> user_input){
        size_t found = vowels.find(tolower(user_input[0]));
        if (!file && user_input == "q"){
            break;
        }else if (found!=string::npos){
            vowels_count++;
        }else if(isalpha(user_input[0])){
            not_vowels++;
        }else {
            others++;
        }
    }
    cout << "Vowels count: " << vowels_count << endl;
    cout << "Not vowels: " << not_vowels << endl;
    cout << "Others: "<< others << endl;
    return 0;
}

int read_from_file(string& file){
    ifstream open_file(file);
    if (!open_file){
        cout << "File do not exists"<< endl;
        return EXIT_FAILURE;
    }
    return vowels_counter(open_file, true);
}

int main(int args, char **argv){
   if (args == 1) {
       cout << "Enter laters (q to exit): ";
       return vowels_counter(cin, false);
   }else if (args == 2){
       return read_from_file(reinterpret_cast<string &>(argv[1]));
   }
   return EXIT_FAILURE;
}
