/*
** EPITECH PROJECT, 2021
** zia
** File description:
** PHPRequest
*/

#include "PHPRequest.hpp"

PHPRequest::PHPRequest(zia::api::http::HTTPRequest request)
	:_request(request)
{
	_descriptor = zia::api::EventDescriptor{"PHPRequest"};
}

PHPRequest::~PHPRequest()
{
}

const zia::api::EventDescriptor &PHPRequest::getDescriptor() const {
	return _descriptor;
}

const zia::api::http::HTTPRequest &PHPRequest::getRequest() const
{
	return _request;
}
