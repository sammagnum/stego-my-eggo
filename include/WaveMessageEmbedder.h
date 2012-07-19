#ifndef WAVEMESSAGEEMBEDDER_H
#define WAVEMESSAGEEMBEDDER_H

#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "windows.h"


class WaveMessageEmbedder
{
private:
    std::vector<bool> message;
    std::bitset<8> * cover;
    //std::vector<BYTE> extractm;
    DWORD mByteCount;
    DWORD cByteCount;
    long long current;
    long long currentbits;
    std::vector<int> sampleVector;
    void embed(int b,int n);
    void setMessageByte(BYTE val);
    void setCoverByte(BYTE val,int cnt);
    int getlsb(int b,int value);
    int averageandgetlsbs(int d,int e,int f,int g);
    int getNbitsFromMessage(int n);
    int averageNLeftSamples(int n);
    int averageNRightSamples(int n);
    void extract(int b,int n);



public:

    //insert overloaded constructor with cover only for extraction
    WaveMessageEmbedder(char * message,unsigned int messageSize, BYTE * cover, DWORD coverSize);
    virtual ~WaveMessageEmbedder();
    BYTE * getStegoData(int bitsPerSample,int noOfBytesToAverage);
    BYTE * getExtractedData(int bitsPerSample,int noOfBytesToAverage);
    void print();


};

#endif // WAVEMESSAGEEMBEDDER_H
