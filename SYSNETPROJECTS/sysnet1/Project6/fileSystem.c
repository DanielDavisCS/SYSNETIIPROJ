/**
 * Emulates a file system.
 *
 * @author Thomas Reichherzer
 */

#include "fileSystem.h"

void readSuperBlock( superBlock_t* superBlock );
void writeSuperBlock( superBlock_t * superBlock );
void readInode( inode_t* inode, int blockNumber );
void writeInode( inode_t* inode, int blockNumber );
void printInodes();
void printFreeBlocks();
void intToByteArray( int value, char* buffer, int pos );
int byteArrayToInt( char* buffer, int pos );


/**
 * A test program for testing file system operations.
 *
 * @param args - a list of arguments
*/
int main(int argc, char* argv[])
{
  int error = format( 100, "c:/disk1.bin" );
  
  return 0;
}

int format( int diskSizeInKB, char* path )
{
  int error;
  // create a disk
  error = createDisk(diskSizeInKB, path);
  
  // complete implementation of this function
  // you must use the functions read/writeSuperblock() & read/writeInode()
  // formatting requires that you setup the superblock, write empty inodes,
  // and setup your free list for the remaining blocks
  
  
  return error;
}

/**
 * Opens a binary file on the disk for storing data.
 */
fd_t* openf(char* name)
{
  return NULL;
}

int closef(fd_t *stream)
{
  
  return -1;
}

int readf(fd_t* stream, char* data, int size)
{
  return -1;
}

int writef(fd_t* stream, char* data, int size)
{
  return -1;
}

/**
 * Reads the super block from disk.
 *
 * @param - destination to store the disk's super block
 */
void readSuperBlock( superBlock_t* superBlock )
{
  int error;
  char buffer[BLOCK_SIZE];
  
  // read block and convert it to the superblock
  error = readBlock(0, buffer);
  
  // read number of disk blocks from block
  int numDiskBlocks = byteArrayToInt(buffer, 0 );
  
  // read number of inodes from block
  int numInodes =  byteArrayToInt(buffer, 4 );
  
  // read start of free block to disk
  
  // finish implementing this function  
}

/**
 * Writes the super block to disk.
 *
 * @param superBlock - the disk's super block
 */
void writeSuperBlock(superBlock_t* superBlock )
{
  // setup buffer to be written to disk
  char buffer[BLOCK_SIZE];
  
  // write number of disk blocks into buffer
  intToByteArray( superBlock->_numberOfDiskBlocks, buffer, 0);
  
  // write number of inodes into buffer
  intToByteArray( superBlock->_numberOfInodes, buffer, 4);
  
  // finish this function
}

/**
 * Reads an Inode from disk.
 *
 * @param inode - the inode to read into
 * @param blockNumber - the block number that holds the inode to be read
 *
 */
void readInode(inode_t* inode, int blockNumber)
{
  int error;
  char block[BLOCK_SIZE];
  // read block containing the Inode
  error = readBlock(blockNumber, block);
  
  // finish implementing this method
  
}

/**
 * Writes an Inode to disk.
 *
 * @param inode - the inode to be written to disk
 * @param blockNumber - the block number in which the inode will be written
 *
 */
void writeInode(inode_t* inode, int blockNumber)
{
  // implement this function
}
	 
/**
 * Prints the content of the Inodes of the virtual disk to the screen.
 */
void printInodes()
{
  // implement this function
}

/**
 * Prints the block numbers of disk blocks that are free.
 */
void printFreeBlocks()
{
  // implement this function
}


/**
 * Writes an integer to a byte array.
 *
 * @param value - the integer to be written to a byte array
 * @param buffer - the byte array in which the integer will be written
 * @param pos - the position in the byte array where an integer will be written
 */
void intToByteArray( int value, char* buffer, int pos )
{
  int i;
  
  for (i = 0; i < 4; i++)
    {
      int shift = (4 - 1 - i) * 8;
      buffer[i+pos] = (char) (( (unsigned int) value >> shift) & 0xFF);
    }
}

/**
 * Reads an integer from a byte array at a specific location.
 *
 * @param buffer - the byte array from which an integer will be read
 * @param pos - the position in the array from where an integer will be read
 *
 * @return an integer read from the byte array
 */
int byteArrayToInt( char* buffer, int pos )
{
  int i, value = 0;
  
  for (i = 0; i < 4; i++)
    {
      int shift = (4 - 1 - i) * 8;
      value += (buffer[i + pos] & 0x000000FF) << shift;
    }
  return value;
}
