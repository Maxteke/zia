#include "badAPI.hpp"

//badAPIHTTPResponse
badAPIHTTPResponse::badAPIHTTPResponse()
{
	_response.status_code = 404;
	_response.status_message = "404 Not found.";
	std::string body = "<html>"
						"<head><title>404 Not Found.</title></head>"
						"<body><h1>404 Not Found.</h1></body>"
						"</html>";
	_response.headers.insert(std::make_pair("Content-Length: ", std::to_string(body.size())));
	_response.headers.insert(std::make_pair("Content-Type: ", "text/html"));
	_response.body = body;
}

const zia::api::http::HTTPResponse &badAPIHTTPResponse::getResponse() const
{
	return _response;
}

void badAPIHTTPResponse::setStatusCode(const unsigned short c) {
	_response.status_code = c;
}
void badAPIHTTPResponse::setStatusMessage(const std::string &s) {
	_response.status_message = s;
}
void badAPIHTTPResponse::setHeaders(const std::unordered_map<std::string, std::string> &m) {
	_response.headers = m;
}
void badAPIHTTPResponse::setBody(const std::string &b) {
	_response.body = b;
}
void badAPIHTTPResponse::setResponse(const zia::api::http::HTTPResponse &r) {
	_response = r;
}

void *badAPIHTTPResponse::toBuffer()
{
	std::string *buffer = new std::string();
	switch (_response.status_code) {
		case 404:
			buffer->append(zia::api::http::not_found);
			break;
		case 200:
			buffer->append(zia::api::http::ok);
			break;
		default:
			buffer->append(zia::api::http::not_found);
	}
	for (auto [key, value]: _response.headers){
		buffer->append(key);
		buffer->append(value);
		buffer->append("\r\n");
	}
	buffer->append("\r\n");
	buffer->append(_response.body);
	return (void *)buffer;
}

//badAPIHTTPRequest
const zia::api::http::HTTPRequest &badAPIHTTPRequest::getRequest()
{
	return _request;
}
