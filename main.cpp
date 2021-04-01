#include "Server.hpp"

#ifdef linux
	void mySleep(int ms) {
		usleep(ms * 1000);
	}
#elif _WIN32
	void mySleep(int ms) {
		Sleep(ms);
	}
#endif

std::vector<std::string> split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

zia::api::http::HTTPMethod matchMethod(std::string method)
{
	if (method == "GET")
		return zia::api::http::HTTPMethod::GET;
	else if (method == "HEAD")
		return zia::api::http::HTTPMethod::HEAD;
	else if (method == "POST")
		return zia::api::http::HTTPMethod::POST;
	else if (method == "PUT")
		return zia::api::http::HTTPMethod::PUT;
	else if (method == "CONNECT")
		return zia::api::http::HTTPMethod::CONNECT;
	else if (method == "OPTIONS")
		return zia::api::http::HTTPMethod::OPTIONS;
	else if (method == "TRACE")
		return zia::api::http::HTTPMethod::TRACE;
	else if (method == "PATCH")
		return zia::api::http::HTTPMethod::PATCH;
	else
		return zia::api::http::HTTPMethod::GET;
}

zia::api::http::HTTPRequest parse(void *buffer)
{
	zia::api::http::HTTPRequest request;
	std::string buf((char *)buffer);
	auto httpRequest = split(buf, '\n');
	auto status = split(httpRequest[0], ' ');
	request.method = matchMethod(status[0]);
	request.route = status[1];
	int sep = 0;
	for (int i = 1; i < httpRequest.size(); i++) {
		if (httpRequest[i].find(':') == std::string::npos) {
			sep = i;
			break;
		}
		auto dot = httpRequest[i].find(':');
		auto key = httpRequest[i].substr(0, dot);
		auto value = httpRequest[i].substr(dot + 2, httpRequest[i].size());
		request.headers[key] = value;
	}
	for (int i = sep + 1; i < httpRequest.size(); i++)
		request.body += httpRequest[i];
	// std::cout << "Method:" << status[0] << std::endl;
	// std::cout << "Route:" << request.route << std::endl;
	// std::cout << "Headers:" << std::endl;
	// for (auto [key, value]: request.headers)
	// 	std::cout << key << " " << value << std::endl;
	// std::cout << "Body:" << std::endl;
	// std::cout << request.body << std::endl;
	return request;
}

void callback(void *buffer, Session *s, Initializer *ini)
{
	badAPIHTTPRequest request(parse(buffer));
	std::string *tmp = (std::string *)ini->getMediator().processQueue(request).toBuffer();
	s->do_write((void *)tmp->c_str());
}

int main(int ac, char **av) {
	try 
	{
		std::vector<std::unique_ptr<zia::api::IModule>> modules;
		Wrapper eminem;
		Initializer *initializer = new Initializer();
		Server server(av[1], av[2], callback, []{}, initializer);
		server.run();
		while (true) {
			YAML::Node n = configHasChanged("../api/examples/mine.yaml");
			if (n.size() != 0) {
				initializer->clean();
				modules.clear();
				std::cout << "Number of YAML nodes: " << n.size() << std::endl;
				for (YAML::const_iterator it = n.begin(); it != n.end(); ++it) {
					modules.push_back(std::move(eminem.rap(it->first.as<std::string>(), *initializer)));
					// std::cout << it->first.as<std::string>() << std::endl;
				}
			}
			mySleep(100);
		}
		server.stop();
		// for (YAML::const_iterator it = n.begin(); it != n.end(); ++it) {
		// 	std::cout << it->first.as<std::string>() << std::endl;
		// }
	}
	catch(const std::exception& e)
	{
		std::cout << "F" << std::endl;
		std::cerr << e.what() << '\n';
	} catch (...) {
		std::cout << "mdr segfault" << std::endl;
	}
	return 0;
}