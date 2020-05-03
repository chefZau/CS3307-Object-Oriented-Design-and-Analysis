/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"

/**
 * Will remove the files given as parameters.
 * command only needs to work with regular files
 * myrm
 *      removes the given files listed as parameters to this command.
 *      using the remove method you have implemented above. 
 * @param argc number of argument you pass in
 * @param argv the array of argument
 * @return 0 when finish
 */
int main( int argc, char *argv[] ){

    // rm only take two arguments
    if (argc != 2) {
        cout << "need two parameter" << endl;
        exit(EXIT_FAILURE);
    }

    file trash_file = file(argv[1]);
    trash_file.remove();

    return 0;
}
