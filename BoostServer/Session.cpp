/*
** EPITECH PROJECT, 2021
** BoostServer
** File description:
** Session
*/

#include "Session.hpp"

Session::Session(boost::asio::io_service &io_service, std::function<void(void *, Session *, Initializer *)> callback, Initializer *ini)
: _socket(io_service), _strand(io_service), _ini(ini), _callback(callback)
{
    _buffer.fill('\0');
}

void Session::start()
{
    do_read();
}

void Session::stop()
{
    _socket.close();
}

void Session::do_write(void *buffer)
{
    auto self(shared_from_this());
    boost::asio::async_write(_socket,
        boost::asio::buffer(buffer, std::strlen((char *)buffer)),
        _strand.wrap([ this , self ](std::error_code ec, std::size_t)
        {
            if (!ec)
            {
                boost::system::error_code ignored_ec;
                _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
            }
            else
                std::cout << "Write: " << ec.message() << std::endl;
        }));
}

boost::asio::ip::tcp::socket &Session::get_socket()
{
    return _socket;
}

void Session::do_read()
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_buffer),
      _strand.wrap([this, self](std::error_code ec, std::size_t bytes_transferred)
      {
          if (!ec)
          {
            _callback(_buffer.data(), this, _ini);
            _buffer.fill('\0');
          }
          else
              std::cout << "Read" << ec.message() << std::endl;
      }));
}
