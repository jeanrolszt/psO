#include <iostream>
#include <math.h>

using namespace std;

class Moto{
 
    private:
    const int MAX_SPEED = 60;
    string plate;
    float speed = 0;
    float p_bateria;
    enum state {Standby,On};
    state estado = Standby;
    bool btn_freio = false, btn_acelerador = false;

    void freiar(){
        if(speed>=2.0) speed-=2.0;
        else speed=0.0;
    }

    void acelerar(){
        if(speed<MAX_SPEED) speed+=0.2;
    }


    public:
    Moto(string plate, float p_bateria):plate(plate),p_bateria(p_bateria){}

    void ligarMoto(){
        if(btn_freio==true){
            if(estado==Standby){
                estado=On;
                cout<<"Moto ligada!\n";
            }
            else cout<<"A moto ja esta ligada\n";
        }
        else cout<<"Acione o freio para ligar a moto!\n";
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

    string returnPlate(){return plate;}

    float returnSpeed(){return speed;}
    
    float returnP_bateria(){return p_bateria;}


    void simulacao_1seg(){
        if(estado==On){
            if(btn_freio==true){
                freiar();
            }
            else if(btn_acelerador==true){
                acelerar();
            }
        }
    }
};

int main(){
    Moto moto("PLA2SA3",85);

    moto.acionarFreio();
    moto.ligarMoto();
    moto.acionarAcelerador();
    moto.liberarFreio();
    

    for(int seg=0;seg<30*60;seg++){

        if(seg==0||seg%10==0){
            cout<<"-----------------------------------------------"<<endl;
            cout<<"Motorcycle plate: "<< moto.returnPlate() <<endl;
            cout<<"Speed: "<< moto.returnSpeed() <<endl;
            cout<<"Motorcycle battery SoC: "<< moto.returnP_bateria() <<endl;
            cout<<"-----------------------------------------------"<<endl;
        }
        moto.simulacao_1seg();
    }
}