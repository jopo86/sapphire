#pragma once

#include <string>
#include <vector>

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire
{
    /*
        @brief A namespace containing functions for system information.
     */
    namespace System 
    {

        /*
            @brief An enum for types of operating systems.
         */
        enum class OS 
        {
            WINDOWS,
            LINUX,
            MAC,
            UNKNOWN
        };

        /*
            @brief An enum for types of architecture.
         */
        enum class ARCH 
        {
            X86,
            X64,
            UNKNOWN
        };

        /*
            @brief A class to represent a display device.
            This means a graphics card, integrated graphics, or possibly other PCI devices.
         */
        class DisplayDevice
        {
        public:
            /*
                @brief Creates a DisplayDevice object with default values.
             */
            DisplayDevice();

            /*
                @brief Creates a DisplayDevice object with the specified values.
                @param cardName The name of the card.
                @param manufacturer The manufacturer of the card.
                @param chipType The type of chip.
                @param memory The amount of memory in MB.
             */
            DisplayDevice(const std::string& cardName, const std::string& manufacturer, const std::string& chipType, int memory);

            /*
                @brief Gets the name of the card.
                @return The name of the card.
             */
            std::string getCardName();

            /*
                @brief Gets the manufacturer of the card.
                @return The manufacturer of the card.
             */
            std::string getManufacturer();

            /*
                @brief Gets the type of chip.
                @return The type of chip.
             */
            std::string getChipType();

            /*
                @brief Gets the amount of memory in MB.
                @return The amount of memory in MB.
             */
            int getMemory();

            /*
                @brief Sets the name of the card.
                @param value The name of the card.
             */
            void setCardName(const std::string& value);

            /*
                @brief Sets the manufacturer of the card.
                @param value The manufacturer of the card.
             */
            void setManufacturer(const std::string& value);

            /*
                @brief Sets the type of chip.
                @param value The type of chip.
             */
            void setChipType(const std::string& value);

            /*
                @brief Sets the amount of memory in MB.
                @param value The amount of memory in MB.
             */
            void setMemory(int value);

        private:
            std::string cardName;
            std::string manufacturer;
            std::string chipType;
            int memory;
        };

        /*
            @brief A class to represent a sound playback device.
            This means speakers, headphones, etc.
         */
        class SoundPlaybackDevice
        {
        public:
            /*
                @brief Creates a SoundPlaybackDevice object with default values.
             */
            SoundPlaybackDevice();

            /*
                @brief Creates a SoundPlaybackDevice object with the specified values.
                @param name The name of the device.
                @param _default Whether the device is the default.
                @param hardwareID The hardware ID of the device.
             */
            SoundPlaybackDevice(const std::string& name, bool _default, const std::string& hardwareID);

            /*
                @brief Gets the name of the device.
                @return The name of the device.
             */
            std::string getName();

            /*
                @brief Gets whether the device is the default.
                @return True if the device is the default, false otherwise.
             */
            bool isDefault();

            /*
                @brief Gets the hardware ID of the device.
                @return The hardware ID of the device.
             */
            std::string getHardwareID();

            /*
                @brief Sets the name of the device.
                @param value The name of the device.
             */
            void setName(const std::string& value);

            /*
                @brief Sets whether the device is the default.
                @param value True if the device is the default, false otherwise.
             */
            void setDefault(bool value);

            /*
                @brief Sets the hardware ID of the device.
                @param value The hardware ID of the device.
             */
            void setHardwareID(const std::string& value);

        private:
            std::string name;
            bool _default;
            std::string hardwareID;
        };

        /*
            @brief A class to represent a sound capture device.
            This means microphones.
         */
        class SoundCaptureDevice
        {
        public:
            /*
                @brief Creates a SoundCaptureDevice object with default values.
             */
            SoundCaptureDevice();

            /*
                @brief Creates a SoundCaptureDevice object with the specified values.
                @param name The name of the device.
                @param _default Whether the device is the default.
             */
            SoundCaptureDevice(const std::string& name, bool _default);

            /*
                @brief Gets the name of the device.
                @return The name of the device.
             */
            std::string getName();

            /*
                @brief Gets whether the device is the default.
                @return True if the device is the default, false otherwise.
             */
            bool isDefault();

            /*
                @brief Sets the name of the device.
                @param value The name of the device.
             */
            void setName(const std::string& value);

            /*
                @brief Sets whether the device is the default.
                @param value True if the device is the default, false otherwise.
             */
            void setDefault(bool value);

        private:
            std::string name;
            bool _default;
        };

        /*
            @brief A class to represent a video capture device.
            This means webcams, etc.
         */
        class VideoCaptureDevice
        {
        public:
            /*
                @brief Creates a VideoCaptureDevice object with default values.
             */
            VideoCaptureDevice();

            /*
                @brief Creates a VideoCaptureDevice object with the specified values.
                @param name The name of the device.
                @param manufacturer The manufacturer of the device.
                @param hardwareID The hardware ID of the device.
             */
            VideoCaptureDevice(const std::string& name, const std::string& manufacturer, const std::string& hardwareID);

            /*
                @brief Gets the name of the device.
                @return The name of the device.
             */
            std::string getName();

            /*
                @brief Gets the manufacturer of the device.
                @return The manufacturer of the device.
             */
            std::string getManufacturer();

            /*
                @brief Gets the hardware ID of the device.
                @return The hardware ID of the device.
             */
            std::string getHardwareID();

            /*
                @brief Sets the name of the device.
                @param value The name of the device.
             */
            void setName(const std::string& value);

            /*
                @brief Sets the manufacturer of the device.
                @param value The manufacturer of the device.
             */
            void setManufacturer(const std::string& value);

            /*
                @brief Sets the hardware ID of the device.
                @param value The hardware ID of the device.
             */
            void setHardwareID(const std::string& value);

        private:
            std::string name;
            std::string manufacturer;
            std::string hardwareID;
        };

        /*
            @brief A class to represent a direct input device.
            This means keyboards, mice, etc.
         */
        class DirectInputDevice
        {
        public:
            /*
                @brief Creates a DirectInputDevice object with default values.
             */
            DirectInputDevice();

            /*
                @brief Creates a DirectInputDevice object with the specified values.
                @param name The name of the device.
                @param numAttached The number of devices attached.
             */
            DirectInputDevice(const std::string& name, int numAttached);

            /*
                @brief Gets the name of the device.
                @return The name of the device.
             */
            std::string getName();

            /*
                @brief Gets the number of devices attached.
                @return The number of devices attached.
             */
            int getNumAttached();

            /*
                @brief Sets the name of the device.
                @param value The name of the device.
             */
            void setName(const std::string& value);

            /*
                @brief Sets the number of devices attached.
                @param value The number of devices attached.
             */
            void setNumAttached(int value);

        private:
            std::string name;
            int numAttached;
        };

        /*
            @brief A class to represent a drive.
            This means a hard drive, SSD, etc.
         */
        class Drive
        {
        public:
            /*
                @brief Creates a Drive object with default values.
             */
            Drive();

            /*
                @brief Creates a Drive object with the specified values.
                @param name The name of the drive.
                @param freeSpace The amount of free space in GB.
                @param totalSpace The total amount of space in GB.
                @param fileSystem The file system of the drive.
             */
            Drive(const std::string& name, int freeSpace, int totalSpace, const std::string& fileSystem);

            /*
                @brief Gets the name of the drive.
                @return The name of the drive.
             */
            std::string getName();

            /*
                @brief Gets the amount of free space in GB.
                @return The amount of free space in GB.
             */
            int getFreeSpace();

            /*
                @brief Gets the total amount of space in GB.
                @return The total amount of space in GB.
             */
            int getTotalSpace();

            /*
                @brief Gets the file system of the drive.
                @return The file system of the drive.
             */
            std::string getFileSystem();

            /*
                @brief Sets the name of the drive.
                @param value The name of the drive.
             */
            void setName(const std::string& value);

            /*
                @brief Sets the amount of free space in GB.
                @param value The amount of free space in GB.
             */
            void setFreeSpace(int value);

            /*
                @brief Sets the total amount of space in GB.
                @param value The total amount of space in GB.
             */
            void setTotalSpace(int value);

            /*
                @brief Sets the file system of the drive.
                @param value The file system of the drive.
             */
            void setFileSystem(const std::string& value);

        private:
            std::string name;
            int freeSpace;
            int totalSpace;
            std::string fileSystem;
        };

        /*
            @brief A class to contain system information.
         */
        class SystemInfo
        {
        public:
            /*
                @brief Creates a SystemInfo object with default values.
             */
            SystemInfo();

            /*
                @brief Creates a SystemInfo object with the specified values.
                @param machineName The name of the machine.
                @param machineID The ID of the machine.
                @param os The operating system.
                @param arch The architecture.
                @param osString The OS string.
                @param language The language.
                @param manufacturer The manufacturer.
                @param model The model.
                @param bios The BIOS.
                @param processor The processor.
                @param memory The amount of memory in MB.
                @param availableMemory The amount of available memory in MB.
                @param displayDevices The display devices.
                @param soundPlaybackDevices The sound playback devices.
                @param soundCaptureDevices The sound capture devices.
                @param videoCaptureDevices The video capture devices.
                @param directInputDevices The direct input devices.
                @param drives The drives.
             */
            SystemInfo(const std::string& machineName, const std::string& machineID, OS os, ARCH arch, const std::string& osString, const std::string& language, const std::string& manufacturer, const std::string& model, const std::string& bios, const std::string& processor, int memory, int availableMemory, std::vector<DisplayDevice> displayDevices, std::vector<SoundPlaybackDevice> soundPlaybackDevices, std::vector<SoundCaptureDevice> soundCaptureDevices, std::vector<VideoCaptureDevice> videoCaptureDevices, std::vector<DirectInputDevice> directInputDevices, std::vector<Drive> drives);

            /*
                @brief Gets the name of the machine.
                @return The name of the machine.
             */
            std::string getMachineName();

            /*
                @brief Gets the ID of the machine.
                @return The ID of the machine.
             */
            std::string getMachineID();

            /*
                @brief Gets the operating system.
                @return The operating system.
             */
            OS getOS();

            /*
                @brief Gets the architecture.
                @return The architecture.
             */
            ARCH getARCH();

            /*
                @brief Gets the OS string.
                @return The OS string, containing more info than the OS enum.
             */
            std::string getOSString();

            /*
                @brief Gets the language.
                @return The language.
             */
            std::string getLanguage();

            /*
                @brief Gets the manufacturer.
                @return The manufacturer.
             */
            std::string getManufacturer();

            /*
                @brief Gets the model.
                @return The model.
             */
            std::string getModel();

            /*
                @brief Gets the BIOS.
                @return The BIOS.
             */
            std::string getBIOS();

            /*
                @brief Gets the processor.
                @return The processor.
             */
            std::string getProcessor();

            /*
                @brief Gets the amount of memory in MB.
                @return The amount of memory in MB.
             */
            int getMemory();

            /*
                @brief Gets the amount of available memory in MB.
                @return The amount of available memory in MB.
             */
            int getAvailableMemory();

            /*
                @brief Gets the display devices.
                @return The display devices.
             */
            std::vector<DisplayDevice> getDisplayDevices();

            /*
                @brief Gets the sound playback devices.
                @return The sound playback devices.
             */
            std::vector<SoundPlaybackDevice> getSoundPlaybackDevices();

            /*
                @brief Gets the sound capture devices.
                @return The sound capture devices.
             */
            std::vector<SoundCaptureDevice> getSoundCaptureDevices();

            /*
                @brief Gets the video capture devices.
                @return The video capture devices.
             */
            std::vector<VideoCaptureDevice> getVideoCaptureDevices();

            /*
                @brief Gets the direct input devices.
                @return The direct input devices.
             */
            std::vector<DirectInputDevice> getDirectInputDevices();

            /*
                @brief Gets the drives.
                @return The drives.
             */
            std::vector<Drive> getDrives();

            /*
                @brief Sets the name of the machine.
                @param value The name of the machine.
             */
            void setMachineName(const std::string& value);

            /*
                @brief Sets the ID of the machine.
                @param value The ID of the machine.
             */
            void setMachineID(const std::string& value);

            /*
                @brief Sets the operating system.
                @param value The operating system.
             */
            void setOS(OS value);

            /*
                @brief Sets the architecture.
                @param value The architecture.
             */
            void setARCH(ARCH value);

            /*
                @brief Sets the OS string.
                @param value The OS string, containing more info than the OS enum.
             */
            void setOSString(const std::string& value);

            /*
                @brief Sets the language.
                @param value The language.
             */
            void setLanguage(const std::string& value);

            /*
                @brief Sets the manufacturer.
                @param value The manufacturer.
             */
            void setManufacturer(const std::string& value);

            /*
                @brief Sets the model.
                @param value The model.
             */
            void setModel(const std::string& value);

            /*
                @brief Sets the BIOS.
                @param value The BIOS.
             */
            void setBIOS(const std::string& value);

            /*
                @brief Sets the processor.
                @param value The processor.
             */
            void setProcessor(const std::string& value);

            /*
                @brief Sets the amount of memory in MB.
                @param value The amount of memory in MB.
             */
            void setMemory(int value);

            /*
                @brief Sets the amount of available memory in MB.
                @param value The amount of available memory in MB.
             */
            void setAvailableMemory(int value);

            /*
                @brief Sets the display devices.
                @param value The display devices.
             */
            void setDisplayDevices(const std::vector<DisplayDevice>& value);

            /*
                @brief Adds a display device.
                @param value The display device to add.
             */
            void addDisplayDevice(const DisplayDevice& value);

            /*
                @brief Sets the sound playback devices.
                @param value The sound playback devices.
             */
            void setSoundPlaybackDevices(const std::vector<SoundPlaybackDevice>& value);

            /*
                @brief Adds a sound playback device.
                @param value The sound playback device to add.
             */
            void addSoundPlaybackDevice(const SoundPlaybackDevice& value);

            /*
                @brief Sets the sound capture devices.
                @param value The sound capture devices.
             */
            void setSoundCaptureDevices(const std::vector<SoundCaptureDevice>& value);

            /*
                @brief Adds a sound capture device.
                @param value The sound capture device to add.
             */
            void addSoundCaptureDevice(const SoundCaptureDevice& value);

            /*
                @brief Sets the video capture devices.
                @param value The video capture devices.
             */
            void setVideoCaptureDevices(const std::vector<VideoCaptureDevice>& value);

            /*
                @brief Adds a video capture device.
                @param value The video capture device to add.
             */
            void addVideoCaptureDevice(const VideoCaptureDevice& value);

            /*
                @brief Sets the direct input devices.
                @param value The direct input devices.
             */
            void setDirectInputDevices(const std::vector<DirectInputDevice>& value);

            /*
                @brief Adds a direct input device.
                @param value The direct input device to add.
             */
            void addDirectInputDevice(const DirectInputDevice& value);

            /*
                @brief Sets the drives.
                @param value The drives.
             */
            void setDrives(const std::vector<Drive>& value);

            /*
                @brief Adds a drive.
                @param value The drive to add.
             */
            void addDrive(const Drive& value);

        private:
            std::string machineName;
            std::string machineID;
            OS os;
            ARCH arch;
            std::string osString;
            std::string language;
            std::string manufacturer;
            std::string model;
            std::string bios;
            std::string processor;
            int memory;
            int availableMemory;
            std::vector<DisplayDevice> displayDevices;
            std::vector<SoundPlaybackDevice> soundPlaybackDevices;
            std::vector<SoundCaptureDevice> soundCaptureDevices;
            std::vector<VideoCaptureDevice> videoCaptureDevices;
            std::vector<DirectInputDevice> directInputDevices;
            std::vector<Drive> drives;
        };

        /*
            @brief Gets system information.
            @return A SystemInfo object containing system information.
         */
        SystemInfo GetSystemInfo();

        /*
            @brief Gets the name of the machine from the SystemInfo object created on initialization and stored.
            @return The name of the machine.
         */
        std::string GetMachineName();

        /*
            @brief Gets the ID of the machine from the SystemInfo object created on initialization and stored.
            @return The ID of the machine.
         */
        std::string GetMachineID();

        /*
            @brief Gets the operating system from the SystemInfo object created on initialization and stored.
            @return The operating system.
         */
        OS GetOS();

        /*
            @brief Gets the architecture from the SystemInfo object created on initialization and stored.
            @return The architecture.
         */
        ARCH GetARCH();

        /*
            @brief Gets the OS string from the SystemInfo object created on initialization and stored.
            @return The OS string, containing more info than the OS enum.
         */
        std::string GetOSString();

        /*
            @brief Gets the language from the SystemInfo object created on initialization and stored.
            @return The language.
         */
        std::string GetLanguage();

        /*
            @brief Gets the manufacturer from the SystemInfo object created on initialization and stored.
            @return The manufacturer.
         */
        std::string GetManufacturer();

        /*
            @brief Gets the model from the SystemInfo object created on initialization and stored.
            @return The model.
         */
        std::string GetModel();

        /*
            @brief Gets the BIOS from the SystemInfo object created on initialization and stored.
            @return The BIOS.
         */
        std::string GetBIOS();

        /*
            @brief Gets the processor from the SystemInfo object created on initialization and stored.
            @return The processor.
         */
        std::string GetProcessor();

        /*
            @brief Gets the amount of memory in MB from the SystemInfo object created on initialization and stored.
            @return The amount of memory in MB.
         */
        int GetMemory();

        /*
            @brief Gets the amount of available memory in MB from the SystemInfo object created on initialization and stored.
            @return The amount of available memory in MB.
         */
        int GetAvailableMemory();

        /*
            @brief Gets the display devices from the SystemInfo object created on initialization and stored.
            @return The display devices.
         */
        std::vector<DisplayDevice> GetDisplayDevices();

        /*
            @brief Gets the sound playback devices from the SystemInfo object created on initialization and stored.
            @return The sound playback devices.
         */
        std::vector<SoundPlaybackDevice> GetSoundPlaybackDevices();

        /*
            @brief Gets the sound capture devices from the SystemInfo object created on initialization and stored.
            @return The sound capture devices.
         */
        std::vector<SoundCaptureDevice> GetSoundCaptureDevices();

        /*
            @brief Gets the video capture devices from the SystemInfo object created on initialization and stored.
            @return The video capture devices.
         */
        std::vector<VideoCaptureDevice> GetVideoCaptureDevices();

        /*
            @brief Gets the direct input devices from the SystemInfo object created on initialization and stored.
            @return The direct input devices.
         */
        std::vector<DirectInputDevice> GetDirectInputDevices();

        /*
            @brief Gets the drives from the SystemInfo object created on initialization and stored.
            @return The drives.
         */
        std::vector<Drive> GetDrives();

    }
}