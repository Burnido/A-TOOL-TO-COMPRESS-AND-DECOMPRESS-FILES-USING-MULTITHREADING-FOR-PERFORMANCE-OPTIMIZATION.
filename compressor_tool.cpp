#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <zlib.h>

std::mutex output_mutex;

struct Chunk {
    std::vector<Bytef> compressed_data;
    std::vector<Bytef> decompressed_data;
    uLongf original_size;
    uLongf compressed_size;
};

void compress_chunk(const std::vector<char>& input, size_t start, size_t end, Chunk& chunk) {
    chunk.original_size = end - start;
    uLongf max_size = compressBound(chunk.original_size);
    chunk.compressed_data.resize(max_size);

    int res = compress(chunk.compressed_data.data(), &max_size,
                       reinterpret_cast<const Bytef*>(&input[start]), chunk.original_size);

    if (res != Z_OK) {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cerr << "Compression failed in thread\n";
    }
    chunk.compressed_size = max_size;
    chunk.compressed_data.resize(max_size);
}

void decompress_chunk(Chunk& chunk) {
    chunk.decompressed_data.resize(chunk.original_size);

    int res = uncompress(chunk.decompressed_data.data(), &chunk.original_size,
                         chunk.compressed_data.data(), chunk.compressed_size);

    if (res != Z_OK) {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cerr << "Decompression failed in thread\n";
    }
}

void compress_file(const std::string& in_file, const std::string& out_file, int num_threads) {
    std::ifstream input(in_file, std::ios::binary);
    if (!input) {
        std::cerr << "Failed to open input file\n";
        return;
    }

    std::vector<char> input_data((std::istreambuf_iterator<char>(input)), {});
    size_t total_size = input_data.size();
    size_t chunk_size = total_size / num_threads;

    std::vector<Chunk> chunks(num_threads);
    std::vector<std::thread> threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? total_size : (i + 1) * chunk_size;
        threads.emplace_back(compress_chunk, std::ref(input_data), start, end, std::ref(chunks[i]));
    }

    for (auto& t : threads) t.join();

    std::ofstream output(out_file, std::ios::binary);
    for (auto& chunk : chunks) {
        output.write(reinterpret_cast<char*>(&chunk.original_size), sizeof(chunk.original_size));
        output.write(reinterpret_cast<char*>(&chunk.compressed_size), sizeof(chunk.compressed_size));
        output.write(reinterpret_cast<char*>(chunk.compressed_data.data()), chunk.compressed_size);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Compression complete in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()
              << " ms\n";
    std::cout << "Compressed from " << total_size << " bytes to " << output.tellp() << " bytes\n";
}

void decompress_file(const std::string& in_file, const std::string& out_file, int num_threads) {
    std::ifstream input(in_file, std::ios::binary);
    if (!input) {
        std::cerr << "Failed to open compressed file\n";
        return;
    }

    std::vector<Chunk> chunks;
    while (input.peek() != EOF) {
        Chunk chunk;
        input.read(reinterpret_cast<char*>(&chunk.original_size), sizeof(chunk.original_size));
        input.read(reinterpret_cast<char*>(&chunk.compressed_size), sizeof(chunk.compressed_size));

        chunk.compressed_data.resize(chunk.compressed_size);
        input.read(reinterpret_cast<char*>(chunk.compressed_data.data()), chunk.compressed_size);

        chunks.push_back(std::move(chunk));
    }

    std::vector<std::thread> threads;
    auto start_time = std::chrono::high_resolution_clock::now();

    for (auto& chunk : chunks) {
        threads.emplace_back(decompress_chunk, std::ref(chunk));
    }

    for (auto& t : threads) t.join();

    std::ofstream output(out_file, std::ios::binary);
    for (auto& chunk : chunks) {
        output.write(reinterpret_cast<char*>(chunk.decompressed_data.data()), chunk.original_size);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Decompression complete in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()
              << " ms\n";
}

int main() {
    std::cout << "1. Compress\n2. Decompress\nChoice: ";
    int choice;
    std::cin >> choice;

    std::string in_file, out_file;
    std::cout << "Enter input file name: ";
    std::cin >> in_file;
    std::cout << "Enter output file name: ";
    std::cin >> out_file;

    int threads = std::thread::hardware_concurrency();
    if (threads < 2) threads = 2;

    if (choice == 1)
        compress_file(in_file, out_file, threads);
    else if (choice == 2)
        decompress_file(in_file, out_file, threads);
    else
        std::cerr << "Invalid choice\n";

    return 0;
}
