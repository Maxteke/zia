#include "zia.hpp"

YAML::Node configHasChanged(const std::string &filename) {
	static std::string lastFileContent = "";
	std::ifstream fileHandler(filename.c_str());
	std::string content(static_cast<std::stringstream const&>(std::stringstream() << fileHandler.rdbuf()).str());
	if (content != lastFileContent) {
		std::cout << "Change detected in config file\t";
		lastFileContent = content;
		try
		{
			YAML::Node n = YAML::LoadFile(filename);
			fileHandler.close();
			std::cout << "Valid file." << std::endl;
			return n;
		}
		catch(const std::exception& e)
		{
			std::cerr << "YAML parsing failed. Syntax still invalid:\t";
			std::cerr << e.what() << std::endl;
		}
	}
	fileHandler.close();
	YAML::Node r;
	return r;
}

#ifdef linux
std::string GetLastErrorAsString() {
	return std::string("Not implement on linux yet...\tF\n");
}
#elif _WIN32
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}
#else
#endif
//Mediator
void Mediator::emit(std::unique_ptr<zia::api::IEvent> e)
{
	_queue.push_back(std::move(e));
}

int Mediator::getResponses()
{
	int r = 0;
	for (int i = 0; i < _queue.size(); i++)
		if (_queue[i]->getDescriptor().name == "NewHTTPResponse")
			r++;
	return r;
}

badAPIHTTPResponse Mediator::processQueue(badAPIHTTPRequest r)
{
	_queue.clear();
	_queue.push_back(std::make_unique<badAPIHTTPRequest>(r));
	while (_queue.size() - getResponses() > 0) {
		for (size_t j = 0; j < _listeners.size(); j++) {
			if (_listeners[j].first == _queue[0]->getDescriptor().name) {
				_listeners[j].second(*this, *(_queue[0]));
			}
		}
		for (size_t j = 0; j < _consumers.size(); j++) {
			if (_consumers[j].first == _queue[0]->getDescriptor().name) {
				_consumers[j].second(*this, std::move(_queue[0]));
				break;
			}
		}
		_queue.erase(_queue.begin());
	}
	if (_queue.size() < 1) {
		badAPIHTTPResponse r;
		std::cout << "404 Response." << std::endl;
		return r;
	} else {
		std::cout << "Queue[0] Response." << std::endl;
		return *((badAPIHTTPResponse*)_queue[0].get());
	}
}

void Mediator::registerConsumer(const std::string &event, zia::api::EventConsumer consumer)
{
	_consumers.push_back(std::pair<std::string, zia::api::EventConsumer>(event, consumer));
}

void Mediator::registerListener(const std::string &event, zia::api::EventListener listener)
{
	_listeners.push_back(std::pair<std::string, zia::api::EventListener>(event, listener));
}

//Initializer
void Initializer::registerConsumer(const zia::api::EventDescriptor &event, zia::api::EventConsumer consumer)
{
	std::cout << "Registering consumer: " << event.name << std::endl;
	_mediator.registerConsumer(std::string(event.name), consumer);
}

void Initializer::registerListener(const zia::api::EventDescriptor &event, zia::api::EventListener listener)
{
	std::cout << "Registering listener: " << event.name << std::endl;
	_mediator.registerListener(std::string(event.name), listener);
}

Mediator &Initializer::getMediator()
{
	return _mediator;
}

//Wrapper
std::unique_ptr<zia::api::IModule> Wrapper::rap(const std::string &moduleName, Initializer &init)
{
	// std::unique_ptr<zia::api::IModule> r;
	if (_os == Linux) {
#ifdef linux
		void *handle = dlopen(("bin/lib" + moduleName + ".so").c_str(), RTLD_NOW);
		if (!handle) {
			std::cerr << "Loading library module failed. Verify file path." << std::endl;
			return nullptr;
		}
		loadmodule f = (loadmodule)dlsym(handle, "load_module");
		if (!f) {
			std::cerr << "Loading load_module failed. Are you sure it's in the library ?" << std::endl;
			return nullptr;
		}
		std::unique_ptr<zia::api::IModule> result = f(init);
		// dlclose(handle); 
		return result;
#endif
	} else if (_os == Windows) {
#ifdef _WIN32
		HMODULE mod = LoadLibraryA(("bin/" + moduleName + ".dll").c_str());
		if (!mod) {
			std::cerr << "Loading library module failed. Verify file path." << std::endl;
			std::cerr << GetLastErrorAsString() << std::endl;
			return nullptr;
		}
		FARPROC proc = GetProcAddress(mod, "load_module");
		if (!proc) {
			std::cerr << "Loading load_module failed. Are you sure it's in the library ?" << std::endl;
			std::cerr << GetLastErrorAsString() << std::endl;
			return nullptr;
		}
		std::unique_ptr<zia::api::IModule> result = ((loadmodule)proc)(init);
		// FreeLibrary(mod);
		return result;
#endif
	}
    return nullptr;
};