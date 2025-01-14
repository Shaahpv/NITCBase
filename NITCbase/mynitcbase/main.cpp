#include <iostream>
#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <cstring>


int main(int argc, char *argv[]) {
  // /* Initialize the Run Copy of Disk */
  // Disk disk_run;

  // unsigned char buffer[BLOCK_SIZE];
  // //BLOCK_SIZE is a constant that has value 2048

  // Disk::readBlock(buffer, 7000);
  // // 7000 is a random block number that's unused.

  // char message[] = "hello\n";
  // memcpy(buffer + 20, message, 7);
  // //Now, buffer[20] = 'h', buffer[21] = 'e' ...
  // Disk::writeBlock(buffer, 7000);

  // unsigned char buffer2[BLOCK_SIZE];
  // char message2[7];
  // Disk::readBlock(buffer2, 7000);
  // memcpy(message2, buffer2 + 20, 7);
  // std::cout << message2;

  // return 0;


  Disk disk_run;

  // create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);

  for (int i=0;i<(relCatHeader).numEntries;i++) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

    for (int j=0;j<(attrCatHeader).numEntries;j++) {

      // declare attrCatRecord and load the attribute catalog entry into it
      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];

      attrCatBuffer.getRecord(attrCatRecord,j);

      // printf("%s\n",attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal);
      // printf("%s\n",relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

      if (!(strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,relCatRecord[RELCAT_REL_NAME_INDEX].sVal))) {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
      }
    }
    printf("\n");
  }

  return 0;


  // StaticBuffer buffer;
  // OpenRelTable cache;

  // return FrontendInterface::handleFrontend(argc, argv);
}
