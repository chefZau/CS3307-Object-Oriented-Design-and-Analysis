#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <iostream>
#include <fstream>1
#include <vector>
#include <cstdio>
#include <algorithm>   // for std::copy
#include <cstdlib>     // for EXIT_FAILURE
#include <iterator>    // for std::{i,o}streambuf_iterator

using namespace std;


string get_file_type(struct stat st);
char *permissions(char *file);


string get_file_type(struct stat st) {
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

char *permissions(char *file) {
	struct stat st;
	char *modeval = (char*)malloc(sizeof(char) * 9 + 1);
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
	else {
		return strerror(errno);
	}
}


class file {

public:
	string name, owner_name, group_name, type, permission;
	off_t size;
	uid_t owner_id;
	gid_t group_id;
	blksize_t block_size;
	string last_access_time;
	string last_modify_time;
	string last_status_change;
	int errno_num;
	// vector <file> children;
	std::list<file> children;

public:
	file(char *filename) {
		struct stat st;
		struct passwd *my_info;
		struct group *grp;
		stat(filename, &st);


		my_info = getpwuid(st.st_uid);
		grp = getgrgid(st.st_gid);

		this->name = (string)filename;
		this->owner_name = my_info->pw_name;
		this->group_name = grp->gr_name;
		this->type = get_file_type(st);
		this->size = st.st_size;
		this->owner_id = st.st_uid;
		this->group_id = st.st_gid;
		this->permission = permissions(filename);
		this->block_size = st.st_blksize;
		this->last_access_time = ctime(&st.st_atime);
		this->last_modify_time = ctime(&st.st_mtime);
		this->last_status_change = ctime(&st.st_ctime);
		this->errno_num = 0;
	}
	~file() {}
	void dump(std::fstream& ofile) {

		if (this->type != "regular file") {
			errno = ENOENT;
			perror("dump(..) error");
			return;
		}
		cout << this->name.c_str() << endl;

		std::fstream ifile(this->name.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
		size_t size   = ifile.tellg();
		char*  buffer = new char[size];
		ifile.seekg(0, std::ios::beg);
		ifile.read(buffer, size);
		ofile.write(buffer, size);
		ifile.close();
	}

	void rename(string new_name) {
		string old_name = this->name;
		int result = std::rename(old_name.c_str(), new_name.c_str());
		if ( result == 0 ) {
			cout << "File successfully moved" << endl;
		}
		else {
			errno = ENOENT;
			cout << "Error renaming file" << endl;
		}
	}

	void remove() {
		int file_descriptor;
		if ((file_descriptor = creat(this->name.c_str(), S_IWUSR)) < 0)
			perror("creat() error");
		else {
			close(file_descriptor);
			if (unlink(this->name.c_str()) != 0)
				perror("unlink() error");
			else {
				cout << "ok remove it alreaady!" << endl;
			}
		}
	}

	bool compare(file compare_object) {
		std::ifstream lFile(this->name.c_str(), std::ios::in | std::ios::binary);
		std::ifstream rFile(compare_object.name.c_str(), std::ios::in | std::ios::binary);

		if (!lFile.is_open() || !rFile.is_open())
		{
			return false;
		}
		char *lBuffer = new char[this->block_size]();
		char *rBuffer = new char[this->block_size]();
		do {
			lFile.read(lBuffer, this->block_size);
			rFile.read(rBuffer, this->block_size);

			if (std::memcmp(lBuffer, rBuffer, this->block_size) != 0)
			{
				delete[] lBuffer;
				delete[] rBuffer;
				return false;
			}
		} while (lFile.good() || rFile.good());

		delete[] lBuffer;
		delete[] rBuffer;
		return true;
	}

	void expand() {

		if (this->type != "directory") {
			cout << "This is not a directory" << endl;
			return;
		}

		DIR *dir;
		char path[1025];
		struct dirent *entry;

		const char *dirname = this->name.c_str();

		if ((dir = opendir(dirname)) == NULL) {
			perror("opendir() error");
		} else {
			while ((entry = readdir(dir)) != NULL) {
				if (entry->d_name[0] != '.') {
					strcpy(path, dirname);
					strcat(path, "/");
					strcat(path, entry->d_name);
					// cout << path << endl;
					// file temp_object = file(path);
					// cout << temp_object.name << endl;
					this->children.push_back(file(path));
				}
			}
			cout << this->children.size() << endl;
			cout << typeid(this->children).name() << endl;
			// std::copy(this->children.begin(), this->children.end(), std::ostream_iterator<char>(std::cout, " "));
			// std::copy(begin(this->children), end(this->children), std::ostream_iterator<file>(std::cout, " " ));
			// std::copy(begin(v), end(v), std::ostream_iterator<file>(std::cout, " "));

			// }
						// for (file p : this->children) {
			// 	cout << p.name << endl;
			// }
			closedir(dir);
		}

	}

};


int main(int argc, char const *argv[]) {
	char filename1[] = "/Users/zaumukcau/Downloads/testing_3307/file1.txt";
	char filename2[] = "/Users/zaumukcau/Downloads/testing_3307/file2.txt";
	file p1 = file(filename1);
	file p2 = file(filename2);

	char filename3[] = "/Users/zaumukcau/Downloads/testing_3307";
	file p3 = file(filename3);
	// cout << "p3: " << p3.name << endl;
	// cout << "p3: " << p3.type << endl;

	p3.expand();
	// ofstream file(filename1);
	// std::filebuf outfile;
	// outfile.open(filename1, std::ios::out | std::ios::binary);


	// std::fstream ofile(filename1, std::ios::out | std::ios::binary);
	// p2.dump(ofile);
	// ofile.close();
	cout << "testing #############" << endl;


	// cout << p1.compare(p2) << endl;


	return 0;
}