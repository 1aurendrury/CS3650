/** 
 * Threaded Merge Sort
 *
 * Modify this file to implement your multi-threaded version of merge sort. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <unistd.h>

#include <assert.h>

#include <pthread.h>


#define tty_printf(...) (isatty(1) && isatty(0) ? printf(__VA_ARGS__) : 0)

#ifndef SHUSH
#define log(...) (fprintf(stderr, __VA_ARGS__))
#else 
#define log(...)
#endif


// struct we are using for thread stats, basically holds the info necessary for each threaded merge
// and merge aux call
// with index representing the thread number
typedef struct threadStats {
  long *nums;
  long *result;
  int from;
  int to;
  int index;
} threadStats;

// need to add this here so threaded helper can work correctly (both merge aux and the helper call each other
void merge_sort_aux(long nums[], int from, int to, long target[], int totalThreads);


/** The number of threads to be used for sorting. Default: 1 */
int thread_count = 1;

/**
 * Compute the delta between the given timevals in seconds.
 */
double time_in_secs(const struct timeval *begin, const struct timeval *end) {
  long s = end->tv_sec - begin->tv_sec;
  long ms = end->tv_usec - begin->tv_usec;
  return s + ms * 1e-6;
}

/**
 * Print the given array of longs, an element per line.
 */
void print_long_array(const long *array, int count) {
  for (int i = 0; i < count; ++i) {
    printf("%ld\n", array[i]);
  }
}

/**
 * Merge two slices of nums into the corresponding portion of target.
 */
void merge(long nums[], int from, int mid, int to, long target[]) {
  int left = from;
  int right = mid;

  int i = from;
  for (; i < to && left < mid && right < to; i++) {
    if (nums[left] <= nums[right]) {
      target[i] = nums[left];
      left++;
    }
    else {
      target[i] = nums[right];
      right++;
    }
  }
  if (left < mid) {
    memmove(&target[i], &nums[left], (mid - left) * sizeof(long));
  }
  else if (right < to) {
    memmove(&target[i], &nums[right], (to - right) * sizeof(long));
  }

}

// acts as a helper as we recur and call merge aux for each of the threads we have (aka the second half referenced in merge aux)
void *threadedHelper(void *currentThread) {
  threadStats *ct = (threadStats *)currentThread;
  merge_sort_aux(ct->nums, ct->from, ct->to, ct->result, ct->index);
}

/**
 * Sort the given slice of nums into target.
 * Altered such that the total number of threads are input as well
 *
 * Warning: nums gets overwritten.
 */
void merge_sort_aux(long nums[], int from, int to, long target[], int totalThreads) {
  if (to - from <= 1) {
    return;
  }

  int mid = (from + to) / 2;
  // if we are only using a single thread, just call regular merge instead
  if (thread_count <= 1) {
    merge_sort_aux(target, from, mid, nums, 1);
    merge_sort_aux(target, mid, to, nums, 1);
    merge(nums, from, mid, to, target);
  }
  else {
    // this will be used when we have more than 1 thread
    // make the main thread, break into two halfs, and recur based on the amount of threads we have access too
    // finish by joining at the end
    pthread_t mainThread;
    // + 1 to total threads to account for the mainthread
    threadStats firstHalf = {target, nums, from, mid, (totalThreads + 1 / 2)};
    pthread_create(&mainThread, NULL, threadedHelper, &firstHalf);
    // this is the second half recurrence call
    merge_sort_aux(target, mid, to, nums, (totalThreads / 2));
    pthread_join(mainThread, NULL);
    // merge once all threads are done
    merge(nums, from, mid, to, target);
  }

}


/**
 * Sort the given array and return the sorted version.
 *
 * The result is malloc'd so it is the caller's responsibility to free it.
 *
 * Warning: The source array gets overwritten.
 */
long *merge_sort(long nums[], int count) {
  long *result = calloc(count, sizeof(long));
  assert(result != NULL);

  memmove(result, nums, count * sizeof(long));

  merge_sort_aux(nums, 0, count, result, thread_count);

  return result;
}

/**
 * Based on command line arguments, allocate and populate an input and a 
 * helper array.
 *
 * Returns the number of elements in the array.
 */
int allocate_load_array(int argc, char **argv, long **array) {
  assert(argc > 1);
  int count = atoi(argv[1]);

  *array = calloc(count, sizeof(long));
  assert(*array != NULL);

  long element;
  tty_printf("Enter %d elements, separated by whitespace\n", count);
  int i = 0;
  while (i < count && scanf("%ld", &element) != EOF)  {
    (*array)[i++] = element;
  }

  return count;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <n>\n", argv[0]);
    return 1;
  }

  struct timeval begin, end;

  // get the number of threads from the environment variable SORT_THREADS
  if (getenv("MSORT_THREADS") != NULL)
    thread_count = atoi(getenv("MSORT_THREADS"));

  log("Running with %d thread(s). Reading input.\n", thread_count);

  // Read the input
  gettimeofday(&begin, 0);
  long *array = NULL;
  int count = allocate_load_array(argc, argv, &array);
  gettimeofday(&end, 0);

  log("Array read in %f seconds, beginning sort.\n", 
      time_in_secs(&begin, &end));
 
  // Sort the array
  gettimeofday(&begin, 0);
  long *result = merge_sort(array, count);
  gettimeofday(&end, 0);
  
  log("Sorting completed in %f seconds.\n", time_in_secs(&begin, &end));

  // Print the result
  gettimeofday(&begin, 0);
  print_long_array(result, count);
  gettimeofday(&end, 0);
  
  log("Array printed in %f seconds.\n", time_in_secs(&begin, &end));

  free(array);
  free(result);

  return 0;
}
