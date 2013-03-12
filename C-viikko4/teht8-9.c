/* 
 * File:   teht8-9.c
 * Author: taneli
 *
 * Created on 1. lokakuuta 2012, 17:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

/*
 * 
 */
char * print_bin(uint32_t value) {

    size_t bitit = sizeof (uint32_t) * CHAR_BIT;

    char * str = malloc(bitit + 1);
    if (!str) return NULL;
    str[bitit] = 0;

    unsigned u = *(unsigned *) &value;
    int seiska = 0;
    
    for (; bitit--; u >>= 1) {
        if (seiska < 7) {
            str[bitit] = u & 1 ? '1' : '0';
            printf("%c", str[bitit]);
            seiska++;
        }
        else {
            str[bitit] = u & 1 ? '1' : '0';
            seiska = 0;
            printf(".%c", str[bitit]);
        }
    }

    return str;

}

uint16_t make_16bit(uint8_t least_significant, uint8_t most_significant) {
    uint8_t temp1;
    uint16_t sixteen;
    temp1 = most_significant;
    sixteen = temp1 << 8;
    sixteen += least_significant;
    
    return sixteen;
}

uint32_t make_32bit(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
      uint8_t temp1 = byte1;  
      uint8_t temp2 = byte2;  
      uint8_t temp3 = byte3;
      uint32_t thirtytwo;
      thirtytwo = temp1 << 23;
      thirtytwo += temp2 << 15;
      thirtytwo += temp3 << 7;
      thirtytwo += byte4;
      
      return thirtytwo;
}

int main(int argc, char** argv) {

    
    int printing = make_32bit(7,1,2,3);
    print_bin(printing);
    

    return (EXIT_SUCCESS);
}

