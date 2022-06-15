#include <iostream>
#include <string.h>
#include <random>
#include<time.h>
#include <string>
#include <vector>
#include <fstream>
// #include <bit

using namespace std;
short* keyvec,len;
char alfabetLF[]=".- abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
unsigned long long keygen()
{
    srand(time(0));
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rand()); // seed the generator
    std::uniform_int_distribution<> distr(1000000000,INT32_MAX);
    int x,y;
    x=(distr(gen));
    y=(distr(gen));
    x-=1000000000;
    y-=1000000000;
    
    unsigned long long key=x,kkey;
    while(x>0){
        key*=10;
        x/=10;
    }
    key+=y;
    kkey=key;
    len=std::to_string(kkey).length();
    keyvec=new short[len];

    for(int i=len-1;i>=0;i--){
        keyvec[i]=kkey%10;
        kkey/=10;
    }
    return key;
}
char* amestecare(unsigned long long key,char* text){
    struct Nod{
        char *linie;
        Nod* next=nullptr;
    }*nod,*startnod;
    unsigned long long tempkey=key;
    char **mat;
    int count=0,ltext=strlen(text),i=0;
    short* marimelinie;
    nod=new Nod;
    startnod=nod;

    nod->linie=new char[keyvec[i]];
    strncpy(nod->linie,(text+count),keyvec[i]);
    count+=keyvec[i];
    i++;
          
    //se taie pe bucati textul
    while(count<ltext){
        nod->next=new Nod;
        nod=nod->next;
        //copiaza
        nod->linie=new char[keyvec[i%len]];
        strncpy(nod->linie,(text+count),keyvec[i%len]);
        // for(int j=0;j<keyvec[i%len];j++)

        //iteratori
       count+=keyvec[i%len];
        i++;
    }
    int nrtaieri=i;
    //cout<<i<<endl;
    marimelinie=new short[nrtaieri];
    mat = new char*[nrtaieri];
    nod = startnod;
    // cout<<"-------"<<endl;
    //se salveaza lista intr-o matrice

    
    for(int j=0;j<nrtaieri;j++){
        marimelinie[j]=keyvec[j%len];
        mat[j]=nod->linie;
        startnod=nod;
        nod=nod->next;
        delete startnod;
        // cout<<mat[j]<<"_";
    }
    
    marimelinie[nrtaieri-1]=keyvec[(nrtaieri-1)%len]-(count%ltext);
    // se v-or amestecha bucatile din text
    // cout<<endl<<"nrtaieri:"<<nrtaieri<<endl;
    for(int j=0;j<nrtaieri;j++){
        swap(mat[j],mat[(keyvec[j%len]+j)%nrtaieri]);
        swap(marimelinie[j],marimelinie[(keyvec[j%len]+j)%nrtaieri]);
        // cout<<j%i<<" swap cu "<<(keyvec[j%len]+j)%i<<"::"<<(keyvec[j%len]+j)<<endl;
        // (j+(keyvec[j%len]%i))%len
    }

    // cout<<endl;
    
    count=0;
    int k=0;
    while(count<ltext||k>9){
        for(int j=0;j<nrtaieri;j++){
            if(k<marimelinie[j]){
               text[count]=mat[j][k];
               count++;
            }
        }
        k++;
    }
    
    // cout<<text<<"::"<<endl;
    return text;
}
char* deamstecare(unsigned long long key,char* text){
    int ltext=strlen(text),nrtaieri=0,count=0;
    short* indexlinie,*marimelinie;
    char** mat;
    while(count<ltext){
        count+=keyvec[nrtaieri%len];
        nrtaieri++;
    }
    // cout<<"-0-0-0-0-0-"<<endl;
    // cout<<keyvec[nrtaieri%len]<<endl;
    // cout<<count<<endl;
    // cout<<ltext<<endl;
    // cout<<nrtaieri<<Pendl;

    indexlinie =new short[nrtaieri];
    marimelinie=new short[nrtaieri];
    mat=new char*[nrtaieri];

    for(int j=0;j<nrtaieri;j++){
        indexlinie[j]=j;
        marimelinie[j]=keyvec[j%len];
        // cout<<indexlinie[j]<<" "<<marimelinie[j]<<endl;
        }
    marimelinie[nrtaieri-1]=keyvec[(nrtaieri-1)%len]-(count%ltext);
    //se reproduce amestecarea
    for(int j=0;j<nrtaieri;j++){
        swap(indexlinie[j],indexlinie[(keyvec[j%len]+j)%nrtaieri]);
        swap(marimelinie[j],marimelinie[(keyvec[j%len]+j)%nrtaieri]);
        // cout<<j%nrtaieri<<" SWAP cu "<<(keyvec[j%len]+j)%nrtaieri<<endl;
        //cout<<j%nrtaieri<<" Swap cu "<<(keyvec[j%len]+j)%nrtaieri<<"::"<<(keyvec[j%len]+j)<<endl;
    }
    for(int j=0;j<nrtaieri;j++){
        // cout<<j<<":"<<marimelinie[j]<<endl;
        mat[j]=new char[marimelinie[j]+1];
    }
    int index=0;
    while(index<ltext){
        for(int i=0;i<10;i++)
            for(int j=0;j<nrtaieri;j++)
                if(i<marimelinie[j]){
                    mat[j][i]=text[index];
                    index++;
                }
    }
    // for(int j=0;j<nrtaieri;j++){
    //     for(int i=0;i<marimelinie[j];i++)
    //     cout<<mat[j][i];
    //     cout<<endl;
    //     }
    char **matord=new char*[nrtaieri];
    short *lungimelin=new short[nrtaieri];
    for(int j=0;j<nrtaieri;j++){
        matord[indexlinie[j]]=mat[j];
        matord[indexlinie[j]][marimelinie[j]]='\0';
        lungimelin[indexlinie[j]]=marimelinie[j];
    }
    // for(int j=0;j<nrtaieri;j++){
    //     for(int i=0;i<lungimelin[j];i++)
    //     cout<<matord[j][i];
    //     cout<<endl;
    //     }
    text=new char[ltext];
    for(int j=0;j<nrtaieri;j++){
        strcat(text,matord[j]);
    }
    return text;
}
char* adaugaLitereFalse(char* text){
    char* textLF;
    int procentLitereFalse,cateLF,ltext=strlen(text),litLF=strlen(alfabetLF);

    srand(time(0));
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rand()); // seed the generator
    std::uniform_int_distribution<> distr(20,80);

    procentLitereFalse=distr(gen);
    // cout<<"cat la suta este fals :"<<procentLitereFalse<<endl;
    //aici o sa fie o problema cu numere mari ca o sa dea overflow
    cateLF=(int)((double)(ltext*procentLitereFalse))/100;
    // cout<<"atatea litere false o sa fie:"<<cateLF<<endl;
    //+1 ii ca sa adaugi un caracter null ca poate nu o sa il am
    //ii *2 ca sa acomodeze doua litere , una de confirmare si cealalta data
    
    textLF=new char[2*(cateLF+ltext)+1];
    std::uniform_int_distribution<> randPF(0,cateLF+ltext-1);
    vector<bool> pozfalse(cateLF+ltext,0);

    // for(int i=0;i<cateLF+ltext;i++){
    //     cout<<pozfalse[i];
    // }
    //cout<<endl;
    //cout<<cateLF+ltext<<endl;
    // bitset<constmarime> pozfalse;
    // //-1 pt ca alege pozitiile
    // std::uniform_int_distribution<> distr(0,cateLF+ltext-1);
    
    for(int i=0;i<cateLF;i++){
        int poz=randPF(gen);
        while(pozfalse[poz]){
            poz=randPF(gen);
            // cout<<"nou::"<<poz<<endl;
        }
        // cout<<poz<<endl;
        pozfalse[poz]=1;
    }
    // for(int i=0;i<cateLF+ltext;i++){
    //     cout<<pozfalse[i];
    // }
    //cout<<endl;
    int contor=0;
    for(int i=0;i<(cateLF+ltext)*2;i+=2){
        if(pozfalse[i/2]){
            std::uniform_int_distribution<> literaFalsa(0,litLF-2);
            int poz=literaFalsa(gen);
            int a,b;
            a=literaFalsa(gen);
            b=poz+((keyvec[(i/2)%len]%2)==poz%2)*1;
            // b=(keyvec[((i/2)+poz)%len]-(keyvec[(i/2)%len]%2));
            textLF[i]=alfabetLF[a];
            textLF[i+1]=alfabetLF[b];
            // textLF[i]='<';
            // textLF[i+1]='>';
            ///
            ///debug
            ///
            // cout<<"i : "<<i<<endl;
            // cout<<"i/2 : "<<i/2<<endl;
            // cout<<"poz = "<<poz<<endl;
            // cout<<"(keyvec[(i/2)%len])%2 = "<<(keyvec[(i/2)%len])%2<<endl;
            // cout<<"(keyvec[(i/2)%len]) = "<<(keyvec[(i/2)%len])<<endl;
            // cout<<"imitatia din text = "<<alfabetLF[a]<<"-"<<(int)alfabetLF[a]<<endl;
            // cout<<"litera alfabet    = "<<alfabetLF[b]<<"-"<<(int)alfabetLF[b]<<endl;
            // cout<<"numere : "<<(keyvec[(i/2)%len])<<"-"<<b<<endl;
            // cout<<" paritate :"<<(keyvec[(i/2)%len])%2<<"-"<<b%2<<endl;
            // cout<<"---"<<endl;
            // alfabetLF[(keyvec[(i/2)%len]%2+keyvec[((i/2)+poz)%len])]
        }else{
            std::uniform_int_distribution<> literaFalsa(0,litLF-2);
            int poz=literaFalsa(gen);
            int a,b;
            b=poz+((keyvec[(i/2)%len]%2)!=poz%2)*1;
            // b=(keyvec[((i/2)+poz)%len]-(keyvec[(i/2)%len]%2));
            textLF[i]=text[contor];
            textLF[i+1]=alfabetLF[b];
            // textLF[i]=',';
            // textLF[i+1]='`';
            contor++;
        }
    }
    // cout<<textLF<<endl;
return textLF;
}
char* scoateLF(char* text){
    int count=0,lenText=strlen(text);
    char* textdescifrat=new char[lenText/2 +1];
    for(int i=0;i<lenText;i+=2){
        if(((keyvec[(i/2)%len]%2)==text[i+1]%2)){
            textdescifrat[count]=text[i];
            count++;
        }
    }
    return textdescifrat;
}
char* criptare(char* text){
    text=adaugaLitereFalse(text);
    text=amestecare(0,text);
    return text;
}
char* decriptare(char* text){
    text=deamstecare(0,text);
    text=scoateLF(text);
    return text;
}
int main()
{

    srand(time(0));
    //"acesta este un mesaj de la bucuresti pentru dumneavoastra"
    char text[]="razvan , sti cum poti sa faci bitset sa fie mai dinamic ? ca vreau sa fac un array de bitset pe baza unei variabile si imi zice ca nu ii o consanta";
    
    char **mat,*textamestecat;
    int n,ltext=strlen(text),stocat=0,nrpermutari;
    mat=new char*[20];

    unsigned long long key=663874105088399729;//keygen();
    
    unsigned long long kkey=key;
    len=std::to_string(kkey).length();
    keyvec=new short[len];

    for(int i=len-1;i>=0;i--){
        keyvec[i]=kkey%10;
        kkey/=10;
    }
    // cout<<"inainte de toate aici am sa pun marimea textului "<<ltext<<endl<<"--__--__--__--__--__--__--__--__--"<<endl;
    textamestecat=text;
    textamestecat=criptare(textamestecat);
    cout<<textamestecat<<"::"<<endl<<endl;
    textamestecat=decriptare(textamestecat);
    cout<<textamestecat<<endl;
    // for(int i=0;i<20&&stocat<ltext;i++){
    //     int k=rand()%(ltext/3)+1;
    //     mat[i]=new char[k+2];
    //     mat[i][0]=(char)k;
    //     mat[i][k+1]='\0';
    //     for(int j=0;j<k&&stocat+j<ltext;j++)
    //         mat[i][j+1]=text[stocat+j];
    //     stocat+=k;
    //    // cout<<k<<endl;
    // }
    // for(int i=0;i<20;i++)
    //     if(mat[i]!=nullptr)
    //         cout<<mat[i]+1<<endl;
    //     else{
    //         n=i;
    //         cout<<n<<endl;
    //         break;
    //     }
    // cout<<"------"<<endl;
    // for(int i=0;i<len;i++)
    // cout<<keyvec[i];
    // cout<<endl<<key<<endl;
      
    //for()
}   