/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModuleConnection
*/

#ifndef MODULECONNECTION_HPP_
#define MODULECONNECTION_HPP_

#include "module.hpp"
#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>

class ModuleConnection : public zia::api::IModule {
	public:
		ModuleConnection();
		~ModuleConnection();

		const std::string &getName() const;
		void configureModule(const YAML::Node &);
		void callback(const zia::api::IZiaMediator &m, const zia::api::IEvent &e);
	private:
		std::string _name;
};

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &);

#endif /* !MODULECONNECTION_HPP_ */
