#include "controller.h"
#include <filesystem>

using namespace std;
using std::filesystem::current_path;

int main()
{

    Controller cntrl;

    cntrl.start();

    return 0;
}
