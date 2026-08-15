#ifndef UNIQUEID_H
#define UNIQUEID_H

template<class T>
class UniqueID
{
public:
    static UniqueID& getInstance()
    {
        static UniqueID instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    UniqueID(UniqueID const&) = delete;
    void operator=(UniqueID const&) = delete;

    unsigned int getNewID()
    {
        return currentID++;
    }

    void reset()
    {
        currentID = 0;
    }

private:
    unsigned int currentID = 0;

    UniqueID() { };
};

#endif // UNIQUEID_H
