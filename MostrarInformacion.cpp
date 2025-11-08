#include "MostrarInformacion.h"
#include <iostream>

MostrarInformacion::MostrarInformacion(){

}

void MostrarInformacion::mostrarManoJugador(Mano& manoMostrar){
    std::cout<< manoMostrar.mostrar();
}

char MostrarInformacion::pedirOrden(){
    std::cout<< " DESEA PEDIR O DEJAR p/d "<<std::endl;
    std::cout<< " ingrese su eleccion: "<<std::endl;
    char eleccion;
    std::cin>>eleccion;
    if(eleccion== 'p' || eleccion == 'd'){
        return eleccion;
    }
    else{
        std::cout<<"No es valido tu eleccion"<< std::endl;
        return pedirOrden(); // llamada recursiva para garantizar que dvuelva una opcion valida
    }
    

}