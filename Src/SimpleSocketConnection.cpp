#include <SimpleSocketConnection.hpp>
#include <SysUtils.hpp>

namespace ArsLexis
{

    SimpleSocketConnection::SimpleSocketConnection(SocketConnectionManager& manager):
        SocketConnection(manager),
        maxResponseSize_(32768),
        sending_(true),
        chunkSize_(256),
        requestBytesSent_(0)
    {}
    
    status_t SimpleSocketConnection::resizeResponse(String::size_type size)
    {
        status_t error=errNone;
        ErrTry {
            response_.resize(size);
        }
        ErrCatch(ex) {
            error=ex;
        } ErrEndCatch
        return error;
    }


    status_t SimpleSocketConnection::notifyWritable()
    {
        assert(sending_);
        uint_t requestSize=request_.size();
        uint_t requestLeft=requestSize-requestBytesSent_;
        if (requestLeft>chunkSize_)
            requestLeft=chunkSize_;
        uint_t dataSize=0;
        processReadyUiEvents();
        status_t error=socket().send(dataSize, request_.data()+requestBytesSent_, requestLeft, transferTimeout());
//        status_t error=socket().send(dataSize, request_.data()+requestBytesSent_, requestLeft, 0);
        if (errNone==error || netErrWouldBlock==error)
        {
            registerEvent(SocketSelector::eventException);
            requestBytesSent_+=dataSize;
            if (requestBytesSent_==requestSize)
            {
                sending_=false;
                registerEvent(SocketSelector::eventRead);
                error=socket().shutdown(netSocketDirOutput);
                if (error)
                    log().debug()<<_T("notifyWritable(): Socket::shutdown() returned error, ")<<error;
            }
            else
                registerEvent(SocketSelector::eventWrite);                
            error=notifyProgress();
        }
        else
            log().error()<<_T("notifyWritable(): Socket::send() returned error, ")<<error;

        return error;        
    }
    
    status_t SimpleSocketConnection::notifyReadable()
    {
        assert(!sending_);
        uint_t dataSize=0;
        uint_t responseSize=response_.size();
        status_t error=errNone;
        if (responseSize<maxResponseSize_-chunkSize_)
        {
            error=resizeResponse(responseSize+chunkSize_);
            if (errNone!=error)
                goto Exit;            
            processReadyUiEvents();
            error=socket().receive(dataSize, &response_[responseSize], chunkSize_, transferTimeout());
            if (errNone!=error)
                goto Exit;
            assert(dataSize<=chunkSize_);
            resizeResponse(responseSize+dataSize);
            if (0==dataSize)
            {   
                error=notifyFinished();
                abortConnection();
            }
            else
            {
                registerEvent(SocketSelector::eventException);
                registerEvent(SocketSelector::eventRead);
                error=notifyProgress();
            }
        }
        else
            error=errResponseTooLong;
Exit:
        if (errNone!=error)
            log().error()<<_T("notifyReadable(): Socket::receive() returned error, ")<<error;
        return error;
    }
    
    status_t SimpleSocketConnection::notifyFinished()
    {return errNone;}
    
    status_t SimpleSocketConnection::notifyProgress()
    {return errNone;}

    SimpleSocketConnection::~SimpleSocketConnection()
    {}
        
}
