/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModuleConnection
*/

#ifndef MODULEHTML_HPP_
#define MODULEHTML_HPP_

#include "zia.hpp"
#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>

class ModuleHtml : public zia::api::IModule {
	public:
		ModuleHtml();
		~ModuleHtml();

		const std::string &getName() const;
		void configureModule(const YAML::Node &);
		void callback(zia::api::IZiaMediator &m, std::unique_ptr<zia::api::IEvent> e);
	private:
		std::string _name;
};

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &);

#endif /* !MODULEHTML_HPP_ */
