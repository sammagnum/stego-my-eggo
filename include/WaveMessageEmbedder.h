#ifndef WAVEMESSAGEEMBEDDER_H
#define WAVEMESSAGEEMBEDDER_H

#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>


#include "windows.h"


class WaveMessageEmbedder
{
private:
    std::vector<bool> message;
    std::bitset<8> * cover;
    DWORD mBitCount;
    DWORD cByteCount;
    long long current;

    void setMessageByte(BYTE val);
    void setCoverByte(BYTE val,int cnt);
    void embed(int b,int n);
    int averageandgetlsbs(int d,int e,int f,int g);
    int getNbitsFromMessage(int n);


public:
    int averageNSamples(int n);
    WaveMessageEmbedder(char * message,unsigned int messageSize, BYTE * cover, DWORD coverSize);
    virtual ~WaveMessageEmbedder();
    BYTE * getStegoData(int bitsPerSample,int noOfBytesToAverage);
    void print();


};

#endif // WAVEMESSAGEEMBEDDER_H
