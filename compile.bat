@echo off
echo ============================================================
echo   Compiling Smart Library Management System
echo ============================================================
echo.

g++ -std=c++17 -I include src\Book.cpp src\AVLTree.cpp src\QueueSystem.cpp src\StackSystem.cpp src\GraphRecommendation.cpp src\FileHandler.cpp src\LibrarySystem.cpp src\main.cpp -o smart_library.exe

if %errorlevel% == 0 (
    echo   [SUCCESS] Compilation successful!
    echo.
    echo   Run the program:  smart_library.exe
    echo.
) else (
    echo   [FAILED] Compilation failed! Check for errors above.
    echo.
)
pause
