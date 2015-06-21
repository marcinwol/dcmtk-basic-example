/**
 * The example program just takes one DCM image
 * and converts it into tiff image.
 */

#include <iostream>
#include <memory>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmimage/dipitiff.h"


using namespace std;

int main() {

    string root_path;

    #ifdef SOURCE_CODE_LOCATION
        root_path = SOURCE_CODE_LOCATION;
    #endif

    string in_file {root_path  + "/DCMIMAGES/77654033/20010101/CR1/6154"};
    string out_file {root_path + "/DCMIMAGES/6154.tiff"};

    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(in_file.c_str());

    if (status.bad()) {
        cout << "Problem openning file:" << in_file << endl;
        return 1;
    } else {
        cout << "DCM file opened properly" << endl;
    }

    DcmDataset* dataset = fileformat.getDataset();
    E_TransferSyntax xfer = dataset->getOriginalXfer();

    // create a DicomImage object
    shared_ptr<DicomImage> dcm_img {new DicomImage(dataset, xfer)};

    if (dcm_img->getStatus() == EIS_InvalidImage)
    {
        cout << "Failed to open: " << in_file << endl;
        return 1;
    }

    // make a tiff image
    FILE* ofile = nullptr;
    ofile = fopen(out_file.c_str(), "wb");

    DiTIFFPlugin tiffPlugin;
    tiffPlugin.setCompressionType(E_tiffLZWCompression);
    tiffPlugin.setLZWPredictor(E_tiffLZWPredictorDefault);
    tiffPlugin.setRowsPerStrip(0);

    int result = dcm_img->writePluginFormat(&tiffPlugin, ofile, 0);

    fclose(ofile);

    cout << "Successful execution" << endl;

    return 0;
}

