/*
** EPITECH PROJECT, 2021
** zia
** File description:
** PHPRequest
*/

#ifndef PHPREQUEST_HPP_
#define PHPREQUEST_HPP_

#include "request.hpp"

class PHPRequest : public zia::api::IEvent {
	public:
		PHPRequest(zia::api::http::HTTPRequest request);
		~PHPRequest();
    	
		const zia::api::EventDescriptor &getDescriptor() const;
		const zia::api::http::HTTPRequest &getRequest() const;

	private:
	    zia::api::http::HTTPRequest _request;
		zia::api::EventDescriptor _descriptor;
};

#endif /* !PHPREQUEST_HPP_ */
