/*
** EPITECH PROJECT, 2021
** BoostServer
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(const std::string &address, const std::string &port, std::function<void(void *, Session *, Initializer *)> callback, std::function<void()> accept, Initializer *ini)
    : _signals(_io_service), _acceptor(_io_service), _ini(ini), _callback(callback), _accept(accept)
{
    do_wait();
    boost::asio::ip::tcp::resolver resolver(_io_service);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();
    do_accept();
}

Server::~Server()
{
    _user->stop();
    _io_service.stop();
    _thread->join();
}

void Server::run()
{
    _thread = new std::thread([this]{
        _io_service.run();
    });
}

void Server::stop()
{
    _user->stop();
    _io_service.stop();
    _thread->join();
}

void Server::do_accept()
{
    _user.reset(new Session(_io_service, _callback, _ini));
    _acceptor.async_accept(_user->get_socket(),
        [this](std::error_code ec)
        {
            if (!_acceptor.is_open()) {
                std::cout << "Close" << std::endl;
                return;
            }
            if (!ec) {
                std::cout << "IP:" << _user->get_socket().remote_endpoint().address().to_string();
                _user->start();
                _accept();
            }
            else
                std::cout << "Accept Err" << ec.message() << std::endl;
            do_accept();
        });
}

void Server::do_wait()
{
    _signals.async_wait([this](std::error_code, int)
        {
            _io_service.stop();
            _acceptor.close();
        });
}
