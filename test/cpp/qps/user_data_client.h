/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <cfloat>

#include <grpc/grpc.h>
#include <grpc++/channel_arguments.h>
#include <grpc++/channel_interface.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/credentials.h>
#include <grpc++/status.h>
#include "test/cpp/qps/user_data.grpc.pb.h"


namespace grpc{
namespace testing {

class UserDataClient {
public:
  UserDataClient(std::shared_ptr<ChannelInterface> channel)
    : stub_(UserDataTransfer::NewStub(channel)) {}
  
  ~UserDataClient() {}

  void setConfigs(const ClientConfig& clientConfig, const ServerConfig& serverConfig);
  
  void setQPS(double QPS);

  void setQPSPerCore(double QPSPerCore);

  void setLatencies(double percentileLatency50, double percentileLatency90,
     double percentileLatency95, double percentileLatency99, double percentileLatency99Point9);

  void setTimes(double serverSystemTime, double serverUserTime, 
    double clientSystemTime, double clientUserTime);

  int sendData(std::string access_token, std::string test_name, std::string sys_info);

private:
  std::unique_ptr<UserDataTransfer::Stub> stub_;
  ClientConfig clientConfig_;
  ServerConfig serverConfig_;
  double QPS_ = DBL_MIN;
  double QPSPerCore_ = DBL_MIN;
  double percentileLatency50_ = DBL_MIN;
  double percentileLatency90_ = DBL_MIN;
  double percentileLatency95_ = DBL_MIN;
  double percentileLatency99_ = DBL_MIN;
  double percentileLatency99Point9_ = DBL_MIN;
  double serverSystemTime_ = DBL_MIN;
  double serverUserTime_ = DBL_MIN;
  double clientSystemTime_ = DBL_MIN;
  double clientUserTime_ = DBL_MIN;
};

} //namespace testing
} //namespace grpc


