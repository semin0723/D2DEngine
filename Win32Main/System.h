#pragma once
#include "ISystem.h"
#include "utilheader.h"
#include "FamilyTypeId.h"

template<class T>
class System :
    public ISystem
{
public:
    static const SystemTypeId SYSTEM_TYPE_ID;

    virtual ~System() {}

    virtual const SystemTypeId GetTypeId() const { return SYSTEM_TYPE_ID; }
    virtual const std::string& GetSystemTypeName() const override {
        std::string TYPE_NAME   { typeid(T).name() };
        return TYPE_NAME;
    }

    virtual void PreUpdate(float dt) override {}
    virtual void Update(float dt) override {}
    virtual void PostUpdate(float dt) override {}

protected:
    System() {}
    

private:
    SystemManager* _systemManager;

    friend class SystemManager;
};

template<class T>
const SystemTypeId System<T>::SYSTEM_TYPE_ID = FamilyTypeId<ISystem>::Get<T>();