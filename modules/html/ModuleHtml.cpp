/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModuleHtml
*/

#include "ModuleHtml.hpp"

ModuleHtml::ModuleHtml()
{
	_name = "Html";
}

ModuleHtml::~ModuleHtml()
{
}

const std::string &ModuleHtml::getName() const {
	return _name;
}

void ModuleHtml::configureModule(const YAML::Node &n) {
	std::cout << "configuring this module : " << std::endl;
	for (YAML::const_iterator it = n.begin(); it != n.end(); ++it) {
		std::cout << it->first.as<std::string>() << std::endl;
	}
}
void ModuleHtml::callback(zia::api::IZiaMediator &m, std::unique_ptr<zia::api::IEvent> e) {
	if (((HTMLRequest&)(*e)).getRequest().route.find(".html") == std::string::npos) {
		std::cout << "Not a .html route. Why did this happen ? (404 expected...)" << std::endl;
		return ;
	}
	std::cout << "Html module eating this event " << e->getDescriptor().name << std::endl;
	std::cout << "Input file requested: " << ((HTMLRequest&)(*e)).getRequest().route.c_str() << std::endl;
	std::ifstream fileHandler(("../." + ((HTMLRequest&)(*e)).getRequest().route).c_str());
	std::string html(static_cast<std::stringstream const&>(std::stringstream() << fileHandler.rdbuf()).str());
	badAPIHTTPResponse *r = new badAPIHTTPResponse();
	zia::api::http::HTTPResponse response;
	response.status_code = 200;
	response.headers["Content-Type: "] = "text/html";
	response.headers["Content-Length: "] = std::to_string(html.size());
	response.body = html;
	// response.headers["Content-Type: "] = "text/html";
	// response.headers["Content-Length: "] = std::to_string(html.size());
	// response.body = html;
	r->setResponse(response);
	m.emit(std::make_unique<badAPIHTTPResponse>(*r));
	// std::unordered_map<std::string, std::string> headers;
	// _response.headers.insert(std::make_pair("Content-Length: ", std::to_string(body.size())));
	// _response.headers.insert(std::make_pair("Content-Type: ", "text/html"));
	// r.setHeaders(headers);
}

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &i) {
	std::unique_ptr<ModuleHtml> ret(new ModuleHtml);
	std::cout << "Loading Html module (depends on RouteHandler)" << std::endl;
	zia::api::EventConsumer var = std::bind(&ModuleHtml::callback, *ret, std::placeholders::_1, std::placeholders::_2);
	i.registerConsumer(zia::api::EventDescriptor{"HTMLRequest"}, var);
	return ret;
}
