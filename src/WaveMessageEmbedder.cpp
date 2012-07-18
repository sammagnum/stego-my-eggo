#include "..\include\WaveMessageEmbedder.h"

using std::cout;
using std::endl;

WaveMessageEmbedder::WaveMessageEmbedder(char * m, unsigned int mSize, BYTE * c, DWORD cSize)
{
    int cnt;
    mBitCount = mSize;
    cByteCount = cSize;
    std::string sm (m);
    current = 0;

//    std::bitset<(size_t) mSize>  temp (sm);
    cover = new std::bitset<8>  [cSize];
    //message = new std::vector<bool>;
    for( cnt = 0 ; cnt < mSize; cnt++)
        setMessageByte(m[cnt]);

    for( cnt = 0 ; cnt < cSize; cnt++)
        setCoverByte(c[cnt],cnt);

}

WaveMessageEmbedder::~WaveMessageEmbedder()
{
//    delete [] message;
    delete [] cover;
}

void WaveMessageEmbedder::setMessageByte(BYTE val)
{
    int i;
    std::bitset<8> bin (val);
    for(i = 0; i < 8; i++)
    {

        message.push_back(bin[8 - i]);

    }
}

void WaveMessageEmbedder::setCoverByte(BYTE val,int cnt)
{
    std::bitset<8> temp (val);
    cover[cnt] = temp;
}

int WaveMessageEmbedder::getNbitsFromMessage(int n)
{
    int i,token = 0;

    for(i = 0; i < n && !message.empty();i++)
    {
        token += pow(2,n-i-1)*(int)message.front();
        message.erase(message.begin());

    }
    return token;

}

int WaveMessageEmbedder::averageNSamples(int n)
{
    int i;
    int sum = 0;
    for(  i = current; i < n * 2 + current ; i+=2 )
    {
       sum += cover[i].to_ulong() * 256 + cover[i + 1].to_ulong();
    }
    current += n;
    return sum/n;

}

void WaveMessageEmbedder::embed(int b,int n)
{
    // get b bits from message
    int token = getNbitsFromMessage(b);
    averageNSamples(n);
    // a = average next set of  n*2 bytes
    //int averageandgetlsbs(int d,int e,int f,int g);
    // increment or decrement average until lsb of a = b bit
    // e = randomly generate
}

BYTE * WaveMessageEmbedder::getStegoData(int bitsPerSample,int noOfBytesToAverage)
{

    embed(bitsPerSample,noOfBytesToAverage);
    //convert cover to BYTE

}


void WaveMessageEmbedder::print()
{
    int cnt;
    cout << "Message Bytes"  <<endl;

    for( cnt = 0 ; cnt < mBitCount * 8 ; cnt++){
        cout<< message[cnt];
        if ( cnt % 8== 7)
            cout << ", " ;
        else if (cnt % 80 == 79)
            cout << endl;
    }

    cout << endl;

    cout << "Cover Bytes" << endl;
    for( cnt = 0 ; cnt < cByteCount; cnt++){
        cout<< cover[cnt] << ", ";
        if ( cnt % 10 == 9)
            cout << endl;
    }

}


int main()
{
    char message [] = "abcd";
    BYTE cover []  = {1,0,0,64};
    WaveMessageEmbedder w (message,4,cover,4);


    w.print();
    cout << w.averageNSamples(2) << endl;

    //w.print();

    return 0;
}
