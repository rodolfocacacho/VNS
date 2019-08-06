/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F46K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <pic18f46k22.h>

#include "mcc_generated_files/mcc.h"

/*******************************************************************************
 Declaracion de variables
 ******************************************************************************/
uint8_t static active_mode;
uint16_t volatile g_contador_on;
uint8_t static cantidad_on;
uint16_t static cantidad_sleep;
uint16_t static contador_sleep;
bool static first_time_mode;
uint16_t static freq_stim;
uint8_t static ancho_pulso;
bool volatile g_stimulate;


/*******************************************************************************
 Function Prototypes
*******************************************************************************/

/*
 Funcion que desactiva modulos previo a ir a sleep
 */
void desactivar_modulos(void);

/*
 Funcion que activa perifericos/modulos previo a estimular
 */
void activar_modulos(void);

/*
 Inicializa parametros del dispositivo con codiciones iniciales
 */
void inicializar_dispositivo(void);

/*
 Estimula por el ancho de pulso correcto.
 130us - 1000us
 */
void estimular_pw(uint8_t pw);


/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    inicializar_dispositivo();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    for(;;)
    {
        while(active_mode == 0)
        {
            if(first_time_mode)
            {
                activar_modulos();
                first_time_mode = false;
            }
            if(g_stimulate)
            {
                estimular_pw(ancho_pulso);
                g_stimulate = false;
            }
            if(g_contador_on == cantidad_on)
            {
                first_time_mode = true;
                active_mode = 1;            
            }
            
        
        }
        
        while(active_mode == 1)
        {
            if(first_time_mode == true)
            {
                desactivar_modulos();
                first_time_mode = false;
            }
            
            WDTCON = 0x1;
            SLEEP();
            NOP();
            NOP();
            ++contador_sleep;
            
            if (contador_sleep == cantidad_sleep)
            {
                WDTCON = 0;
                active_mode = 0;
                first_time_mode = true;
            }
        
        }
        
        
    }
}

/*
 Funcion que desactiva modulos previo a ir a sleep
 */
void desactivar_modulos(void)
{
    TMR0_StopTimer();
    TMR1_StopTimer();
    TRISA = 0xFF;
    LATA = 0x00;
    contador_sleep = 0;
}

/*
 Funcion que activa perifericos/modulos previo a estimular
 */
void activar_modulos(void)
{
    TRISA = 0x02;
    TMR0_Initialize();
    TMR0_StartTimer();
    TMR1_StartTimer();
    estimular_pw(ancho_pulso);
    LATA = 0x01;
    g_contador_on = 0;
}

/*
 Inicializa parametros del dispositivo con codiciones iniciales
 */
void inicializar_dispositivo(void)
{
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    contador_sleep = 0;
    g_contador_on = 0;
    cantidad_sleep = 1;
    cantidad_on = 10;
    active_mode = 0;
    first_time_mode = true;
    ancho_pulso = 1;
}

void estimular_pw(uint8_t pw)
{
    switch(pw)
    {
        case 1:
            LATAbits.LATA1 = 1;
            LATAbits.LATA1 = 0;
        break;
            
        case 2:
            LATAbits.LATA1 = 1;
            NOP();
            LATAbits.LATA1 = 0;
        break;
        
        case 3:
            LATAbits.LATA1 = 1;
            NOP();
            NOP();
            NOP();
            LATAbits.LATA1 = 0;
        break;
        
        case 4:
            LATAbits.LATA1 = 1;
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            LATAbits.LATA1 = 0;
        break;
        
        case 5:
            LATAbits.LATA1 = 1;
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            LATAbits.LATA1 = 0;
        break;
        
        default:
            
        break;
    }
            
}

/**
 End of File
*/
