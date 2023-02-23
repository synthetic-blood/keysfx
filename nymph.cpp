#include"nymph.h"
Nymph nymphCore;
float randomizeFloatInRange(float max, float min)
{
    float result = min*1000;
    result += rand()%int(max)*1000;
    result /= 1000;
    if(rand()%2)
        result = -result;
    return result;
}