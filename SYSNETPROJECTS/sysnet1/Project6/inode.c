/**
 * Models an inode in a file system.
 *
 * @author Thomas Reichherzer
 */

#include "inode.h"

// complete this code

void initializeInode(inode_t* inode){
  int i;  
  for (i=0; i < MAX_POINTERS; i++){
    inode->pointer[i] = -1;
  }
}
