#ifndef UNIQUEID_H
#define UNIQUEID_H


namespace ayin{

class UniqueIdSystem
{
private:
    int lastId = 0;
public:
    UniqueIdSystem();
    int newId(){
        lastId++;
        return lastId-1;
    }
};
}
#endif // UNIQUEID_H
