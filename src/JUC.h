#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace JUC {

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

    private:
        bool throws;
        bool logs;

        void err(const std::string& message);
    };
    
    void SetErrorHandler(ErrorHandler& handler);

    namespace Console {



    }

    namespace FileSystem {

        class File {
        public:
            File(const std::string& path);

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
    }

}
