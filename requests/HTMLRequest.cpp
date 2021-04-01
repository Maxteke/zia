/*
** EPITECH PROJECT, 2021
** zia
** File description:
** HTMLRequest
*/

#include "HTMLRequest.hpp"

HTMLRequest::HTMLRequest(zia::api::http::HTTPRequest request)
	:_request(request)
{
	_descriptor = zia::api::EventDescriptor{"HTMLRequest"};
}

HTMLRequest::~HTMLRequest()
{
}

const zia::api::EventDescriptor &HTMLRequest::getDescriptor() const {
	return _descriptor;
}

const zia::api::http::HTTPRequest &HTMLRequest::getRequest() const
{
	return _request;
}
