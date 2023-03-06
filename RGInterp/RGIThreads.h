//
// Created by tom on 03/03/23.
//

#ifndef RGINTERP_RGI_THREADS_H
#define RGINTERP_RGI_THREADS_H

#include <thread>
#include <vector>
#include <iostream>
/**
 * @brief Utility function to split a job of size into chunks based on the max number of threads on the PC
 *
 * @param worker The worker function, it will be called with the stard and end positions for the work it should perform.
 * @param size The size of the job
 * @param num_threads 1 to perform the job single threadedly, 0 to perform multi-threaded.
 */
template<typename Lambda>
void dispatch(const Lambda &worker, size_t size, size_t num_threads) noexcept {
    if (num_threads == 1) {
        worker(0, size);
        return;
    }

    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
    }

    // List of threads responsible for parallelizing the calculation
    std::vector<std::thread> threads(num_threads);

    // Access index to the vectors required for calculation
    size_t start = 0;
    size_t shift = size / num_threads;

    // Launch and join threads
    for (auto it = std::begin(threads); it != std::end(threads) - 1; ++it) {
        *it = std::thread(worker, start, start + shift);
        start += shift;
    }
    threads.back() = std::thread(worker, start, size);

    for (auto &&item : threads) {
        item.join();
    }
}

#endif //VERSION_RGITHREADS_H
