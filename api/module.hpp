#ifndef ZIA_MODULE_API_H_
#define ZIA_MODULE_API_H_

#include <deque>
#include <memory>
#include <string>

#include "initializer.hpp"

// From yaml-cpp
namespace YAML
{
class Node;
}

namespace zia::api
{
class IModule
{
public:
    virtual ~IModule(){};

    virtual const std::string &getName() const = 0;
    virtual void configureModule(const YAML::Node &) = 0;
};
#ifdef _WIN32
template class std::unique_ptr<zia::api::IModule>;
#endif
extern "C" std::unique_ptr<zia::api::IModule> load_module(zia::api::IZiaInitializer &);

}    // namespace zia::api

#endif
