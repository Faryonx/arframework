#include <Text.hpp>

#ifdef __MWERKS__
# pragma pcrelconstdata on
#endif

namespace ArsLexis 
{

#if defined(_WIN32)    
    char_t PalmToUnicode[160-128] = 
    {
     8364, 129 , 8218,  131, 8222, 8230, 8224, 8225,  710, 8240, 
      352, 8249,  338, 9674,  142,  143,  144, 8216, 8217, 8220, 
     8221, 8226, 8211, 8212, 8776, 8482,  353, 8250,  339,  157, 
      158,  159
    };

    char_t UnicodeToPalm[24][2] = 
    {
      338, 140,  339, 156,  352, 138,  353, 154,  710, 136, 
     8211, 150, 8212, 151, 8216, 145, 8217, 146, 8218, 130, 
     8220, 147, 8221, 148, 8222, 132, 8224, 134, 8225, 135,
     8226, 149, 8230, 133, 8240, 137, 8249, 139, 8250, 155,
     8364, 128, 8482, 153, 8776, 152, 9674, 141
    };
    struct CharToByte
    { 
        char operator()(char_t in) 
        {   
            if(in<=255) //Is it common code ?
                return char(in);
            else //It's unicode char
            {
                //Maybe binary search - MS doesn't support 
                //as always standard and bsearch
                for(int i=0; i<24; i++)
                    if(UnicodeToPalm[i][0]==in)
                        return (char)UnicodeToPalm[i][1];
                assert(false); //we never shall reach this point
                return 0;
            }
        }
    };
    
    struct ByteToChar 
    { 
        char_t operator()(unsigned char in) {
            if((in>=128)&&(in<=159))
                return PalmToUnicode[in-128];
            else
                return char_t(in);
        }
    };
#endif
    
    void TextToByteStream(const String& inTxt, NarrowString& outStream)
    {
#if defined(_WIN32)
        /*Why this doesn't work I have no idea
        char *out=NULL;
        int size = WideCharToMultiByte(CP_OEMCP, WC_SEPCHARS, inTxt.c_str(), -1, out, 0, NULL,NULL);
        out=new char[size];
        WideCharToMultiByte(CP_OEMCP, WC_SEPCHARS, inTxt.c_str(), -1, out, size, NULL,NULL);
        outStream.assign(out);
        delete []out;*/
        outStream.reserve(inTxt.length());
        std::transform(inTxt.begin(), inTxt.end(), std::back_inserter(outStream), CharToByte());
#else
        outStream.assign(inTxt);
#endif
    }

    void ByteStreamToText(const NarrowString& inStream, String& outTxt)
    {
#if defined(_WIN32)
        /*Why this doesn't work I have no idea
        char_t *out=NULL;
        int size = MultiByteToWideChar(CP_OEMCP, MB_COMPOSITE, inStream.c_str(), -1, out, 0);
        out=new char_t[size];
        MultiByteToWideChar(CP_OEMCP, MB_COMPOSITE, inStream.c_str(), -1, out, size);
        outTxt.assign(out);
        delete []out;*/
        outTxt.reserve(inStream.length());
        std::transform(inStream.begin(), inStream.end(), std::back_inserter(outTxt), ByteToChar());
#else
        outTxt.assign(inStream);
#endif
    }

    bool startsWith(const String& text, const char_t* start, uint_t startOffset)
    {
        while (startOffset<text.length() && *start)
        {
            if (*start==text[startOffset])
            {
                ++start;
                ++startOffset;
            }
            else
                return false;
        }
        return 0==*start;
    }
    
    bool startsWith(const String& text, const String& start, uint_t startOffset)
    {
        uint_t pos=0;
        while (startOffset<text.length() && pos<start.length())
        {
            if (text[startOffset]==start[pos])
            {
                ++startOffset;
                ++pos;
            }
            else
                return false;
        }
        return pos==start.length();
    }
    
    bool startsWithIgnoreCase(const String& text, const char_t* start, uint_t startOffset)
    {
        while (startOffset<text.length() && *start)
        {
            if (toLower(*start)==toLower(text[startOffset]))
            {
                ++start;
                ++startOffset;
            }
            else
                return false;
        }
        return 0==*start;
    }

    bool equalsIgnoreCase(const char_t* s1start, const char_t* s1end, const char_t* s2start, const char_t* s2end)
    {
        while (s1start!=s1end && s2start!=s2end)
        {
            if (toLower(*s1start)==toLower(*s2start))
            {
                ++s1start;
                ++s2start;
            }
            else 
                return false;
        }
        return (s1start==s1end && s2start==s2end);
    }
    
}

ArsLexis::status_t ArsLexis::numericValue(const char_t* begin, const char_t* end, long& result, uint_t base)
{
    ArsLexis::status_t error=errNone;
    bool     negative=false;
    long     res=0;
    String   numbers(_T("0123456789abcdefghijklmnopqrstuvwxyz"));
    char_t   buffer[2];

    if (begin>=end || base>numbers.length())
    {    
        error=sysErrParamErr;
        goto OnError;           
    }
    if (*begin==_T('-'))
    {
        negative=true;
        if (++begin==end)
        {
            error=sysErrParamErr;
            goto OnError;           
        }
    }           
    buffer[1]=chrNull;
    while (begin!=end) 
    {
        // TODO: will it work with unicode on WINCE?
        buffer[0]=toLower(*(begin++));
        String::size_type num=numbers.find(buffer);
        if (num>=base)
        {   
            error=sysErrParamErr;
            break;
        }
        else
        {
            res*=base;
            res+=num;
        }
    }
    if (!error)
       result=res;
OnError:
    return error;    
}

#define HEX_DIGITS _T("0123456789ABCDEF")

static ArsLexis::char_t numToHex(int num)
{
    assert( (num>=0) && (num<16) );
    ArsLexis::char_t c = HEX_DIGITS[num];
    assert( '\0' != c );
    return c;
}

// encode binary blob of blobSize size and put the result in the out string
void ArsLexis::HexBinEncodeBlob(unsigned char *blob, int blobSize, ArsLexis::String& out)
{
    out.clear();
    out.reserve(blobSize*2); // 2 chars per each byte

    unsigned char b;
    char_t        hexChar;
    for (int i=0; i<blobSize; i++)
    {
        b = blob[i];
        hexChar = numToHex(b / 16);
        out.append(1,hexChar);
        hexChar = numToHex(b % 16);
        out.append(1,hexChar);
    }
}

ArsLexis::String ArsLexis::hexBinEncode(const String& in)
{
    String out;
    out.reserve(2*in.length());
    String::const_iterator it=in.begin();
    String::const_iterator end=in.end();
    char_t hexChar;
    while (it!=end)
    {
        // at some point this was char_t (i.e. signed char on Palm)
        // and it caused bugs due to b being promoted to unsigned int, which
        // was negative for b values > 127
        unsigned char b=*(it++);
        hexChar = numToHex(b / 16);
        out.append(1,hexChar);
        hexChar = numToHex(b % 16);
        out.append(1,hexChar);
    }
    return out;
}

namespace {

    inline static void CharToHexString(ArsLexis::char_t* buffer, ArsLexis::char_t chr)
    {
        buffer[0]=HEX_DIGITS[chr/16];
        buffer[1]=HEX_DIGITS[chr%16];
    }

}

void ArsLexis::urlEncode(const ArsLexis::String& in, ArsLexis::String& out)
{
    char_t *hexNum = _T("%  ");

    const char_t* begin=in.data();
    const char_t* end=begin+in.length();
    out.resize(0);
    out.reserve(in.length());

    while (begin!=end)
    {        
        char_t chr=*begin++;
        if ((chr>=_T('a') && chr<=_T('z')) || 
            (chr>=_T('A') && chr<=_T('Z')) || 
            (chr>=_T('0') && chr<=_T('9')) || 
            _T('-')==chr || _T('_')==chr || _T('.')==chr || _T('!')==chr || 
            _T('~')==chr || _T('*')==chr || _T('\'')==chr || _T('(')==chr || _T(')')==chr)
            out.append(chr, 1);
        else
        {
            CharToHexString(hexNum+1, chr);
            out.append(hexNum, 3);
        }
    }
}

void ArsLexis::removeNonDigits(const char_t* in, uint_t len, ArsLexis::String& out)
{
    out.resize(0);
    out.reserve(len);

    while (len>0)
    {
        if (isDigit(*in))
            out.append(1, *in);
        ++in;
        --len;
    }
}

// format number num so that they easier to read e.g. turn '10343' into '10.343'
// i.e. insert (locale-dependent) thousand separator in apropriate places
// put the result in buffer buf of length bufSize. Buffer must be big enough
// for the result.
int ArsLexis::formatNumber(long num, char_t* buf, int bufSize)
{
    char thousand=',';
 
#if defined(_PALM_OS)
    char dontMind;
    NumberFormatType nf=static_cast<NumberFormatType>(PrefGetPreference(prefNumberFormat));
    LocGetNumberSeparators(nf, &thousand, &dontMind);
#endif 
   
    char_t buffer[32];
    int len = tprintf(buffer, _T("%ld"), num);
    int lenOut = len + ((len-1)/3);  // a thousand separator every 3 chars
    assert(bufSize>=lenOut+1);
    // copy str in buffer to output buf from the end, adding thousand separator every 3 chars
    char_t *tmp = buffer+len;
    assert( '\0' == *tmp );
    char_t *out = buf+lenOut;
    int toDot = 4; // 3 + 1 for trailing '\0'
    while (true)
    {
        *out = *tmp;
        if (tmp==buffer)
            break;
        --out;
        --tmp;
        --toDot;
        if (0==toDot)
        {
            toDot = 3;
            *out-- = thousand;  // don't put separator if this is the last number
        }
    }
    assert(out==buf);
    return lenOut;
}

