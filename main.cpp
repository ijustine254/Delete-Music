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
                for (int i = 0; i < 5; i++) {
                    string di = static_cast<string>(f->d_name);
                    if (dir_ignore.find(f->d_name) != string::npos) {
                        if (dir_ignore.substr(dir_ignore.find(f->d_name), dir_ignore.rfind(f->d_name)) == f->d_name) {
                            continue;
                        }
                    }
                }
                listFiles(path + f->d_name + "/", cb);
                cout << "Directory ------- " << f->d_name << endl;
            }
            if (f->d_type == DT_REG)
                cb(path + f->d_name);
        }
        closedir(dir);
    }
}

LPCWSTR drive[13] = { L"A:\\", L"B:\\", L"C:\\", L"D:\\", L"E:\\", L"F:\\", L"G:\\", L"H:\\", L"I:\\", L"J:\\",  L"K:\\", L"L:\\" };


int main() {
    UINT drives_num;
    int i;
    // loop through fixed drives
    for (i = 0; i < 12; i++) {
        drives_num = GetDriveType(reinterpret_cast<LPCSTR>(drive[i]));
        if (drives_num == DRIVE_FIXED) {
            // convert LPCSTR to string
            wstring st(drive[i]);
            string drive_label(st.begin(), st.end());
            // end of conversion
            listFiles("E:\\", [](const string &path) {
                string ext, str;
                ext = path.substr(path.find_last_of('.')+1);
                str = "mp3 mp4 3gp mkv avi webm avi ogg wav";
                if (str.find(ext) != string::npos) {
                    // Delete File
                    const char* patth = path.c_str();
//                    remove(patth);
                }
                cout << path << endl;
            });
        }
    }
    return 0;
}

