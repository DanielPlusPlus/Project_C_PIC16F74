/*
8. Zmierzy? d?ugo?? przedmiotu, kt?ry ze znan? pr?dko?ci? porusza si? po ta?mie. Na wej?ciu
kontrolera jest dost?pny sygna?, kt?ry zmienia si? z 0 na 1 gdy przedmiot pojawia si? pod
czujnikiem po czym nast?puje zmiana z 1 na 0 gdy przedmiot wyje?d?a spod czujnika.
Przeprowadzi? dyskusj? zakresu mierzonych d?ugo?ci. Mile widziane zabezpieczenie przed
przepe?nieniem dla d?ugich przedmiot?w.
(Wiktoria W?jcik, Daniel Cie?lak) 
*/

#include "xc.h"
#include <pic16f74.h>

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, CP = OFF, BOREN = OFF
#define _XTAL_FREQ 4000000
#define znanaPredkosc 1

unsigned int iloscPrzepelnien=0;

unsigned int obliczDlugosc(void){
    unsigned int dlugosc=iloscPrzepelnien/1000*znanaPredkosc;
    if(dlugosc>0 && dlugosc<255)
        return dlugosc;
    else
        return 0;
}
unsigned int obliczPrzecinek(void){
    unsigned int przecinek=iloscPrzepelnien%1000;
    przecinek/=10;
    return przecinek;
}

void __interrupt() proceduraObslugiPrzerwan(void){
    if(TMR2IF){
        TMR2IF=0;
        iloscPrzepelnien++;
    }
    return;
}

void main(void) {
    TRISB=0b00000001;
    TRISD=0b00000000;
    TRISC=0b00000000;
    T2CON=0b00000001;
    PR2 = 249;
    TMR2IF=0;
    TMR2IE=1;
    PEIE=1;
    GIE=1;
    
    while(1){
        T2CONbits.TMR2ON=1;
        while(RB0==0){
            
        }
        TMR2=0;
        iloscPrzepelnien=0;
        while(RB0==1){
            
        }
        T2CONbits.TMR2ON=0;
        unsigned int dlugosc=obliczDlugosc();
        if(dlugosc>0)
            PORTD=dlugosc;
        else
            PORTD=0;
        unsigned int przecinek=obliczPrzecinek();
        PORTC=przecinek;
    }
}