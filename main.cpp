/**
 * The basic example program just takes one DCM image and reads a patient's name from it.
 *
 * For more information go to: https://github.com/marcinwol/dcmtk-basic-example
 */

#include <iostream>


#include "dcmtk/dcmdata/dctk.h"


using namespace std;

void print_info(DcmItem* dcm_item)
{
    DcmElement* dcm_elem;

    for (size_t i = 0; i < dcm_item->card(); ++i)
    {
        dcm_elem = dcm_item->getElement(i);
        DcmTag tag = dcm_elem->getTag();

        OFString str;

        dcm_item->findAndGetOFString(tag, str);

        const char* symbol = nullptr;

        if (dcm_elem->ident() == EVR_UI)
        {
            symbol = dcmFindNameOfUID(str.c_str());
            if (symbol != nullptr) {
                //cout << symbol << endl;
                str = OFString(symbol);
            }
        }

        if (dcm_elem->ident() == EVR_SQ) {
            DcmObject* dcm_obj = nullptr;

            cout << "EVR_SQ: " << dcm_elem->ident() << endl;

           // dcm_item->findAndGetElement(tag, dcm_obj);



            if (tag.getXTag() == DCM_DirectoryRecordSequence)
            {
                cout << "DCM_DirectoryRecordSequence" << endl;
                DcmDirectoryRecord dir(tag, 0);
                //dir = static_cast<DcmDirectoryRecord*>(dcm_elem);
                DcmStack s;
                if (dir.search(DCM_ReferencedFileID, s, ESM_fromHere, OFFalse).good())
                {
                    cout << "DCM_ReferencedFileID found" << endl;
                }

                cout << "Stack: " << s.card() << endl;

                cout << dir.getReferencedMRDR() << endl;
            }

            DcmElement* dcm_elem2;

            DcmSequenceOfItems* seq;

            seq = static_cast<DcmSequenceOfItems*>(dcm_elem);

            unsigned long nitems = seq->card();
            for (unsigned long j=0; j<nitems; j++) {
                /* check each item.  an item is just another dataset */
                cout << endl<< endl<< endl<< endl;

                DcmTag tag2;
                tag2 = seq->getItem(j)->getTag();



                print_info(seq->getItem(j));


                cout << "Is leaf:" << dcm_elem->isLeaf() << endl;

//                DcmSequenceOfItems* seq2;
//                unsigned long nitems1 = seq2->card();
//                for (unsigned long jj=0; jj<nitems1; jj++) {
//                    cout << seq2->getItem(jj)->getTag();
//                }


                //checkitem(seq->getItem(j), oxfer, stack, showFullData, dderrors);

            }

//
//            dcm_item->findAndGetSequence(tag, items);
//
//            cout << items->card() << endl;
//            DcmTag tag1;
//
//            dcm_obj = items->nextInContainer(nullptr);
//
//
//            DcmItem* it = items->getItem(0);
//            //cout << "tag:" << it->get << endl;

//            do {
//               dcm_obj = items->nextInContainer(dcm_obj);
//
//               cout << static_cast<unsigned >(dcm_obj->ident()) << endl;
//
//               tag1 = dcm_obj->getTag();
//               cout << "IDENT: " << tag1.getTagName() << endl;
//            } while(dcm_obj);

            cout << "IDENT: "<<endl;


            //cout << dcm_elem2->ident() << static_cast<uint >(EVR_SQ) << endl;

           // print_info(static_cast<DcmItem*>(dcm_elem2));

        }


        cout << i << ": " << tag << ": "  << tag.getTagName() << ": "  << str << endl;
        cout << "Is leaf:" << dcm_elem->isLeaf() << endl;
    }
}


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

    //in_file = "/mnt/e/ImageDatabases/Martin_MOA_knee_xrays/04_only_0000b_dcm_decompressed/159169_1_anon_im_3_i0000,0000b-no-phi.dcm";
    in_file = "/home/marcin/mycpp/dcmtk-basic-example/DCMIMAGES/DICOMDIR";

    DcmFileFormat file_format;
    OFCondition status = file_format.loadFile(in_file.c_str());

    if (status.bad()) {
        cerr << "Problem openning file:" << in_file << endl;
        return 1;
    }

    DcmMetaInfo* meta   = file_format.getMetaInfo();
    DcmDataset* dataset = file_format.getDataset();

    if (!meta->isEmpty())
    {
        cout << "Meta data: " << endl;
        print_info(meta);
        cout << endl;
    }

    if (!dataset->isEmpty())
    {
        cout << "Data set: " << endl;
        print_info(dataset);
        cout << endl;
    }


    cout << "Program finish." << endl;

    return 0;
}

