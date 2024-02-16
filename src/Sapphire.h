#ifndef _SAPPHIRE_H
#define _SAPPHIRE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace Sapphire {

    void Init();

    class ErrorHandler {
    public:
        friend class FileSystem::File;

        ErrorHandler();
        ErrorHandler(bool throws, bool logs);

        void setThrow(bool value);
        void setLog(bool value);

        bool throwsErrors();
        bool logsErrors();

        std::vector<std::string> getErrors();
        std::string getLastError();

    private:
        bool throws;
        bool logs;
        std::vector<std::string> errors;

        void err(const std::string& message);
    };
    
    void SetErrorHandler(ErrorHandler& handler);

    namespace Console {

        

    }

    namespace FileSystem {

        class File {
        public:
            File(const std::string& path, bool dynamic = false);

            void refresh();

            std::string getContents();
            std::vector<std::string> getLines();
            std::string getPath();
            std::string getExtension();
            std::string getFilename();
            int getSize();
            int getLineCount();
        };

        File Write(const std::string& path, const std::string& contents);

        std::string Read(const std::string& path);
        std::vector<std::string> ReadLines(const std::string& path);
    }

}

#endif
