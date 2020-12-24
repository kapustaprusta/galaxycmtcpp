#include <memory>
#include <future>
#include <atomic>
#include <iostream>

#include "src/walker/dir_walker/dir_walker.h"

int main()
{
	galaxycmt::WalkerConfig config = {false};
	std::unique_ptr<galaxycmt::IWalker> walker = std::make_unique<galaxycmt::DirWalker>(config);

	std::atomic<bool> isStop(false);

	auto printFuture = std::async(std::launch::async,
	                              [&]() -> void
	                              {
		                              std::cout << "printing start\n";
		                              while (!isStop.load())
		                              {
			                              auto visitedFiles = walker->GetVisited();
			                              if (visitedFiles.empty())
			                              {
			                                std::this_thread::sleep_for(std::chrono::milliseconds(20));
			                              }

			                              for (const auto& visitedFile : visitedFiles)
			                              {
				                              std::cout << visitedFile << "\n";
			                              }
		                              }
		                              std::cout << "printing stop\n";
	                              });

	auto walkFuture = std::async(std::launch::async,
	                             [&]() -> void
	                             {
		                             std::cout << "walk start\n";
		                             walker->Walk("/home/vniksihov/src/cpp/galaxycmt/src");
		                             std::cout << "walk stop\n";
	                             });

	walkFuture.wait();
	isStop.store(true);
	printFuture.wait();

	return 0;
}
