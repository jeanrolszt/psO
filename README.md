# Processo Seletivo para Origem

Processo seletivo feito para a empresa Origem.

[Desafio](https://origemmotos.notion.site/Desafio-Est-gio-desenvolvimento-de-firmware-43c05ca9dbba43c5b19517815ee430d7)

## Primeiros passos

### Qual o ambiente de desenvolvimento?

SO: W10 com WSL Ubuntu 20.04.1

Compilador: G++ 9.4.0

Versão do C++: C++17

### Como executar a aplicação?

Primeiro é preciso compilar com o comando:

```bash
make psO
```

Logo após, executar:

```bash
./psO
```
### Funcionalidades 
#### Bateria

Para criar a bateria, utilizamos o comando:
```
 Bateria bateria;
```

 Para setar um ID:
```
 bateria.setSoc(porcentagembateria);
```

 #### Moto

 Para criar a moto:
```
 Moto moto(placa);
```
 Para associar uma bateria:
```
 moto.associarBateria(ponteirobateria);
```
 Para desassociar a bateria:
```
 moto.liberarBateria();
```

Para ligar a moto é necessário acionar o freio:
```
moto.acionarFreio();
moto.ligarMoto();
```
Para acelerar a moto é necessário que o freio não esteja pressionado:
```
moto.liberarFreio();
moto.acionarAcelerador();
```
#### Estação de carga 

Para criar a estação de carga:
```
EstacaoCarga etb(id);
```
Para associar uma bateria:
```
etb.associaBateriaNoCP(nCP, poteirobateria);
```
Para desassociar:
```
etc.liberarBateriaDoCP(nCP);
```
### Simulação

Para simular 1 (um) segundo de operação da moto:
```
moto.simular_1seg();
```
A simulação da moto segue as instruções informadas no processo seletivo.

A moto só ganha velocidade quando o acelerador está acionado, ofreio não pressionado e a velocidade está menor do que a velocidade máxima da moto.

Quando o freio é pressionado, não acontece aceleração e a moto perde velocidade gradativa até que se chegue o freio seja liberado ou até que atinja a frenagem completa da moto. 

Para simular 1 (um) segundo da operação da estação de carga:
```
etb.simular_1seg();
```
A estação de carga possui a capacidade de carregamento de no máximo 6 baterias em simultaneidade. Quando houver mais do que 6 baterias em carregamento, estação dará preferência àquela em que estiver mais próxima de sua carga completa. 

Para apresentar um resumo das informações acerca da moto e uma estação de carga:
```
relatorio(moto,etb);
```
