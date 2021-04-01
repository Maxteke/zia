/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModuleConnection
*/

#include "ModuleConnection.hpp"

ModuleConnection::ModuleConnection()
{
	_name = "Connection";
}

ModuleConnection::~ModuleConnection()
{
}

const std::string &ModuleConnection::getName() const {
	return _name;
}

void ModuleConnection::configureModule(const YAML::Node &n) {
	std::cout << "configuring this module : " << std::endl;
	for (YAML::const_iterator it = n.begin(); it != n.end(); ++it) {
		std::cout << it->first.as<std::string>() << std::endl;
	}
}
void ModuleConnection::callback(const zia::api::IZiaMediator &m, const zia::api::IEvent &e) {
	std::cout << "Connection module listening to this event " << e.getDescriptor().name << std::endl;
}

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &i) {
	std::unique_ptr<ModuleConnection> ret(new ModuleConnection);
	std::cout << "Loading connection module" << std::endl;
	zia::api::EventListener var = std::bind(&ModuleConnection::callback, *ret, std::placeholders::_1, std::placeholders::_2);
	i.registerListener(zia::api::EventDescriptor{"NewHTTPRequest"}, var);
	return ret;
}
