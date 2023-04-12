#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int mod(int a)
{
    return a>=0?a%26:a+26;
}

bool CompareVector(const vector<int>& v1,const vector<int>& v2)
{
    if(v1.size()!=v2.size()) return false;
    else
    {
        for(int i=0;i<v1.size();i++)
        {
            if(v1[i]!=v2[i]) return false;
        }
        return true;
    }
}

class Rotor
{
    int output[26];
    int backoutput[26];
    char pos;
    int dev;
    char notch;
public:
    Rotor(){}

    explicit Rotor(string charr,char _pos,char _dev,char _notch)
    {
        for(int i=0;i<26;i++) 
        {
            output[i]=charr[i]-'A';
            backoutput[charr[i]-'A']=i;
        }
        pos=_pos;
        dev=_dev-'A';
        notch=_notch;
    }

    explicit Rotor(string charr,char _notch)
    {
        for(int i=0;i<26;i++) 
        {
            output[i]=charr[i]-'A';
            backoutput[charr[i]-'A']=i;
        }
        pos='A';
        dev=0;
        notch=_notch;
    }

    void setState(char _pos)
    {
        pos=_pos;
    }

    bool reachNotch()
    {
        return pos==notch+1;
    }

    char getState()
    {
        return pos;
    }

    int GetOutput(int input)
    {
        int delta=pos-'A';
        return mod(output[mod(input+delta-dev)]-delta+dev);
    }

    int GetBackOutput(int input)
    {
        int delta=pos-'A';
         return mod(backoutput[mod(input+delta-dev)]-delta+dev);
    }


    char GetCharOutput(int input)
    {
        return (char)(GetOutput(input)+'A');
    }

    char GetCharBackOutput(int input)
    {
        return (char)(GetBackOutput(input)+'A');
    }

    void Rotate()
    {
        pos=='Z'?pos='A':pos++;
    }

    void setRingSetting(char ch)
    {
        dev=ch-'A';
    }

};

class Reflexor
{
    int output[26];
public:  
    Reflexor(){}

    Reflexor(int* arr)
    {
        for(int i=0;i<26;i++) output[i]=arr[i];
    }

    Reflexor(string arr)
    {
        for(int i=0;i<26;i++) output[i]=arr[i]-'A';
    }

    int GetOutPut(int input)
    {
        return output[input];
    }

};

class Enigma
{
    Rotor rotor[3];
    Reflexor reflexor;
    char state[3];

public:  
    Enigma(){}

    Enigma(Rotor rotor1,Rotor rotor2,Rotor rotor3,Reflexor ref,string state_initial,string ringsetting)
    {
        rotor[0]=rotor1;
        rotor[1]=rotor2;
        rotor[2]=rotor3;
        reflexor=ref;
        state[0]=state_initial[0];
        state[1]=state_initial[1];
        state[2]=state_initial[2];
        rotor[0].setState(state[0]);rotor[0].setRingSetting(ringsetting[0]);
        rotor[1].setState(state[1]);rotor[1].setRingSetting(ringsetting[1]);
        rotor[2].setState(state[2]);rotor[2].setRingSetting(ringsetting[2]);
    }

    void NextState()
    {
        rotor[2].Rotate();
        state[2]=rotor[2].getState();
        if(rotor[2].reachNotch())
        {
            rotor[1].Rotate();
            state[1]=rotor[1].getState();
            if(rotor[1].reachNotch())
            {
                rotor[0].Rotate();
                state[0]=rotor[0].getState();
            }
        }

    }

    void GotoNextNState(int n)
    {
        while(n--)
        {
            NextState();
        }
    }

    int GetOutput(int input)
    {
        NextState();

        int o2=rotor[2].GetOutput(input);
        int o1=rotor[1].GetOutput(o2);
        int o0=rotor[0].GetOutput(o1);
        int ef=reflexor.GetOutPut(o0);
        int e0=rotor[0].GetBackOutput(ef);
        int e1=rotor[1].GetBackOutput(e0);
        int e2=rotor[2].GetBackOutput(e1);

        //cout<<input<<"->"<<o2<<"->"<<o1<<"->"<<o0<<"->(ref)"<<ef<<"->"<<e0<<"->"<<e1<<"->"<<e2<<endl;
        return e2;
    }

      int GetOutputWithoutRotate(int input)
    {
        int o2=rotor[2].GetOutput(input);
        int o1=rotor[1].GetOutput(o2);
        int o0=rotor[0].GetOutput(o1);
        int ef=reflexor.GetOutPut(o0);
        int e0=rotor[0].GetBackOutput(ef);
        int e1=rotor[1].GetBackOutput(e0);
        int e2=rotor[2].GetBackOutput(e1);
        return e2;
    }

    char GetCharOutput(char input)
    {
        return (char)(GetOutput(input-'A')+'A');
    }

    void setState(char ch1,char ch2,char ch3)
    {
        rotor[0].setState(ch1);
        rotor[1].setState(ch2);
        rotor[2].setState(ch3);
    }

    string getState()
    {
        string result;
        result+=state[0];result+=state[1];result+=state[2];
        return result;
    }

    string Encrypt(string cleartext)
    {
        string cipher_text;
        for(int i=0;i<cleartext.length();i++)
        {
            cipher_text+=GetCharOutput(cleartext[i]);
        }
        return cipher_text;
    }


};

vector<int> FindCircle(const char* chs)
{
    bool visit[26];
    for(int i=0;i<26;i++) visit[i]=false;
    vector<int> loopsizes;
    for(int i=0;i<26;i++)
    {
        if(visit[i]) continue;
        visit[i]=true;
        int loop=1;
        int next=chs[i]-'A';
        while(!visit[next])
        {
            loop++;
            visit[next]=true;
            next=chs[next]-'A';
        }
        loopsizes.push_back(loop);
    }
    sort(loopsizes.begin(),loopsizes.end(),greater<int>());
    return loopsizes;
}



class CircleCondition
{
    vector<int> circle1;
    vector<int> circle2;
    vector<int> circle3;

    public:  
    CircleCondition(vector<int> str1,vector<int> str2,vector<int> str3)
    {
        circle1=str1;
        circle2=str2;
        circle3=str3;
    }


    bool CompareComponent(const vector<int>& other,int dim)
    {
        switch(dim)
        {
            case 1: return CompareVector(circle1,other);
            case 2: return CompareVector(circle2,other);
            case 3: return CompareVector(circle3,other);
            default: return false;
        }
    }
};



void PrintVec(vector<int>& vec)
{
    for(int i=0;i<vec.size();i++)
    cout<<vec[i]<<" ";
    cout<<endl;
}

#endif