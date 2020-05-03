/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"



/**
 * Will dump the contents of all files given as parameters to the terminal.
 * mycat:  mycat filename1 filename2 ...
 *      display the contents of all of the files given as parameters to the command to the terminal.
 *      support more than one file as the original command does.
 *
 * @param argc the number of argument to be passed
 *  in this file you can pass as many argument as you want
 * @param argv the char array of the element in this case
 *  is file1.txt file2.txt ...
 * @return 0 when finish
 */
int main(int argc, char *argv[]) {

    for (int i = 1 ; i < argc; ++i){
        file source_file = file(argv[i]);
        std::cout << std::ifstream(source_file.get_name()).rdbuf(); // print the entire file in one line
		cout << '\n';
    }
    
    return 0;
}
