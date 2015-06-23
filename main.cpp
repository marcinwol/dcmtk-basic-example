/**
 * The basic example program just takes one DCM image and reads a patient's name from it.
 *
 * For more information go to: https://github.com/marcinwol/dcmtk-basic-example
 */

#include <iostream>

#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

using namespace std;

int main(int argc, const char *argv[]) {

    string root_path;

    // SOURCE_CODE_LOCATION is set by cmake during compilation.
    // this contains the path to the source folder.
    // This is only helper for convenience. Without this
    // in_file below should contain absolute path.
    #ifdef SOURCE_CODE_LOCATION
        root_path = SOURCE_CODE_LOCATION;
    #endif

    // where does this example dcm come from, is
    // is explained at https://github.com/marcinwol/dcmtk-basic-example
    string in_file {root_path  + "/DCMIMAGES/77654033/20010101/CR1/6154"};

    DcmFileFormat file_format;
    OFCondition status = file_format.loadFile(in_file.c_str());

    if (status.bad()) {
        cerr << "Problem openning file:" << in_file << endl;
        return 1;
    }

    DcmDataset* dataset = file_format.getDataset();

    OFString patient_name;

    OFCondition condition;
    condition = dataset->findAndGetOFStringArray(DCM_PatientName, patient_name);

    if (condition.good())  {
        cout << "Patient name is: " << patient_name << endl;
    } else {
        cerr << "Could not get patient name" << endl;
    }

    cout << "Program finish." << endl;

    return 0;
}

