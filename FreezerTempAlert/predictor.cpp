int arrayLength = 720;

float normalize(float value[])
{
    float mean = meanOf(value);
}

float meanOf(float value[])
{
    float totalValue;
    for (int i = 0; i < arrayLength; i++)
    {
        totalValue += value[i];
    }
    float mean = totalValue/arrayLength;
    return mean;
}

float stdOf(float value, float mean)
{
    float std;
    return std;
}