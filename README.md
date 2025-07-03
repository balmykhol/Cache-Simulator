# Pinepline Stall Simulator 
- https://github.com/balmykhol/Pipeline-Stall-Simulator

# Cache Hit/Miss Simulator

This repository contains a Cache Hit/Miss Simulator implemented in C. The simulator reads memory access patterns and configuration settings from `cache.access` and `cache.config` files to simulate cache operations and determine cache hits and misses.

## Files

- **`cache.access`**: Contains memory access patterns in hexadecimal format.
- **`cache.config`**: Configuration file specifying cache parameters such as size, block size, associativity, replacement policy, and write policy.

## Code Files

- **`hextoBinary.c`**: Converts hexadecimal addresses to binary representation.
- **`sliceString.c`**: Extracts substrings from strings based on start and end indices.
- **`code.c`**: Main program file that reads `cache.access` and `cache.config`, performs cache simulation, and outputs results.

## Compilation and Execution

1. **Compile the Program**:
   ```bash
   gcc code.c -o cache_simulator
   ```

2. **Run the Simulator**:
   ```bash
   ./cache_simulator
   ```

   Make sure `cache.access` and `cache.config` files are in the same directory as the executable.

## Simulation Output

The simulator outputs cache access results, indicating whether each access resulted in a hit or miss along with the corresponding tag and set information.

## Configuration Customization

You can customize the cache configuration by editing `cache.config` with different parameters such as cache size, block size, associativity, replacement policy (FIFO, LRU, RANDOM), and write policy (WT: WriteThrough, WB: WriteBack).

## Contributing

Feel free to contribute by forking this repository, making enhancements, and creating pull requests. Bug fixes, additional features, and optimizations are welcome!
