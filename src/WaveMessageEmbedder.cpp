#include "..\include\WaveMessageEmbedder.h"

using std::cout;
using std::endl;

WaveMessageEmbedder::WaveMessageEmbedder(char * m, unsigned int mSize, BYTE * c, DWORD cSize)
{
    int cnt;
    mByteCount = mSize;
    cByteCount = cSize;
    message = new std::bitset<8>  [mSize];
    cover = new std::bitset<8>  [cSize];

    for( cnt = 0 ; cnt < mSize; cnt++)
        setMessageByte(m[cnt],cnt);

    for( cnt = 0 ; cnt < cSize; cnt++)
        setCoverByte(c[cnt],cnt);

}

WaveMessageEmbedder::~WaveMessageEmbedder()
{
    delete [] message;
    delete [] cover;
}

void WaveMessageEmbedder::print()
{
    int cnt;
    cout << "Message Bytes" << endl;
    for( cnt = 0 ; cnt < mByteCount; cnt++){
        cout<< message[cnt] << ", ";
        if ( cnt % 10 == 0)
            cout << endl;
    }

    cout << "Cover Bytes" << endl;
    for( cnt = 0 ; cnt < cByteCount; cnt++){
        cout<< cover[cnt] << ", ";
        if ( cnt % 10 == 0)
            cout << endl;
    }

}

void WaveMessageEmbedder::setMessageByte(BYTE val,int cnt)
{
    std::bitset<8> temp (val);
    message[cnt] = temp;
}

void WaveMessageEmbedder::setCoverByte(BYTE val,int cnt)
{
    std::bitset<8> temp (val);
    cover[cnt] = temp;
}
int main()
{
    char message [] = "abcd";
    BYTE cover []  = {1,255,1,255};
    WaveMessageEmbedder w (message,4,cover,4);
    w.print();

    return 0;
}
