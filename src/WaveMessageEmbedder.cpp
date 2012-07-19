#include "..\include\WaveMessageEmbedder.h"

using std::cout;
using std::endl;

WaveMessageEmbedder::WaveMessageEmbedder(char * m, unsigned int mSize, BYTE * c, DWORD cSize)
{
    int cnt;
    mByteCount = mSize;
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

        message.push_back(bin[8 - i - 1]);

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

int WaveMessageEmbedder::averageNLeftSamples(int n)
{
    int i;
    int sum = 0;
    sampleVector.clear();
    for(  i = current; i < n * 2 + current ; i+=4 )
    {
       sum += cover[i].to_ulong()  + cover[i + 1].to_ulong() * 256;
       sampleVector.push_back(cover[i].to_ulong() + cover[i + 1].to_ulong() * 256 );

    }

    return sum/n;

}

int WaveMessageEmbedder::averageNRightSamples(int n)
{
    int i;
    int sum = 0;
    sampleVector.clear();
    for(  i = current; i < n * 2 + current ; i+=4 )
    {
       sum += cover[i + 2].to_ulong()  + cover[i + 3].to_ulong() * 256;
       sampleVector.push_back(cover[i + 2].to_ulong() + cover[i + 3].to_ulong() * 256 );

    }

    return sum/n;

}

int WaveMessageEmbedder::getlsb(int b,int value)
{
    int i,mask = 0;
    for(i = 0; i < b; i++)
    {
        mask += pow(2,i);

    }

    return value & mask;
}



void WaveMessageEmbedder::embed(int b,int n)
{
    // get b bits from message
    int changeByte;
    int token = getNbitsFromMessage(b);
    int average_lsb = getlsb(b,averageNLeftSamples(n));
    srand(time(NULL));
    while(average_lsb != token)
    {
        changeByte = rand() % n;
        if(average_lsb < token)
        {
            if(cover[current + (4 * changeByte)] != pow(2,b)-1)
            {
                std::bitset<8> temp (cover[current + (4 * changeByte)].to_ulong()+1);
                cover[current + (4 * changeByte)] = temp;
            }
        }else{
            if(cover[current + (4 * changeByte)] != 0)
            {
                std::bitset<8> temp (cover[current + (4 * changeByte)].to_ulong()-1);
                cover[current + (4 * changeByte)] = temp;
            }
        }
        average_lsb = getlsb(b,averageNLeftSamples(n));
    }

    current += 4;
    //int averageandgetlsbs(int d,int e,int f,int g);
    // increment or decrement average until lsb of a = b bit255,255,255,
    //increment current by n * 2
    // e = randomly generate
}

BYTE * WaveMessageEmbedder::getStegoData(int bitsPerSample,int noOfBytesToAverage)
{
    while(current < cByteCount && !message.empty())
        embed(bitsPerSample,noOfBytesToAverage);
    //convert cover to BYTE
    return 0;
}

void WaveMessageEmbedder::extract(int b,int n)
{

    int average_lsb = getlsb(b,averageNLeftSamples(n));

    int i;
    for(i = currentbits ; i < currentbits + b; i ++)
    {

        message[currentbits +b -i - 1]= average_lsb%2;
        average_lsb = average_lsb >> 1;

    }


    currentbits += b;

}

BYTE * WaveMessageEmbedder::getExtractedData(int bitsPerSample,int noOfBytesToAverage)
{
    message.clear();
    currentbits = 0;
    while(currentbits < cByteCount * 8)
        extract(bitsPerSample,noOfBytesToAverage);
    //conver message to BYTE *
    return 0;
}

void WaveMessageEmbedder::print()
{
    int cnt;
    cout << "Message Bytes"  <<endl;

    for( cnt = 0 ; cnt < mByteCount * 8 ; cnt++){
        cout << message[cnt];
        if ( cnt % 8== 7)
            cout << ", " ;
        else if (cnt % 80 == 79)
            cout << endl;
    }
    //cout << message;

    cout << endl;

    cout << "Cover Bytes" << endl;
    for( cnt = 0 ; cnt < cByteCount; cnt++){
        cout<< cover[cnt] << ", ";
        if ( cnt % 4 == 3)
            cout << endl;
    }

}


int main()
{
    char message [] = "a";
    BYTE cover []  = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
    WaveMessageEmbedder w (message,1,cover,32);
    w.print();
    w.getStegoData(2,4);
    w.print();
    w.getExtractedData(2,4);
    w.print();

    return 0;
}
