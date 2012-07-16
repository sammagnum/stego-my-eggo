#include "..\include\WaveMessageEmbedder.h"

WaveMessageEmbedder::WaveMessageEmbedder(char * m, unsigned int mSize, BYTE * c, DWORD cSize)
{
    int cnt = 0;
    mByteCount = mSize;
    cByteCount =
    message = new std::bitset<8>  [mSize];
    cover = new std::bitset<8>  [cSize];
    for( cnt = 0 ; cnt < mSize; cnt++)
        setMessageByte(m[cnt],cnt);
}

WaveMessageEmbedder::~WaveMessageEmbedder()
{
    delete [] message;
    delete [] cover;
}

WaveMessageEmbedder::print()
{
    cout << "Message Bytes" << endl;
    for( cnt = 0 ; cnt < mByteCount; cnt++)
        std::cout<< message[cnt] << ", "

}

int main()
{
    char message [] = "abcd";
    BYTE cover []  = {1,255,1,255};
    WaveMessageEmbedder * w  = new WaveMessageEmbedder(message,4,cover,4);
    std::cout<< "test";
    delete w;
    return 0;
}
