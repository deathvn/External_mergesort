#include <bits/stdc++.h>
using namespace std;

FILE* openFile(const char* fileName, char* mode)
{
    FILE* fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

int main()
{
    //int num_ways = 10;

    for (int ii=1; ii<=9; ++ii)
    {

        int Size = ii*10*pow(10, 3);

        //int run_size = 100000;
        string S = "input";
        S +=  (ii+'0');
        S +=  "0K.bin";

        const char* input_file = S.c_str();

        FILE* in = openFile(input_file, "w");

        srand(time(NULL));

        for (int i = 0; i < Size; i++)
            fprintf(in, "%f ", double (rand()) / double (rand()));

        fclose(in);
    }

    return 0;
}
