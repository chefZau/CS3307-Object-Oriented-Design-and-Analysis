void dump(ofstream & out_file) {

	if (this->name != "regular file") {
		errno = ENOENT;
		throw "not a regular file";
		return;
	}

	ifstream in_file(this->name.c_str(), std::ios::in | std::ios::binary);

	if (!in_file.is_open()) {
		cout << "Unable to open file";
		return;
	}

	char* buffer = new char[this->block_size];
	do {
		in_file.read(buffer, size);
		out_file.write(buffer, size);
	} while (in_file.good());

	delete[] buffer;
	out_file.close();
	in_file.close();
}