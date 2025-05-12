#include <iostream>
#include <cstring>
using namespace std;
//potsetnik so usul da prepishuvate 🙃
class ocila{
    private:
    int brDostapni;
    char *ime=nullptr;
    public:
    void operator =(ocila &o){
        brDostapni=o.brDostapni;
        delete[] ime;
        ime=new char[strlen(o.ime)+1];
        strcpy(ime,o.ime);
    }
    void set(int brDost,const char *im){
        delete[] ime;
        ime=new char[strlen(im)+1];
        brDostapni=brDost;
        strcpy(ime,im);
    }
    void pechati(){
        cout<<brDostapni<<endl;
        cout<<ime<<endl;
    }
    ~ocila(){
        delete[] ime;
    }
};

class prodavnica{
    private:
    char *ime=nullptr,*lok=nullptr;
    int brNaVidovi,brOcila;
    ocila *oc=nullptr;
    public:
    prodavnica(){}
    prodavnica(const char *im=nullptr,const char *lo=nullptr,int bVid=0,ocila *o=nullptr,int brNaOcila=0){
        delete[] ime,lok;
        ime=new char[strlen(im)+1];
        lok=new char[strlen(lo)+1];
        strcpy(ime,im);
        strcpy(lok,lo);
        brNaVidovi=bVid;
        brOcila=brNaOcila;
        oc=new ocila[brNaOcila];
        for(int i=0;i<brNaOcila;i++)oc[i]=o[i];
    }
    prodavnica(prodavnica &p){
        delete[] ime,lok;
        strcpy(ime,p.ime);
        strcpy(lok,p.lok);
        brNaVidovi=p.brNaVidovi;
        brOcila=p.brOcila;
        for(int i=0;i<brOcila;i++)oc[i]=p.oc[i];
    }
    void operator+=(ocila o){
        brOcila++;
        ocila *pom=new ocila[brOcila];
        for(int i=0;i<brOcila-1;i++)pom[i]=oc[i];
        pom[brOcila-1]=o;
        oc=new ocila[brOcila];
        for(int i=0;i<brOcila;i++)oc[i]=pom[i];
    }
    void operator-=(ocila o){
        brOcila+=1;
        ocila *pom=new ocila[brOcila];
        for(int i=1;i<brOcila;i++)pom[i]=oc[i-1];
        pom[0]=o;
        oc=new ocila[brOcila];
        for(int i=0;i<brOcila;i++)oc[i]=pom[i];
    }
    void operator++(){
        brOcila--;
        ocila *pom=new ocila[brOcila];
        for(int i=0;i<brOcila;i++)pom[i]=oc[i];
        oc=new ocila[brOcila];
        for(int i=0;i<brOcila;i++)oc[i]=pom[i];
    }
    void operator--(){
        if(brOcila==0)return;
        brOcila--;
        ocila *pom=new ocila[brOcila];
        for(int i=1;i<brOcila+1;i++)pom[i-1]=oc[i];
        oc=new ocila[brOcila];
        for(int i=0;i<brOcila;i++)oc[i]=pom[i];
    }
    friend ostream& operator<<(ostream &o,prodavnica &p){
        o<<"ime "<<p.ime<<endl;
        o<<"lok "<<p.lok<<endl;
        o<<"br na vid "<<p.brNaVidovi<<endl;
        for(int i=0;i<p.brOcila;i++)p.oc[i].pechati();
        return o;
    }
    ~prodavnica(){
        delete[] ime,lok,oc;
    }
};

int main(){
    ocila o[5];
    o[0].set(0,"bla");
    o[1].set(1,"blabla");
    o[2].set(2,"blabla");
    o[3].set(3,"blabla");
    o[4].set(4,"blabla");
    prodavnica p("ime","lok",2,o,5);
    cout<<p<<endl;
    cout<<"dodadi kraj"<<endl;
    p+=o[0];
    cout<<p<<endl;
    cout<<"dodadi pocetok"<<endl;
    p-=o[1];
    cout<<p<<endl;
    cout<<"trgni kraj"<<endl;
    ++p;
    cout<<p<<endl;
    cout<<"trgni pocetok"<<endl;
    --p;
    cout<<p<<endl;
}