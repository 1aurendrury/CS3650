#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
};

// the new struct we are adding to analyze the bytes :)
struct iostats {
    uint read_bytes;     // the total number of bytes read
    uint write_bytes;    // the total number of bytes written
};
