#include <atomic>
#include <iostream>
#include <folly/init/Init.h>
#include <folly/coro/AsyncScope.h>
#include <folly/executors/GlobalExecutor.h>
#include <folly/coro/Task.h>
#include <folly/coro/BlockingWait.h>

folly::coro::Task<void> test() {
  std::atomic<int> count = 0;

  auto incrementBy5 = [&]() -> folly::coro::Task<> {
    count += 5;
    co_return;
  };

  auto incrementBy10 = [&]() -> folly::coro::Task<> {
    count += 10;
    co_return;
  };

  auto incrementBy100 = [&]() -> folly::coro::Task<> {
    count += 100;
    co_return;
  };

  folly::coro::AsyncScope scope;
  scope.add(incrementBy5().scheduleOn(folly::getGlobalCPUExecutor()));
  scope.add(incrementBy10().scheduleOn(folly::getGlobalCPUExecutor()));
  scope.add(incrementBy100().scheduleOn(folly::getGlobalCPUExecutor()));

  co_await scope.joinAsync();
  std::cout << "count:" << count << std::endl;
  co_return;
}

int main(int argc, char** argv) {
  folly::Init init(&argc, &argv);
  folly::coro::blockingWait(test());
  return 0;
}
