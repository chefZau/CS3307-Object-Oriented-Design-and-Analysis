/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"

/**
 * Only For a directory
 * list the contents of the directory also implement a "-l" option for this command
 * myls: Will display the contents of the current directory.
 *
 * myls filename
 *      Will display the file’s name if the file exists (the file in this case is not a directory).
 *
 * myls dirname
 *      Will list the contents of the directory dirname.
 *
 * @param argc the number of argument to be passed
 * @param argv the char array of the element
 * @return 0 when finish
 */
int main(int argc, char *argv[]) {

    // the situation when myls  stand alone
    if (argc == 1){
        char current_directory[] = ".";
        file directory = file(current_directory);
        directory.expand();
        vector<file> child = directory.get_children();
        for (int i = 0; i < child.size()-1; i++) {
            cout << child[i].get_name() << endl;
        }
        return 0;
    }

    // the situation when -l command is specify
    char option[] = "-l";
    if (strcmp(argv[1], option) == 0) {
        char current_directory[] = ".";
        file directory = file(current_directory);

        directory.expand();

        // iterate over the vector using for loop
        vector<file> child = directory.get_children();
        for (int i = 0; i < child.size(); i++) {
            child[i].ls_helper();
        }
        cout << '\n';
        return 0;
    }

    // the situation when myls direname
    file directory = file(argv[1]);
    directory.expand();
    vector<file> child = directory.get_children();
    for (int i = 0; i < child.size(); i++) {
        child[i].ls_helper();
    }
    cout << '\n';

    return 0;
}
