/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"


/**
 * Will compare the contents of filename1 and filename2
 * and report whether they are the same or different
 * (It does not list the differences as diff would.).
 * We will only try with regular files.
 *
 * compares two files named as parameters
 * mydiff: mydiff filename1 filename2
 *      compare two different files
 * @param argc the number of argument to be passed
 *  in this method you can only pass two parameters
 * @param argv the char array of the element in this case
 *  is the two file name you want to compare
 * @return 0 when finish
 */
int main(int argc, char *argv[]) {
    file compare_object1 = file(argv[1]);
    file compare_object2 = file(argv[2]);
    if (compare_object1.compare(compare_object2) == 1){
        cout << "They are the same!" << endl;
    } else {
        cout << "They are not the same!" << endl;
    }

    return 0;
}
