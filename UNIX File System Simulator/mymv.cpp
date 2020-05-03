/**
 *  @author MingCong Zhou
 *  @desc pass argument by command promomt, mymv linux command
 *  @date 2019/10/2
 *  @student_number 250945414
 *  @student_account MZHOU272
 */
#include "file.h"

/**
 * command format: mymv oldname newname
 *      move and rename files around
 *      use the rename method of your class from above to do this.
 *      if EXDEV error or other error
 *          indicating that the source and destination are on different file
 *          systems, you should try to use the dump and remove methods to
 *          copy the file and then remove the original instead.
 *      you only have to do this copy-delete alternative for regular files;
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

    file source_file = file(argv[1]);
    source_file.rename(argv[2]);

    int error_num = errno;

    if (error_num == EXDEV) {
        std::filebuf outfile;
        outfile.open(argv[2], std::ios::out | std::ios::binary);
        std::fstream out_file(argv[2], std::ios::out | std::ios::binary);
        source_file.dump(out_file);
        out_file.close();
        source_file.remove();
    }

    return 0;
}
