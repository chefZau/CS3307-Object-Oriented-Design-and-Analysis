/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"

bool exists_test2 (const std::string& name); // the declaration of the function

/**
 * Copies a file (not a directory) with name oldname to a new copy newname,
 * where oldname and newname do not have any path information.
 * (They’re both in the current directory.)
 *
 * mymv pathname1/oldname pathname2/newname
 *      Copies a file (again not a directory) as above, but to a different directory.
 * mycp: mycp oldname newname
 *    make a copy of a file from a source
 *    Parameter: destination named as parameters
 *
 * @param argc the number of argument to be passed
 *  in this method you can only pass two parameter
 * @param argv the char array of the element in this case
 *  is old name and new name
 * @return 0 when finish
 */
int main( int argc, char *argv[] ){

    file source_file = file(argv[1]);
    cout << argv[1] << endl;
    cout << argv[2] << endl;

    // if the file does not exist create a new file
    if (exists_test2(argv[2]) == -1){
        cout << argv[2] << endl;
        fstream fs;
        fs.open(argv[2], ios::out);
        fs.close();
    }

    // use the file we just create and create a new object
    file dest_file = file(argv[2]);

    // create a file stream and dump to proper location
    std::filebuf outfile;
    outfile.open(dest_file.get_name().c_str(), std::ios::out | std::ios::binary);

    std::fstream out_file(dest_file.get_name().c_str(), std::ios::out | std::ios::binary);
    source_file.dump(out_file);
    outfile.close();

    return 0;
}

/**
 * The function can check whether the file exist or not
 * @param name of the path of the file
 * @return -1 when the file does not exist
 */
bool exists_test2 (const std::string& name) {
    cout << access( name.c_str(), F_OK ) << endl;
    return ( access( name.c_str(), F_OK ) != -1 );
}