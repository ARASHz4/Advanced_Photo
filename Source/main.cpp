#include "advancedphoto.h"

int main(int argc, char *argv[])
{
    AdvancedPhoto APApplication(argc, argv);

    APApplication.setOrganizationName("ARASHz4");
    APApplication.setApplicationName("Advanced Photo");
    APApplication.setApplicationVersion("1.5.0");
    APApplication.setOrganizationDomain("ARASHz4");

    APApplication.StartApplication();

    return APApplication.exec();
}
