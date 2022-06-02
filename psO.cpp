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
        if(host)host=in;
        else cout<<"Nao foi possivell associar, a bateria já contem um host.\n";
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
    void adicionarBateria(Bateria* in){
        if(bateria)cout<<"Ja existe uma bateria!\n";
        else bateria=in;
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
// void relatorio(Moto moto,EstacaoCarga etb){
//     if(false){
//         cout<<"Motorcycle plate: "<<moto.getPlate()<<endl;
//         cout<<"Speed: "<<moto.getSpeed()<<endl;
//         cout<<"Attached battery UID: ";
//         if(moto.getBatteryUid()==0){cout<<"NONE"<<endl;}
//         else cout<<moto.getBatteryUid()<<endl;
//         cout<<"Motorcycle battery SoC: ";
//         if(moto.getBatteryUid()==0){cout<<"NONE"<<endl;}
//         else cout<<moto.getSoc()<<"%"<<endl<<endl;
//     }
//     if(false){
//         cout<<"ETB ID: ";
//         if(etb.getUid()==0)cout<<"NULL";
//         else cout<<etb.getUid();
//         cout<<endl;

//         for(int i=0;i<8;i++){
//             cout<<"CP "<<i<<"  [";
//             if(etb.cp[i].getBateria().uid==0){
//                 cout<<"NONE";
//             }
//             else{
//                 cout<<"battery "<<etb.cp[i].getBateria().uid;
//                 cout<<" | SoC: "<<etb.cp[i].getBateria().soc;
//                 if(etb.cp[i].getstatusPC()==1){cout<<" | charging: NO";}
//                 else cout<<" | charging: YES";
//             }
//             cout<<"]\n\n";
//         }
//     }
// }
/////////////////////////////////////////////////////////////////////
int main(){
    //criando a moto
    Moto moto("PLA2SA3");
    
    //criando as baterias;
    Bateria baterias[10];

    //criando a Estação de Carga;
    EstacaoCarga etb(1);

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


}