#include "Backup.hpp"

Backup::Backup(const std::string& players, const std::string& worlds) {
    for (const auto& file : std::filesystem::directory_iterator("players")) m_files.push_back(file.path().string()), m_players = m_files.size();
    for (const auto& file : std::filesystem::directory_iterator("worlds")) m_files.push_back(file.path().string()); m_worlds = m_files.size() - m_players;
}

void Backup::create_name() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    int year = now.tm_year + 1900, month = now.tm_mon + 1, day = now.tm_mday, hour = now.tm_hour, minute = now.tm_min;

    char buffer[20];
    std::snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d-%02d.%02d", day, month, year, hour, minute);

    m_backup = std::string(buffer) + ".zip";
}

std::string Backup::get_files() {
    return std::to_string(m_players) + " Players and " + std::to_string(m_worlds) + " Worlds backed up!";
}

void Backup::Zip() {
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));
    mz_zip_writer_init_file(&zip_archive, m_backup.c_str(), 0);

    for (const std::string& file : m_files) {
        std::ifstream input(file, std::ios::binary);
        if (!input.is_open()) {
            std::cerr << "Failed to open: " << file << std::endl;
            mz_zip_writer_end(&zip_archive);
            continue;
        }

        input.seekg(0, std::ios::end);
        size_t size = input.tellg();
        input.seekg(0, std::ios::beg);

        void* buffer = malloc(size);
        input.read(reinterpret_cast<char*>(buffer), size);
        mz_zip_writer_add_mem(&zip_archive, file.c_str(), buffer, size, MZ_DEFAULT_COMPRESSION);
        free(buffer);
    }

    mz_zip_writer_finalize_archive(&zip_archive);
    mz_zip_writer_end(&zip_archive);
    std::cout << "Created Backup: " << m_backup << std::endl;
}