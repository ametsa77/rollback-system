#include <Windows.h>
#include "Backup.hpp"
#include "Webhook.hpp"

int main() {

    int hours = 1;
    std::cout << "Set the backup time in hours: ", std::cin >> hours;

    while (true) {
        auto file = new Backup("players", "worlds");
        auto wh = new Webhook();
        file->create_name(), file->Zip(), wh->message(file->get_files().c_str()), wh->file(file->get_backup().c_str());
        delete file, wh;
        Sleep(60000 * 60 * hours);
    }
}
