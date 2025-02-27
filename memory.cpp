#include "benchmark.h"
// #include "osv/mempool.hh"
#include "osv/mempool.hh"
#include "osv/mmu-defs.hh"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

namespace benchmark {

void mem_worker(unsigned core_id, size_t const measurements, size_t const granularity, uint64_t* alloc_time, uint64_t* free_time, size_t size)
{
    stick_this_thread_to_core(core_id);
   }

} // namespace benchmark

int main(int argc, char* argv[])
{
    size_t measurements{4096};
    size_t granularity{128};
    size_t threads{1};
    size_t size{4096};
    benchmark::parse_args(argc, argv, &measurements, &granularity, &threads, &size);
    std::cout << "xlabel: Allocations\n";
    std::cout << "ylabel: Avg. CPU Cycles\n";
    std::cout << "out:\n";

    std::vector<void*> mem;
    mem.reserve(measurements * granularity);

    uint64_t start = memory::stats::free();
    uint64_t requested_bytes{0};

    for (size_t i = 0; i < measurements; ++i) {
        for (size_t j = 0; j < granularity; ++j) {
            // uint64_t alloc_size = (size * j) % mmu::huge_page_size;
            uint64_t alloc_size = size;
            void* page = _alloc(alloc_size);
            requested_bytes += alloc_size;
            if (!page) {
                std::cerr << "Memory allocation failed at iteration " << i << "\n";
                exit(1);
            }
            for(size_t k{0}; k < alloc_size; k += memory::page_size)
              *reinterpret_cast<uint64_t *>(page + k) = 5;
            mem.push_back(page);
        }
    }

    uint64_t end = memory::stats::free();

    for (size_t i = 0; i < measurements; ++i) {
        for (size_t j = 0; j < granularity; ++j) {
            _free(mem.at(i * granularity + j));
        }
    }

    // std::cout << start << " - " << end << " - " << requested_bytes << " = ";
    std::cout << (double)(start - end - requested_bytes) / requested_bytes;
    std::cout << std::endl;

    return 0;
}
