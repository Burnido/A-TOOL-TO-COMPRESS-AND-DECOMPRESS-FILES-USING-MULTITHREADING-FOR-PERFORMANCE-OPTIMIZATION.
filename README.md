# A-TOOL-TO-COMPRESS-AND-DECOMPRESS-FILES-USING-MULTITHREADING-FOR-PERFORMANCE-OPTIMIZATION.

C++ APPLICATION TO READ, WRITE, AND APPEND DATA TO TEXT FILES.

COMPANY : CODTECH IT SOLUTION

NAME : MANAV AWANA

INTERN ID : CT04DN1135

DOMAIN : C++

DURATION : 4 WEEKS

MENTOR NAME : NEELA SANTOSH

DESCRIPTION :  
This project demonstrates a C++ application designed to compress and decompress files using multithreading for performance optimization. Built with the zlib library, the tool efficiently reduces file sizes (compression) and restores them to their original state (decompression). It provides a clear showcase of how leveraging multiple CPU threads can improve processing speed for large files.

1. Purpose & Objective
The main goal of the project is to build a practical and efficient file compressor and decompressor using C++, which utilizes multiple threads to handle chunks of data concurrently. This approach improves speed, especially when working with large files or on systems with multi-core processors. The application prompts the user to choose between compression or decompression, processes the file accordingly, and displays useful metrics such as total bytes processed and time taken.

2. How It Works
a. Compression Workflow
The user selects the compression mode.

The program reads the entire input file (e.g., a .txt or .log) into memory.

It divides the file into equally sized chunks, one for each thread.

Each thread uses the zlib::compress() function to compress its assigned chunk independently.

The compressed chunks are stored alongside metadata: original and compressed sizes.

The final output is a single binary file combining all compressed chunks.

The program prints how many bytes were compressed and how long it took.

b. Decompression Workflow
The user selects decompression mode.

The program reads the metadata and compressed data chunks from the input file.

Each thread decompresses its assigned chunk using zlib::uncompress().

All decompressed chunks are then written in order to reconstruct the original file.

The time taken to restore the file is displayed.

3. Why Use Multithreading?
Compression and decompression are CPU-bound operations, especially when dealing with large files. Traditional single-threaded implementations compress the file sequentially, which becomes inefficient on modern multi-core CPUs. By dividing the task into chunks and assigning them to different threads:

The workload is distributed evenly.

Threads work simultaneously.

Execution time is significantly reduced.

This project uses std::thread from C++11, making it cross-platform and lightweight.

4. Features
🔹 User-Friendly CLI: Prompts for mode, input, and output file names.

🔹 Multithreaded Processing: Automatically detects number of available CPU cores and uses them.

🔹 Performance Metrics: Shows compression ratio, total bytes processed, and time in milliseconds.

🔹 Zlib Integration: Utilizes standard DEFLATE compression, ensuring compatibility and reliability.

🔹 Binary Chunk Format: Stores compressed chunks with size metadata, enabling exact reconstruction during decompression.

5. Example Output
Compression:

pgsql
Copy
Edit
Choice: 1
Input file: large.txt
Output file: large_compressed.z
Compression complete in 132 ms
Compressed from 4,000,000 bytes to 720,000 bytes
Decompression:

yaml
Copy
Edit
Choice: 2
Input file: large_compressed.z
Output file: restored.txt
Decompression complete in 90 ms
6. What Does the Compressed File Look Like?
The output of compression is not human-readable. It contains raw binary data that may appear as gibberish characters (e.g., Ê, É, œ, etc.) when opened in Notepad. This is expected — compression algorithms remove redundant patterns, resulting in compact, encoded data. Only the decompression function can properly decode it.

7. Real-World Applications
This kind of system could be used in:

Archiving systems

Backup tools

Network transmission (reducing size before sending)

Game engines (compressing textures, logs)

Embedded systems where space and speed are critical

8. Learning Outcomes
By completing this project, you've learned how to:

Use zlib in C++

Read and write binary files

Work with std::thread for concurrent processing

Manage shared memory safely with std::mutex

Benchmark performance using std::chrono

Structure compressed file formats for reuse

Conclusion
This project showcases how a traditionally CPU-heavy task like compression can benefit from multithreaded design in C++. With a clean user interface, efficient implementation, and performance output, it not only solves the problem but also demonstrates software engineering principles. You’ve successfully created a robust and extensible compression tool that can be enhanced further with features like progress bars, file integrity checks, and GUI support.

Let me know if you'd like this formatted as a PDF or added to a README for GitHub!****

Output :

when using compression 
![Image](https://github.com/user-attachments/assets/34a7d51f-d63f-4d19-9766-8cd3c687e772)
![Image](https://github.com/user-attachments/assets/a13d37e9-2217-46ef-bcfc-f4bc0b3cfe4c)
![Image](https://github.com/user-attachments/assets/40cbb8e9-78c7-4dfa-9828-c3c6aeb6972d)

when using decompression 
put it as input becoz it is compressed
![Image](https://github.com/user-attachments/assets/40cbb8e9-78c7-4dfa-9828-c3c6aeb6972d)
![Image](https://github.com/user-attachments/assets/954f12a7-9cc0-40a6-9e2a-8d4361da279f)
![Image](https://github.com/user-attachments/assets/b4406c66-3ba1-4191-a0d6-07ca4d2c536c)
  


