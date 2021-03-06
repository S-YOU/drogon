/**
 *
 *  ListenerManager.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  https://github.com/an-tao/drogon
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */

#pragma once

#include "impl_forwards.h"
#include <trantor/utils/NonCopyable.h>
#include <trantor/net/EventLoopThreadPool.h>
#include <trantor/net/callbacks.h>
#include <string>
#include <vector>
#include <memory>

namespace drogon
{
class ListenerManager : public trantor::NonCopyable
{
  public:
    void addListener(const std::string &ip,
                     uint16_t port,
                     bool useSSL = false,
                     const std::string &certFile = "",
                     const std::string &keyFile = "");
    std::vector<trantor::EventLoop *> createListeners(
        const HttpAsyncCallback &httpCallback,
        const WebSocketNewAsyncCallback &webSocketCallback,
        const trantor::ConnectionCallback &connectionCallback,
        size_t connectionTimeout,
        const std::string &globalCertFile,
        const std::string &globalKeyFile,
        size_t threadNum,
        const std::vector<
            std::function<HttpResponsePtr(const HttpRequestPtr &)>>
            &syncAdvices);
    void startListening();
    ~ListenerManager();

  private:
    struct ListenerInfo
    {
        ListenerInfo(const std::string &ip,
                     uint16_t port,
                     bool useSSL,
                     const std::string &certFile,
                     const std::string &keyFile)
            : ip_(ip),
              port_(port),
              useSSL_(useSSL),
              certFile_(certFile),
              keyFile_(keyFile)
        {
        }
        std::string ip_;
        uint16_t port_;
        bool useSSL_;
        std::string certFile_;
        std::string keyFile_;
    };
    std::vector<ListenerInfo> listeners_;
    std::vector<std::shared_ptr<HttpServer>> servers_;
    std::vector<std::shared_ptr<trantor::EventLoopThread>>
        listeningloopThreads_;
    std::shared_ptr<trantor::EventLoopThreadPool> ioLoopThreadPoolPtr_;
};

}  // namespace drogon
