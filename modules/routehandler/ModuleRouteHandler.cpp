/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModuleRouteHandler
*/

#include "ModuleRouteHandler.hpp"

ModuleRouteHandler::ModuleRouteHandler()
{
	_name = "RouteHandler";
}

ModuleRouteHandler::~ModuleRouteHandler()
{
}

const std::string &ModuleRouteHandler::getName() const {
	return _name;
}

void ModuleRouteHandler::configureModule(const YAML::Node &n) {
	std::cout << "configuring this module : " << std::endl;
	for (YAML::const_iterator it = n.begin(); it != n.end(); ++it) {
		std::cout << it->first.as<std::string>() << std::endl;
	}
}
void ModuleRouteHandler::callback(zia::api::IZiaMediator &m, std::unique_ptr<zia::api::IEvent> e) {
	if (((zia::api::http::NewHTTPRequest&)(*e)).getRequest().route.find(".php") != std::string::npos) {
		std::cout << "RouteHandler found .php route. Transmitting php request." << std::endl;
		PHPRequest *request = new PHPRequest(((zia::api::http::NewHTTPRequest&)(*e)).getRequest());
		m.emit(std::make_unique<PHPRequest>(*request));
	}
	else if (((zia::api::http::NewHTTPRequest&)(*e)).getRequest().route.find(".html") != std::string::npos) {
		std::cout << "RouteHandler found .html route. Transmitting html request." << std::endl;
		HTMLRequest *request = new HTMLRequest(((zia::api::http::NewHTTPRequest&)(*e)).getRequest());
		m.emit(std::make_unique<HTMLRequest>(*request));
	} else
		std::cout << "RouteHandler found no modules to handle this request. No emits, 404 expected." << std::endl;
}

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &i) {
	std::unique_ptr<ModuleRouteHandler> ret(new ModuleRouteHandler);
	std::cout << "Loading RouteHandler module" << std::endl;
	zia::api::EventConsumer var = std::bind(&ModuleRouteHandler::callback, *ret, std::placeholders::_1, std::placeholders::_2);
	i.registerConsumer(zia::api::EventDescriptor{"NewHTTPRequest"}, var);
	return ret;
}
