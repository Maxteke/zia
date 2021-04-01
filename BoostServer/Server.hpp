/*
** EPITECH PROJECT, 2021
** BoostServer
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Session.hpp"
#include <thread>

typedef std::shared_ptr<Session> user;

class Server {
    public:
        Server(const std::string &address, const std::string &port, std::function<void(void *, Session *, Initializer *)> callback, std::function<void()> accept, Initializer *ini);
        ~Server();
        void run();
        void stop();
    private:
        void do_accept();
        void do_wait();
        boost::asio::io_service _io_service;
        boost::asio::signal_set _signals;
        boost::asio::ip::tcp::acceptor _acceptor;
        Initializer *_ini;
        std::function<void(void *, Session *, Initializer *)> _callback;
        std::function<void()> _accept;
        user _user;
        std::thread *_thread;
};

#endif /* !SERVER_HPP_ */
