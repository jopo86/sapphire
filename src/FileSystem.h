#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire
{

    /*
        @brief A namespace containing functions for file manipulation.
     */
    namespace FileSystem 
    {

        /*
            @brief A class to represent a file.
         */
        class File {
        public:
            /*
                @brief Creates a File object with default values.
             */
            File();

            /*
                @brief Creates a File object from a path.
                Reads the file and sets all other member variables accordingly.
             *  To refresh any member variables after changes to the file, call refresh().
             */
            File(const std::string& path);

            /*
                @brief Refreshes the file.
                Re-reads the file and sets all member variables accordingly.
             *  Use after changes to the file, except for write() and writeAppend() (because they do it for you).
             */
            void refresh();

            /*
                @brief Writes to the file.
             *  Automatically refreshes the file after write.
                @param contents The contents to write to the file.
             */
            void write(const std::string& contents);

            /*
                @brief Appends to contents of the file.
             *  Automatically refreshes the file after writeAppend.
                @param contents The contents to append to the file.
             */
            void writeAppend(const std::string& contents);

            /*
                @brief Deletes the file from the system.
             *  Member variables remain unchanged.
             *  Calling refresh() after remove() will result in an error.
             */
            void remove();

            /*
                @brief Copies the file to another location.
             *  Member variables, including `path`, remain unchanged.
                @param to The path to copy the file to.
             */
            void copy(const std::string& to);

            /*
                @brief Gets the contents of the file.
             *  Does not re-read the file, so may be outdated if the file has changed and refresh() has not been called.
                @return The contents of the file.
             */
            std::string getContents();

            /*
                @brief Gets the lines of the file.
             *  Does not re-read the file, so may be outdated if the file has changed and refresh() has not been called.
                @return The lines of the file.
             */
            std::vector<std::string> getLines();

            /*
                @brief Gets the path of the file.
                @return The path of the file.
             */
            std::string getPath();

            /*
                @brief Gets the extension of the file.
                @return The extension of the file.
             */
            std::string getExtension();

            /*
                @brief Gets the filename of the file.
                @return The filename of the file.
             */
            std::string getFilename();

            /*
                @brief Gets the size of the file in bytes.
             *  Does not re-read the file, so may be outdated if the file has changed and refresh() has not been called.
                @return The size of the file in bytes.
             */
            int getSize();

            /*
                @brief Gets the number of lines in the file.
             *  Does not re-read the file, so may be outdated if the file has changed and refresh() has not been called.
                @return The number of lines in the file.
             */
            int getLineCount();

        private:
            std::ifstream istream;
            std::ofstream ostream;

            std::string path;
            std::string contents;
            std::vector<std::string> lines;
            std::string extension;
            std::string filename;
            int size;
            int lineCount;
        };

        /*
            @brief Checks if a file or directory exists.
            @param path The path to check.
            @return True if the file or directory exists, false otherwise.
         */
        bool Exists(const std::string& path);

        /*
            @brief Checks if the path is a directory.
            @param path The path to check.
            @return True if the path is a directory, false otherwise.
         */
        bool IsDir(const std::string& path);

        /*
            @brief Gets the extension of a file.
         *  Does not check the existence of the path.
            @param path The path to get the extension of.
            @return The extension of the file.
         */
        std::string GetExtension(const std::string& path);

        /*
            @brief Gets the filename of a file.
         *  Does not check the existence of the path.
            @param path The path to get the filename of.
            @return The filename of the file.
         */
        std::string GetFilename(const std::string& path);

        /*
            @brief Gets the directory of a file.
         *  Does not check the existence of the path.
            @param path The path to get the directory of.
            @return The directory of the file.
         */
        std::string GetDir(const std::string& path);

        /*
            @brief Creates a directory.
         *  Must be used before writing a file to a new directory.
            @param path The path to create the directory at.
         */
        void CreateDir(const std::string& path);
        
        /*
            @brief Deletes a file from the system.
         *  Member variables of any File objects created from the file will remain unchanged.
            @param path The path of the file to remove.
         */
        void RemoveFile(const std::string& path);

        /*
            @brief Deletes a directory from the system, as well as all subdirectories and files inside.
         *  Member variables of any File objects created from files in the directory will remain unchanged.
            @param path The path of the directory to remove.
         */
        void RemoveDir(const std::string& path);

        /*
            @brief Copies a file to another location.
         *  Member variables of any File objects created from the file will remain unchanged.
            @param from The path of the file to copy.
            @param to The path to copy the file to.
         */
        void CopyFile(const std::string& from, const std::string& to);

        /*
            @brief Copies a directory to another location, as well as all subdirectories and files inside.
         *  Member variables of any File objects created from files in the directory will remain unchanged.
            @param from The path of the directory to copy.
            @param to The path to copy the directory to.
         */
        void CopyDir(const std::string& from, const std::string& to);

        /*
            @brief Iterates through all files and directories in a directory.
         *  Does not include subdirectories.
            @param path The path of the directory to iterate through.
            @return A vector containing all files and directories in the directory.
         */
        std::vector<std::string> GetFilesAndDirsInDir(const std::string& path);

        /*
            @brief Iterates through all files and directories in a directory.
         *  Does not include subdirectories.
         *  Only includes files with the specified extensions.
            @param path The path of the directory to iterate through.
            @param extensionFilter A vector containing the extensions to filter by --> ex: `{ "cpp", "h" }`
            @return A vector containing all files and directories in the directory.
         */
        std::vector<std::string> GetFilesAndDirsInDir(const std::string& path, std::vector<std::string> extensionFilter);

        /*
            @brief Iterates through all files in a directory.
         *  Does not include subdirectories.
            @param path The path of the directory to iterate through.
            @return A vector containing all files in the directory.
         */
        std::vector<std::string> GetFilesInDir(const std::string& path);

        /*
            @brief Iterates through all files in a directory.
         *  Does not include subdirectories.
         *  Only includes files with the specified extensions.
            @param path The path of the directory to iterate through.
            @param extensionFilter A vector containing the extensions to filter by --> ex: `{ "cpp", "h" }`
            @return A vector containing all files in the directory.
         */
        std::vector<std::string> GetFilesInDir(const std::string& path, std::vector<std::string> extensionFilter);

        /*
            @brief Iterates through all directories in a directory.
         *  Does not include subdirectories.
            @param path The path of the directory to iterate through.
            @return A vector containing all directories in the directory.
         */
        std::vector<std::string> GetDirsInDir(const std::string& path);

        /*
            @brief Iterates through all files and directories in a directory and its subdirectories.
            @param path The path of the directory to iterate through.
            @return A vector containing all files and directories in the directory and its subdirectories.
         */
        std::vector<std::string> GetFilesAndDirsInDirRecursive(const std::string& path);

        /*
            @brief Iterates through all files and directories in a directory and its subdirectories.
         *  Only includes files with the specified extensions.
            @param path The path of the directory to iterate through.
            @param extensionFilter A vector containing the extensions to filter by --> ex: `{ "cpp", "h" }`
            @return A vector containing all files and directories in the directory and its subdirectories.
         */
        std::vector<std::string> GetFilesAndDirsInDirRecursive(const std::string& path, std::vector<std::string> extensionFilter);

        /*
            @brief Iterates through all files in a directory and its subdirectories.
            @param path The path of the directory to iterate through.
            @return A vector containing all files in the directory and its subdirectories.
         */
        std::vector<std::string> GetFilesInDirRecursive(const std::string& path);

        /*
            @brief Iterates through all files in a directory and its subdirectories.
         *  Only includes files with the specified extensions.
            @param path The path of the directory to iterate through.
            @param extensionFilter A vector containing the extensions to filter by --> ex: `{ "cpp", "h" }`
            @return A vector containing all files in the directory and its subdirectories.
         */
        std::vector<std::string> GetFilesInDirRecursive(const std::string& path, std::vector<std::string> extensionFilter);

        /*
            @brief Iterates through all directories in a directory and its subdirectories.
            @param path The path of the directory to iterate through.
            @return A vector containing all directories in the directory and its subdirectories.
         */
        std::vector<std::string> GetDirsInDirRecursive(const std::string& path);

        /*
            @brief Writes to a file.
         *  Member variables of any File objects created from the file will remain unchanged.
         *  If writing to a new file in a directory that doesn't exist, use CreateDir() first.
            @param path The path of the file to write to.
            @param contents The contents to write to the file.
            @return A File object representing the file.
         */
        File Write(const std::string& path, const std::string& contents);

        /*
            @brief Appends to the contents of a file.
         *  Member variables of any File objects created from the file will remain unchanged.
         *  If writing to a new file in a directory that doesn't exist, use CreateDir() first.
            @param path The path of the file to append to.
            @param contents The contents to append to the file.
            @return A File object representing the file.
         */
        File WriteAppend(const std::string& path, const std::string& contents);

        /*
            @brief Counts the number of lines in a file.
            @param path The path of the file to count the lines of.
            @return The number of lines in the file.
         */
        int CountLines(const std::string& path);

        /*
            @brief Counts the number of lines in a file, excluding empty lines.
            @param path The path of the file to count the lines of.
            @return The number of lines in the file, excluding empty lines.
         */
        int CountLinesNoEmpty(const std::string& path);

        /*
            @brief Reads a file.
            @param path The path of the file to read.
            @return The contents of the file.
         */
        std::string Read(const std::string& path);

        /*
            @brief Reads a file.
            @param path The path of the file to read.
            @return The contents of the file as a vector of strings, each string representing a line.
         */
        std::vector<std::string> ReadLines(const std::string& path);

        /*
            @brief Gets the size of a file in bytes.
            @param path The path of the file to get the size of.
            @return The size of the file in bytes.
         */
        int GetSize(const std::string& path);
    }

}