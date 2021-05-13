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

#include <gtest/gtest.h>
#include <musen/musen.hpp>

#include <string>

TEST(StringBroadcasterAndListenerTest, SendAndReceive) {
  musen::StringBroadcaster broadcaster(5000);
  musen::StringListener listener(5000);

  // Trying to connect both broadcaster and listener
  ASSERT_TRUE(broadcaster.connect());
  ASSERT_TRUE(listener.connect());

  std::string broadcast_data = "Hello World!";

  // Do up to 3 times until the listener received a message
  int iteration = 0;
  while (iteration++ < 3) {
    // Sending string data
    broadcaster.send(broadcast_data);

    // Wait a bit so listener could receive the data
    usleep(10 * 1000);

    // Receiving string data
    const auto & listen_data = listener.receive(32);
    if (listen_data.size() > 0) {
      // Compare the received and the sent string
      ASSERT_STREQ(listen_data.c_str(), broadcast_data.c_str());

      return SUCCEED();
    }
  }

  FAIL() << "listener did not receive any data";
}

TEST(StringBroadcasterAndListenerTest, ReceiveNothing) {
  musen::StringListener listener(5000);

  // Trying to connect the listener
  ASSERT_TRUE(listener.connect());

  // Do for 3 times
  for (int i = 0; i < 3; ++i) {
    // Must received empty string
    const auto & data = listener.receive(32);
    ASSERT_EQ(data.size(), 0u);

    // Wait a bit
    usleep(10 * 1000);
  }
}
