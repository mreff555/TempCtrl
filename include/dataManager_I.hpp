#ifndef DATA_MANAGER_I_HPP
#define DATA_MANAGER_I_HPP

class DataManager_I
{
    virtual ~DataManager_I;

    virtual void setCurrentTempStruct(const TempStruct tempStruct) = 0;
};

#endif /* DATA_MANAGER_I_HPP */
