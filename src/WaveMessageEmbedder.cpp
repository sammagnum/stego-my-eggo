#include "..\include\WaveMessageEmbedder.h"

WaveMessageEmbedder::WaveMessageEmbedder(char * message, unsigned int messageSize, BYTE * cover, DWORD coverSize)
{
    this->message = (std::bitset<8> *) malloc(messageSize);


}

WaveMessageEmbedder::~WaveMessageEmbedder()
{
    //dtor
}

int main(){
    char message [] = "abcd";
    BYTE cover []  = {1,255,1,255};
    WaveMessageEmbedder * w  = new WaveMessageEmbedder(message,4,cover,4);
    std::cout<< "test";
    delete w;
    return 0;
}
