#include <iostream>
#include <math.h>

using namespace std;

const int MAX_SPEED = 60;

class Moto;
class EstacaoCarga;


////////////////////////////////////////////////////////////////////
class Bateria{
    private:
    int uid = 0;
    float soc = 0;
    void* host=NULL;
//---------------------------------
    public:
    void setUid(int in) {uid=in;}
    int getUid(){return uid;}
//---------------------------------
    void setSoc(float in){soc=in;}
    float getSoc(){return soc;}
//---------------------------------
    void setHost(void* in){host=in;}
    void* getHost(){return host;}
//---------------------------------
    void associarHost(void* in){
        if(host)cout<<"Nao foi possivell associar, a bateria já contem um host.\n";
        else host=in;
    }
//---------------------------------
    void desassociarHost(){
        if(host)host=NULL;
        else cout<<"A bateria nao contem um host para desassociar.\n";
    }
};
/////////////////////////////////////////////////////////////////////
class Moto{
    private:
    string plate;
    float speed = 0;
    Bateria* bateria=NULL;
    bool btn_freio = false, btn_acelerador = false, ligada = false;
//---------------------------------
    void freiar(){
        if(speed>=2.0) speed-=2.0;
        else speed=0.0;
    }
//---------------------------------
    void acelerar(){
        if(speed<=MAX_SPEED-0.2) speed+=0.2;
        else speed=MAX_SPEED;
    }
//---------------------------------
    public:
//---------------------------------
    Moto(string plate):plate(plate){}//metodo construtor
//---------------------------------
    string getPlate(){return plate;}
//---------------------------------
    float getSpeed(){return speed;}
//---------------------------------
    Bateria* getBateria(){return bateria;}
//---------------------------------
    bool freioAcionado(){return btn_freio;}
//---------------------------------
    bool aceleradorAcionado(){return btn_acelerador;}
//---------------------------------
    void ligarMoto(){
        if(bateria){
            if(speed==0){
                if(btn_freio==true){
                    ligada=true;
                    cout<<"Moto ligada!\n";
                }
                else cout<<"Acione o freio para ligar a moto!\n";
            }
            else cout<<"A moto ja esta ligada\n";
        }
        else cout<<"A moto nao possui bateria\n";
    }
//---------------------------------    
    void desligarMoto(){
        if(ligada){
            ligada=false;
            cout<<"Moto desligada!\n";
        }
        else cout<<"A moto ja esta desligada\n";
    }
//---------------------------------
    void acionarAcelerador(){btn_acelerador=true;}
//---------------------------------
    void liberarAcelerador(){btn_acelerador=false;}
//---------------------------------
    void acionarFreio(){btn_freio=true;}
//---------------------------------
    void liberarFreio(){btn_freio=false;}
//---------------------------------
    void associarBateria(Bateria* in){
        if (bateria) cout<<"Ja existe uma bateria!\n";
        else if (in->getHost())cout<<"A bateria ja esta associada a um host!\n";
        else{
            bateria=in;
            bateria->associarHost(this);
        }
    }
//---------------------------------
    Bateria* liberarBateria(){
        Bateria* out=bateria;
        if(bateria)bateria=NULL;
        else cout<<"A moto ja esta sem bateria\n";
        return out;
    }
};
/////////////////////////////////////////////////////////////////////
class PontoCarga{
    private:
    Bateria* bateria;
//---------------------------------
    public:
    Bateria* getBateria(){return bateria;}
//---------------------------------
    void setBateria(Bateria* in){bateria=in;}
};
////////////////////////////////////////////////////////////////////
class EstacaoCarga{
    private:
    int uid;
    PontoCarga cp[8];
    bool statusCp[8];
//---------------------------------   
    public:
    EstacaoCarga(int in){ //metodo construtor
        uid=in;
        for(int i=0;i<8;i++){
            statusCp[i]=false;
        }
    }
//---------------------------------
    int getUid(){return uid;}
//---------------------------------
    PontoCarga* getPontosCargas(){return &cp[0];}
//---------------------------------
    void associarBateriaNoCP(int nCp,Bateria* in){
        if(cp[nCp].getBateria())cp[nCp].setBateria(in);
        else cout<<"Ja existe uma bateria!\n";
    }
//---------------------------------
    void acionarCarregamento(int nCp){
        if(cp[nCp].getBateria()) cout<<"Nao existe bateria nesse local\n";
        else statusCp[nCp]=true;
    }
//---------------------------------    
    void desativarCarregamento(int nCp){
        if(cp[nCp].getBateria()) cout<<"Nao existe bateria nesse local\n";
        else statusCp[nCp]=false;
    }
//---------------------------------
    Bateria* liberarBateriaDoCP(int nCp){
        Bateria* out=cp[nCp].getBateria();
        if(cp[nCp].getBateria())cp[nCp].setBateria(NULL);
        else cout<<"A moto ja esta sem bateria\n";
        return out;
    }
//---------------------------------
    int getNBaterias(){
        int count=0;
        for(int i=0;i<8;i++){
            if(cp[i].getBateria())count++;
        }
        return count;
    }
//---------------------------------
    int getNBateriasCarregando(){
        int count=0;
        for(int i=0;i<8;i++){
            if(statusCp[i])count++;
        }
        return count;
    }
};
/////////////////////////////////////////////////////////////////////
void resumoMoto(Moto moto){
    cout<<"Moto [plate: "<<moto.getPlate()<<"] | [speed:"<<moto.getSpeed();
    cout<<"] | [battery UID: ";
    if(moto.getBateria())cout<<moto.getBateria()->getUid();
    else cout<<"NONE";
    cout<<"] | [soc:";
    if(moto.getBateria())cout<<moto.getBateria()->getSoc();
    else cout<<"NONE";
    cout<<"] | [btn_freio:"<<moto.freioAcionado()<<"] | [btn_acelerador:"<<moto.aceleradorAcionado()<<"]\n";
}
/////////////////////////////////////////////////////////////////////
// void resumoBateria(Bateria bateria){
//     cout<<"\nBateria [UID: "<<bateria.getUid<<"] | [speed:"<<moto.getSpeed();
//     cout<<"] | [battery UID: ";
//     if(moto.getBateria())cout<<moto.getBateria()->getUid();
//     else cout<<"NONE";
//     cout<<"] | [soc:";
//     if(moto.getBateria())cout<<moto.getBateria()->getSoc();
//     else cout<<"NONE";
//     cout<<"]\n";
// }
/////////////////////////////////////////////////////////////////////
int main(){
    //criando as baterias
    cout<<"\nCriando baterias\n";
    Bateria baterias[10];
    for(int i=0;i<10;i++){
        baterias[i].setUid(i+1);
        cout<<baterias[i].getUid()<<endl;
    }

    //criando a moto
    cout<<"\nCriando a moto\n";
    Moto moto("PLA2SA3");
    resumoMoto(moto);

    //testando botoes
    cout<<"\nTestando acelerador e freio\n";
    cout<<"freio\n";
    moto.acionarFreio();
    resumoMoto(moto);
    cout<<"acelerador\n";
    moto.acionarAcelerador();
    resumoMoto(moto);
    cout<<"soltando\n";
    moto.liberarAcelerador();
    moto.liberarFreio();
    resumoMoto(moto);

    //adicionando baterias na moto
    cout<<"\nAdicionando Bateria UID: "<<baterias[0].getUid()<<" na Moto Placa: "<<moto.getPlate()<<endl;
    moto.associarBateria(&baterias[0]);
    resumoMoto(moto);
    //testando adicionar outras baterias
    cout<<"\nAdicionando Bateria UID: "<<baterias[0].getUid()<<" na Moto Placa: "<<moto.getPlate()<<endl;
    moto.associarBateria(&baterias[1]);
    resumoMoto(moto);

    //criando a Estação de Carga;
    cout<<"\nCriando Estacao de Carga\n";
    EstacaoCarga etb(1);
    cout<<"Estacao de Carga UID: "<<etb.getUid()<<endl;










    // bateria.uid=1;
    // bateria.soc=85.0;


    // moto.adicionarBateria(bateria);
    // moto.acionarFreio();
    // moto.ligarMoto();

    // bateria1.uid=2;
    // bateria1.soc=85;

    // EstacaoCarga etb;
    // etb.addBateriaToCP(0,bateria1);
    // etb.addBateriaToCP(7,bateria1);
    // etb.acionarCarregamento(0);
    // etb.acionarCarregamento(7);
    // etb.desativarCarregamento(0);




















    

    // //simulação completa
    // int seg=0;

    // //6 ciclos
    // for(int i=0;i<6;i++){
    //     //3min de aceleração
    //     moto.liberarFreio();
    //     moto.acionarAcelerador();
    //     for(int j=0;j<3*60;j++,seg++){
    //         if(seg%10==0){relatorio(moto,etb);}
    //         moto.simulacao_1seg();
    //     }
    //     //10seg de frenagem
    //     moto.acionarFreio();
    //     moto.liberarAcelerador();
    //     for(int j=0;j<10;j++,seg++){
    //         if(seg%10==0){relatorio(moto,etb);}
    //         moto.simulacao_1seg();
    //     }
    // }

    // //4 ciclos
    // for(int i=0;i<4;i++){
    //     //2min de aceleração
    //     moto.liberarFreio();
    //     moto.acionarAcelerador();
    //     for(int j=0;j<2*60;j++,seg++){
    //         if(seg%10==0){relatorio(moto,etb);}
    //         moto.simulacao_1seg();
    //     }
    //     //12seg de frenagem
    //     moto.acionarFreio();
    //     moto.liberarAcelerador();
    //     for(int j=0;j<12;j++,seg++){
    //         if(seg%10==0){relatorio(moto,etb);}
    //         moto.simulacao_1seg();
    //     }
    // }

    // //1min e 40seg de aceleração
    // moto.liberarFreio();
    // moto.acionarAcelerador();
    // for(int j=0;j<100;j++,seg++){
    //     if(seg%10==0){relatorio(moto,etb);}
    //     moto.simulacao_1seg();
    // }

    // //32seg de frenagem
    // moto.acionarFreio();
    // moto.liberarAcelerador();
    // for(int j=0;j<32;j++,seg++){
    //     if(seg%10==0){relatorio(moto,etb);}
    //     moto.simulacao_1seg();
    // }
    
    // moto.desligarMoto();

    // cout<<seg;

    return 0;

}