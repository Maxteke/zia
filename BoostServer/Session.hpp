/*
** EPITECH PROJECT, 2021
** BoostServer
** File description:
** Session
*/

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "zia.hpp"
#include <iostream>
#include <array>


class Session: public std::enable_shared_from_this<Session> {
    public:
        Session(boost::asio::io_service &io_service, std::function<void(void *, Session *, Initializer *)> callback, Initializer *ini);
        void start();
        void stop();
        void do_write(void *buffer);
        boost::asio::ip::tcp::socket &get_socket();
    private:
        void do_read();
        std::array<char, 8192> _buffer;
        boost::asio::ip::tcp::socket _socket;
        boost::asio::io_service::strand _strand;
        Initializer *_ini;
        std::function<void(void *, Session *, Initializer *)> _callback;
};

#endif /* !SESSION_HPP_ */
