#include "XCSP3CoreParser.h"
#include "XCSP3PrintCallbacks.h"
#include "HModel.h"
#include "BMFileParser.h"
using namespace XCSP3Core;
using namespace cp;

const string x_path = "/home/leezear/CLionProjects/reader/BMPath.xml";

int main() {
    string bm_path;
    if (FindBMPath(x_path))
        bm_path = _bm_path;
    cout << bm_path << endl;
    HModel *hm = new HModel();
    GetHModel(bm_path, *hm);
    hm->show();
    delete hm;
    return 0;
}
