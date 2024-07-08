#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXROWS 100

void hextoBinary(char arr[][80], int num, char add[][15])
{
    int i = 0;
    while (i < 8)
    {
        switch (add[num][i])
        {
        case '0':
            strcat(arr[num], "0000");
            break;
        case '1':
            strcat(arr[num], "0001");
            break;
        case '2':
            strcat(arr[num], "0010");
            break;
        case '3':
            strcat(arr[num], "0011");
            break;
        case '4':
            strcat(arr[num], "0100");
            break;
        case '5':
            strcat(arr[num], "0101");
            break;
        case '6':
            strcat(arr[num], "0110");
            break;
        case '7':
            strcat(arr[num], "0111");
            break;
        case '8':
            strcat(arr[num], "1000");
            break;
        case '9':
            strcat(arr[num], "1001");
            break;
        case 'a':
            strcat(arr[num], "1010");
            break;
        case 'b':
            strcat(arr[num], "1011");
            break;
        case 'c':
            strcat(arr[num], "1100");
            break;
        case 'd':
            strcat(arr[num], "1101");
            break;
        case 'e':
            strcat(arr[num], "1110");
            break;
        case 'f':
            strcat(arr[num], "1111");
            break;
        default:
            printf(" Invalid input %c\n", add[num][i]);
        }
        i++;
    }
}

char *sliceString(char *str, int start, int end)
{
    int i;
    int temp = start;
    start = 32 - end;
    end = 32 - temp;
    int size = (end - start) + 1;
    char *output = (char *)malloc(size * sizeof(char));

    for (i = 0; start < end; start++, i++)
    {
        output[i] = str[start];
    }
    output[size] = '\0';
    return output;
}

int tointeger(char arr[])
{
    int i = 0;
    long long int result = 0;
    while (arr[i])
    {
        result += (int)arr[i] - 48;
        result *= 10;
        i++;
    }
    result /= 10;
    return result;
}

int twosComplementToDecimal(char arr2[], int yes)
{
    int length = strlen(arr2);
    long long int n = tointeger(arr2);
    long long int dec = 0, i = 0, rem = 0;
    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        i++;
    }
    i -= 1;
    if (length == i + 1 && yes == 1)
        dec -= 2 * rem * pow(2, i);
    char str[100];
    sprintf(str, "%lld", dec);
    return dec;
}

char *binaryToHex(char arr[])
{

    int len = strlen(arr);

    int added = 0;
    if (len % 4 != 0)
    {
        added = 4 - (len % 4);
    }

    char *paddedBinary = (char *)malloc((len + added + 1) * sizeof(char));
    for (int i = 0; i < added; i++)
    {
        paddedBinary[i] = '0';
    }
    paddedBinary[added] = '\0';
    strcat(paddedBinary, arr);
    len = len + added;

    int hex_len = len / 4;
    char *hex = (char *)malloc((hex_len + 1) * sizeof(char));
    char *hexChars = "0123456789ABCDEF";

    for (int i = 0; i < hex_len; i++)
    {
        int value = twosComplementToDecimal(sliceString(paddedBinary, 32 - (i + 1) * 4, 32 - i * 4), 0);
        hex[i] = hexChars[value];
    }
    hex[hex_len] = '\0';
    return hex;
}

int main()
{
    FILE *file = fopen("cache.access", "r");
    FILE *file2 = fopen("cache.config", "r");

    char address[MAXROWS][15] = {'\0'};
    char config[7][20] = {'\0'};
    char type[MAXROWS] = {'\0'};
    char ch;
    int rows = 0, cols = 0;
    int rows1 = 0, cols1 = 0;
    while ((ch = fgetc(file)) != EOF && rows < MAXROWS)
    {
        if (ch == '\n')
        {
            cols = -1;
            rows++;
        }
        if (cols == 0)
        {
            if (ch == 'W')
            {
                type[rows] = '1';
            }
            else
            {
                type[rows] = '0';
            }
        }
        if (cols < 5)
        {
            cols++;
        }
        else if (cols < 15)
        {
            address[rows][cols - 5] = ch;
            cols++;
        }
    }

    while ((ch = fgetc(file2)) != EOF && rows1 < 7)
    {
        if (ch == '\n')
        {
            cols1 = 0;
            rows1++;
        }
        else if (cols1 < 20)
        {
            config[rows1][cols1] = ch;
            cols1++;
        }
    }
    int total_size = tointeger(config[0]);
    int block_size = tointeger(config[1]);
    int associativity = tointeger(config[2]);
    // 0 fifo
    // 1 lru
    // 2 random
    int policy;
    if (strcmp("FIFO", config[3]) == 0)
        policy = 0;
    if (strcmp("LRU", config[3]) == 0)
        policy = 1;
    if (strcmp("RANDOM", config[3]) == 0)
        policy = 2;
    // 0 no allocate
    // 1 yes allocate
    int write;
    if (strcmp("WT", config[4]) == 0)
        write = 0;
    if (strcmp("WB", config[4]) == 0)
        write = 1;

    rows = rows + 1;
    cols = cols - 4;

    char binary[MAXROWS][40] = {'\0'};
    for (int i = 0; i < rows; i++)
    {
        hextoBinary(binary, i, address);
    }

    if (associativity == 0)
    {
        associativity = total_size / block_size;
    }

    int sets = total_size / (associativity * block_size);
    int index = log2(sets);
    int lru[50][50];
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            lru[i][j] = associativity - 1;
        }
    }
    int offset = log2(block_size);
    int valid[50][50] = {0};
    char tags[50][50][50] = {'\0'};

    int replace = 0;
    for (int k = 0; k < rows; k++)
    {
        replace = 0;
        char tag[40] = {'\0'};
        strcpy(tag, sliceString(binary[k], offset + index, 32));
        char indexing[40] = {'\0'};
        strcpy(indexing, sliceString(binary[k], offset, index + offset));
        int indexes = twosComplementToDecimal(indexing, 0);

        for (int i = 0; i < associativity; i++)
        {
            if (valid[indexes][i] == 1)
            {
                if (strcmp(tags[indexes][i], tag) == 0)
                {
                    printf("Address: 0x%s, Set: 0x%s, Hit, Tag: 0x%s\n", address[k], binaryToHex(indexing), binaryToHex(tag));
                    if (policy == 1)
                    {
                        int temp = lru[indexes][i];
                        lru[indexes][i] = -1;
                        for (int j = 0; j < associativity; j++)
                        {
                            if (lru[indexes][j] < temp)
                            {
                                lru[indexes][j] += 1;
                            }
                        }
                    }
                    break;
                }
                else
                {
                    if (i == associativity - 1)
                    {
                        printf("Address: 0x%s, Set: 0x%s, Miss, Tag: 0x%s\n", address[k], binaryToHex(indexing), binaryToHex(tag));
                        if ((write == 1 && type[k] == '1') || type[k] == '0')
                        {
                            replace = 1;
                        }
                    }
                }
            }
            else
            {
                printf("Address: 0x%s, Set: 0x%s, Miss, Tag: 0x%s\n", address[k], binaryToHex(indexing), binaryToHex(tag));
                strcpy(tags[indexes][i], tag);
                valid[indexes][i] = 1;
                int temp = lru[indexes][i];
                if ((write == 1 && type[k] == '1') || type[k] == '0')
                {
                    lru[indexes][i] = -1;
                    for (int j = 0; j < associativity; j++)
                    {
                        if (lru[indexes][j] < temp)
                        {
                            lru[indexes][j] += 1;
                        }
                    }
                }
                break;
            }
        }
        if (replace == 1)
        {
            int temp;
            if (policy != 2)
            {
                temp = associativity - 1;
            }
            else
            {
                temp = rand() % associativity;
            }
            for (int i = 0; i < associativity; i++)
            {
                if (lru[indexes][i] == temp)
                {
                    strcpy(tags[indexes][i], tag);
                    lru[indexes][i] = -1;
                    for (int j = 0; j < associativity; j++)
                    {
                        if (lru[indexes][j] < temp)
                        {
                            lru[indexes][j] += 1;
                        }
                    }
                    break;
                }
            }
        }
    }
}