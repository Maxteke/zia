/*
** EPITECH PROJECT, 2021
** zia
** File description:
** ModulePhp
*/

#include "ModulePhp.hpp"

#ifdef linux
std::string exec(const char* cmd) {
    std::array<char, 1024> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
#elif _WIN32
std::string exec(const char* cmd) {
    std::array<char, 1024> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
#else
#endif

ModulePhp::ModulePhp()
{
	_name = "Php";
}

ModulePhp::~ModulePhp()
{
}

const std::string &ModulePhp::getName() const {
	return _name;
}

void ModulePhp::configureModule(const YAML::Node &n) {
	std::cout << "configuring this module : " << std::endl;
	for (YAML::const_iterator it = n.begin(); it != n.end(); ++it) {
		std::cout << it->first.as<std::string>() << std::endl;
	}
}
void ModulePhp::callback(zia::api::IZiaMediator &m, std::unique_ptr<zia::api::IEvent> e) {
	if (((PHPRequest&)(*e)).getRequest().route.find(".php") == std::string::npos) {
		std::cout << "Not a .php route. Why did this happen ? (404 expected...)" << std::endl;
		return ;
	}
	std::cout << "Php module eating this event " << e->getDescriptor().name << std::endl;
	std::cout << "Input file requested: " << ((PHPRequest&)(*e)).getRequest().route.c_str() << std::endl;
	std::string html = exec(("php-cgi ../." + ((PHPRequest&)(*e)).getRequest().route).c_str()) + '\n';
	badAPIHTTPResponse *r = new badAPIHTTPResponse();
	zia::api::http::HTTPResponse response;
	response.status_code = 200;
	size_t start = 0U;
	size_t end = html.find('\n');
	std::string cursor = html.substr(start, end-start);
	while (cursor != "\r") {
		std::cout << cursor << std::endl;
		std::string key = cursor.substr(0U, cursor.find(':'));
		std::string value = cursor.substr(cursor.find(':')+1, cursor.size() - cursor.find(':') - 1);
		response.headers[key] = value;
		start = end + 1;
		end = html.find('\n', start);
		cursor = html.substr(start, end-start);
	}
	if (end >= html.size()) {
		response.body = "Body failed.";
	} else {
		response.body = html.substr(end, html.size()-end);
	}
	r->setResponse(response);
	m.emit(std::make_unique<badAPIHTTPResponse>(*r));
}

extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &i) {
	std::unique_ptr<ModulePhp> ret(new ModulePhp);
	std::cout << "Loading Php module (depends on RouteHandler)" << std::endl;
	zia::api::EventConsumer var = std::bind(&ModulePhp::callback, *ret, std::placeholders::_1, std::placeholders::_2);
	i.registerConsumer(zia::api::EventDescriptor{"PHPRequest"}, var);
	return ret;
}
