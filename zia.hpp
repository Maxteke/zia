#ifndef ZIA_HPP
#define ZIA_HPP
// #include "connection.hpp"
// #include "routing.hpp"
#include "HTMLRequest.hpp"
#include "PHPRequest.hpp"
#include "badAPI.hpp"
#include <boost/asio.hpp>
#include "mediator.hpp"
#include "module.hpp"
#include <yaml-cpp/yaml.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


enum OS_TYPE { Linux, Windows };
#ifdef linux
	#include <dlfcn.h>
	#include <unistd.h>
	#define WRAPPER_OS Linux
#elif _WIN32
	#include <windows.h>
	#define WRAPPER_OS Windows
#else
#endif

YAML::Node configHasChanged(const std::string &filename);

std::string GetLastErrorAsString();

typedef std::unique_ptr<zia::api::IModule> (*loadmodule)(zia::api::IZiaInitializer &);

class Mediator : public zia::api::IZiaMediator
{
    public:
	    Mediator() {}
	    ~Mediator() {}

        void emit(std::unique_ptr<zia::api::IEvent> e);
	    int getResponses();
	    badAPIHTTPResponse processQueue(badAPIHTTPRequest r);
        void registerConsumer(const std::string &event, zia::api::EventConsumer consumer);
        void registerListener(const std::string &event, zia::api::EventListener listener);
		void clean() {
			_consumers.clear();
			_listeners.clear();
			_queue.clear();
		}
    private:
	    std::vector<std::pair<std::string, zia::api::EventConsumer>> _consumers;
	    std::vector<std::pair<std::string, zia::api::EventListener>> _listeners;
	    std::vector<std::unique_ptr<zia::api::IEvent>> _queue;
};

class Initializer : public zia::api::IZiaInitializer
{
    public:
	    Initializer() : _mediator(Mediator()) {};
	    ~Initializer() {};

        void registerConsumer(const zia::api::EventDescriptor &event, zia::api::EventConsumer consumer);
        void registerListener(const zia::api::EventDescriptor &event, zia::api::EventListener listener);
		Mediator &getMediator();
		void clean() {
			_mediator.clean();
		}
    private:
    	Mediator _mediator;
};

class Wrapper
{
    public:
	    Wrapper(OS_TYPE os = WRAPPER_OS) : _os(os){};
	    ~Wrapper() {};

	    std::unique_ptr<zia::api::IModule> rap(const std::string &moduleName, Initializer &init);
    private:
	    OS_TYPE _os;
};

#endif