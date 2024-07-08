# Cache Miss Simulator
This C program code will simulate a cache to identify which accesses would cause a cache hit and which accesses would cause a cache miss.

## Usage

1. Compile the program using a C compiler:

   ```bash
   gcc code -o lab6
2. Run the program:

   ```bash
   ./lab6
3. The program will read two files, namely cache.access and cache.config. Make sure both the files are in the same directory

## Customisable options in simulation
- Total cache size in bytes 
- Total block size in bytes
- Associativity (1: Direct mapped, 0: Fully associative, any other number: set associative)
- Replacement policy (FIFO, LRU, RANDOM)
- Write policy (WB: WriteBack, WT: WriteThrough)

## Input File Format

1. The input file should be a .access for address values and .config for configurations. 

2. Sample input files named 
    ```bash
    cache.access
    cache.config
I used are also attached.

3. Change the appropriate global variables to accomadate a size of '.access' file greater than 100 rows

## Output

The program will simulate the cache with .config settings and output the address, set, tag, mention if hit/miss. For example input:

    R: 0x20203302
    R: 0x20202011
    R: 0x20203304
    R: 0x20203303
    R: 0x20203401
    R: 0x20203304
    R: 0x20203305

and configurations:

    32
    16
    0
    FIFO
    WT

The output would be :

    Address: 0x20203302, Set: 0x0, Miss, Tag: 0x2020330
    Address: 0x20202011, Set: 0x0, Miss, Tag: 0x2020201
    Address: 0x20203304, Set: 0x0, Hit, Tag: 0x2020330
    Address: 0x20203303, Set: 0x0, Hit, Tag: 0x2020330
    Address: 0x20203401, Set: 0x0, Miss, Tag: 0x2020340
    Address: 0x20203304, Set: 0x0, Miss, Tag: 0x2020330
    Address: 0x20203305, Set: 0x0, Hit, Tag: 0x2020330

## Note

1. The second parameter in function 
    ```bash
    twosComplementToDecimal(char arr[], int yes)
being one considers the string parameter as twos compliment but for any other value the string parameter is considered as a binary value

2. The code reuses varous functions already used in the earlier lab questions.

3. The alphabets in the hex values should be lower case

4. If the code has associativity as 0, it prints the set as 0x as there is no need for any index in that case