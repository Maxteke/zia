/*
** EPITECH PROJECT, 2021
** zia
** File description:
** HTMLRequest
*/

#ifndef HTMLREQUEST_HPP_
#define HTMLREQUEST_HPP_

#include "request.hpp"

class HTMLRequest : public zia::api::IEvent {
	public:
		HTMLRequest(zia::api::http::HTTPRequest request);
		~HTMLRequest();
    	
		const zia::api::EventDescriptor &getDescriptor() const;
		const zia::api::http::HTTPRequest &getRequest() const;

	private:
	    zia::api::http::HTTPRequest _request;
		zia::api::EventDescriptor _descriptor;
};

#endif /* !HTMLREQUEST_HPP_ */
