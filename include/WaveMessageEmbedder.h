#ifndef WAVEMESSAGEEMBEDDER_H
#define WAVEMESSAGEEMBEDDER_H

#include <iostream>
#include <bitset>
#include <fstream>

#include "windows.h"


class WaveMessageEmbedder
{
    private:
        std::bitset<8> * message;
        std::bitset<8> * cover;
        DWORD mByteCount;
        DWORD cByteCount;

        void setMessageByte(BYTE val,int cnt);
        void setCoverByte(BYTE val,int cnt);

    public:
        WaveMessageEmbedder(char * message,unsigned int messageSize, BYTE * cover, DWORD coverSize);
        virtual ~WaveMessageEmbedder();
        std::bitset<8> * getMessage() { return message; }
        std::bitset<8> * getCover() { return cover; }
        void print();


};

#endif // WAVEMESSAGEEMBEDDER_H
