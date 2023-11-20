#include "utility.h"

/**
 * power - Calculate b to the power of e
 * 
 * @b: Base
 * @e: Exposant
 * 
 * Return: b^e
*/
int power(int b, int e) {

    if (e == 0)
        return (1);

    return b * power(b, e - 1);
}