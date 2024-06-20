# Threaded Merge Sort Experiments


## Host 1: XOA VM Server

- CPU: 1
- Cores: 2
- Cache size (if known): 64 KiB
- RAM: 4 GB
- Storage (if known): 20 GB
- OS: Ubuntu 22.04.3 LTS

### Input data

Data set is 1000000 random numbers, using the file million.txt and the command shuf -i1-1000000 > million.txt. Msort took 4.509951 seconds to sort.

### Experiments


#### 1 Threads

Command used to run experiment: `./tmsort 1000000 < million.txt`

Sorting portion timings:

1. 5.530527 seconds
2. 6.952897 seconds
3. 4.002837 seconds
4. 4.453456 seconds

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 1000000 < million.txt`

Sorting portion timings:

1. 6.197720 seconds
2. 8.817342 seconds
3. 8.764567 seconds
4. 9.128953 seconds

#### 4 Threads

Command used to run experiment: `MSORT_THREADS=4 ./tmsort 1000000 < million.txt`

Sorting portion timings:

1. 8.534578 seconds
2. 8.426514 seconds
3. 8.597613 seconds
4. 8.684545 seconds


## Host 2: My Desktop


- CPU: 12
- Cores: 24
- Cache size (if known): N/A
- RAM: 32 GB
- Storage (if known): 1TB
- OS: Windows 11

### Input data
Data set is the same as before. 1 Million random numbers using the file million.txt and the command shuf -i1-1000000 > million.txt. Msort took 2.385466 seconds to sort.


### Experiments

#### 1 Threads

Command used to run experiment: `./tmsort 1000000 < million.txt`

Sorting portion timings:

1. 2.518941 seconds
2. 2.678546 seconds
3. 2.411513 seconds
4. 2.796612 seconds

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 1000000 < million.txt`

Sorting portion timings:

1. 2.679514 seconds
2. 2.845213 seconds
3. 2.941254 seconds
4. 2.618215 seconds

#### 4 Threads

Command used to run experiment: `MSORT_THREADS=4 ./tmsort 1000000 < million.txt`

Sorting portion timings:

1. 2.344596 seconds
2. 2.276461 seconds
3. 2.416975 seconds
4. 2.154785 seconds


## Observations and Conclusions

Overall, I am surprised at how 1 thread seemed to perform better than 2 threads on both my desktop computer and the virtual machine. Ultimately, the optimal number of threads on each host seems to be 4 based on my research, as spreading out the work amongst a higher number of threads yields better results can evenly/quicker sort the data. However, it is equally important to note that the data size is important as well, and using a higher set of numbers could easily require more threads or yield different results on lower thread counts and less powerful machines. I am also not surprised that my desktop outperformed the XOA VM, as my desktop has a much better setup and more resources available when sorting. The main takeaway here is that data size, the machine's components (ram, cpus, cores, memory, etc.) all must be taken into account when performing sorts and determining what thread count is reasonable.


