import os
import subprocess
from sys import platform

class Setup:
    def __init__(self):
        self.web_version = False     # Tracks whether the user wants web version setup
        self.linux_base = "unknown"  # Stores the base Linux family detected

    # Prompt the user to ask if they want the web version
    def ask_web_version(self):
        try:
            answer = input("Do you want the web version? (y/n): ").strip().lower()
            self.web_version = answer == "y"
        except:
            self.web_version = False

    # Check if a tool/command is available in the system PATH
    def is_installed(self, tool):
        try:
            subprocess.run([tool, "--version"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return True
        except:
            return False

    # Determine which base Linux distribution is being used
    def detect_linux_base(self):
        try:
            if os.path.exists("/etc/os-release"):
                with open("/etc/os-release") as f:
                    lines = f.readlines()
                    id_line = [line for line in lines if line.startswith("ID=")]
                    id_like_line = [line for line in lines if line.startswith("ID_LIKE=")]

                    id_val = id_line[0].split("=")[1].strip().strip('"') if id_line else ""
                    id_like_val = id_like_line[0].split("=")[1].strip().strip('"') if id_like_line else ""

                    # Match known Linux families
                    if "debian" in id_like_val or id_val in ["debian", "ubuntu", "linuxmint"]:
                        self.linux_base = "debian"
                    elif "arch" in id_like_val or id_val == "arch":
                        self.linux_base = "arch"
                    elif "rhel" in id_like_val or id_val in ["fedora", "centos", "rhel"]:
                        self.linux_base = "redhat"
                    elif "suse" in id_like_val or id_val == "suse":
                        self.linux_base = "suse"
        except:
            print("Could not detect Linux base.")

    # Install missing build tools (gcc and make) if not already installed
    def install_tools_linux(self):
        tools_needed = []
        if not self.is_installed("gcc"):
            tools_needed.append("gcc")
        if not self.is_installed("make"):
            tools_needed.append("make")

        if not tools_needed:
            print("GCC and Make are already installed.")
            return

        print("Installing:", ", ".join(tools_needed))
        try:
            # Install according to detected Linux base
            if self.linux_base == "debian":
                subprocess.run(["sudo", "apt", "update"])
                subprocess.run(["sudo", "apt", "install", "-y"] + tools_needed)
            elif self.linux_base == "arch":
                subprocess.run(["sudo", "pacman", "-Sy", "--noconfirm"] + tools_needed)
            elif self.linux_base == "redhat":
                subprocess.run(["sudo", "dnf", "install", "-y"] + tools_needed)
            elif self.linux_base == "suse":
                subprocess.run(["sudo", "zypper", "install", "-y"] + tools_needed)
            else:
                print("Unsupported Linux base.")
        except Exception as e:
            print(f"Failed to install tools: {e}")

    # Install Node.js and npm if they are not already installed
    def install_node_npm(self):
        if self.is_installed("node") and self.is_installed("npm"):
            print("Node.js and npm are already installed.")
            return

        print("Installing Node.js and npm...")
        try:
            if platform.startswith("linux"):
                if self.linux_base == "debian":
                    subprocess.run(["sudo", "apt", "install", "-y", "nodejs", "npm"])
                elif self.linux_base == "arch":
                    subprocess.run(["sudo", "pacman", "-Sy", "--noconfirm", "nodejs", "npm"])
                elif self.linux_base == "redhat":
                    subprocess.run(["sudo", "dnf", "install", "-y", "nodejs", "npm"])
                elif self.linux_base == "suse":
                    subprocess.run(["sudo", "zypper", "install", "-y", "nodejs", "npm"])
                else:
                    print("Unknown Linux base.")
            elif platform == "win32":
                print("Please install Node.js manually from https://nodejs.org/")
        except Exception as e:
            print(f"Failed to install Node.js/npm: {e}")

    # Set up the web directory if web version is selected
    def setup_web_dependencies(self):
        if not os.path.isdir("web"):
            print("Web directory not found.")
            return
        try:
            os.chdir("web")
            subprocess.run(["npm", "init", "-y"])
            subprocess.run(["npm", "install", "express", "cors", "child_process"])
            print("Web dependencies installed successfully.")
            os.chdir("..")
        except Exception as e:
            print(f"Failed to set up web dependencies: {e}")
            os.chdir("..")

    # Run the build script based on the platform
    def run_build(self):
        try:
            if platform.startswith("linux"):
                if os.path.exists("./Makefile"):
                    subprocess.run(["make", "-f", "Makefile"])
                    print("Linux build finished.")
                else:
                    print("Makefile not found.")
            elif platform == "win32":
                if os.path.exists(".\\make-windows.bat"):
                    subprocess.run([".\\make-windows.bat"], shell=True)
                    print("Windows build script executed.")
                else:
                    print("Windows build script not found.")
        except Exception as e:
            print(f"Build failed: {e}")

    # Main logic controller
    def run(self):
        self.ask_web_version()

        if platform.startswith("linux"):
            print("Detected Linux.")
            self.detect_linux_base()
            self.install_tools_linux()
            if self.web_version:
                self.install_node_npm()
                self.setup_web_dependencies()

        elif platform == "win32":
            print("Detected Windows.")
            if self.web_version:
                self.install_node_npm()
                self.setup_web_dependencies()
            else:
                print("Please install GCC (via MinGW) and Node.js manually if needed.")

        else:
            print("Unsupported OS.")

        self.run_build()

# Entry point
if __name__ == "__main__":
    Setup().run()
