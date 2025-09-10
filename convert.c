#include<stdio.h>
#include<stdint.h>
#include<string.h>

void div_convert (uint32_t n , int base , char *out) {
    char temp [65]; // Temporary buffer
    int pos = 0;
    
    // Handle zero case
    if ( n == 0) {
        strcpy ( out , "0" ) ;
        return ;
    }
        
    // Extract digits from right to left
    while ( n > 0) {
        int remainder = n % base ;
        n = n / base ;
        
        // Convert digit to character
        if ( remainder < 10)
            temp [ pos ++] = '0' + remainder ;
        else
            temp [ pos ++] = 'A'  + (remainder - 10) ;
    }
    
    // Reverse the result
    for (int i = 0; i < pos; i++) {
        out[i] = temp[pos - 1 - i];
    }
    out[pos] = '\0';
}

void sub_convert (uint32_t n, int base, char *out) {
    int pos = 0;
    
    // Handle zero case
    if (n == 0) {
        strcpy (out, "0" );
        return;
    }
    
    // Find the highest power
    uint32_t power = 1;
    while (power <= n / base) {
        power *= base;
    }
    
    // Subtract multiples 
    while (power > 0) {
        int num = 0;
        while (n >= power) {
            n -= power;
            num++;
        }
        
        // Convert digit to character
        if ( num < 10)
            out [ pos ++] = '0' + num ;
        else
            out [ pos ++] = 'A'  + (num - 10) ;
        
        // Move to lower power and repeat
        power /= base;
    }
    
    out[pos] = '\0';
}

void print_tables (uint32_t n, char *out) {
    char bin [33] , oct [12] , hex [9];
    char temp [512];
    
    //Clear output
    out[0] = '\0';
    
    // Original number
    div_convert (n , 2 , bin ) ;
    div_convert (n , 8 , oct ) ;
    div_convert (n , 16 , hex ) ;
    //Add text to output
    snprintf (temp, sizeof(temp), "Original: Binary = %s Octal = %s Decimal = %u Hex = %s \n", bin, oct, n, hex);
    strcat(out, temp);
    
    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert ( shifted , 2 , bin ) ;
    div_convert ( shifted , 8 , oct ) ;
    div_convert ( shifted , 16 , hex ) ;
    //Add text to output
    snprintf (temp, sizeof(temp), "Left Shift by 3: Binary = %s Octal = %s Decimal = %u Hex = %s \n", bin, oct, shifted, hex);
    strcat(out, temp);
    
    // AND with 0xFF
    uint32_t masked = n & 0xFF ;
    div_convert ( masked , 2 , bin );
    div_convert ( masked , 8 , oct );
    div_convert ( masked , 16 , hex );
    //Add text to output
    snprintf (temp, sizeof(temp), "AND with 0xFF: Binary = %s Octal = %s Decimal = %u Hex = %s \n", bin, oct, masked, hex);
    strcat(out, temp);
    
}