@echo off
echo ===== Transaction System Windows Build =====

REM Create required directories
mkdir build\cpp
mkdir build\c
mkdir build\shared_lib\cpp
mkdir build\shared_lib\c
mkdir bin

echo Compiling C++ sources...
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\cpp\main.cc -o build\cpp\main.o
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\cpp\account_manager.cc -o build\cpp\account_manager.o
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\cpp\account.cc -o build\cpp\account.o
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\cpp\database.cc -o build\cpp\database.o
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\cpp\logger.cc -o build\cpp\logger.o
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\cpp\transaction.cc -o build\cpp\transaction.o
g++ -Wall -Wextra -std=c++11 -Iinclude\cpp -Iinclude\c -Iinclude\shared_lib\cpp -Iinclude\shared_lib\c -D_WINDOWS -c src\shared_lib\cpp\shared_transaction.cc -o build\shared_lib\cpp\shared_transaction.o

echo Compiling C sources...
gcc -Wall -Wextra -std=c11 -Iinclude\c -Iinclude\shared_lib\c -D_WINDOWS -c src\c\utils.c -o build\c\utils.o
gcc -Wall -Wextra -std=c11 -Iinclude\c -Iinclude\shared_lib\c -D_WINDOWS -c src\c\security.c -o build\c\security.o
gcc -Wall -Wextra -std=c11 -Iinclude\c -Iinclude\shared_lib\c -D_WINDOWS -c src\shared_lib\c\shared_utils.c -o build\shared_lib\c\shared_utils.o

echo Linking all objects...
g++ build\cpp\main.o build\cpp\account_manager.o build\cpp\account.o build\cpp\database.o build\cpp\logger.o build\cpp\transaction.o build\shared_lib\cpp\shared_transaction.o build\c\utils.o build\c\security.o build\shared_lib\c\shared_utils.o -lstdc++ -o bin\transaction_system.exe

echo ===== Build Complete =====
echo Executable: bin\transaction_system.exe

