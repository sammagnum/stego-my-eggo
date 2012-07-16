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
    public:
        WaveMessageEmbedder(char * message,unsigned int messageSize, BYTE * cover, DWORD coverSize);
        virtual ~WaveMessageEmbedder();
        std::bitset<8> * getMessage() { return message; }
        void setMessageByte(std::bitset<8> val,int cnt) { message[cnt].set(val); }
        std::bitset<8> * getCover() { return cover; }
        void setCoverByte(std::bitset<8> * val) {cover = val; }

};

#endif // WAVEMESSAGEEMBEDDER_H
