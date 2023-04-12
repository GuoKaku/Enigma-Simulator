
#include <iostream>
#include "Enigma.h"

using namespace std;


int main()
{
    string wire1="EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    string wire2="AJDKSIRUXBLHWTMCQGZNPYFVOE";
    string wire3="BDFHJLCPRTXVZNYEIWGAKMUSQO";
    string wire_reflex="YRUHQSLDPXNGOKMIEBFZCWVJAT";
    Rotor rotor1(wire1,'Q');
    Rotor rotor2(wire2,'E');
    Rotor rotor3(wire3,'V');
    Reflexor reflexor(wire_reflex);
    string initial_state="AAA";
    string ring_setting="DES";


    string str1="ELCONWDIAPKSZHFBQTJYRGVXMU";
    string str2="MRWJFDVSQEXUCONHBIPLTGAYZK";
    string str3="WADFRPOLNTVCHMYBJQIGEUSKZX";

    vector<int> vec1=FindCircle(str1.c_str());
    vector<int> vec2=FindCircle(str2.c_str());
    vector<int> vec3=FindCircle(str3.c_str());
    CircleCondition given_condition(vec1,vec2,vec3);

    Enigma enigma(rotor2,rotor3,rotor1,reflexor,initial_state,ring_setting);
    Enigma enigma_3(rotor2,rotor3,rotor1,reflexor,initial_state,ring_setting);

    /*for(int i=0;i<30;i++)
    {
        cout<<enigma.getState()<<endl;
        enigma.GetOutput(0);
    }*/

    string str(225,'W');
    cout<<"明文:"<<str<<endl;
    cout<<"密文:"<<enigma.Encrypt(str)<<endl;

    for(char ch1='A';ch1<='Z';ch1++)
        for(char ch2='A';ch2<='Z';ch2++)
            for(char ch3='A';ch3<='Z';ch3++)
            {
                enigma.setState(ch1,ch2,ch3);
                enigma_3.setState(ch1,ch2,ch3);
                enigma.NextState();
                enigma_3.NextState();
                enigma_3.GotoNextNState(3);

                
                char table1[26];
                char table2[26];
                char table3[26];

                for(char ch='A';ch<='Z';ch++)
                {
                    int a4=enigma_3.GetOutputWithoutRotate(enigma.GetOutputWithoutRotate(ch-'A'));
                    table1[ch-'A']=(char)(a4+'A');
                }
                vector<int> v1=FindCircle(table1);
                if(!given_condition.CompareComponent(v1,1)) continue;


                enigma.NextState();enigma_3.NextState();
                for(char ch='A';ch<='Z';ch++)
                {
                    int a5=enigma_3.GetOutputWithoutRotate(enigma.GetOutputWithoutRotate(ch-'A'));
                    table2[ch-'A']=(char)(a5+'A');
                }
                vector<int> v2=FindCircle(table2);
                if(!given_condition.CompareComponent(v2,2)) continue;


                enigma.NextState();enigma_3.NextState();
                for(char ch='A';ch<='Z';ch++)
                {
                    int a6=enigma_3.GetOutputWithoutRotate(enigma.GetOutputWithoutRotate(ch-'A'));
                    table3[ch-'A']=(char)(a6+'A');
                }
                vector<int> v3=FindCircle(table3);
                if(!given_condition.CompareComponent(v3,3)) continue;

                string state;
                state+=ch1;state+=ch2;state+=ch3;
                cout<<state<<endl;

            }
            
    return 0;
};

