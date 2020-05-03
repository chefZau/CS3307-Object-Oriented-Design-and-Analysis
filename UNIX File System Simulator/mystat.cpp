/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"

/**
 * Will output all of the information on the named file name
 * to the terminal.  It should be formatted in a humanly
 * readable fashion as noted in the assignment specification.
 * command format: mystat name
 * @param argc the number of the argument in this case is one
 * @param argv the argument you pass in
 * @return
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "need two parameter" << endl;
        exit(EXIT_FAILURE);
    }

    file file_object = file(argv[1]);
    cout << file_object.get_name() << " ";
    cout << file_object.get_owner_name() << " ";
    cout << file_object.get_group_name() << " ";
    cout << file_object.get_type() << " ";
    cout << file_object.get_permission() << " ";
    cout << file_object.get_size() << " ";
    cout << file_object.get_owner_id() << " ";
    cout << file_object.get_group_id() << " ";
    cout << file_object.get_block_size() << " ";
    cout << file_object.get_last_access_time() << " ";
    cout << file_object.get_last_modify_time() << " ";
    cout << file_object.get_last_status_change() << " ";
    cout << file_object.get_errno_num() << " ";
    cout << "\n";
    exit(EXIT_SUCCESS);
}
