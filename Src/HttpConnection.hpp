#ifndef __ARSLEXIS_HTTP_CONNECTION_HPP__
#define __ARSLEXIS_HTTP_CONNECTION_HPP__

#include <SimpleSocketConnection.hpp>
#include <vector>
#include <utility>

namespace ArsLexis {

    class HttpConnection: public SimpleSocketConnection {

    public:
    
        explicit HttpConnection(SocketConnectionManager& manager);
        
        ~HttpConnection();

        void setProtocolVersion(uint_t major, uint_t minor)
        {
            protocolVersionMajor_=major;
            protocolVersionMinor_=minor;
        }
        
        enum RequestMethod {
            methodOptions,
            methodGet,
            methodHead,
            methodPost,
            methodPut,
            methodDelete,
            methodTrace,
            methodConnect
        };

        void setRequestMethod(RequestMethod rm)
        {requestMethod_=rm;}
        
        void setMessageBody(const String& mb)
        {messageBody_=mb;}
        
        void setUri(const String& uri)
        {uri_=uri;}
        
        enum Error {
            errHttpUnknownTransferEncoding=errFirstAvailable,
            errHttpUnsupportedStatusCode,
            errFirstAvailable
        };

    private:
    
        void renderRequestLine(String& out);
        
        uint_t protocolVersionMajor_:4;
        uint_t protocolVersionMinor_:4;
        RequestMethod requestMethod_:8;
        
        bool insideResposeHeaders_:1;
        bool insideResponseBody_:1;
        bool chunkedEncoding_:1;
        bool skippingInfoResponse_:1;
        
        String uri_;
        String messageBody_;
        typedef std::pair<String, String> RequestField_t;
        typedef std::vector<RequestField_t> RequestFields_t;
        RequestFields_t requestFields_;

        void renderHeaderField(String& out, const RequestField_t& field);
        
        void commitRequest();
        
    protected:
    
        virtual Err handleResponseField(const String& field, const String& value);
        
        virtual Err handleStatusLine(uint_t versionMajor, uint_t versionMinor, uint_t statusCode, const String& reason);
        
        virtual Err handleBodyIncrement(const String& body, ulong_t& length, bool finish)
        {return errNone;}      

    };

}

#endif