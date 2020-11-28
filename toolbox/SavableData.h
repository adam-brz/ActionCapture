#ifndef SAVABLE_DATA_H
#define SAVABLE_DATA_H

#include <vector>

#define RawBytesConst(obj) (reinterpret_cast<const unsigned char*>((obj)))
#define RawBytes(obj) (reinterpret_cast<unsigned char*>((obj)))

class SavableData
{
private:
    std::vector<unsigned char> data;
    unsigned cursor = 0;

public:
    SavableData(unsigned reserveSize = 0);
    void reserve(unsigned length);

    void add(unsigned char byte);
    void add(const unsigned char *newData, unsigned size);
    void add(const SavableData &other);

    const unsigned char *getRaw() const;
    unsigned read(unsigned char *destination, int maxAmount = -1);
    unsigned char read();

    unsigned pos() const;
    void seek(unsigned pos);
    bool atEnd() const;

    unsigned size() const;
    void clear();
};


#endif // SAVABLE_DATA_H
