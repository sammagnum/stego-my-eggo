#ifndef WAVEMESSAGEEMBEDDER_H
#define WAVEMESSAGEEMBEDDER_H

#include <iostream>
#include <bitset>
#include <fstream>

#include "windows.h"


class WaveMessageEmbedder
{
    public:
        WaveMessageEmbedder(char * message,unsigned int messageSize, BYTE * cover, DWORD coverSize);
        virtual ~WaveMessageEmbedder();
        std::bitset<8> * Getmessage() { return message; }
        void Setmessage(std::bitset<8> * val) { message = val; }
        std::bitset<8> * Getcover() { return cover; }
        void Setcover(std::bitset<8> * val) {cover = val; }
    protected:
    private:
        std::bitset<8> * message;
        std::bitset<8> * cover;
};

#endif // WAVEMESSAGEEMBEDDER_H
