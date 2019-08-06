/* 
 * File:   pwm_manual.h
 * Author: rcaca
 *
 * Created on August 6, 2019, 12:38 AM
 */

#ifndef PWM_MANUAL_H
#define	PWM_MANUAL_H

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PWM_MANUAL_H */

/**
  Section: PWM Manual APIs
*/

/**
  @Summary
    Inicializa TMR2 y contadores para generar PWM manual.

  @Description
    Esta funcion se llama de primero antes de cualquier otra implementacion
    del PWM Manual

  @Preconditions
    None

  @Param
    None

  @Returns
    None

*/
void pwm_manual_init(void);

/**
  @Summary
    Inicializa TMR2 y contadores para generar PWM manual.

  @Description
    Esta funcion se llama de primero antes de cualquier otra implementacion
    del PWM Manual

  @Preconditions
    None

  @Param
    None

  @Returns
    None

*/
void pwm_manual_stop(void);

/**
  @Summary
    Detiene el PWM Manual.

  @Description
   Esta funcion detendra el PWM manual

  @Preconditions
    None

  @Param
    None

  @Returns
    None

*/
void pwm_manual_mod_pw(uint8_t pwm_pw);

/**
  @Summary
    Modifica la frecuencia de estimulacion del PWM Manual.

  @Description
    Esta funcion se encargara de modificar la frecuencia del PWM manual.
    Las frecuencias generadas seran aprox: 1, 2, 5, 10, 15, 20, 25 y 30 Hz 

  @Preconditions
    None

  @Param
    None

  @Returns
    None

*/
void pwm_manual_mod_freq(uint16_t pwm_freq);

/**
 End of File
*/
