#include "Enigma.h"

using namespace std;


bool FitCircle(Enigma* enigmas,vector<int> circle,char ch)
{
    int ch0=ch-'A';
    for(int i=0;i<circle.size();i++)
    {
        ch0=enigmas[circle[i]].GetOutputWithoutRotate(ch0);
    }
    return ch0==(ch-'A');
}

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

    Enigma enigmas[18];
    for(int i=0;i<=17;i++)
    {
        enigmas[i]=Enigma(rotor2,rotor3,rotor1,reflexor,initial_state,ring_setting);
        enigmas[i].GotoNextNState(i);
    }

        vector<int> circles[5];
        circles[0].push_back(1);   circles[0].push_back(10); 
        circles[1].push_back(3);   circles[1].push_back(4); 
        circles[2].push_back(8);   circles[2].push_back(12);    circles[2].push_back(5); 

        circles[3].push_back(8);   circles[3].push_back(9);
        circles[3].push_back(2);   circles[3].push_back(17);    circles[3].push_back(7);
        
        circles[4].push_back(11);   circles[4].push_back(13);    circles[4].push_back(8);
        circles[4].push_back(9);    circles[4].push_back(10);
 
        /*for(char base='A';base<='Z';base++)
        {
            if(FitCircle(enigmas,circles[0],base)) cout<<base<<endl;
        }*/
        int count[5]={0,0,0,0,0};


      for(char ch1='A';ch1<='Z';ch1++)
        for(char ch2='A';ch2<='Z';ch2++)
        for(char ch3='A';ch3<='Z';ch3++)
        {  
            for(int i=0;i<=17;i++)
            {
                  enigmas[i].NextState();
            }

            
            for(char base='A';base<='Z';base++)
            {
                if(!FitCircle(enigmas,circles[0],base)) continue;count[0]++;
                if(!FitCircle(enigmas,circles[4],base)) continue;count[1]++;
                char newbase=enigmas[13].GetOutputWithoutRotate(enigmas[11].GetOutputWithoutRotate(base-'A'))+'A';
                if(!FitCircle(enigmas,circles[2],newbase)) continue;count[2]++;
                if(!FitCircle(enigmas,circles[3],newbase)) continue;count[3]++;
                newbase=enigmas[2].GetOutputWithoutRotate(enigmas[1].GetOutputWithoutRotate(base-'A'))+'A';
                if(!FitCircle(enigmas,circles[1],newbase)) continue;count[4]++;
                 
                 cout<<enigmas[0].getState()<<endl;
            }
        }

        for(int i=0;i<5;i++) cout<<count[i]<<endl;
    return 0;
}

/*if(ch1=='A'&&ch2=='A'&&ch3=='B') 
            for(int i=1;i<=17;i++)
            {
                  cout<<enigmas[i].getState()<<endl;
            }*/