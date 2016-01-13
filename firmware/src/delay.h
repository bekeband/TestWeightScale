/* 
 * File:   delay.h
 * Author: user
 *
 * Created on 2016. január 6., 8:58
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DELAY_USEC  1000

void delayusec(uint32_t usectime);
void debug_LED();

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

