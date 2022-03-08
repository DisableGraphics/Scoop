#include <cstdint>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <list>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <sstream>
#include <vector>
/*
                                SCOOP - A LANGUAGE DESIGNED AFTER JUST ONE VARIABLE
            - a: The main part of this programming language. An 8-bit unsigned integer with values between (included) 0
            and 255. 'a' is the only variable in the language.

            - Instructions:
                - 'substract': Reduces 'a' by the number following it
                - 'add': Adds the number following it to 'a'
                - 'min': Assigns 0 to 'a'
                - 'max': Assigns 255 to 'a'
                - 'show': Shows the value of 'a' in console
                - 'print': Shows the ASCII value of 'a' in console
                - 'set': Sets 'a' to the number following it
                - 'input': Sets 'a' to the either ASCII value or number in the cin
*/
using namespace std;

inline bool checkCondition(uint8_t &a, string comparator, string comparison){
    try{        
        if(comparator == "<"){ //Esto se ve mu mal, pero weno
            if(stoi(comparison) <= a){
                return false;
            } else {
                return true;
            }
        } else if(comparator == "<="){
            if(stoi(comparator) < a){
                return false;
            }
        } else if(comparator == ">"){
            if(stoi(comparison) >= a){
                return false;
            } else {
                return true;
            }
        } else if(comparator == ">="){
            if(stoi(comparison) > a){
                return false;
            }
        } else if(comparator == "=="){
            if(stoi(comparison) != a){
                return false;
            }
        } else if(comparator == "!="){
            if(stoi(comparison) == a){
                return false;
            }
        } else {
            cout << "Error: No comparation given" << endl;
            return false;
        }
        return true;
    } catch(const std::out_of_range& oor){
        cout << "Error: Number too large" << endl;
        return false;
    } catch(const std::invalid_argument& ia){
        cout << "Error: Incorrect parameters" << endl;
        return false;
    }
}

inline void interpret(uint8_t &a, string input){
    bool continueExecution = true;

    stringstream input_stream(input); //We'll use the input stream. VERY MUCH
    string tmp{""};
    while(!input_stream.eof()){
        input_stream >> tmp;
        if(continueExecution){
            if (tmp == "substract"){ //Substract
                input_stream >> tmp;
                    try{
                    int number = stoi(tmp); //Yes, I know this succs, but it's the easiest one (The most bug-free, lol)
                    a -= number;
                } catch(const std::invalid_argument& ia){
                    a--;
                } catch(const std::out_of_range& oor){
                    cout << "Error: number too large\n";
                }
            } else if (tmp == "add"){ //Add
                input_stream >> tmp;
                try{
                    int number = stoi(tmp);
                    a += number;
                } catch(const std::invalid_argument& ia){
                    a++;
                } catch(const std::out_of_range& oor){
                    cout << "Error: number too large\n";
                }
            } else if (tmp == "min"){ //Set a to 0
                a = 0;
            } else if (tmp == "max"){ //Set a to 255
                a = 255;
            } else if (tmp == "show"){ //Show the value of a
                cout << to_string(a) << endl;
            } else if (tmp == "print"){ //Show the char (represented in the uint8_t) of a
                cout << (char)a;
            } else if (tmp == "printline"){
                cout << (char)a << endl;
            } else if (tmp == "set"){ //Set a to a value. Sets 'a' to 0 if blank
                input_stream >> tmp;
                try{
                    int number = stoi(tmp);
                    a = number;
                } catch(const std::invalid_argument& ia){
                    if(tmp.size() == 1){
                        int number = (int)tmp[0];
                        a = number;
                    } else {
                        a = 0;
                    }
                } catch(const std::out_of_range& oor){
                    cout << "Error: number too large\n";
                }
                
            }
            else if(tmp == "if"){
                input_stream >> tmp;
                string tmp_2;
                input_stream >> tmp_2;

                continueExecution = checkCondition(a,tmp,tmp_2);
                
            }else if (tmp == "random"){
                string tmp_firstarg, tmp_secondarg;

                input_stream >> tmp_firstarg;
                input_stream >> tmp_secondarg;
                try{
                    if(stoi(tmp_firstarg) < stoi(tmp_secondarg)){
                            a = stoi(tmp_firstarg) + (rand()% stoi(tmp_secondarg) - stoi(tmp_firstarg) + 1);
                    } else {
                        cout << "Error: Second limit of range equal or less than the first limit" << endl;
                    }
                } catch(const std::out_of_range& oor){
                    cout << "Error: number too large" << endl;
                } catch(const std::invalid_argument& ia){
                    cout << "Error: Expected two valid arguments" << endl;
                }

            }else if(tmp == "input"){
                try{
                    string tmp_arg;
                    cin >> tmp_arg;
                    a = stoi(tmp_arg);
                    input_stream >> tmp_arg;

                }catch(const std::out_of_range& oor){
                    cout << "Error: number too large" << endl;
                } catch(const std::invalid_argument& ia){
                    cout << "Error: Expected two valid arguments" << endl;
                }
            } else if(tmp == "while"){
                try{
                    input_stream >> tmp;
                    string tmp_2;
                    input_stream >> tmp_2;
                    string instructions{""};
                    string instruction{""};
                    bool space = false;
                    while(input_stream >> instruction){
                        if(space){
                            instructions += " " + instruction;
                        } else {
                            instructions += instruction;
                        }
                        space = true;  
                        if(instruction == "endwhile"){
                            break;
                        } 
                    }
                    while(checkCondition(a, tmp, tmp_2) && !(instructions == "")){
                        interpret(a, instructions);
                    }
                }catch(const std::out_of_range& oor){
                    cout << "Error: number too large" << endl;
                } catch(const std::invalid_argument& ia){
                    cout << "Error: Expected two valid arguments" << endl;
                }
            } else {
                if(!(tmp == "exit" || tmp == "q" || tmp == "quit" || tmp == "endif")){
                    if(tmp != "endwhile"){
                        cout << "Error: command not recognized: " << stoi(tmp) << endl;
                        break;
                    }
                }
            }
        }
        if(tmp == "endif"){
            continueExecution = true;
        }
    }
}