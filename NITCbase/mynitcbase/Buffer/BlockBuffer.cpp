#include "BlockBuffer.h"

#include <cstdlib>
#include <cstring>

// Constructor for BlockBuffer
BlockBuffer::BlockBuffer(int blockNum) {
    // Initialize this.blockNum with the argument
    this->blockNum = blockNum;
}

// Constructor for RecBuffer (calls parent class constructor)
RecBuffer::RecBuffer(int blockNum) : BlockBuffer(blockNum) {}

// Load the block header into the argument pointer
int BlockBuffer::getHeader(struct HeadInfo *head) {
    unsigned char buffer[BLOCK_SIZE];

    // Read the block at this.blockNum into the buffer
    Disk::readBlock(buffer, this->blockNum);

    // Populate the numEntries, numAttrs, numSlots, rblock, and lblock fields in *head
    memcpy(&head->numSlots, buffer + 24, 4);
    memcpy(&head->numEntries, buffer, 4);
    memcpy(&head->numAttrs, buffer + 4, 4);
    memcpy(&head->rblock, buffer + 8, 4);
    memcpy(&head->lblock, buffer + 12, 4);

    return SUCCESS; // SUCCESS should be a predefined constant
}

// Load the record at slotNum into the argument pointer
int RecBuffer::getRecord(union Attribute *rec, int slotNum) {
    struct HeadInfo head;

    // Get the header using this.getHeader() function
    this->getHeader(&head);

    int attrCount = head.numAttrs;    // Number of attributes per record
    int slotCount = head.numSlots;   // Number of slots in the block

    unsigned char buffer[BLOCK_SIZE];

    // Read the block at this.blockNum into a buffer
    Disk::readBlock(buffer, this->blockNum);

    // Calculate sizes
    const int HEADER_SIZE = 28;      // Header size in bytes (example: includes numSlots, etc.)
    const int SLOT_MAP_SIZE = slotCount; // Each slot is 1 byte (e.g., 0 or 1 for empty/occupied)
    const int RECORD_SIZE = attrCount * ATTR_SIZE; // Record size in bytes

    // Calculate the offset for the specific record
    int offset = HEADER_SIZE + SLOT_MAP_SIZE + (RECORD_SIZE * slotNum);
    unsigned char *slotPointer = buffer + offset;

    // Load the record into the rec data structure
    memcpy(rec, slotPointer, RECORD_SIZE);

    return SUCCESS; // SUCCESS should be a predefined constant
}

