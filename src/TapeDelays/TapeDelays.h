#ifndef INT_TAPE_TAPE_DELAYS
#define INT_TAPE_TAPE_DELAYS

struct TapeDelays {
    unsigned int read;
    unsigned int write;
    unsigned int shift;
    unsigned int rewind;
};

#endif // INT_TAPE_TAPE_DELAYS
