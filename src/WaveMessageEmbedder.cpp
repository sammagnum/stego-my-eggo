#include "../include/WaveMessageEmbedder.h"
#include <iomanip>

using std::setw;
using std::right;
using std::cout;
using std::endl;

WaveMessageEmbedder::WaveMessageEmbedder(char * m, unsigned int mSize, BYTE * c, DWORD cSize)
{
    int cnt;
    mByteCount = mSize;
    cByteCount = cSize;
    std::string sm (m);
    current = 0;
    lsb_bits = 0;

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

    for(i = 0; i < n ;i++)
    {
        cout << "message.front " << message.front() << "current: " << current << endl;
        token += pow(2,n-i-1)*(int)message.front();
        message.erase(message.begin());

    }
    return token;

}

int WaveMessageEmbedder::averageNLeftSamples(int n)
{
    int i;
    int sum = 0;
    //sampleVector.clear();
    for(  i = current; i < n * 4 + current ; i+=4 )
    {
        //cout <<"in func:" << cover[i].to_ulong()  + cover[i + 1].to_ulong() * 256 << endl;
       sum += cover[i].to_ulong()  + cover[i + 1].to_ulong() * 256;
       //sampleVector.push_back(cover[i].to_ulong() + cover[i + 1].to_ulong() * 256 );

    }

    return sum/n;

}

int WaveMessageEmbedder::averageNRightSamples(int n)
{
    int i;
    int sum = 0;
    sampleVector.clear();
    for(  i = current; i < n * 4 + current ; i+=4 )
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
    int cnt;
    changeByte = 0;

    bool allones;
    //srand(time(NULL));

    while(changeByte < n){
        cnt =  0;
        while(cnt < b){
        cover[current + (4 * changeByte)][cnt]= 0;
            cnt++;
        }
        changeByte++;
    }
    changeByte = 0;
    while(average_lsb != token)
    {

        //changeByte = rand() % n;
        //cout << "random:" << changeByte << endl;
        //if (average_lsb < token)
        //{
        cnt = 0;
        while( cnt < b)
        {
            //allones = false;
            if(cover[current + (4 * changeByte)][cnt]== 0){
                cover[current + (4 * changeByte)][cnt]=1;
                //for(cnt = 0; cnt < n; cnt ++)
                    //printf("%x, ",cover[current + (4 * cnt)].to_ulong());
                //cout << endl;
                break;
            }
           // allones = true;
            cnt ++;

        }
       /* if(allones)
            {
            cnt = 0;
            while( cnt < b)
            {
                cover[current + (4 * changeByte)][cnt]=0;
                cnt++;
            }
        }*/

        average_lsb = getlsb(b,averageNLeftSamples(n));
        changeByte++;
        changeByte%=n;
        //cout<< "during averaging: average_lsb = " << average_lsb << "token = " << token <<endl ;
        //for(cnt = 0; cnt < n; cnt ++)
            //cout<<getlsb(b,cover[current + (4 * cnt)].to_ulong())<<",";

    }
     cout<< "\nembedded token: average_lsb = " << average_lsb << "token = " << token <<endl ;

    current += 4 * n;
    //int averageandgetlsbs(int d,int e,int f,int g);
    // increment or decrement average until lsb of a = b bit255,255,255,
    //increment current by n * 2
    // e = randomly generate
}

BYTE * WaveMessageEmbedder::getStegoData(int bitsPerSample,int noOfBytesToAverage)
{
    lsb_bits = bitsPerSample;
    while(current < cByteCount && !message.empty())
        embed(bitsPerSample,noOfBytesToAverage);
    //convert cover to BYTE
    return 0;
}

void WaveMessageEmbedder::extract(int b,int n)
{

    int average_lsb = getlsb(b,averageNLeftSamples(n));
    std::vector<int> temp;
    cout<< "\non extraction: average_lsb = " << average_lsb << "current = " << current <<endl ;
    int i;
    for(i = currentbits ; i < currentbits + b; i ++)
    {

        temp.insert(temp.begin(),average_lsb%2);
        average_lsb = average_lsb >> 1;
       // cout<<(bool)temp[i];

    }
    for( i = 0; i < temp.size(); i++)
    {
        message.push_back((bool)temp[i]);
    }

    temp.clear();
    current += 4 *n;
    currentbits += b;

}

BYTE * WaveMessageEmbedder::getExtractedData(int bitsPerSample,int noOfBytesToAverage)
{
    lsb_bits = bitsPerSample;
    message.clear();
    current = 0;
    currentbits = 0;
    while(current < cByteCount && currentbits < cByteCount * 8)
        extract(bitsPerSample,noOfBytesToAverage);
    //conver message to BYTE *
    return 0;
}

void WaveMessageEmbedder::print()
{
    int cnt;
    cout << "Message Bits"  <<endl;

    for( cnt = 0 ; cnt < message.size() ; cnt++){
        cout << (bool)message[cnt];
        if ( cnt % 8== 7)
            cout << ", " ;
        else if (cnt % 80 == 79)
            cout << endl;
    }
    //cout << message;

    cout << endl;

    cout << "Cover Bytes" << endl;
    cout << "Left low     Left High      Right Low      Right High" <<endl;
    for( cnt = 0 ; cnt < cByteCount; cnt++){
        if( cnt % 4 == 2 )
        cout << ",  ";

        cout<<setw(10)<< right << cover[cnt].to_ulong() << ".." << getlsb(lsb_bits,cover[cnt].to_ulong()) ;
        if ( cnt % 4 == 3)
            cout << endl;
    }

        cout << endl;
            cout << endl;
                cout << endl;

}


int main()
{
    char message [] = "a";
    BYTE cover [64];
    srand(time(NULL));
    int i;
    for(i = 0; i < 64; i ++)
        cover[i] = rand() % 256;
    WaveMessageEmbedder w (message,1,cover,64);
    //cout << w.averageNLeftSamples(4)<< endl;
    //cout << w.getlsb(2,w.averageNLeftSamples(4)) << endl;
    w.print();
    w.getStegoData(2,4);
    w.print();
    w.getExtractedData(2,4);
    w.print();




    return 0;
}
