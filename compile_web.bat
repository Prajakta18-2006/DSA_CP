@echo off
echo ============================================================
echo   Compiling Smart Library Web Server (Crow)
echo ============================================================
echo.

:: Ensure g++ is in the path. Using C++17 as required by Crow.
:: Crow on Windows needs ws2_32 and mswsock libraries.

g++ -std=c++17 -I include ^
    src\Book.cpp ^
    src\AVLTree.cpp ^
    src\QueueSystem.cpp ^
    src\StackSystem.cpp ^
    src\GraphRecommendation.cpp ^
    src\FileHandler.cpp ^
    src\LibrarySystem.cpp ^
    src\web_main.cpp ^
    -o library_web_server.exe ^
    -lws2_32

if %errorlevel% == 0 (
    echo.
    echo   [SUCCESS] Compilation successful!
    echo.
    echo   To run the server:
    echo   1. Make sure 'templates' and 'public' folders are in the same directory.
    echo   2. Run: library_web_server.exe
    echo   3. Open http://localhost:8080 in your browser.
    echo.
) else (
    echo.
    echo   [FAILED] Compilation failed! Check for errors above.
    echo.
)
pause
