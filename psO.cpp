#include <iostream>
#include <math.h>

using namespace std;

class Bateria{
    public:
    int uid = 0;
    float soc = 0;
    enum state {Idle,Attached};
    state estado = Idle;

    void setAttached(){
        estado=Attached;
    }
};





class Moto{
 
    private:
    const int MAX_SPEED = 60;
    string plate;
    float speed = 0;
    enum state {Standby,On};
    state estado = Standby;
    Bateria bateria;
    bool btn_freio = false, btn_acelerador = false;

    void freiar(){
        if(speed>=2.0) speed-=2.0;
        else speed=0.0;
    }

    void acelerar(){
        if(speed<=MAX_SPEED-0.2) speed+=0.2;
        else speed=MAX_SPEED;
    }

    public:
    Moto(string plate):plate(plate){}

    void ligarMoto(){
        if(hasBattery()){
            if(btn_freio==true){
                if(estado==Standby){
                    estado=On;
                    cout<<"Moto ligada!\n";
                }
                else cout<<"A moto ja esta ligada\n";
            }
            else cout<<"Acione o freio para ligar a moto!\n";
        }
        else cout<<"A moto nao possui bateria\n";
    }
    
    void desligarMoto(){
        if(estado==On){
            estado=Standby;
            cout<<"Moto desligada!\n";
        }
        else cout<<"A moto ja esta desligada\n";
    }

    void acionarAcelerador(){btn_acelerador=true;}
    void liberarAcelerador(){btn_acelerador=false;}

    void acionarFreio(){btn_freio=true;}
    void liberarFreio(){btn_freio=false;}

    string getPlate(){return plate;}

    float getSpeed(){return speed;}
    float getMAX_SPEED(){return MAX_SPEED;}
    
    void adicionarBateria(Bateria b){
        if(b.uid==0){
            cout<<"nao e possivel adicionar uma bateria sem id\n";
        }
        else{
            bateria=b;
            bateria.setAttached();
        }
    }
    float getSoc(){
        return bateria.soc;
    }

    int getBatteryUid(){
        return bateria.uid;
    }

    bool hasBattery(){
        if(bateria.uid!=0){return true;}
        else return false;
    }


    void simulacao_1seg(){
        if(estado==On){
            if(btn_freio==true){
                freiar();
            }
            else if(btn_acelerador==true){
                acelerar();
            }
        bateria.soc= bateria.soc-0.01-((pow((speed/MAX_SPEED),2))*0.05);             
        }
        else if(estado==Standby){
            bateria.soc-=0.01;
        }
    }
};






class PontoCarga{
    private:
    enum state {Empty,Idle,Charging};
    state estado = Empty;
    Bateria bateria;

    public:
    Bateria getBateria(){
        return bateria;
    }

    int getstatusPC(){
        return estado;
    }

    void addBateria(Bateria in){
        if(estado==Empty){
            bateria = in;
            bateria.setAttached();
            estado=Idle;
        }
        else cout<<"Ja existe uma bateria no CP!\n";
    }

    void startingCharging(){
        if(estado){
            estado=Charging;
        }
    }

    Bateria rmvBateria(){
        if(estado!= Empty){
            estado = Empty;
            return bateria;
        }
        else{
            Bateria out;
            out.uid=0;
            return out;
        }
    }

};





class EstacaoCarga{
    private:
    int uid;


    public:
    PontoCarga cp[8];
    int getUid(){return uid;}
    void addBateriaToCP(int nCp,Bateria in){
        cp[nCp].addBateria(in);
    }
    void acionarCarregamento(int nCp){
        cp[nCp].startingCharging();
    }


};



void relatorio(Moto moto,EstacaoCarga etb){
    if(true){
        cout<<"Motorcycle plate: "<<moto.getPlate()<<endl;
        cout<<"Speed: "<<moto.getSpeed()<<endl;
        cout<<"Attached battery UID: ";
        if(moto.getBatteryUid()==0){cout<<"NONE"<<endl;}
        else cout<<moto.getBatteryUid()<<endl;
        cout<<"Motorcycle battery SoC: ";
        if(moto.getBatteryUid()==0){cout<<"NONE"<<endl;}
        else cout<<moto.getSoc()<<"%"<<endl<<endl;
    }
    if(true){
        cout<<"ETB ID: ";
        if(etb.getUid()==0)cout<<"NULL";
        else cout<<etb.getUid();
        cout<<endl;

        for(int i=0;i<8;i++){
            cout<<"CP "<<i<<"  [";
            if(etb.cp[i].getBateria().uid==0){
                cout<<"NONE";
            }
            else{
                cout<<"battery "<<etb.cp[i].getBateria().uid;
                cout<<" | SoC: "<<etb.cp[i].getBateria().soc;
                if(etb.cp[i].getstatusPC()==1){cout<<" | charging: NO";}
                else cout<<" | charging: YES";
            }
            cout<<"]\n";
        }
    }
}

int main(){

    Moto moto("PLA2SA3");
    Bateria bateria,bateria1;
    bateria.uid=1;
    bateria.soc=85.0;


    moto.adicionarBateria(bateria);
    moto.acionarFreio();
    moto.ligarMoto();

    bateria1.uid=2;
    bateria1.soc=85;

    EstacaoCarga etb;
    etb.addBateriaToCP(0,bateria1);
    etb.addBateriaToCP(7,bateria1);
    etb.acionarCarregamento(0);





















    //simulação completa
    int seg=0;

    //6 ciclos
    for(int i=0;i<6;i++){
        //3min de aceleração
        moto.liberarFreio();
        moto.acionarAcelerador();
        for(int j=0;j<3*60;j++,seg++){
            if(seg%10==0){relatorio(moto,etb);}
            moto.simulacao_1seg();
        }
        //10seg de frenagem
        moto.acionarFreio();
        moto.liberarAcelerador();
        for(int j=0;j<10;j++,seg++){
            if(seg%10==0){relatorio(moto,etb);}
            moto.simulacao_1seg();
        }
    }

    //4 ciclos
    for(int i=0;i<4;i++){
        //2min de aceleração
        moto.liberarFreio();
        moto.acionarAcelerador();
        for(int j=0;j<2*60;j++,seg++){
            if(seg%10==0){relatorio(moto,etb);}
            moto.simulacao_1seg();
        }
        //12seg de frenagem
        moto.acionarFreio();
        moto.liberarAcelerador();
        for(int j=0;j<12;j++,seg++){
            if(seg%10==0){relatorio(moto,etb);}
            moto.simulacao_1seg();
        }
    }

    //1min e 40seg de aceleração
    moto.liberarFreio();
    moto.acionarAcelerador();
    for(int j=0;j<100;j++,seg++){
        if(seg%10==0){relatorio(moto,etb);}
        moto.simulacao_1seg();
    }

    //32seg de frenagem
    moto.acionarFreio();
    moto.liberarAcelerador();
    for(int j=0;j<32;j++,seg++){
        if(seg%10==0){relatorio(moto,etb);}
        moto.simulacao_1seg();
    }
    
    moto.desligarMoto();

    cout<<seg;


}