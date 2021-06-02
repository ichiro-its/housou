// Copyright (c) 2021 ICHIRO ITS
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef MUSEN__TCP__SERVER_HPP_
#define MUSEN__TCP__SERVER_HPP_

#include <memory>
#include <string>

#include "../socket/tcp_socket.hpp"
#include "../receiver.hpp"
#include "../sender.hpp"

namespace musen
{

class Server : public Sender, public Receiver
{
public:
  explicit Server(
    const int & port, std::shared_ptr<TcpSocket> tcp_socket = std::make_shared<TcpSocket>());

  bool connect();
  bool disconnect();

  size_t send_raw(const char * data, const size_t & length) override;
  size_t receive_raw(char * data, const size_t & length) override;

  std::shared_ptr<TcpSocket> get_tcp_socket() const;

  bool is_connected() const;

  const int & get_port() const;
  const int & get_new_sockfd() const;

protected:
  std::shared_ptr<TcpSocket> tcp_socket;

  int port;
  int new_sockfd;
};

}  // namespace musen

#endif  // MUSEN__TCP__SERVER_HPP_
