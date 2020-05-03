#include "file.h"

/**
 * Constructor of the class.
 * It creates an instance of the class and initiatives it.
 * It will take the name of a file as a parameter and use the stat() function
 * to initialize everything else.  It will also initialize its error number, as noted above.
 * If the file does not exists in the system, is will not be generate
 * @param pathname either the filename or the pathname of a file/directory
 */
file::file(char *pathname) {
    struct stat st;
    struct passwd *my_info;
    struct group *grp;
    errno = 0;

    // check if the file/directory exists
    if (stat(pathname, &st) == -1){
        perror("unable open file");
    }

    my_info = getpwuid(st.st_uid);
    grp = getgrgid(st.st_gid);

    this->name = (string) pathname;
    this->owner_name = my_info->pw_name;
    this->group_name = grp->gr_name;
    this->type = get_file_type(st);
    this->size = st.st_size;
    this->owner_id = st.st_uid;
    this->group_id = st.st_gid;
    this->permission = permissions(pathname);
    this->block_size = st.st_blksize;
    this->last_access_time = st.st_atime;
    this->last_modify_time = st.st_mtime;
    this->last_status_change = st.st_ctime;
    this->errno_num = 0;
}

/**
 * This function will take a file stream as a parameter and dump the contents
 * of the named file to that file stream.  This can be used to copy the file,
 * display its contents to the terminal, and so on.
 * @param out_file the output stream of the destination file
 * @return return 0 when success, else generate perror() (print out what is the error string)
 */
int file::dump(std::fstream &out_file) {

    // we can only dump a regular file, if not print out error
    if (this->type != "regular file") {
        errno = ENOTSUP;
        perror("dump(..) error");
    }

    std::fstream in_file(this->name.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    size_t size = in_file.tellg();
    char *buffer = new char[size]; // create a buffer size of entire file
    in_file.seekg(0, std::ios::beg);
    in_file.read(buffer, size);
    out_file.write(buffer, size);
    in_file.close();

    return 0;
}

/**
 * This changes the name of the file from its existing name to the
 * new name provided as a parameter to this function.
 * this will change the name of the file on disk.
 *      - done using the rename() system function.
 * @param new_name
 */
void file::rename(string new_name) {

    string old_name = this->name;
    int result = std::rename(old_name.c_str(), new_name.c_str()); //system function to change the name
    if (result == 0) {
        cout << "File successfully moved" << endl;
    } else {
        // return error code if the operation could not be completed
        perror("rename() error");
    }
}

/**
 *  This removes the file from the file system.
 *  Once completed, this function should clear out or reset the
 *  attributes of the file object in question as this object no
 *      - done using the unlink() system function.
 */
void file::remove() {
    int file_descriptor;

    if ((file_descriptor = creat(this->name.c_str(), S_IWUSR)) < 0) {
        perror("creat() error");
    } else {
        close(file_descriptor);
        if (unlink(this->name.c_str()) != 0) { // use system function unlink()
            // return error code if the operation could not be completed
            perror("unlink() error");
        } else {
            cout << "ok remove it already!" << endl;
        }
    }
}

/**
 * This function takes another one of the file objects as a parameter
 * and will compare the contents of the file object this function was
 * invoked upon to this other file object.  For performance reasons, you should
 * use the block size of the file (one of the attributes from above) to determine the
 * amount of data to be compared at a time.
 * @param compare_object the file object that we want to compare with
 * @return return true when success, false otherwise
 */
bool file::compare(file compare_object) {
    std::ifstream lFile(this->name.c_str(), std::ios::in | std::ios::binary);
    std::ifstream rFile(compare_object.name.c_str(), std::ios::in | std::ios::binary);

    // check if both file stream is open
    if (!lFile.is_open() || !rFile.is_open()) {
        return false;
    }

    // create buffer of the size
    blksize_t temp_block_size = this->block_size;
    char *lBuffer = new char[temp_block_size]();
    char *rBuffer = new char[temp_block_size]();

    // while the file is still good read block by block
    do {
        lFile.read(lBuffer, temp_block_size);
        rFile.read(rBuffer, temp_block_size);

        // if it is different, return false
        if (memcmp(lBuffer, rBuffer, temp_block_size) != 0) {
            delete[] lBuffer;
            delete[] rBuffer;
            return false;
        }
    } while (lFile.good() || rFile.good());

    // release the buffer
    delete[] lBuffer;
    delete[] rBuffer;
    return true;
}

/**
 * This function operates on directories only and is used to
 * fill in the children of the file object this function was invoked upon.
 * It does so by obtaining a listing of the directory in question and
 * creating a new file object for each file found in the directory,
 * adding these new objects to the vector of children as it goes.
 * @return return 0 if the function is terminated, jump error otherwise
 */
int file::expand() {

    // expand only work for directory, if it is not directory return
    if (this->type != "directory") {
        cout << "This is not a directory" << endl;
        errno = ENOTDIR;
        return errno;
    }

    DIR *dir;
    // char path[1025];
    struct dirent *entry;

    const char *dirname = this->name.c_str();

    // if directory name does noe exist return
    if ((dir = opendir(dirname)) == NULL) {
        perror("opendir() error");
    } else {
        while ((entry = readdir(dir)) != NULL) {
            // skip the file that start with "." like .git . ..
            if (entry->d_name[0] != '.') {

                //push the temp object to the vector
                this->children.emplace_back(file(entry->d_name));
            }
        }
        cout << "total: " << this->children.size() << endl;
        closedir(dir);
    }
    return 0;
}

/**
 *  Instead of using get method for all the attribute
 *  This ls_helper() will print every attribute in one line
 */
void file::ls_helper() {
    cout << this->permission << " " << this->owner_name << " " << this->owner_name << " " << this->type << " "
         << this->name << endl;
}

/**
 * @return return the name attribute of the select object
 */
string file::get_name() {
    return this->name;
}

/**
 * @return return the owner name attribute of the select object
 */
string file::get_owner_name() {
    return this->owner_name;
}

/**
 * @return return the owner name attribute of the select object
 */
string file::get_group_name() {
    return this->group_name;
}

/**
 * @return return the owner name attribute of the select object
 */
string file::get_type() {
    return this->type;
}

/**
 * @return return the owner name attribute of the select object
 */
string file::get_permission() {
    return this->permission;
}

/**
 * @return return the owner name attribute of the select object
 */
off_t file::get_size() {
    return this->size;
}

/**
 * @return return the owner name attribute of the select object
 */
uid_t file::get_owner_id() {
    return this->owner_id;
}

/**
 * @return return the owner name attribute of the select object
 */
gid_t file::get_group_id() {
    return this->group_id;
}

/**
 * @return return the owner name attribute of the select object
 */
blksize_t file::get_block_size() {
    return this->block_size;
}

/**
 * @return return the owner name attribute of the select object
 */
time_t file::get_last_access_time() {
    return this->last_access_time;
}

/**
 * @return return the owner name attribute of the select object
 */
time_t file::get_last_modify_time() {
    return this->last_modify_time;
}

/**
 * @return return the owner name attribute of the select object
 */
time_t file::get_last_status_change() {
    return this->last_status_change;
}

/**
 * @return return the owner name attribute of the select object
 */
int file::get_errno_num() {
    return this->errno_num;
}

/**
 * @return return the owner name attribute of the select object
 */
vector <file> file::get_children() {
    return this->children;
}

/**
 * using bitwise operation, get the target type
 * @param st this is generate by the stat() function, able to access the attribute of stat
 * @return return corresponding file type
 */
string file::get_file_type(struct stat st) {
    string type;
    switch (st.st_mode & S_IFMT) {
        case S_IFBLK:
            type = "block device";
            break;
        case S_IFCHR:
            type = "character device";
            break;
        case S_IFDIR:
            type = "directory";
            break;
        case S_IFIFO:
            type = "FIFO/pipe";
            break;
        case S_IFLNK:
            type = "symlink";
            break;
        case S_IFREG:
            type = "regular file";
            break;
        case S_IFSOCK:
            type = "socket";
            break;
        default:
            type = "unknown?";
            break;
    }
    return type;
}

/**
 * return rwx format of the file using stat attribute st_mode
 * @param file the target file path
 * @return return the permission in rwx format
 */
char *file::permissions(char *file) {
    struct stat st;
    char *modeval = (char *) malloc(sizeof(char) * 9 + 1);
    if (stat(file, &st) == 0) {
        mode_t perm = st.st_mode;
        modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
        modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
        modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
        modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
        modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
        modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
        modeval[6] = (perm & S_IROTH) ? 'r' : '-';
        modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
        modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
        modeval[9] = '\0';
        return modeval;
    }
}

