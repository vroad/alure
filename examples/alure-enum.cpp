
#include <iostream>

#include "alure2.h"

int main(int argc, char *argv[])
{
    alure::DeviceManager &devMgr = alure::DeviceManager::get();
    alure::Vector<alure::String> list;
    alure::String defname;

    list = devMgr.enumerate(alure::DevEnum_Basic);
    defname = devMgr.defaultDeviceName(alure::DefaultDevType_Basic);
    std::cout<< "Available basic devices:\n";
    for(const auto &name : list)
        std::cout<< "  "<<name<<((defname==name)?"  [DEFAULT]":"") <<'\n';
    std::cout<<std::endl;

    list = devMgr.enumerate(alure::DevEnum_Complete);
    defname = devMgr.defaultDeviceName(alure::DefaultDevType_Complete);
    std::cout<< "Available devices:\n";
    for(const auto &name : list)
        std::cout<< "  "<<name<<((defname==name)?"  [DEFAULT]":"") <<'\n';
    std::cout<<std::endl;

    list = devMgr.enumerate(alure::DevEnum_Capture);
    defname = devMgr.defaultDeviceName(alure::DefaultDevType_Capture);
    std::cout<< "Available capture devices:\n";
    for(const auto &name : list)
        std::cout<< "  "<<name<<((defname==name)?"  [DEFAULT]":"") <<'\n';
    std::cout<<std::endl;

    alure::Device *dev = [&devMgr, argc, argv]()
    {
        if(argc > 1) try {
            return devMgr.openPlayback(argv[1]);
        }
        catch(std::exception &e) {
            std::cerr<< "Exception while opening requested device: "<<e.what() <<std::endl;
        }
        return devMgr.openPlayback();
    }();
    std::cout<< "Info for device \""<<dev->getName(alure::PlaybackDeviceName_Complete)<<"\":" <<std::endl;
    ALCuint version = dev->getALCVersion();
    std::cout<< "ALC version: "<<alure::MajorVersion(version)<<"."<<alure::MinorVersion(version) <<std::endl;
    version = dev->getEFXVersion();
    if(version)
    {
        std::cout<< "EFX version: "<<alure::MajorVersion(version)<<"."<<alure::MinorVersion(version) <<'\n';
        std::cout<< "Max auxiliary sends: "<<dev->getMaxAuxiliarySends() <<std::endl;
    }
    else
        std::cout<< "EFX not supported" <<std::endl;
    dev->close();
    dev = 0;

    return 0;
}
