#ifndef BADAPI_HPP
#define BADAPI_HPP

#include "request.hpp"
#include "response.hpp"
#include <iostream>

class badAPIHTTPResponse : public zia::api::http::NewHTTPResponse
{
    public:
	    badAPIHTTPResponse();
	    ~badAPIHTTPResponse() {}
        const zia::api::http::HTTPResponse &getResponse() const;
		void setStatusCode(const unsigned short);
		void setStatusMessage(const std::string &);
		void setHeaders(const std::unordered_map<std::string, std::string> &);
		void setBody(const std::string &);
		void setResponse(const zia::api::http::HTTPResponse &r);
		void *toBuffer();
    private:
	    zia::api::http::HTTPResponse _response;
};

class badAPIHTTPRequest : public zia::api::http::NewHTTPRequest {
    public:
		badAPIHTTPRequest(zia::api::http::HTTPRequest request):_request(request) {}
		~badAPIHTTPRequest() {}
        const zia::api::http::HTTPRequest &getRequest();
    private:
	    zia::api::http::HTTPRequest _request;
};

#endif