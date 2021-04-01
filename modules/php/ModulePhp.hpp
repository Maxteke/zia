/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModuleConnection
*/

#ifndef MODULEPHP_HPP_
#define MODULEPHP_HPP_

#include "zia.hpp"
#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>

class ModulePhp : public zia::api::IModule {
	public:
		ModulePhp();
		~ModulePhp();

		const std::string &getName() const;
		void configureModule(const YAML::Node &);
		void callback(zia::api::IZiaMediator &m, std::unique_ptr<zia::api::IEvent> e);
	private:
		std::string _name;
};

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &);

#endif /* !MODULEPHP_HPP_ */
