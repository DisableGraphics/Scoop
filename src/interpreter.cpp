#include "scoopstd.hpp"

using namespace std;

int main(void){
    cout << "Scoop: The language with only one variable" << endl; //MOTD
    string input{""};
    //The only variable. Can be modified and accesed (not directly, but whatever)
    uint8_t a{0};

    while(input != "q" && input != "exit" && input != "quit"){
        cout << ">>> ";
        getline(cin, input);
        interpret(a, input);
    }
}